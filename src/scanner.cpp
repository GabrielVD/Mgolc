#include "scanner.h"
#include <iostream>
#include <utility>
#include <cassert>

using std::istream;
using std::string;
using std::optional;

scanner::recognizer_t build_recognizer();

scanner::scanner() :
	recognizer(build_recognizer())
{
}

token scanner::next(std::istream& source, symbol_table& symtable)
{
	std::optional<token> token;

	do
	{
		token = process_symbol(source, symtable);
	} while (!token.has_value());

	return token.value();
}

optional<token> scanner::process_symbol(istream& source, symbol_table& symtable)
{
	const auto symbol{ next_symbol(source) };
	const auto previous_state{ recognizer.state() };

	recognizer.transition(symbol);

	optional<token> result;

	if (recognizer.state() == states::sink)
	{
		result = process_lexeme(previous_state, symbol, symtable);
	}
	else if (recognizer.state() != states::initial)
	{
		// not whitespace
		lexeme += symbol;
	}

	update_line_count();
	previous_symbol = symbol;
	return result;
}

std::optional<token> scanner::process_lexeme(
	states final_state,
	char err_symbol,
	symbol_table& symtable)
{
	optional<token> result(build_token(final_state, symtable));
	if (result.value().tclass == token::tclass_enum::comment)
	{
		result.reset();
	}

	recognizer.rewind();
	recognizer.transition(err_symbol);

	lexeme.clear();
	if (recognizer.state() != states::initial)
	{
		// not whitespace
		lexeme += err_symbol;
	}

	return result;
}

char scanner::next_symbol(istream& source) const
{
	char symbol;
	return source.get(symbol) ? symbol : EOF;
}

void scanner::update_line_count()
{
	if (previous_symbol != '\n') { ++column; }
	else
	{
		++line;
		column = 1;
	}
}

token scanner::build_token(scanner::states last, symbol_table &symtable)
{
	token::tclass_enum tclass{ token::tclass_enum::error_invalid_symbol };
	token::ttype_enum ttype{ token::ttype_enum::null };
	string token_lexeme{ lexeme };

	switch (last)
	{
	case scanner::states::num1:
		tclass = token::tclass_enum::error_num_separator;
		break;

	case scanner::states::num3:
	case scanner::states::num4:
		tclass = token::tclass_enum::error_num_exponent;
		break;

	case scanner::states::comment0:
		tclass = token::tclass_enum::error_comment;
		break;

	case scanner::states::lit_string0:
		tclass = token::tclass_enum::error_lit_string;
		break;

	case scanner::states::lit_char0:
		tclass = token::tclass_enum::error_lit_char_empty;
		break;

	case scanner::states::lit_char1:
		tclass = token::tclass_enum::error_lit_char_open;
		break;

	case scanner::states::error:
		tclass = token::tclass_enum::error_invalid_symbol;
		break;

	case scanner::states::num0_accept:
		tclass = token::tclass_enum::num;
		ttype = token::ttype_enum::integer;
		break;

	case scanner::states::num2_accept:
	case scanner::states::num5_accept:
		tclass = token::tclass_enum::num;
		ttype = token::ttype_enum::real;
		break;

	case scanner::states::rcb_accept:
		tclass = token::tclass_enum::rcb;
		break;

	case scanner::states::opr_less_accept:
	case scanner::states::opr_greater_accept:
	case scanner::states::opr_equal_accept:
		tclass = token::tclass_enum::opr;
		break;

	case scanner::states::opm_accept:
		tclass = token::tclass_enum::opm;
		break;

	case scanner::states::ab_p_accept:
		tclass = token::tclass_enum::ab_p;
		break;

	case scanner::states::fc_p_accept:
		tclass = token::tclass_enum::fc_p;
		break;

	case scanner::states::pt_v_accept:
		tclass = token::tclass_enum::pt_v;
		break;

	case scanner::states::vir_accept:
		tclass = token::tclass_enum::vir;
		break;

	case scanner::states::comment1_accept:
		tclass = token::tclass_enum::comment;
		break;

	case scanner::states::id_accept:
	{
		auto id{ symtable.insert_query(token_lexeme) };
		id.line = line;
		id.column = column;
		return id;
	}

	case scanner::states::lit_string1_accept:
	case scanner::states::lit_char2_accept:
		tclass = token::tclass_enum::lit;
		ttype = token::ttype_enum::lit;
		break;

	case scanner::states::eof_accept:
		tclass = token::tclass_enum::eof;
		if (token_lexeme.compare("$") != 0) { token_lexeme = "EOF"; }
		break;
	}

	return token(token_lexeme, tclass, ttype, line, column);
}

