#ifndef DFA_H
#define DFA_H

#include <array>
#include <cassert>
#include <algorithm>

template<
	class TState,
	class TSymbol,
	std::size_t TState_count,
	std::size_t TAlphabet_size
>
class dfa
{
	typedef std::array<TState, TState_count * TAlphabet_size> transition_t;

private:
	transition_t transition_table;
	TState current_state;
	const TState initial_state;

	std::size_t index(TState state, TSymbol symbol) const;
	std::size_t wrap_state(TState state) const;
	std::size_t wrap_symbol(TSymbol symbol) const;

public:
	dfa(TState initial_state, TState default_transition);

	TState state() const;

	TState transition(TSymbol symbol);
	void rewind();

	void set_transition(
		std::initializer_list<TState> states,
		TState transition,
		std::initializer_list<TSymbol> symbols);

	void fill_state_transition(
		std::initializer_list<TState> states,
		TState transition);
};

template<class TState, class TSymbol, std::size_t TState_count, std::size_t TAlphabet_size>
std::size_t dfa<TState, TSymbol, TState_count, TAlphabet_size>::index(TState state, TSymbol symbol) const
{
	return wrap_symbol(symbol) + wrap_state(state) * TAlphabet_size;
}

template<class TState, class TSymbol, std::size_t TState_count, std::size_t TAlphabet_size>
inline std::size_t dfa<TState, TSymbol, TState_count, TAlphabet_size>::wrap_state(TState state) const
{
	std::size_t result{ static_cast<std::size_t>(state) };
	if (result > TState_count) { result += TState_count; }

	assert(result < TState_count);
	return result;
}

template<class TState, class TSymbol, std::size_t TState_count, std::size_t TAlphabet_size>
inline std::size_t dfa<TState, TSymbol, TState_count, TAlphabet_size>::wrap_symbol(TSymbol symbol) const
{
	std::size_t result{ static_cast<std::size_t>(symbol) };
	if (result > TAlphabet_size) { result += TAlphabet_size; }

	assert(result < TAlphabet_size);
	return result;
}

template<class TState, class TSymbol, std::size_t TState_count, std::size_t TAlphabet_size>
dfa<TState, TSymbol, TState_count, TAlphabet_size>::dfa(
	TState initial_state,
	TState default_transition) :
	initial_state(initial_state),
	current_state(initial_state),
	transition_table()
{
	transition_table.fill(default_transition);
}

template<class TState, class TSymbol, std::size_t TState_count, std::size_t TAlphabet_size>
TState dfa<TState, TSymbol, TState_count, TAlphabet_size>::state() const
{
	return current_state;
}

template<class TState, class TSymbol, std::size_t TState_count, std::size_t TAlphabet_size>
TState dfa<TState, TSymbol, TState_count, TAlphabet_size>::transition(TSymbol symbol)
{
	return current_state = transition_table[index(current_state, symbol)];
}

template<class TState, class TSymbol, std::size_t TState_count, std::size_t TAlphabet_size>
void dfa<TState, TSymbol, TState_count, TAlphabet_size>::rewind()
{
	current_state = initial_state;
}

template<class TState, class TSymbol, std::size_t TState_count, std::size_t TAlphabet_size>
void dfa<TState, TSymbol, TState_count, TAlphabet_size>::set_transition(
	std::initializer_list<TState> states,
	TState transition,
	std::initializer_list<TSymbol> symbols)
{
	for (auto state : states)
	{
		for (auto symbol : symbols)
		{
			transition_table[index(state, symbol)] = transition;
		}
	}
}

template<class TState, class TSymbol, std::size_t TState_count, std::size_t TAlphabet_size>
void dfa<TState, TSymbol, TState_count, TAlphabet_size>::fill_state_transition(
	std::initializer_list<TState> states,
	TState transition)
{
	for (auto state : states)
	{
		std::fill(
			transition_table.begin() + index(state, 0),
			transition_table.begin() + index(state, TAlphabet_size - 1),
			transition);
	}
}

#endif
