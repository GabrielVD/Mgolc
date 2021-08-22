#include "except.h"
#include "io.h"
#include "frontend.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::string;

void compile(const char* filename)
{
	string code;
	{
		ifstream input(filename, ifstream::in);

		if (!input.is_open())
		{
			throw io_error(string("Error reading file: ") + filename);
		}

		code = compile(input);
	}

	string output_path(string(filename) + ".c");
	ofstream output(output_path, ofstream::out);

	if (!output.is_open())
	{
		throw io_error(string("Error writing to file: ") + output_path);
	}

	output << code;
}
