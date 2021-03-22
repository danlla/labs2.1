#pragma once

template<typename T>

class unique_ptr
{
	T* ptr;
public:
	unique_ptr():ptr(nullptr){}

	unique_ptr(T* ptr):ptr(ptr){}

	unique_ptr(unique_ptr<T>& rhs) = delete;

	unique_ptr(unique_ptr<T>&& rhs) noexcept
	{
		ptr = rhs.ptr;
		rhs.ptr = nullptr;
	}

	unique_ptr<T>& operator=(const unique_ptr<T>& rhs) = delete;

	unique_ptr<T>& operator=(const unique_ptr<T>&& rhs)
	{
		swap(ptr, rhs.ptr);
		return *this;
	}

	unique_ptr& operator=(std::nullptr_t)
	{
		if (ptr != nullptr)
			delete ptr;
		ptr = nullptr;
		return *this;
	}

	T* release() noexcept
	{
		if (ptr == nullptr)
			return nullptr;
		auto tmp = ptr;
		ptr = nullptr;
		return tmp;
	}

	void reset(T* new_ptr) noexcept
	{
		if (ptr != nullptr)
			delete ptr;
		ptr = new_ptr;
	}

	T* get() const
	{
		return ptr;
	}

	void swap(unique_ptr<T>& rhs) noexcept
	{
		auto tmp = ptr;
		ptr = rhs.ptr;
		rhs.ptr = tmp;
	}

	operator bool() const noexcept
	{
		return ptr != nullptr;
	}

	T& operator*()
	{
		return *ptr;
	}

	const T& operator*() const
	{
		return *ptr;
	}

	T* operator->() const noexcept
	{
		return ptr;
	}

	~unique_ptr()
	{
		delete ptr;
	}
};

template<typename T>
bool operator==(const unique_ptr<T> lhs, const unique_ptr<T> rhs)
{
	return lhs.get() == rhs.get();
}

template<typename T>
bool operator!=(const unique_ptr<T> lhs, const unique_ptr<T> rhs)
{
	return lhs.get() != rhs.get();
}

template<typename T>
bool operator<(const unique_ptr<T> lhs, const unique_ptr<T> rhs)
{
	return lhs.get() < rhs.get();
}

template<typename T>
bool operator>(const unique_ptr<T> lhs, const unique_ptr<T> rhs)
{
	return rhs<lhs;
}

template<typename T>
bool operator<=(const unique_ptr<T> lhs, const unique_ptr<T> rhs)
{
	return !(rhs<lhs);
}

template<typename T>
bool operator>=(const unique_ptr<T> lhs, const unique_ptr<T> rhs)
{
	return !(lhs<rhs);
}