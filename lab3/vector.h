#pragma once
template<typename T>
class vector
{
	T* _data;
	size_t _size;
	size_t _capacity;

public:
	using iterator = T * ;
	using const_iterator = const T*;

	vector() : _data(nullptr), _size(0), _capacity(0) { }

	vector(size_t size) : _data(new T[size]), _size(size), _capacity(size)
	{
		for (size_t i = 0; i < _size; ++i)
			_data[i] = 0;
	}

	vector(const vector<T>& rhs) : _data(new T[rhs._size]), _size(rhs._size), _capacity(rhs._capacity)
	{
		for (size_t i = 0; i < _size; ++i)
			_data[i] = rhs._data[i];
	}

	vector(vector<T>&& rhs) noexcept : _data(rhs.data), _size(rhs._size)
	{
		rhs._data = nullptr;
		rhs._size = 0;
	}

	vector<T>& operator=(const vector<T>& rhs)
	{
		auto temp(rhs);
		swap(temp);
		return *this;
	}

	vector<T>& operator=(vector<T>&& rhs) noexcept
	{
		swap(rhs);
		return *this;
	}

	void swap(vector<T>& rhs) noexcept
	{
		std::swap(_data, rhs._data);
		std::swap(_size, rhs._size);
		std::swap(_capacity, rhs._capacity);
	}

	size_t size() const noexcept
	{
		return _size;
	}

	size_t capacity() const noexcept
	{
		return _capacity;
	}

	const T& operator[](const size_t index) const
	{
		return _data[index];
	}

	T& operator[](size_t index)
	{
		return _data[index];
	}

	const_iterator begin() const
	{
		return _data;
	}

	const_iterator end() const
	{
		return _data + _size;
	}

	void resize(size_t new_size)
	{
		if (_capacity >= new_size)
		{
			auto tmp = new T[new_size];
			for (int i = 0; i < _size; ++i)
				tmp[i] = std::move_if_noexcept(_data[i]);
			_size = new_size;
			_capacity = new_size;
			delete[]_data;
			_data = tmp;
		}
		else
		{
			auto tmp = new T[new_size];
			for (int i = 0; i < _size; ++i)
				tmp[i] = std::move_if_noexcept(_data[i]);
			++_size;
			_capacity = new_size;
			delete[] _data;
			_data = tmp;
		}
	}
	iterator insert(const_iterator pos, const T& value) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("iterator out of range");
		size_t count_move = _size == 0 ? 0 : _size - (pos - _data);
		if (_size + 1 > _capacity)
		{
			size_t new_size = _size == 0 ? 1 : _size * 2;
			this->resize(new_size);
		}
		else
			++_size;
		auto insert_place = _data + (_size - 1 - count_move);
		for (int i = (int)count_move; i > 0; --i)
		{
			*(insert_place + i) = std::move_if_noexcept(*(insert_place + i - 1));
		}
		*insert_place = value;
		return insert_place;
	}

	const_iterator erase(const_iterator pos)
	{
		if (pos < begin() || pos > end())
			throw std::out_of_range("iterator out of range");
		size_t index_deleted = pos - _data;
		size_t count_move = _size - index_deleted - 1;
		auto delete_place = _data + index_deleted;
		for (int i = 0; i < (int)count_move; ++i)
		{
			*(delete_place + i) = std::move_if_noexcept(*(delete_place + i+1));
		}
		--_size;
		return pos;
	}

	void clear() noexcept
	{
		delete[] _data;
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}

	~vector()
	{
		clear();
	}
};