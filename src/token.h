#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

class token
{
public:
	enum class tclass_enum;
	enum class ttype_enum { null, integer, real, lit };

	int line{ 0 }, column{ 0 };
	std::string lexeme;
	tclass_enum tclass;
	ttype_enum ttype;

	token(const std::string& lexeme,
		tclass_enum tclass,
		ttype_enum ttype,
		int line,
		int column) :
		lexeme(lexeme),
		tclass(tclass),
		ttype(ttype),
		line(line),
		column(column)
	{}

	token(const std::string& lexeme, tclass_enum tclass, ttype_enum ttype) :
		lexeme(lexeme),
		tclass(tclass),
		ttype(ttype)
	{}

	friend std::ostream& operator<<(std::ostream&, const token&);

	bool is_eof() const { return tclass == tclass_enum::eof; }
	bool is_error() const;
	std::string describe() const;

	enum class tclass_enum
	{
		eof,
		error_num_separator = 1,
		error_num_exponent = 2,
		error_comment = 3,
		error_lit_string = 4,
		error_lit_char_empty = 5,
		error_lit_char_open = 6,
		error_invalid_symbol = 7,
		num,
		lit,
		id,
		comment,
		opr,
		rcb,
		opm,
		ab_p,
		fc_p,
		pt_v,
		vir,
		inicio,
		varinicio,
		varfim,
		escreva,
		leia,
		se,
		entao,
		fimse,
		repita,
		fimrepita,
		fim,
		inteiro,
		literal,
		real
	};
};

#endif
