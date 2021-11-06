#include "action.h"
#include <initializer_list>
#include <cassert>

using std::initializer_list;

action_table::action_table() :
	table(action())
{
	set_actions();
}

void action_table::set_shift(
	const state_syntatic state,
	const token::tclass_enum term,
	const state_syntatic shift)
{
	auto& action = at(state, term);
	action.type = action::types::shift;
	action.state = shift;
}

void action_table::set_reduce(const state_syntatic state, const production prod)
{
	for (auto term : follow(production_data::of(prod).left_symbol))
	{
		auto& action = at(state, term);
		action.type = action::types::reduce;
		action.production = prod;
	}
}

void action_table::set_actions()
{
	state_syntatic state;

#define SET_SHIFT(TERMINAL, STATE)\
set_shift(state, token::tclass_enum:: TERMINAL, state_syntatic:: STATE)

#define SET_REDUCE(PROD)\
set_reduce(state, production:: PROD)

	state = state_syntatic::s0;
	SET_SHIFT(inicio, s2);
	state = state_syntatic::s1;
	at(state, token::tclass_enum::eof).type = action::types::accept;
	state = state_syntatic::s2;
	SET_SHIFT(varinicio, s3);
	state = state_syntatic::s3;
	SET_SHIFT(varfim, s7);
	SET_SHIFT(inteiro, s15);
	SET_SHIFT(real, s16);
	SET_SHIFT(literal, s17);
	state = state_syntatic::s4;
	SET_REDUCE(p3);
	state = state_syntatic::s5;
	SET_SHIFT(varfim, s7);
	SET_SHIFT(inteiro, s15);
	SET_SHIFT(real, s16);
	SET_SHIFT(literal, s17);
	state = state_syntatic::s6;
	SET_REDUCE(p4);
	state = state_syntatic::s7;
	SET_SHIFT(pt_v, s8);
	state = state_syntatic::s8;
	SET_REDUCE(p5);
	state = state_syntatic::s9;
	SET_SHIFT(id, s12);
	state = state_syntatic::s10;
	SET_SHIFT(pt_v, s11);
	state = state_syntatic::s11;
	SET_REDUCE(p6);
	state = state_syntatic::s12;
	SET_SHIFT(vir, s13);
	SET_REDUCE(p8);
	state = state_syntatic::s13;
	SET_SHIFT(id, s12);
	state = state_syntatic::s14;
	SET_REDUCE(p7);
	state = state_syntatic::s15;
	SET_REDUCE(p9);
	state = state_syntatic::s16;
	SET_REDUCE(p10);
	state = state_syntatic::s17;
	SET_REDUCE(p11);
	state = state_syntatic::s18;
	SET_SHIFT(fim, s37);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	SET_SHIFT(id, s47);
	SET_SHIFT(se, s56);
	SET_SHIFT(repita, s64);
	state = state_syntatic::s19;
	SET_REDUCE(p2);
	state = state_syntatic::s20;
	SET_SHIFT(fim, s37);
	SET_SHIFT(repita, s64);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s21;
	SET_REDUCE(p32);
	state = state_syntatic::s22;
	SET_SHIFT(fim, s37);
	SET_SHIFT(repita, s64);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s23;
	SET_REDUCE(p24);
	state = state_syntatic::s24;
	SET_SHIFT(fim, s37);
	SET_SHIFT(repita, s64);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s25;
	SET_REDUCE(p18);
	state = state_syntatic::s26;
	SET_SHIFT(fim, s37);
	SET_SHIFT(repita, s64);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s27;
	SET_REDUCE(p12);
	state = state_syntatic::s28;
	SET_SHIFT(fimse, s30);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s29;
	SET_REDUCE(p25);
	state = state_syntatic::s30;
	SET_REDUCE(p31);
	state = state_syntatic::s31;
	SET_SHIFT(fimse, s30);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s32;
	SET_REDUCE(p30);
	state = state_syntatic::s33;
	SET_SHIFT(fimse, s30);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s34;
	SET_REDUCE(p29);
	state = state_syntatic::s35;
	SET_SHIFT(fimse, s30);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s36;
	SET_REDUCE(p28);
	state = state_syntatic::s37;
	SET_REDUCE(p38);
	state = state_syntatic::s38;
	SET_SHIFT(id, s39);
	state = state_syntatic::s39;
	SET_SHIFT(pt_v, s40);
	state = state_syntatic::s40;
	SET_REDUCE(p13);
	state = state_syntatic::s41;
	SET_SHIFT(lit, s42);
	SET_SHIFT(num, s43);
	SET_SHIFT(id, s44);
	state = state_syntatic::s42;
	SET_REDUCE(p15);
	state = state_syntatic::s43;
	SET_REDUCE(p16);
	state = state_syntatic::s44;
	SET_REDUCE(p17);
	state = state_syntatic::s45;
	SET_SHIFT(pt_v, s46);
	state = state_syntatic::s46;
	SET_REDUCE(p14);
	state = state_syntatic::s47;
	SET_SHIFT(rcb, s48);
	state = state_syntatic::s48;
	SET_SHIFT(id, s49);
	SET_SHIFT(num, s50);
	state = state_syntatic::s49;
	SET_REDUCE(p22);
	state = state_syntatic::s50;
	SET_REDUCE(p23);
	state = state_syntatic::s51;
	SET_SHIFT(pt_v, s52);
	state = state_syntatic::s52;
	SET_REDUCE(p19);
	state = state_syntatic::s53;
	SET_SHIFT(opm, s54);
	SET_REDUCE(p21);
	state = state_syntatic::s54;
	SET_SHIFT(id, s49);
	SET_SHIFT(num, s50);
	state = state_syntatic::s55;
	SET_REDUCE(p20);
	state = state_syntatic::s56;
	SET_SHIFT(ab_p, s57);
	state = state_syntatic::s57;
	SET_SHIFT(id, s49);
	SET_SHIFT(num, s50);
	state = state_syntatic::s58;
	SET_SHIFT(fc_p, s59);
	state = state_syntatic::s59;
	SET_SHIFT(entao, s60);
	state = state_syntatic::s60;
	SET_REDUCE(p26);
	state = state_syntatic::s61;
	SET_SHIFT(opr, s62);
	state = state_syntatic::s62;
	SET_SHIFT(id, s49);
	SET_SHIFT(num, s50);
	state = state_syntatic::s63;
	SET_REDUCE(p27);
	state = state_syntatic::s64;
	SET_SHIFT(ab_p, s65);
	state = state_syntatic::s65;
	SET_SHIFT(id, s49);
	SET_SHIFT(num, s50);
	state = state_syntatic::s66;
	SET_SHIFT(fc_p, s67);
	state = state_syntatic::s67;
	SET_SHIFT(fimrepita, s69);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s68;
	SET_REDUCE(p33);
	state = state_syntatic::s69;
	SET_REDUCE(p37);
	state = state_syntatic::s70;
	SET_SHIFT(fimrepita, s69);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s71;
	SET_REDUCE(p36);
	state = state_syntatic::s72;
	SET_SHIFT(fimrepita, s69);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s73;
	SET_REDUCE(p35);
	state = state_syntatic::s74;
	SET_SHIFT(fimrepita, s69);
	SET_SHIFT(se, s56);
	SET_SHIFT(id, s47);
	SET_SHIFT(leia, s38);
	SET_SHIFT(escreva, s41);
	state = state_syntatic::s75;
	SET_REDUCE(p34);

#undef SET_SHIFT
#undef SET_REDUCE
}
