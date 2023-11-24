#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "enable_if.hpp"

namespace ft
{
	template <class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type distance(InputIt lhs, InputIt rhs)
	{
		typename ft::iterator_traits<InputIt>::difference_type dist = 0;
		for (; lhs != rhs; lhs++)
			dist++;
		return dist;
	}

	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		/* Member type */
		public:
			typedef T															value_type;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef	ft::random_access_iterator<value_type>						iterator;
			typedef	ft::random_access_iterator<const value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename allocator_type::size_type							size_type;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;

		/* Member val */
		private:
			allocator_type														__alloc;
			pointer																__start;
			pointer																__finish;
			pointer																__end_of_capacity;

		public:
			// constructor
			vector(const allocator_type& __a = allocator_type()) : __alloc(__a)
			{
				__start = __alloc.allocate(0);
				__finish = __start;
				__end_of_capacity = __start;
			}
			explicit vector(size_type __n, const value_type& __v = value_type(), const allocator_type& __a = allocator_type()) : __alloc(__a)
			{
				__start = __alloc.allocate(__n);
				__finish = __start;
				__end_of_capacity = __start + __n;
				insert(begin(), __n, __v);
			}
			template <class InputIt>
			vector(InputIt first, InputIt last, const allocator_type& __a = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0) : __alloc(__a)
			{
				typename InputIt::difference_type __n = ft::distance(first, last);
				__start = __alloc.allocate(__n);
				__finish = __start;
				__end_of_capacity = __start + __n;
				insert(begin(), first, last);
			}
			// copy
			vector(const vector& __v) : __alloc(__v.__alloc), __start(0), __finish(0), __end_of_capacity(0)
			{
				size_type cap = __v.capacity();
				__start = __alloc.allocate(cap);
				__finish = __start;
				__end_of_capacity = __start + cap;
				insert(begin(), __v.begin(), __v.end());
			}
			// distructor
			~vector ()
			{
				clear();
				if (__end_of_capacity >= __start)
					__alloc.deallocate(__start, capacity());
			}
			// operator =
			vector& operator=(const vector& __v)
			{
				if (this != &__v)
					assign(__v.begin(), __v.end());
				return (*this);
			}
			// assign
			template <class InputIt>
			void assign (InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
			{
				clear();
				insert(end(), first, last);
			}
			void assign(size_type __n, const value_type& __v)
			{
				clear();
				insert(end(), __n, __v);
			}
			// get_allocator
			allocator_type get_allocator() const
				{return Alloc(__alloc);}

			/* elenemt access */
			reference at(size_type __n)
			{
				if (__n >= size())
					throw (std::out_of_range("vector"));
				return (__start[__n]);
			}
			const_reference at(size_type __n) const
			{
				if (__n >= size())
					throw (std::out_of_range("vector"));
				return (__start[__n]);
			}
			reference operator[](size_type __n)
				{return (__start[__n]);}
			const_reference operator[](size_type __n) const
				{return (__start[__n]);}
			reference front()
				{return *begin();}
			const_reference front() const
				{return *begin();}
			reference back()
				{return *(end() - 1);}
			const_reference back() const
				{return *(end() - 1);}
			pointer data()
			{
				if (size() == 0)
					return 0;
				return __start;
			}
			const_pointer data() const
			{
				if (size() == 0)
					return 0;
				return __start;
			}

			// iterator
			iterator begin()
				{return iterator(__start);}
			const_iterator begin() const
				{return const_iterator(__start);}
			iterator end()
				{return iterator(__finish);}
			const_iterator end() const
				{return const_iterator(__finish);}
			reverse_iterator rbegin()
				{return reverse_iterator(end());}
			const_reverse_iterator rbegin() const
				{return const_reverse_iterator(end());}
			reverse_iterator rend()
				{return reverse_iterator(begin());}
			const_reverse_iterator rend() const
				{return const_reverse_iterator(begin());}

			// capacity
			bool empty() const
				{return (size() == 0);}
			size_type size() const
				{return __finish - __start;}
			size_type max_size() const
				{return __alloc.max_size();}
			size_type capacity() const
				{return __end_of_capacity - __start;}
			void reserve(size_type __n)
			{
				if (__n > capacity())
				{
					pointer	__tmp = __alloc.allocate(__n);
					size_type __size = size();
					for (size_type i = 0; i < __size; i++)
						std::memcpy(__tmp + i, __start + i, sizeof(value_type));
					__alloc.deallocate(__start, capacity());
					__start = __tmp;
					__finish = __start + __size;
					__end_of_capacity = __start + __n;
				}
			}

			/* modifier */
			void clear()
			{
				if (size() > 0)
				{
					for (iterator it = begin(); it != end(); it++)
						__alloc.destroy(&(*it));
					__finish = __start;
				}
			}

		private:
			void copy_backword(pointer __ori, pointer __dst, size_type size)
			{
				if (size < 1)
					return ;
				for (size_type i = 0; i < size; i++)
				{
					std::memcpy(__dst + size - 1 - i, __ori + size - 1 - i , sizeof(value_type));
				}
			}

		public:
			iterator insert(iterator __pos, const value_type& __v)
			{
				return insert(__pos, 1, __v);
			}
			iterator insert(iterator __pos, size_type __n, const value_type& __v)
			{
				if (__n == 0)
					return __pos;

				size_type __after_pos = end() - __pos;
				size_type __idx = __pos - begin();
				pointer __new = 0;
				size_type new_capacity = 0;

				if (capacity() < size() + __n && size() + __n <= capacity() * 2)
					new_capacity = capacity() * 2;
				else if (size() + __n > capacity() * 2)
					new_capacity = size() + __n;
				else
				{
					copy_backword(__start + __idx, __start + __idx + __n, __after_pos);
					for (size_type i = 0; i < __n; i++)
						__alloc.construct(__start + __idx + i, __v);
					__finish += __n;
					return iterator(__start + __idx);
				}
				__new = __alloc.allocate(new_capacity);

				size_type i = 0;
				for (; i < __idx; i++)
					std::memcpy(__new + i, __start + i, sizeof(value_type));
				for (; i < __idx + __n; i++)
					__alloc.construct(__new + i, __v);
				for (; i < __idx + __n + __after_pos; i++)
					std::memcpy(__new + i, __start + i - __n, sizeof(value_type));
				__alloc.deallocate(__start, capacity());
				__start = __new;
				__finish = __start + __idx + __n + __after_pos;
				__end_of_capacity = __start + new_capacity;
				return iterator(__start + __idx);
			}
			template <class InputIt>
			iterator insert (iterator __pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
			{
				size_type __after_pos = end() - __pos;
				size_type __idx = __pos - begin();
				size_type __n = static_cast<size_type>(ft::distance(first, last));
				pointer __new;
				size_type new_capacity;

				if (capacity() < size() + __n && size() + __n <= capacity() * 2)
					new_capacity = capacity() * 2;
				else if (size() + __n > capacity() * 2)
					new_capacity = size() + __n;
				else
				{
					copy_backword(__start + __idx, __start + __idx + __n, __after_pos);
					for (size_type i = 0; i < __n; i++)
					{
						__alloc.construct(__start + __idx + i, *first);
						first++;
					}
					__finish += __n;
					return iterator(__start + __idx);
				}
				__new = __alloc.allocate(new_capacity);

				size_type i = 0;
				for (; i < __idx; i++)
					std::memcpy(__new + i, __start + i, sizeof(value_type));
				for (; i < __idx + __n; i++)
				{
					__alloc.construct(__new + i, *first);
					first++;
				}
				for (; i < __idx + __n + __after_pos; i++)
					std::memcpy(__new + i, __start + i - __n, sizeof(value_type));
				__alloc.deallocate(__start, capacity());
				__start = __new;
				__finish = __start + __idx + __n + __after_pos;
				__end_of_capacity = __start + new_capacity;
				return iterator(__start + __idx);
			}
			iterator erase(iterator __pos)
			{
				if (empty())
					return end();
				iterator it = begin();
				while (it != __pos)
					it++;
				__alloc.destroy(&(*it));
				while (it + 1 != end())
				{
					std::memcpy(&(*it), &(*(it + 1)), sizeof(value_type));
					it++;
				}
				__finish--;
				return __pos;
			}
			iterator erase(iterator first, iterator last)
			{
				if (empty())
					return end();
				iterator it = begin();
				iterator res = first;
				difference_type dist = last - first;
				while (it != first)
					it++;
				while (first != last)
				{
					__alloc.destroy(&(*first));
					first++;
				}
				while (it + dist != end())
				{
					std::memcpy(&(*it), &(*(it + dist)), sizeof(value_type));
					it++;
				}
				__finish -= dist;
				return res;
			}
			void push_back(const value_type& __v)
			{
				if (__finish == __end_of_capacity)
				{
					if (empty())
						reserve(1);
					else
						reserve(size() * 2);
				}
				__alloc.construct(__start + size(), __v);
				__finish++;
			}
			void pop_back()
			{
				if (__finish > __start)
				{
					__alloc.destroy(__finish - 1);
					__finish--;
				}
			}
			void resize(size_type __n, value_type __v = value_type())
			{
				if (__n > capacity())
					reserve(__n);
				if (__n >= size())
				{
					for (size_type i = size(); i < __n; i++)
						__alloc.construct(__start + i, __v);
				}
				else
				{
					for (size_type i = __n; i < size(); i++)
						__alloc.destroy(__start + i);
				}
				__finish = __start + __n;
			}
			void swap(vector& __v)
			{
				allocator_type	tmp_alloc = __alloc;
				pointer			tmp_start = __start;
				pointer			tmp_finish = __finish;
				pointer			tmp_end_of_capacity = __end_of_capacity;

				__alloc = __v.__alloc;
				__start = __v.__start;
				__finish = __v.__finish;
				__end_of_capacity = __v.__end_of_capacity;

				__v.__alloc = tmp_alloc;
				__v.__start = tmp_start;
				__v.__finish = tmp_finish;
				__v.__end_of_capacity = tmp_end_of_capacity;
			}
	};

	/* non-member function */
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return !(lhs == rhs);}
	template <class T, class Alloc>
	bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return !(lhs > rhs);}
	template <class T, class Alloc>
	bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return rhs < lhs;}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{return !(lhs < rhs);}

	template <class T, class Alloc>
	void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
		{lhs.swap(rhs);}

} // namespace ft


#endif
