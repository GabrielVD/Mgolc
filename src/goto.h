#ifndef GOTO_H
#define GOTO_H

#include "enum_syntatic.h"
#include "grammar.h"
#include "array2d.h"

class goto_table
{
private:
	typedef array2d<
		state_syntatic,
		state_syntatic,
		nterminal,
		static_cast<std::size_t>(state_syntatic::MAX) + 1,
		static_cast<std::size_t>(nterminal::MAX) + 1> table_t;

	table_t table;

public:
	goto_table();

	state_syntatic at(state_syntatic state, nterminal symbol) const
	{
		auto goto_state{ table.at(state, symbol) };
		assert(goto_state != state_syntatic::s0);
		return goto_state;
	}

	std::vector<state_syntatic> valid_for(state_syntatic state) const;

private:
	void set_gotos();
};

#endif
