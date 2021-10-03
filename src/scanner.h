#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include "dfa.h"
#include "symbol.h"
#include <istream>
#include <optional>

class scanner
{
public:
	enum class states : unsigned char
	{
		sink,
		error,
		initial,
		num0_accept,
		num1,
		num2_accept,
		num3,
		num4,
		num5_accept,
		rcb_accept,
		opr_less_accept,
		opr_greater_accept,
		opr_equal_accept,
		opm_accept,
		ab_p_accept,
		fc_p_accept,
		pt_v_accept,
		vir_accept,
		comment0,
		comment1_accept,
		id_accept,
		lit_string0,
		lit_string1_accept,
		lit_char0,
		lit_char1,
		lit_char2_accept,
		eof_accept,
		MAX = eof_accept
	};

	typedef dfa<scanner::states, char, static_cast<size_t>(scanner::states::MAX) + 1, 256> recognizer_t;

public:
	scanner();
	token next(std::istream& source);

private:
	recognizer_t recognizer;
	symbol_table symbol;
	std::string lexeme;
	int line{ 1 }, column{ 0 };
	char previous_symbol{ 0 };

	std::optional<token> process_symbol(std::istream& source);
	std::optional<token> process_lexeme(states final_state, char err_symbol);
	char next_symbol(std::istream& source) const;
	void update_line_count();
	token build_token(scanner::states last);
};

#endif
