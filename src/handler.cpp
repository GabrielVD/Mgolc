#include "handler.h"
#include <iostream>

using std::cout;
using std::endl;

void handle(const std::exception& e)
{
	cout << e.what() << endl;
}
