#ifndef PARSER_H
#define PARSER_H

#include "symbol.h"
#include <istream>

void parser(std::istream& source, std::ostream& output, symbol_table&);

#endif
