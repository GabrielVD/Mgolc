#ifndef EXCEPT_H
#define EXCEPT_H

#include <stdexcept>

class io_error : public std::runtime_error
{
	using runtime_error::runtime_error;
};

#endif
