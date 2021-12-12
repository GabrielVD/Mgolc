#ifndef PARSER_H
#define PARSER_H

#include "symbol.h"
#include <istream>

/**
* Returns true on error
*/
bool parser(std::istream& source, symbol_table&,
	std::ostream& output, std::ostream& prompt);

#endif
