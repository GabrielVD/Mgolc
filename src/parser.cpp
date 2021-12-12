#include "parser.h"
#include "scanner.h"
#include "goto.h"
#include "action.h"
#include "semantic.h"
#include <stack>
#include <algorithm>
#include <optional>

using std::min_element;
using std::optional;
using std::pair;
using std::vector;
using std::istream;
using std::ostream;
using std::stack;
using std::string;
using std::array;

void print_production(const char*, ostream&);
state_syntatic best_recovery(const vector<pair<state_syntatic, action>>& actions);

class parser_engine
{
public:
	bool has_error{ false };

private:
	const action_table action_table;
	const goto_table goto_table;
	stack<state_syntatic> state_stack;
	scanner scanner;
	semantic semantic;
	token terminal;
	istream& source;
	ostream& output;
	ostream& prompt;
	symbol_table& st;

public:
	parser_engine(istream& source_, symbol_table& st_,
		ostream& output_, ostream& prompt_) :
		source(source_), st(st_), output(output_), prompt(prompt_)
	{
		state_stack.push(state_syntatic::s0);
		terminal = scanner.next(source_, st_);
	}

	/**
	* Returns true while there are more actions to process
	*/
	bool process_action();

private:
	action current() const;
	token next();
	void shift(state_syntatic);
	void reduce(production);
	bool handle_error();
	void print_error() const;
	vector<pair<state_syntatic, action>> seek_panic_actions();
	vector<state_syntatic> seek_panic_goto();
};

bool parser(istream& source, symbol_table& st,
	ostream& output, ostream& prompt)
{
	parser_engine p(source, st, output, prompt);
	while (p.process_action());
	return p.has_error;
}

void print_production(const char *string, ostream& output)
{
	output << string << '\n';
}

bool parser_engine::process_action()
{
	auto is_finished{ false };
	auto action{ current() };
	switch (action.type)
	{
	case action::types::error:
		has_error = true;
		if (!handle_error()) { is_finished = true; }
		break;

	case action::types::shift:
		shift(action.state);
		break;

	case action::types::reduce:
		reduce(action.production);
		break;

	case action::types::accept:
		print_production("P' --> P", prompt);
		is_finished = true;
		break;
	}

	return !is_finished;
}

action parser_engine::current() const
{
	return action_table.at(state_stack.top(), terminal.tclass);
}

token parser_engine::next()
{
	return scanner.next(source, st);
}

void parser_engine::shift(state_syntatic state)
{
	semantic.push(terminal);
	state_stack.push(state);
	terminal = next();
}

void parser_engine::reduce(production p)
{
	auto data{ production_data::of(p) };
	for (int i = data.reduction_size; i --> 0;) { state_stack.pop(); }
	state_stack.push(goto_table.at(state_stack.top(), data.left_symbol));
	print_production(data.string, prompt);

	has_error |= semantic.execute(p, st, output, prompt);
}

bool parser_engine::handle_error()
{
	print_error();

	if (terminal.is_error())
	{
		terminal = next();
		return true;
	}

	auto actions{ seek_panic_actions() };
	auto can_recover{ !actions.empty() };
	if (can_recover) { state_stack.push(best_recovery(actions)); }

	return can_recover;
}

void parser_engine::print_error() const
{
#define INT(x) static_cast<int>(x)
#define TERM(x) static_cast<token::tclass_enum>(x)

	if (terminal.is_error())
	{
		prompt << "Erro lexico: " << terminal.describe() << '\n';
		return;
	}

	prompt << "Erro sintatico: " << terminal.describe() << ". Esperava: ";

	auto state{ state_stack.top() };
	auto comma{ false };
	for (int i = INT(token::tclass_enum::MIN);
		i <= INT(token::tclass_enum::MAX);
		i++)
	{
		if (action_table.at(state, i).valid())
		{
			if (comma) { prompt << ", "; }
			prompt << token::tclass_string(TERM(i));
			comma = true;
		}
	}

	prompt << '\n';

#undef INT
#undef TERM
}

vector<pair<state_syntatic, action>> parser_engine::seek_panic_actions()
{
	auto goto_list{ seek_panic_goto() };

	vector<pair<state_syntatic, action>> action_list;
	while (true)
	{
		for (auto state : goto_list)
		{
			auto action{ action_table.at(state, terminal.tclass) };
			if (action.valid()) { action_list.push_back({ state, action }); }
		}
		if (!action_list.empty() || terminal.is_eof()) { break; }

		terminal = next();
	}

	return action_list;
}

vector<state_syntatic> parser_engine::seek_panic_goto()
{
	vector<state_syntatic> goto_list;
	while (true)
	{
		goto_list = goto_table.valid_for(state_stack.top());
		if (!goto_list.empty()) { break; }
		state_stack.pop();
		semantic.pop();
	}

	return goto_list;
}

state_syntatic best_recovery(const vector<pair<state_syntatic, action>>& actions)
{
#define REDUCTION(A) production_data::of(A.production).reduction_size

	return min_element(actions.begin(), actions.begin(),
		[](const auto& a, const auto& b)
		{
			auto action_a{ a.second };
			auto action_b{ b.second };
			return action_a.type == action::types::shift
				|| (action_b.type == action::types::reduce
					&& REDUCTION(action_a) < REDUCTION(action_b));
		})->first;

#undef REDUCTION
}
