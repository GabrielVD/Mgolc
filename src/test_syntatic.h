#ifndef TEST_SYNTATIC_H
#define TEST_SYNTATIC_H

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
	} while (!is_eof);
}

#endif
