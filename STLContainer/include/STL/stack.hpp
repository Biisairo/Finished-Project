#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		/* member type */
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

		/* member val */
		protected:
			container_type						c;

		/* member function */
		public:
			// constructor
			explicit stack(const container_type &cont = container_type()) : c(cont) {}

			// copy
			stack(const stack& __s) : c(__s.c) {}

			// destructor
			~stack() {}

			// operator =
			stack& operator=(const stack& __s)
				{c = __s.c; return (*this);}

			/* element eccess */
			reference top()
				{return c.back();}
			const_reference top() const
				{return c.back();}

			/* capacity */
			bool empty()
				{return c.empty();}
			size_type size()
				{return c.size();}

			/* modifier */
			void push(const value_type& __v)
				{c.push_back(__v);}
			void pop()
				{c.pop_back();}

		/* non-member function */
		friend bool operator==(const stack& lhs, const stack& rhs)
			{return (lhs.c == rhs.c);}
		friend bool operator!=(const stack& lhs, const stack& rhs)
			{return !(lhs == rhs);}
		friend bool operator<(const stack& lhs, const stack& rhs)
			{return (lhs.c < rhs.c);}
		friend bool operator<=(const stack& lhs, const stack& rhs)
			{return (lhs.c <= rhs.c);}
		friend bool operator>(const stack& lhs, const stack& rhs)
			{return (lhs.c > rhs.c);}
		friend bool operator>=(const stack& lhs, const stack& rhs)
			{return (lhs.c >= rhs.c);}
	};

}


#endif
