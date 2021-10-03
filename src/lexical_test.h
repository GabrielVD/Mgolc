#ifndef LEXICAL_TEST_H
#define LEXICAL_TEST_H

#include "scanner.h"
#include <iostream>

inline void test(std::istream& source, std::ostream& output)
{
	scanner scanner;
	bool is_eof{ false };

	do
	{
		auto token{ scanner.next(source) };
		is_eof = token.is_eof();

		output << token << "\n\n";
		if (token.is_error()) { output << token.describe() << "\n\n"; }
	} while (!is_eof);
}

#endif
