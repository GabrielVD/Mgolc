#include "semantic.h"
#include <cassert>

using std::move;
using std::to_string;

const char* to_code(token::ttype_enum);

bool semantic::execute(production p, symbol_table& st,
	std::ostream& out, std::ostream& prompt)
{
	bool has_error{ false };

	switch (p)
	{
	case production::p5:
		out << new_indent << new_indent << new_indent;
		break;

	case production::p6:
		p6(st, out);
		break;

	case production::p7:
		has_error = p7(st, out, prompt);
		break;

	case production::p8:
		has_error = p8(st, out, prompt);
		break;

	case production::p9:
	case production::p10:
	case production::p11:
		out << to_code(semstack.back().ttype) << ' ';
		break;

	case production::p13:
		has_error = p13(st, out, prompt);
		break;

	case production::p14:
		p14(st, out);
		break;

	case production::p17:
	case production::p22:
		has_error = p17(st, out, prompt);
		break;

	case production::p19:
		has_error = p19(st, out, prompt);
		break;

	case production::p20:
		has_error = execute_operator(st, out, prompt, false);
		break;

	case production::p25:
	case production::p37:
		new_indent.pop_back();
		out << new_indent << '}' << new_indent;
		break;

	case production::p26:
		new_indent += '\t';
		out << "if (" << (semstack.rbegin() + 2)->lexeme
			<< ") {" << new_indent << new_indent;
		break;

	case production::p27:
		has_error = p27(st, out, prompt);
		break;

	default:
		break;
	}

	reduce_stack(p);
	return has_error;
}

void semantic::p6(symbol_table& st, std::ostream& out)
{
	auto type{ (semstack.rbegin() + 2)->ttype };

	for (const auto& id : (semstack.rbegin() + 1)->ids)
	{
		st.query(id).ttype = type;
	}

	out << ';' << new_indent;
}

bool semantic::p7(symbol_table& st,
	std::ostream& out, std::ostream& prompt)
{
	auto has_error{ false };
	auto& symb0{ *(semstack.rbegin() + 2) };

	if (st.contains(symb0.lexeme))
	{
		print_error("Erro semantico: Redefinicao de variavel.",
			symb0, prompt);
		has_error = true;
	}
	else
	{
		st.query(symb0.lexeme) = token(symb0.lexeme);
		symb0.ids = move(semstack.rbegin()->ids);
		symb0.ids.emplace_back(symb0.lexeme);

		out << ", " << symb0.lexeme;
	}

	return has_error;
}

bool semantic::p8(symbol_table& st, std::ostream& out, std::ostream& prompt)
{
	auto has_error{ false };
	auto& symb0{ *semstack.rbegin() };

	if (st.contains(symb0.lexeme))
	{
		print_error("Erro semantico: Redefinicao de variavel.",
			symb0, prompt);
		has_error = true;
	}
	else
	{
		st.query(symb0.lexeme) = token(symb0.lexeme);
		symb0.ids.emplace_back(symb0.lexeme);

		out << symb0.lexeme;
	}

	return has_error;
}

bool semantic::p13(symbol_table& st, std::ostream& out, std::ostream& prompt)
{
	auto& symb1{ *(semstack.rbegin() + 1) };
	if (!st.contains_typed(symb1.lexeme))
	{
		print_error("Erro semantico: Variavel nao declarada.",
			symb1, prompt);
		return true;
	}

	out << "scanf(\"%";

	switch (st.query(symb1.lexeme).ttype)
	{
	case token::ttype_enum::integer:
		out << "d\", &";
		break;

	case token::ttype_enum::real:
		out << "lf\", &";
		break;

	case token::ttype_enum::lit:
		out << "s\", ";
		break;

	default:
		assert(false);
		break;
	}

	out << symb1.lexeme << ");" << new_indent;
	return false;
}

void semantic::p14(symbol_table& st, std::ostream& out)
{
	const auto& symb1{ *(semstack.rbegin() + 1) };

	if (st.contains(symb1.lexeme))
	{
		switch (st.query(symb1.lexeme).ttype)
		{
		case token::ttype_enum::integer:
			out << "printf(\"%d\\n\", ";
			break;

		case token::ttype_enum::real:
			out << "printf(\"%lf\\n\", ";
			break;

		case token::ttype_enum::lit:
			out << "printf(\"%s\\n\", ";
			break;

		default:
			break;
		}

		out << symb1.lexeme << ");";
	}
	else if (symb1.ttype == token::ttype_enum::lit)
	{
		out << "printf(" << symb1.lexeme << ");" << new_indent
			<< "putchar('\\n');";
	}
	else { out << "printf(\"" << symb1.lexeme << "\\n\");"; }

	out << new_indent;
}

