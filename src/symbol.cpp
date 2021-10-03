#include "symbol.h"

token symbol_table::insert(const std::string& lexeme, const token& token)
{
	return (*token_map.insert({ lexeme, token }).first).second;
}

symbol_table::symbol_table()
{
	insert("inicio",	token("inicio",		token::tclass_enum::inicio,		token::ttype_enum::null));
	insert("varinicio",	token("varinicio",	token::tclass_enum::varinicio,	token::ttype_enum::null));
	insert("varfim",	token("varfim",		token::tclass_enum::varfim,		token::ttype_enum::null));
	insert("escreva",	token("escreva",	token::tclass_enum::escreva,	token::ttype_enum::null));
	insert("leia",		token("leia",		token::tclass_enum::leia,		token::ttype_enum::null));
	insert("se",		token("se",			token::tclass_enum::se,			token::ttype_enum::null));
	insert("entao",		token("entao",		token::tclass_enum::entao,		token::ttype_enum::null));
	insert("fimse",		token("fimse",		token::tclass_enum::fimse,		token::ttype_enum::null));
	insert("repita",	token("repita",		token::tclass_enum::repita,		token::ttype_enum::null));
	insert("fimrepita",	token("fimrepita",	token::tclass_enum::fimrepita,	token::ttype_enum::null));
	insert("fim",		token("fim",		token::tclass_enum::fim,		token::ttype_enum::null));
	insert("inteiro",	token("inteiro",	token::tclass_enum::inteiro,	token::ttype_enum::integer));
	insert("literal",	token("literal",	token::tclass_enum::literal,	token::ttype_enum::lit));
	insert("real",		token("real",		token::tclass_enum::real,		token::ttype_enum::real));
}
