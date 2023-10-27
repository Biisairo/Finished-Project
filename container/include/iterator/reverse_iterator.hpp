#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
		/* Member type */
		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;

		protected:
			iterator_type current;

		/* Member function */

		public:

							// constructor
							reverse_iterator() : current(iterator_type()) {}
							explicit reverse_iterator(iterator_type __x) : current(__x) {}
							template <class U>
							reverse_iterator(const reverse_iterator<U>& __u) : current(__u.base()) {}

							// operator =
		template <class U>
		reverse_iterator&	operator=(const reverse_iterator<U>& __u)
		{
			if (current != __u.base())
				current = __u.base();
			return *this;
		}

							//distructor
		virtual				~reverse_iterator() {}

							// get base
		iterator_type		base() const {return current;}

							// operator overloading
		reference			operator*() const {iterator_type tmp(current); return *--tmp;}
		pointer				operator->() const {return &(operator*());}
		reference			operator[](difference_type __n) const {return *(*this + __n);}
		reverse_iterator	operator+ (difference_type __n) const {return reverse_iterator(current - __n);}
		reverse_iterator	operator- (difference_type __n) const {return reverse_iterator(current + __n);}
		reverse_iterator&	operator++() {--current; return *this;}
		reverse_iterator	operator++(int) {reverse_iterator __tmp(*this); --current; return __tmp;}
		reverse_iterator&	operator--() {++current; return *this;}
		reverse_iterator	operator--(int) {reverse_iterator __tmp(*this); ++current; return __tmp;}
		reverse_iterator&	operator+=(difference_type __n) {current -= __n; return *this;}
		reverse_iterator&	operator-=(difference_type __n) {current += __n; return *this;}
	};

	/* Non-member function */
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return lhs.base() == rhs.base();}
	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return lhs.base() != rhs.base();}
	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return lhs.base() > rhs.base();}
	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return lhs.base() < rhs.base();}
	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return lhs.base() >= rhs.base();}
	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return lhs.base() <= rhs.base();}

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
		{return reverse_iterator<Iter>(it.base() - n);}
	template<class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{return rhs.base() - lhs.base();}
}

#endif
