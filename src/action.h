#ifndef ACTION_H
#define ACTION_H

#include "enum_syntatic.h"
#include "array2d.h"
#include "grammar.h"
#include "token.h"

struct action
{
	enum class types : unsigned char
	{
		error,
		shift,
		reduce,
		accept
	};

	union
	{
		state_syntatic state;
		production production;
	};

	types type{ types::error };

	action(){}
	bool valid() const { return type != types::error; }
};

class action_table
{
private:
	typedef array2d<
		action,
		state_syntatic,
		token::tclass_enum,
		static_cast<std::size_t>(state_syntatic::MAX) + 1,
		static_cast<std::size_t>(token::tclass_enum::MAX) + 1> table_t;

	table_t table;

public:
	action_table();

	const action& at(state_syntatic state, token::tclass_enum terminal) const
	{
		return table.at(state, terminal);
	}

	const action& at(state_syntatic state, int terminal_ordinal) const
	{
		return table.at(state, static_cast<token::tclass_enum>(terminal_ordinal));
	}

private:
	action& at(state_syntatic state, token::tclass_enum terminal)
	{
		return table.at(state, terminal);
	}

	void set_shift(state_syntatic, token::tclass_enum, state_syntatic shift);
	void set_reduce(state_syntatic, production);
	void set_actions();
};

#endif