bool semantic::p17(symbol_table& st, std::ostream& out, std::ostream& prompt)
{
	const auto& symb0{ semstack.back() };

	if (!st.contains_typed(symb0.lexeme))
	{
		print_error("Erro semantico: Variavel nao declarada.",
			symb0, prompt);
		return true;
	}

	return false;
}

bool semantic::p19(symbol_table& st, std::ostream& out, std::ostream& prompt)
{
	auto& symb0{ *(semstack.rbegin() + 3) };

	if (!st.contains_typed(symb0.lexeme))
	{
		print_error("Erro semantico: Variavel nao declarada.",
			symb0, prompt);
		return true;
	}

	auto& symb2{ *(semstack.rbegin() + 1) };

	assign_id_type(symb0, st);
	assign_id_type(symb2, st);

	if (symb0.ttype != symb2.ttype)
	{
		print_error("Erro semantico: Tipos diferentes para atribuicao.",
			symb0, prompt);
		return true;
	}

	out << symb0.lexeme << " = " << symb2.lexeme << ';' << new_indent;

	return false;
}

bool semantic::p27(symbol_table& st, std::ostream& out, std::ostream& prompt)
{
	bool is_loop{ (semstack.rbegin() + 4)->lexeme.compare("repita") == 0 };

	if (!is_loop) { return execute_operator(st, out, prompt, true); }
	if (!is_valid_operation(st, prompt, true)) { return true; }

	new_indent += '\t';
	out << "while ("
		<< (semstack.rbegin() + 2)->lexeme
		<< (semstack.rbegin() + 1)->lexeme
		<< (semstack.rbegin())->lexeme
		<< ") {"
		<< new_indent << new_indent;

	return false;
}

bool semantic::execute_operator(symbol_table& st, std::ostream& out,
	std::ostream& prompt, bool is_relational)
{
	if (!is_valid_operation(st, prompt, is_relational)) { return true; }

	auto& symb0{ *(semstack.rbegin() + 2) };
	const auto& symb1{ *(semstack.rbegin() + 1) };
	const auto& symb2{ *(semstack.rbegin()) };
	auto operand1{ symb0.lexeme };

	symb0.lexeme = "T" + to_string(get_counter());
	out << (is_relational ? "int" : to_code(symb0.ttype)) << ' ' <<
		symb0.lexeme << " = " << operand1 << symb1.lexeme
		<< symb2.lexeme << ';' << new_indent;

	return false;
}

bool semantic::is_valid_operation(symbol_table& st, std::ostream& prompt,
	bool is_relational)
{
	auto& symb0{ *(semstack.rbegin() + 2) };
	auto& symb2{ *(semstack.rbegin()) };

	assign_id_type(symb0, st);
	assign_id_type(symb2, st);

	if (symb0.ttype != symb2.ttype
		|| (!is_relational && symb0.ttype == token::ttype_enum::lit))
	{
		print_error("Erro semantico: Operandos com tipos incompativeis.",
			symb0, prompt);
		return false;
	}

	return true;
}

void semantic::reduce_stack(production p)
{
	auto size{ production_data::of(p).reduction_size };
	if (size > 1)
	{
		--size;
		semstack.resize(semstack.size() - size);
	}
}

void semantic::print_error(const char* msg, const attributes& symb,
	std::ostream& prompt)
{
	prompt << msg <<
		" linha " << symb.line << ", coluna " << symb.column << '\n';
}

int semantic::get_counter()
{
	return var_counter++;
}

void semantic::assign_id_type(attributes& symb, symbol_table& st)
{
	if (st.contains(symb.lexeme))
	{
		symb.ttype = st.query(symb.lexeme).ttype;
	}
}

const char* to_code(token::ttype_enum type)
{
	switch (type)
	{
	case token::ttype_enum::integer:
		return "int";

	case token::ttype_enum::real:
		return "double";

	case token::ttype_enum::lit:
		return "literal";

	default:
		assert(false);
		return "";
	}
}
