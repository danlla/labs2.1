#include "binim.h"
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

binim::binim(size_t row, size_t col) : data(new bool[col*row]), row(row), col(col)
{
	for (size_t i = 0; i < col*row; ++i)
	{
		data[i] = 0;
	}
}

binim::binim(size_t row, size_t col, bool fill_data) : data(new bool[col*row]), row(row), col(col)
{
	for (size_t i = 0; i < col*row; ++i)
	{
		data[i] = fill_data;
	}
}

binim::binim(const binim & rhs) : data(new bool[rhs.col*rhs.row]), row(rhs.row), col(rhs.col), is_cache_valid(rhs.is_cache_valid), fill_cache(rhs.fill_cache)
{
	puts("COPY-CTOR");
	for (size_t i = 0; i < row*col; ++i)
	{
		data[i] = rhs.data[i];
	}
}

binim::binim(binim && rhs) noexcept : data(rhs.data), row(rhs.row), col(rhs.col), is_cache_valid(rhs.is_cache_valid), fill_cache(rhs.fill_cache)
{
	puts("MOVE-CTOR");
	rhs.data = nullptr;
	rhs.row = 0;
	rhs.col = 0;
}

binim & binim::operator=(const binim & rhs)
{
	puts("COPY-ASSIGN");
	if (this->data == rhs.data)
		return *this;
	binim tmp(rhs);
	swap(tmp);
	return *this;
}

binim & binim::operator=(binim && rhs) noexcept
{
	puts("MOVE-ASSIGN");
	swap(rhs);
	return *this;
}

void binim::swap(binim & rhs) noexcept
{
	puts("CUSTOM SWAP");
	std::swap(data, rhs.data);
	std::swap(row, rhs.row);
	std::swap(col, rhs.col);
	std::swap(is_cache_valid, rhs.is_cache_valid);
	std::swap(fill_cache, rhs.fill_cache);
}

size_t binim::get_col() const
{
	return col;
}

size_t binim::get_row() const
{
	return row;
}

bool binim::operator()(const size_t in_row, const size_t in_col) const
{
	if (in_row >= row || in_col >= col)
	{
		throw std::logic_error("Index out of range");
	}
	is_cache_valid = false;
	return data[in_col + col * in_row];
}

bool & binim::operator()(size_t in_row, size_t in_col)
{
	if (in_row >= row || in_col >= col)
	{
		throw std::logic_error("Index out of range");
	}
	is_cache_valid = false;
	return data[in_col + col * in_row];
}

float binim::get_fill() const
{
	if (is_cache_valid)
	{
		return fill_cache;
	}
	fill_cache = 0.0f;
	size_t amount_true = 0;
	for (size_t i = 0; i < row*col; ++i)
	{
		if (data[i] == 1)
			++amount_true;
	}
	fill_cache = (float)amount_true / row * col;
	is_cache_valid = true;
	return fill_cache;
}

binim::~binim()
{
	delete[] data;
}

binim & operator+=(binim & lhs, const binim & rhs)
{
	if (lhs.get_col() != rhs.get_col() || lhs.get_row() != rhs.get_row())
	{
		throw std::logic_error("Images must have the same size");
	}
	const auto col = lhs.get_col();
	const auto row = lhs.get_row();
	for (size_t i = 0; i < row; ++i)
		for (size_t j = 0; j < col; ++j)
			lhs(i, j) = lhs(i, j) || rhs(i, j);
	return lhs;
}

binim & operator+(binim & lhs, const binim & rhs)
{
	lhs += rhs;
	return lhs;
}

binim & operator*=(binim & lhs, const binim & rhs)
{
	if (lhs.get_col() != rhs.get_col() || lhs.get_row() != rhs.get_row())
	{
		throw std::logic_error("Images must have the same size");
	}
	const auto col = lhs.get_col();
	const auto row = lhs.get_row();
	for (size_t i = 0; i < row; ++i)
		for (size_t j = 0; j < col; ++j)
			lhs(i, j) = lhs(i, j) && rhs(i, j);
	return lhs;
}

binim & operator*(binim & lhs, const binim & rhs)
{
	lhs *= rhs;
	return lhs;
}

binim & operator!(binim & rhs)
{
	for (size_t i = 0; i < rhs.get_row(); ++i)
		for (size_t j = 0; j < rhs.get_col(); ++j)
			rhs(i, j) = !rhs(i, j);
	return rhs;
}

bool operator==(binim & lhs, binim & rhs)
{
	if (lhs.get_col() != rhs.get_col() || lhs.get_row() != rhs.get_row())
	{
		throw std::logic_error("Images must have the same size");
	}
	for (size_t i = 0; i < rhs.get_row(); ++i)
		for (size_t j = 0; j < rhs.get_col(); ++j)
			if (lhs(i, j) != rhs(i, j))
				return false;
	return true;
}

bool operator!=(binim & lhs, binim & rhs)
{
	if (lhs.get_col() != rhs.get_col() || lhs.get_row() != rhs.get_row())
	{
		throw std::logic_error("Images must have the same size");
	}
	for (size_t i = 0; i < rhs.get_row(); ++i)
		for (size_t j = 0; j < rhs.get_col(); ++j)
			if (lhs(i, j) == rhs(i, j))
				return false;
	return true;
}
