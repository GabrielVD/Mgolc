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

	token& query(const std::string& lexeme)
	{
		return token_map[lexeme];
	}

	bool is_reserved(const std::string& id)
	{
		auto i{ token_map.find(id) };
		return i != token_map.end() && !i->second.is_id();
	}

	bool contains(const std::string& id)
	{
		return token_map.find(id) != token_map.end();
	}

	bool contains_typed(const std::string& id)
	{
		auto i{ token_map.find(id) };
		return i != token_map.end()
			&& i->second.ttype != token::ttype_enum::null;
	}
};

#endif
