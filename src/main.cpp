#include "io.h"
#include "handler.h"
#include "except.h"
#include <iostream>

using std::invalid_argument;

void validate_arguments(int argc, const char* argv[]);

int main(const int argc, const char* argv[])
{
	try
	{
		validate_arguments(argc, argv);

		for (int i = 1; i < argc; i++)
		{
			compile(argv[i]);
		}
	}
	catch (const invalid_argument& e) { handle(e); }
	catch (const io_error& e) { handle(e); }

	return 0;
}

void validate_arguments(const int argc, const char* argv[])
{
	if (argc == 1)
	{
		throw invalid_argument("No arguments. Missing source file path.");
	}
}
