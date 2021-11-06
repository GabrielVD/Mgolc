#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <array>
#include <cassert>
#include <algorithm>

template<
	class TVal,
	class TRow,
	class TColumn,
	std::size_t TRow_count,
	std::size_t TColumn_count
>
class array2d
{
private:
	std::array<TVal, TRow_count * TColumn_count> data;

public:
	array2d(const TVal &initial_value);

	const TVal& at(TRow, TColumn) const;
	TVal& at(TRow, TColumn);


private:
	std::size_t index(TRow, TColumn) const;
	std::size_t index(TRow) const;
};

template<class TVal, class TRow, class TColumn, std::size_t TRow_count, std::size_t TColumn_count>
array2d<TVal, TRow, TColumn, TRow_count, TColumn_count>::array2d(const TVal &initial_value)
{
	data.fill(initial_value);
}

template<class TVal, class TRow, class TColumn, std::size_t TRow_count, std::size_t TColumn_count>
const TVal& array2d<TVal, TRow, TColumn, TRow_count, TColumn_count>::at(TRow row, TColumn column) const
{
	return data[index(row, column)];
}

template<class TVal, class TRow, class TColumn, std::size_t TRow_count, std::size_t TColumn_count>
TVal& array2d<TVal, TRow, TColumn, TRow_count, TColumn_count>::at(TRow row, TColumn column)
{
	return data[index(row, column)];
}

template<class TVal, class TRow, class TColumn, std::size_t TRow_count, std::size_t TColumn_count>
std::size_t array2d<TVal, TRow, TColumn, TRow_count, TColumn_count>::index(TRow row, TColumn column) const
{
	const auto i{ static_cast<std::size_t>(row) };
	const auto j{ static_cast<std::size_t>(column) };
	assert(i < TRow_count);
	assert(j < TColumn_count);
	return i * TColumn_count + j;
}

template<class TVal, class TRow, class TColumn, std::size_t TRow_count, std::size_t TColumn_count>
std::size_t array2d<TVal, TRow, TColumn, TRow_count, TColumn_count>::index(TRow) const
{
	const auto i{ static_cast<std::size_t>(row) };
	assert(i < TRow_count);
	return i * TColumn_count;
}

#endif
