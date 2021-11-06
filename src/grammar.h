#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "enum_syntatic.h"
#include "token.h"
#include <cstdint>
#include <vector>

enum class nterminal : unsigned char
{
	P,
	V,
	LV,
	D,
	L,
	TIPO,
	A,
	ES,
	ARG,
	CMD,
	LD,
	OPRD,
	COND,
	CAB,
	EXP_R,
	CP,
	R,
	CP_R,
	MAX = CP_R,
	MIN = P
};

enum class production : unsigned char
{
	p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,
	MAX = p38
};

struct production_data
{
	int8_t reduction_size;
	nterminal left_symbol;
	const char* string;

	static production_data of(production p)
	{
		static const production_data data[] =
		{
			{ 3, nterminal::P, "P --> inicio V A" },
			{ 2, nterminal::V, "V --> varinicio LV" },
			{ 2, nterminal::LV, "LV --> D LV" },
			{ 2, nterminal::LV, "LV --> varfim;" },
			{ 3, nterminal::D, "D --> TIPO L;" },
			{ 3, nterminal::L, "L --> id, L" },
			{ 1, nterminal::L, "L --> id" },
			{ 1, nterminal::TIPO, "TIPO --> inteiro" },
			{ 1, nterminal::TIPO, "TIPO --> real" },
			{ 1, nterminal::TIPO, "TIPO --> literal" },
			{ 2, nterminal::A, "A --> ES A" },
			{ 3, nterminal::ES, "ES --> leia id;" },
			{ 3, nterminal::ES, "ES --> escreva ARG;" },
			{ 1, nterminal::ARG, "ARG --> lit" },
			{ 1, nterminal::ARG, "ARG --> num" },
			{ 1, nterminal::ARG, "ARG --> id" },
			{ 2, nterminal::A, "A --> CMD A" },
			{ 4, nterminal::CMD, "CMD --> id <- LD;" },
			{ 3, nterminal::LD, "LD --> OPRD opm OPRD" },
			{ 1, nterminal::LD, "LD --> OPRD" },
			{ 1, nterminal::OPRD, "OPRD --> id" },
			{ 1, nterminal::OPRD, "OPRD --> num" },
			{ 2, nterminal::A, "A --> COND A" },
			{ 2, nterminal::COND, "COND --> CAB CP" },
			{ 5, nterminal::CAB, "CAB --> se (EXP_R) entao" },
			{ 3, nterminal::EXP_R, "EXP_R --> OPRD opr OPRD" },
			{ 2, nterminal::CP, "CP --> ES CP" },
			{ 2, nterminal::CP, "CP --> CMD CP" },
			{ 2, nterminal::CP, "CP --> COND CP" },
			{ 1, nterminal::CP, "CP --> fimse" },
			{ 2, nterminal::A, "A --> R A" },
			{ 5, nterminal::R, "R  --> repita (EXP_R) CP_R" },
			{ 2, nterminal::CP_R, "CP_R --> ES CP_R" },
			{ 2, nterminal::CP_R, "CP_R --> CMD CP_R" },
			{ 2, nterminal::CP_R, "CP_R --> COND CP_R" },
			{ 1, nterminal::CP_R, "CP_R --> fimrepita" },
			{ 1, nterminal::A, "A --> fim" }
		};

		return data[static_cast<size_t>(p)];
	}
};

std::vector<token::tclass_enum> follow(nterminal symb);

#endif
