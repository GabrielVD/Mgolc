#include "goto.h"

goto_table::goto_table() :
	table(state_syntatic::s0)
{
	set_gotos();
}

std::vector<state_syntatic> goto_table::valid_for(const state_syntatic state) const
{
#define INT(x) static_cast<int>(x)
#define NTERM(x) static_cast<nterminal>(x)

	std::vector<state_syntatic> vec;

	for (int i = INT(nterminal::MIN); i <= INT(nterminal::MAX); i++)
	{
		const auto goto_state{ table.at(state, NTERM(i)) };
		if (goto_state != state_syntatic::s0) { vec.push_back(goto_state); }
	}

	return vec;

#undef INT
#undef STATE
}

void goto_table::set_gotos()
{
	state_syntatic state;
#define SET_GOTO(A, B) table.at(state, nterminal:: A) = state_syntatic:: B;

	state = state_syntatic::s0;
	SET_GOTO(P, s1);
	state = state_syntatic::s2;
	SET_GOTO(V, s18);
	state = state_syntatic::s3;
	SET_GOTO(LV, s4);
	SET_GOTO(D, s5);
	SET_GOTO(TIPO, s9);
	state = state_syntatic::s5;
	SET_GOTO(LV, s6);
	SET_GOTO(D, s5);
	SET_GOTO(TIPO, s9);
	state = state_syntatic::s9;
	SET_GOTO(L, s10);
	state = state_syntatic::s13;
	SET_GOTO(L, s14);
	state = state_syntatic::s18;
	SET_GOTO(A, s19);
	SET_GOTO(R, s20);
	SET_GOTO(COND, s22);
	SET_GOTO(CMD, s24);
	SET_GOTO(ES, s26);
	SET_GOTO(CAB, s28);
	state = state_syntatic::s20;
	SET_GOTO(A, s21);
	SET_GOTO(R, s20);
	SET_GOTO(COND, s22);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s24);
	SET_GOTO(ES, s26);
	state = state_syntatic::s22;
	SET_GOTO(A, s23);
	SET_GOTO(R, s20);
	SET_GOTO(COND, s22);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s24);
	SET_GOTO(ES, s26);
	state = state_syntatic::s24;
	SET_GOTO(A, s25);
	SET_GOTO(R, s20);
	SET_GOTO(COND, s22);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s24);
	SET_GOTO(ES, s26);
	state = state_syntatic::s26;
	SET_GOTO(A, s27);
	SET_GOTO(R, s20);
	SET_GOTO(COND, s22);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s24);
	SET_GOTO(ES, s26);
	state = state_syntatic::s28;
	SET_GOTO(CP, s29);
	SET_GOTO(CAB, s28);
	SET_GOTO(COND, s31);
	SET_GOTO(CMD, s33);
	SET_GOTO(ES, s35);
	state = state_syntatic::s31;
	SET_GOTO(CP, s32);
	SET_GOTO(COND, s31);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s33);
	SET_GOTO(ES, s35);
	state = state_syntatic::s33;
	SET_GOTO(CP, s34);
	SET_GOTO(COND, s31);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s33);
	SET_GOTO(ES, s35);
	state = state_syntatic::s35;
	SET_GOTO(CP, s36);
	SET_GOTO(COND, s31);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s33);
	SET_GOTO(ES, s35);
	state = state_syntatic::s41;
	SET_GOTO(ARG, s45);
	state = state_syntatic::s48;
	SET_GOTO(LD, s51);
	SET_GOTO(OPRD, s53);
	state = state_syntatic::s54;
	SET_GOTO(OPRD, s55);
	state = state_syntatic::s57;
	SET_GOTO(EXP_R, s58);
	SET_GOTO(OPRD, s61);
	state = state_syntatic::s62;
	SET_GOTO(OPRD, s63);
	state = state_syntatic::s65;
	SET_GOTO(OPRD, s61);
	SET_GOTO(EXP_R, s66);
	state = state_syntatic::s67;
	SET_GOTO(CP_R, s68);
	SET_GOTO(CAB, s28);
	SET_GOTO(COND, s70);
	SET_GOTO(CMD, s72);
	SET_GOTO(ES, s74);
	state = state_syntatic::s70;
	SET_GOTO(CP_R, s71);
	SET_GOTO(COND, s70);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s72);
	SET_GOTO(ES, s74);
	state = state_syntatic::s72;
	SET_GOTO(CP_R, s73);
	SET_GOTO(COND, s70);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s72);
	SET_GOTO(ES, s74);
	state = state_syntatic::s74;
	SET_GOTO(CP_R, s75);
	SET_GOTO(COND, s70);
	SET_GOTO(CAB, s28);
	SET_GOTO(CMD, s72);
	SET_GOTO(ES, s74);

#undef SET_GOTO
}
