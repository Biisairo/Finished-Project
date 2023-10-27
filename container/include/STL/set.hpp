#ifndef SET_HPP
#define SET_HPP

#include <memory>
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "rbtree_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{
	template <class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set
	{

		public:
			typedef Key																							key_type;
			typedef Key																							value_type;
			typedef std::size_t																					size_type;
			typedef std::ptrdiff_t																				difference_type;
			typedef Compare																						key_compare;
			typedef Compare																						value_compare;
			typedef Alloc																						allocator_type;
			typedef typename Alloc::pointer 																	pointer;
			typedef typename Alloc::const_pointer																const_pointer;
			typedef typename ft::rbtree<value_type, key_type, value_compare, allocator_type>::iterator			iterator;
			typedef typename ft::rbtree<value_type, key_type, value_compare, allocator_type>::const_iterator	const_iterator;
			typedef value_type&																					reference;
			typedef const value_type&																			const_reference;
			typedef ft::reverse_iterator<iterator>																reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>														const_reverse_iterator;

		private:
			key_compare														__key;
			value_compare													__value;
			ft::rbtree<value_type, key_type, value_compare, allocator_type>	__tree;



			/* member function */
		public:
			// constructor
			explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : __key(comp), __value(comp), __tree(__value, alloc) {}
			template <class InputIt>
			set(InputIt first, InputIt last, const key_compare& comp = key_compare(), const Alloc& alloc = allocator_type()) :  __key(comp), __value(comp), __tree(__value, alloc)
				{insert(first, last);}

			// copy
			set(const set& __m) : __key(__m.__key), __value(__m.__value), __tree(__m.__tree) {}

			// destructor
			~set() {}

			//operator =
			set& operator=(const set& __m)
			{
				if (this != &__m)
				{
					__key = __m.__key;
					__value = __m.__value;
					__tree = __m.__tree;
				}
				return *this;
			}

			// get_allocator
			allocator_type get_allocator() const;

			/* iterator */
			iterator begin()
				{return __tree.begin();}
			const_iterator begin() const
				{return __tree.begin();}
			iterator end()
				{return __tree.end();}
			const_iterator end() const
				{return __tree.end();}
			reverse_iterator rbegin()
				{return reverse_iterator(end());}
			const_reverse_iterator rbegin() const
				{return reverse_iterator(end());}
			reverse_iterator rend()
				{return reverse_iterator(begin());}
			const_reverse_iterator rend() const
				{return reverse_iterator(begin());}

			/* capacity */
			bool empty() const
				{return __tree.empty();}
			size_type size() const
				{return __tree.size();}
			size_type max_size() const
				{return __tree.max_size();}

			/* modifier */
			void clear()
				{__tree.clear();}
			ft::pair<iterator, bool> insert(const value_type& value)
				{return __tree.insert(value);}
			iterator insert(iterator __pos, const value_type& value)
				{return __tree.insert(__pos, value);}
			template<class InputIt>
			void insert(InputIt first, InputIt last)
				{__tree.insert(first, last);}
			iterator erase(iterator __pos)
				{return __tree.erase(__pos);}
			iterator erase(iterator first, iterator last)
				{return __tree.erase(first, last);}
			size_type erase(const Key& key)
				{return __tree.erase(key);}
			void swap(set& __m)
				{__tree.swap(__m.__tree);}

			/* lookup */
			size_type count(const Key& key) const
				{return !(find(key) == end());}
			iterator find(const Key& key)
				{return __tree.find(key);}
			const_iterator find(const Key& key) const
				{return __tree.find(key);}
			ft::pair<iterator, iterator> equal_range(const Key& key)
				{return __tree.equal_range(key);}
			ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
				{return __tree.equal_range(key);}
			iterator lower_bound(const Key& key)
				{return __tree.lower_bound(key);}
			const_iterator lower_bound(const Key& key) const
				{return __tree.lower_bound(key);}
			iterator upper_bound(const Key& key)
				{return __tree.upper_bound(key);}
			const_iterator upper_bound(const Key& key) const
				{return __tree.upper_bound(key);}

			/* observers */
			key_compare key_comp() const
				{return __key;}
			value_compare value_comp() const
				{return __value;}
	};

	/* non-member function */
	template <class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
		{return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));}
	template <class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
		{return (!(lhs == rhs));}
	template <class Key, class Compare, class Alloc>
	bool operator< (const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
		{return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
	template <class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
		{return (!(rhs < lhs));}
	template <class Key, class Compare, class Alloc>
	bool operator> (const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
		{return (rhs < lhs);}
	template <class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
		{return (!(lhs < rhs));}

	template <class Key, class Compare, class Alloc>
	void swap(set<Key, Compare, Alloc>& lhs, set<Key, Compare, Alloc>& rhs)
		{lhs.swap(rhs);}
}

#endif
