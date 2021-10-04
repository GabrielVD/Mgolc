#ifndef TEST_LEXICAL_H
#define TEST_LEXICAL_H

#include "scanner.h"
#include <iostream>

inline void test(std::istream& source, std::ostream& output)
{
	scanner scanner;
	symbol_table symtable;

	bool is_eof{ false };

	do
	{
		auto token{ scanner.next(source, symtable) };
		is_eof = token.is_eof();

		output << token << "\n\n";
		if (token.is_error()) { output << token.describe() << "\n\n"; }
	} while (!is_eof);
}

#endif
