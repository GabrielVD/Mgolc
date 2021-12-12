#include "frontend.h"
#include "parser.h"
#include <sstream>

using std::stringstream;
using std::istream;
using std::ostream;
using std::cout;

void compile(istream& source, ostream& output)
{
	stringstream buffer;
	symbol_table symtable;

	if (!parser(source, symtable, buffer, cout))
	{
		output << "#include <stdio.h>\n"
			"typedef char literal[256];\n"
			"void main(void)\n"
			"{\n\t"
			<< buffer.str()
			<< "\n}";
	}
}
