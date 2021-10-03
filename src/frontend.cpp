#include "frontend.h"
#include "lexical_test.h"

using std::istream;
using std::ostream;

void compile(istream& source, ostream& output)
{
	test(source, output);
}
