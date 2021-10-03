#ifndef SYMBOL_H
#define SYMBOL_H

#include "token.h"
#include <unordered_map>
#include <string>

class symbol_table
{
public:
	typedef std::unordered_map<std::string, token> token_map_t;

private:
	token_map_t token_map;
	token insert(const std::string& lexeme, const token& token);

public:
	symbol_table();

	token insert_query(const std::string& lexeme)
	{
		return insert(
				lexeme,
				token(lexeme, token::tclass_enum::id, token::ttype_enum::null)
			);
	}
};

#endif
