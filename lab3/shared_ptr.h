#pragma once

template<typename T>

class shared_ptr
{
	T* ptr;
	int* counter;
public:
	shared_ptr(): ptr(nullptr), counter(nullptr){}

	shared_ptr(T* ptr): ptr(ptr), counter(ptr!=nullptr? new int(1): nullptr){}

	shared_ptr(const shared_ptr<T>& rhs) : ptr(rhs.ptr), counter(rhs.counter)
	{
		++*counter;
	}

	shared_ptr(shared_ptr<T>&& rhs) noexcept : ptr(rhs.ptr), counter(rhs.counter)
	{
		rhs.ptr=nullptr;
		rhs.counter = nullptr;
	}

	shared_ptr<T>& operator=(const shared_ptr<T>& rhs)
	{
		auto copy = rhs;
		swap(copy);
		return *this;
	}

	shared_ptr<T>& operator=(std::nullptr_t)
	{
		shared_ptr<T> copy = nullptr;
		swap(copy);
		return *this;
	}

	shared_ptr<T>& operator=(shared_ptr<T>&& rhs)
	{
		swap(rhs);
		return *this;
	}

	int use_count() const
	{
		if (counter == nullptr)
			return 0;
		return *counter;
	}

	void reset() noexcept
	{
		reset(nullptr);
	}

	void reset(T* const new_ptr)
	{
		/*shared_ptr<T> p = new_ptr;
		swap(p);*/

		if (counter != nullptr)
		{

			if (*counter != 1)
				--*counter;
			else
			{
				delete ptr;
				delete counter;
			}
		}
		if (new_ptr == nullptr)
		{
			ptr = nullptr;
			counter = nullptr;
		}
		else
		{
			ptr = new_ptr;
			counter = new int(1);
		}
	}

	void swap(shared_ptr<T>& rhs) noexcept
	{
		std::swap(ptr, rhs.ptr);
		std::swap(counter, rhs.counter);
	}

	T* get() const
	{
		return ptr;
	}

	operator bool() const
	{
		return ptr != nullptr;
	}

	T& operator*()
	{
		return *ptr;
	}
	T* operator->()
	{
		return ptr;
	}

	~shared_ptr()
	{
		reset();
	}
};

template<typename T>
bool operator==(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs) 
{
	return lhs.get() == rhs.get();
}

template<typename T>
bool operator!=(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs) 
{
	return lhs.get() != rhs.get();
}

template<typename T>
bool operator<(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
{
	return lhs.get() < rhs.get();
}

template<typename T>
bool operator>(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
{
	return rhs<lhs;
}

template<typename T>
bool operator<=(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
{
	return !(rhs<lhs);
}

template<typename T>
bool operator>=(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
{
	return !(lhs<rhs);
}