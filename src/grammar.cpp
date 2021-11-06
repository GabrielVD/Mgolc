#include "grammar.h"
#include <cassert>

std::vector<token::tclass_enum> follow(nterminal symb)
{
#define T(TERMINAL) token::tclass_enum:: TERMINAL
	switch (symb)
	{
	case nterminal::P:
	case nterminal::A:
		return { T(eof) };

	case nterminal::V:
	case nterminal::LV:
	case nterminal::R:
	case nterminal::CP_R:
		return { T(leia), T(escreva), T(id), T(se), T(repita), T(fim) };

	case nterminal::D:
		return { T(inteiro), T(real), T(literal), T(varfim) };

	case nterminal::L:
	case nterminal::ARG:
	case nterminal::LD:
		return { T(pt_v) };

	case nterminal::TIPO:
		return { T(id) };

	case nterminal::ES:
	case nterminal::CMD:
	case nterminal::COND:
	case nterminal::CP:
		return { T(leia), T(escreva), T(id), T(se),
			T(repita), T(fim), T(fimse), T(fimrepita) };

	case nterminal::OPRD:
		return { T(opm), T(pt_v), T(opr), T(fc_p) };

	case nterminal::CAB:
		return { T(leia), T(id), T(escreva), T(se), T(fimse) };

	case nterminal::EXP_R:
		return { T(fc_p) };
	}

	assert(false);
	return {};
#undef T
}
