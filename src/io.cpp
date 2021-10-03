#include "io.h"
#include "except.h"
#include "frontend.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::string;

void compile(const char* filename)
{
	ifstream input(filename, ifstream::in);

	if (!input.is_open())
	{
		throw io_error(string("Error reading file: ") + filename);
	}

	string output_path(string(filename) + ".c");
	ofstream output(output_path, ofstream::out);

	if (!output.is_open())
	{
		throw io_error(string("Error writing to file: ") + output_path);
	}

	compile(input, output);
}
