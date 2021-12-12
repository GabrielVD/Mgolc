#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "grammar.h"
#include "symbol.h"
#include <ostream>

class semantic
{
private:
	struct attributes
	{
		int line{ 0 }, column{ 0 };
		std::string lexeme;
		token::ttype_enum ttype{ token::ttype_enum::null };
		std::vector<std::string> ids;

		attributes() {}
		attributes(const token& t) :
			line(t.line), column(t.column),
			lexeme(t.lexeme), ttype(t.ttype)
		{
		}
	};

	std::vector<attributes> semstack;
	std::string new_indent{ "\n\t" };
	int var_counter{ 0 };

public:

	void push(const token&t) { semstack.emplace_back(t); }
	void pop() { semstack.pop_back(); }

	/**
	* Returns true if error ocurred
	*/
	bool execute(production, symbol_table&,
		std::ostream& out, std::ostream& prompt);

private:
	void p6(symbol_table& st, std::ostream& out);
	bool p7(symbol_table& st, std::ostream& out, std::ostream& prompt);
	bool p8(symbol_table& st, std::ostream& out, std::ostream& prompt);
	bool p13(symbol_table& st, std::ostream& out, std::ostream& prompt);
	void p14(symbol_table& st, std::ostream& out);
	bool p17(symbol_table& st, std::ostream& out, std::ostream& prompt);
	bool p19(symbol_table& st, std::ostream& out, std::ostream& prompt);
	bool p27(symbol_table& st, std::ostream& out, std::ostream& prompt);
	bool execute_operator(symbol_table& st, std::ostream& out,
		std::ostream& prompt, bool is_relational);
	bool is_valid_operation(symbol_table&, std::ostream& prompt,
		bool is_relational);
	void reduce_stack(production);
	void print_error(const char* msg, const attributes&,
		std::ostream& prompt);
	int get_counter();
	void assign_id_type(attributes&, symbol_table&);
};

#endif
