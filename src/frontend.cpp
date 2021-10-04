#include "frontend.h"
#include "test_lexical.h"

using std::istream;
using std::ostream;

void compile(istream& source, ostream& output)
{
	test(source, output);
}
