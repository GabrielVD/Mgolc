#ifndef TEST_SYNTATIC_H
#define TEST_SYNTATIC_H

#include "parser.h"
#include <iostream>

inline void test(std::istream& source, std::ostream& output)
{
	symbol_table symtable;
	parser(source, output, symtable);
}

#endif
