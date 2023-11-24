#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
		/* Member type */
		public:
			typedef T																		iterator_type;
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename iterator<random_access_iterator_tag, T>::value_type			value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename iterator<random_access_iterator_tag, T>::pointer				pointer;
			typedef typename iterator<random_access_iterator_tag, T>::reference				reference;

		protected:
			pointer __ptr;

		/* Member function */
		public:
								// constructor
								random_access_iterator() : __ptr(pointer()) {}
								explicit random_access_iterator(pointer __x) : __ptr(__x) {}
								template <typename U>
								random_access_iterator(const random_access_iterator<U>& __u) : __ptr(__u.base()) {}

								// operator =
		template <class U>
		random_access_iterator&	operator=(const random_access_iterator<U>& __u)
		{
			if (__ptr != __u.base())
				__ptr = __u.base();
			return *this;
		}

								// distructor
		virtual					~random_access_iterator() {}

								// get base
		pointer					base() const {return (__ptr);}

								// operator overloading
		reference				operator*() const {return *__ptr;}
		pointer					operator->() const {return &(operator*());}
		reference				operator[](difference_type __n) const {return *(__ptr + __n);}
		random_access_iterator	operator+ (difference_type __n) const {return random_access_iterator(__ptr + __n);}
		random_access_iterator	operator- (difference_type __n) const {return random_access_iterator(__ptr - __n);}
		random_access_iterator&	operator++() {++__ptr; return *this;}
		random_access_iterator	operator++(int) {random_access_iterator _tmp(*this); ++__ptr; return _tmp;}
		random_access_iterator&	operator--() {--__ptr; return *this;}
		random_access_iterator	operator--(int) {random_access_iterator _tmp(*this); --__ptr; return _tmp;}
		random_access_iterator&	operator+=(difference_type __n) {__ptr += __n; return *this;}
		random_access_iterator&	operator-=(difference_type __n) {__ptr -= __n; return *this;}
	};

	/* Non-member function */
	template <class Iter1, class Iter2>
	bool operator==(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
		{return lhs.base() == rhs.base();}
	template <class Iter1, class Iter2>
	bool operator!=(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
		{return lhs.base() != rhs.base();}
	template <class Iter1, class Iter2>
	bool operator<(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
		{return lhs.base() < rhs.base();}
	template <class Iter1, class Iter2>
	bool operator>(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
		{return lhs.base() > rhs.base();}
	template <class Iter1, class Iter2>
	bool operator<=(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
		{return lhs.base() <= rhs.base();}
	template <class Iter1, class Iter2>
	bool operator>=(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
		{return lhs.base() >= rhs.base();}

	template <class Iter>
	random_access_iterator<Iter> operator+(typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it)
		{return random_access_iterator<Iter>(it.base() + n);}
	template<class Iterator1, class Iterator2>
	typename random_access_iterator<Iterator1>::difference_type operator-(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
		{return lhs.base() - rhs.base();}
}

#endif
