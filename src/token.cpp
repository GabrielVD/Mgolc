#include "token.h"
#include <cassert>

using std::string;
using std::to_string;
using std::ostream;

const char* ttype_string(token::ttype_enum);

ostream& operator<<(ostream& os, const token& token)
{
	return os << "Classe: " << token::tclass_string(token.tclass)
		<< ", Lexema: " << token.lexeme
		<< ", Tipo: " << ttype_string(token.ttype);
}

bool token::is_error() const
{
	return tclass == tclass_enum::error_num_separator
		|| tclass == tclass_enum::error_num_exponent
		|| tclass == tclass_enum::error_comment
		|| tclass == tclass_enum::error_lit_string
		|| tclass == tclass_enum::error_lit_char_empty
		|| tclass == tclass_enum::error_lit_char_open
		|| tclass == tclass_enum::error_invalid_symbol;
}

string token::describe() const
{
	string msg{ tclass_string(tclass) };

	switch (tclass)
	{
	case token::tclass_enum::error_num_separator:
		msg += " - Numero com separador sem digito";
		break;

	case token::tclass_enum::error_num_exponent:
		msg += " - Numero com expoente sem valor";
		break;

	case token::tclass_enum::error_comment:
		msg += " - Comentario sem fechamento";
		break;

	case token::tclass_enum::error_lit_string:
	case token::tclass_enum::error_lit_char_open:
		msg += " - Literal sem fechamento";
		break;

	case token::tclass_enum::error_lit_char_empty:
		msg += " - Caractere literal vazio";
		break;

	case token::tclass_enum::error_invalid_symbol:
		msg += " - Simbolo invalido";
		break;

	default:
		break;
	}

	msg += ", linha ";
	msg += to_string(line);
	msg += ", coluna ";
	msg += to_string(column);

	return msg;
}

const char* ttype_string(token::ttype_enum ttype)
{
	switch (ttype)
	{
	case token::ttype_enum::null:
		return "Nulo";

	case token::ttype_enum::integer:
		return "Inteiro";

	case token::ttype_enum::real:
		return "Real";

	case token::ttype_enum::lit:
		return "Literal";
	}

	assert(false);
	return "";
}

const char* token::tclass_string(token::tclass_enum tclass)
{
	switch (tclass)
	{
	case token::tclass_enum::eof:
		return "EOF";

	case token::tclass_enum::num:
		return "Numero";

	case token::tclass_enum::lit:
		return "Literal";

	case token::tclass_enum::id:
		return "Identificador";

	case token::tclass_enum::comment:
		return "Comentario";

	case token::tclass_enum::opr:
		return "Operador relacional";

	case token::tclass_enum::rcb:
		return "Atribuicao";

	case token::tclass_enum::opm:
		return "Operador aritmetico";

	case token::tclass_enum::ab_p:
		return "Abre parenteses";

	case token::tclass_enum::fc_p:
		return "Fecha parenteses";

	case token::tclass_enum::pt_v:
		return "Ponto e virgula";

	case token::tclass_enum::vir:
		return "Virgula";

	case token::tclass_enum::error_num_separator:
		return "ERRO1";

	case token::tclass_enum::error_num_exponent:
		return "ERRO2";

	case token::tclass_enum::error_comment:
		return "ERRO3";

	case token::tclass_enum::error_lit_string:
		return "ERRO4";

	case token::tclass_enum::error_lit_char_empty:
		return "ERRO5";

	case token::tclass_enum::error_lit_char_open:
		return "ERRO6";

	case token::tclass_enum::error_invalid_symbol:
		return "ERRO7";

	case token::tclass_enum::inicio:
		return "inicio";

	case token::tclass_enum::varinicio:
		return "varinicio";

	case token::tclass_enum::varfim:
		return "varfim";

	case token::tclass_enum::escreva:
		return "escreva";

	case token::tclass_enum::leia:
		return "leia";

	case token::tclass_enum::se:
		return "se";

	case token::tclass_enum::entao:
		return "entao";

	case token::tclass_enum::fimse:
		return "fimse";

	case token::tclass_enum::repita:
		return "repita";

	case token::tclass_enum::fimrepita:
		return "fimrepita";

	case token::tclass_enum::fim:
		return "fim";

	case token::tclass_enum::inteiro:
		return "inteiro";

	case token::tclass_enum::literal:
		return "literal";

	case token::tclass_enum::real:
		return "real";
	}

	assert(false);
	return "";
}