scanner::recognizer_t build_recognizer()
{
#define DIGIT '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
#define LETTER 'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's', 'T', 't', 'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z'
#define ALPHABET DIGIT, LETTER, '(', ')', '{', '}', '.', ';', '*', '/', '-', '+', '\n', '\t', ' ', '"', '\'', '_', '<', '>', '=', ','

	scanner::recognizer_t recognizer(scanner::states::initial, scanner::states::sink);

	recognizer.fill_state_transition({ scanner::states::initial }, scanner::states::error);
	recognizer.set_transition({ scanner::states::initial }, scanner::states::initial, { ' ', '\n', '\t' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::num0_accept, { DIGIT });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::opr_less_accept, { '<' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::opr_greater_accept, { '>' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::opr_equal_accept, { '=' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::opm_accept, { '+', '-', '*', '/' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::ab_p_accept, { '(' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::fc_p_accept, { ')' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::pt_v_accept, { ';' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::vir_accept, { ',' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::eof_accept, { '$', EOF });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::comment0, { '{' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::id_accept, { LETTER });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::lit_string0, { '"' });
	recognizer.set_transition({ scanner::states::initial }, scanner::states::lit_char0, { '\'' });
	recognizer.set_transition({ scanner::states::num0_accept }, scanner::states::num0_accept, { DIGIT });
	recognizer.set_transition({ scanner::states::num0_accept }, scanner::states::num1, { '.' });
	recognizer.set_transition({ scanner::states::num0_accept }, scanner::states::num3, { 'E', 'e' });
	recognizer.set_transition({ scanner::states::num1 }, scanner::states::num2_accept, { DIGIT });
	recognizer.set_transition({ scanner::states::num2_accept }, scanner::states::num2_accept, { DIGIT });
	recognizer.set_transition({ scanner::states::num2_accept }, scanner::states::num3, { 'E', 'e' });
	recognizer.set_transition({ scanner::states::num3 }, scanner::states::num4, { '-', '+' });
	recognizer.set_transition({ scanner::states::num3 }, scanner::states::num5_accept, { DIGIT });
	recognizer.set_transition({ scanner::states::num5_accept }, scanner::states::num5_accept, { DIGIT });
	recognizer.set_transition({ scanner::states::opr_less_accept }, scanner::states::opr_equal_accept, { '=', '>' });
	recognizer.set_transition({ scanner::states::opr_less_accept }, scanner::states::rcb_accept, { '-' });
	recognizer.set_transition({ scanner::states::opr_greater_accept }, scanner::states::opr_equal_accept, { '=' });
	recognizer.set_transition({ scanner::states::comment0 }, scanner::states::comment0, { ALPHABET });
	recognizer.set_transition({ scanner::states::comment0 }, scanner::states::comment1_accept, { '}' });
	recognizer.set_transition({ scanner::states::id_accept }, scanner::states::id_accept, { LETTER, DIGIT, '_' });
	recognizer.set_transition({ scanner::states::lit_string0 }, scanner::states::lit_string0, { ALPHABET });
	recognizer.set_transition({ scanner::states::lit_string0 }, scanner::states::lit_string1_accept, { '"' });
	recognizer.set_transition({ scanner::states::lit_char0 }, scanner::states::lit_char1, { ALPHABET });
	recognizer.set_transition({ scanner::states::lit_char0 }, scanner::states::error, { '\'' });
	recognizer.set_transition({ scanner::states::lit_char1 }, scanner::states::lit_char2_accept, { '\'' });

	return recognizer;
}
