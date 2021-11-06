#include "frontend.h"
#include "test_syntatic.h"

using std::istream;
using std::ostream;

void compile(istream& source, ostream& output)
{
	test(source, output);
}
