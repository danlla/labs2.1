#pragma once

template<typename T>
class list
{
	struct node
	{
		T data; //T* std::allocator
		node* prev;
		node* next;

		node(const T& data, node* prev, node* next) : data(data), prev(prev), next(next) { }
		node(T&& data, node* prev, node* next) : data(data), prev(prev), next(next) { }
	};

	node* _dummy;
	node* _head;
	node* _tail;
	size_t _size;

public:
	class const_iterator
	{
		node* _node;

		const_iterator(node* _node) : _node(_node) {}

	public:
		using difference_type = void;
		using value_type = T;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::bidirectional_iterator_tag;

		friend class list<T>;

		const_iterator& operator++()
		{
			_node = _node->next;
			return *this;
		}

		const_iterator operator++(int)
		{
			auto result(*this);
			_node = _node->next;
			return result;
		}

		const_iterator operator+(int count)
		{
			for (int i = 0; i < count; ++i)
				++(*this);
			return *this;
		}

		const_iterator& operator--()
		{
			_node = _node->prev;
			return *this;
		}
		const_iterator& operator--(int)
		{
			auto result(*this);
			_node = _node->prev;
			return result;
		}

		const T& operator*()
		{
			return _node->data;
		}

		T* operator->()
		{
			return &(_node->_data);
		}

		bool operator==(const_iterator rhs)
		{
			return _node == rhs._node;
		}

		bool operator!=(const_iterator rhs)
		{
			return _node != rhs._node;
		}
		};

		list() : _dummy(new node(T(), nullptr, nullptr)), _size(0)
		{
			_dummy->prev = _dummy;
			_dummy->next = _dummy;
			_head = _dummy;
			_tail = _dummy;
		}

		list(const list<T>& rhs)
		{
			node * src = rhs.tail;
			dummy->next = _dummy;
			node* dst = _dummy;
			for (size_t i = 0; i < rhs._size; ++i)
			{
				node* tmp = new node(src->data, dst, nullptr);
				dst->prev = tmp;
				src = src->prev;
				dst = tmp;
			}
			dst->_prev = dummy;
			head = dst;
			tail = dst->prev->prev;
			_size = rhs._size;
		}

		list(list<T>&& rhs) noexcept
		{
			swap(*this, rhs);
		}

		list<T>& operator=(const list<T>& rhs)
		{
			auto temp(rhs);
			swap(temp);
			return *this;
		}

		list<T>& operator=(list<T>&& rhs) noexcept
		{
			swap(rhs);
			return *this;
		}

		void swap(list<T>& rhs) noexcept
		{
			std::swap(_head, rhs._head);
			std::swap(_tail, rhs._tail);
			std::swap(_dummy, rhs._dummy);
			std::swap(_size, rhs._size);
		}

		size_t size() const noexcept
		{
			return _size;
		}

		const_iterator begin() const
		{
			return const_iterator(_head);
		}

		const_iterator end() const
		{
			return const_iterator(_dummy);
		}

		const_iterator insert(const_iterator pos, const T& value)
		{
			auto prev = pos._node->prev;
			auto next = pos._node;
			auto _node = new node(value, prev, next);
			prev->next = _node;
			next->prev = _node;
			if (prev == _dummy)
				_head = _node;
			++_size;
			return const_iterator(_node);
		}

		const_iterator insert(const_iterator pos,T&& value)
		{
			auto prev = pos._node->prev;
			auto next = pos._node;
			auto _node = new node(value, prev, next);
			prev->next = _node;
			next->prev = _node;
			if (prev == _dummy)
				_head = _node;
			++_size;
			return const_iterator(_node);
		}

		const_iterator erase(const_iterator pos)
		{
			if (pos == this->end())
				return _dummy;
			auto _node = pos._node;
			if (pos == this->begin())
			{
				_node->next->prev = _dummy;
				_head = _node->next;
			}
			else
			{
				_node->prev->next = _node->next;
				_node->next->prev = _node->prev;
			}
			++pos;
			--_size;
			delete _node;
			return pos;

		}

		void clear() noexcept
		{
			for (int i = 0; i < _size; ++i)
			{
				auto tmp = _head;
				_head = _head->next;
				delete tmp;
			}
			_size = 0;
			_tail = _head;
			_dummy->prev = _dummy;
		}

		~list()
		{
			clear();
			delete _dummy;
		}
};