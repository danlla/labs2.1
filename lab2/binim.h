#pragma once

class binim
{
	bool* data;
	size_t row;
	size_t col;
	mutable bool is_cache_valid = false;
	mutable float fill_cache = 0.0f;
public:
	binim(size_t row, size_t col);
	binim(size_t row, size_t col, bool fill_data);
	binim(const binim& rhs);
	binim(binim&& rhs) noexcept;
	binim& operator=(const binim& rhs);
	binim& operator=(binim&& rhs) noexcept;
	void swap(binim& rhs) noexcept;
	size_t get_col() const;
	size_t get_row() const;
	bool operator()(const size_t in_row, const size_t in_col) const;
	bool& operator()(size_t in_row, size_t in_col);
	float get_fill() const;
	~binim();
};

binim& operator+=(binim& lhs, const binim&rhs);
binim& operator+(binim& lhs, const binim&rhs);
binim& operator*=(binim& lhs, const binim&rhs);
binim& operator*(binim& lhs, const binim&rhs);
binim& operator!(binim& rhs);
bool operator ==(binim& lhs, binim& rhs);
bool operator !=(binim& lhs, binim& rhs);