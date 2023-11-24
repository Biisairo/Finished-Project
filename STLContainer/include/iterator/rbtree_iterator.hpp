#ifndef rbtREE_ITERATOR_HPP
#define rbtREE_ITERATOR_HPP

#include "pair.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template <typename T>
	struct Node
	{
		typedef T	value_type;

		Node*		left;
		Node*		right;
		Node*		parent;
		value_type	value;
		bool		isBlack;

		Node() : left(0), right(0), parent(0), value(value_type()), isBlack(bool()) {}
		Node(const value_type& value) : left(0), right(0), parent(0), value(value), isBlack(bool()) {}
		Node(const Node& node) : left(node.left), right(node.right), parent(node.parent), value(node.value), isBlack(node.isBlack) {}
		~Node() {}

		Node& operator=(const Node& node)
		{
			if (this != *node)
			{
				left = node.left;
				right = node.right;
				parent = node.parent;
				value = node.value;
				isBlack = node.isBlack;
			}
			return *this;
		}
	};

	template <typename N>
	bool isLeftChild(const N& node)
		{return (node == node->parent->left);}
	template <typename N>
	bool isRightChild(const N& node)
		{return (node == node->parent->right);}
	template <typename N>
	bool isBlack(const N& node)
		{return (node->isBlack);}
	template <typename N>
	bool isRed(const N& node)
		{return (!node->isBlack);}
	template <typename N>
	N getMinimum(N node, N nil)
	{
		while (node->left != nil)
			node = node->left;
		return (node);
	}
	template <typename N>
	N getMaximum(N node, N nil)
	{
		while (node->right != nil)
			node = node->right;
		return (node);
	}
	template <typename N>
	N getNextNode(N node, N nil)
	{
		if (node->right != nil)
			return (getMinimum(node->right, nil));
		while (!isLeftChild(node))
			node = node->parent;
		return (node->parent);
	}
	template <typename N>
	N getPreNode(N node, N nil)
	{
		if (node->left != nil)
			return (getMaximum(node->left, nil));
		while (!isRightChild(node))
			node = node->parent;
		return (node->parent);
	}
	template <typename U, typename V, class Comp>
	bool isEqual(const U& u, const V& v, Comp comp)
		{return (!comp(u, v) && !comp(v, u));}

	template <typename U, typename V>
	class rbtree_iterator
	{
		public:
			typedef U															value_type;
			typedef value_type*													pointer;
			typedef value_type&													reference;
			typedef V* 															iterator_type;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename iterator_traits<iterator_type>::value_type			node_type;
			typedef typename iterator_traits<iterator_type>::pointer			node_pointer;
			typedef typename iterator_traits<iterator_type>::reference			node_reference;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

		private:
			node_pointer __cur;
			node_pointer __nill;

		public:
			rbtree_iterator() : __cur(0), __nill(0) {}
			rbtree_iterator(node_pointer cur, node_pointer nill) : __cur(cur), __nill(nill) {}
			rbtree_iterator(const rbtree_iterator& it) : __cur(it.__cur) , __nill(it.__nill) {}
			~rbtree_iterator() {}

			rbtree_iterator& operator=(const rbtree_iterator& it)
			{
				if (this != &it)
				{
					__cur = it.__cur;
					__nill = it.__nill;
				}
				return *this;
			}

			node_pointer		base() const {return __cur;}
			reference			operator*() const {return __cur->value;}
			pointer				operator->() const {return &(operator*());}

			rbtree_iterator&	operator++()
			{
				__cur = getNextNode(__cur, __nill);
				return *this;
			}
			rbtree_iterator		operator++(int)
			{
				rbtree_iterator _tmp(*this);
				++(*this);
				return _tmp;
			}
			rbtree_iterator&	operator--()
			{
				__cur = getPreNode(__cur, __nill);
				return *this;
			}
			rbtree_iterator		operator--(int)
			{
				rbtree_iterator _tmp(*this);
				--(*this);
				return _tmp;
			}
			template <typename T>
			bool operator==(const rbtree_iterator<T, node_type>&__x) const
				{return (__cur == __x.base());}
			template <typename T>
			bool operator!=(const rbtree_iterator<T, node_type>&__x) const
				{return !(*this == __x);}
			operator rbtree_iterator<const value_type, node_type>() const
				{return rbtree_iterator<const value_type, node_type>(__cur, __nill);}

			friend bool operator==(const rbtree_iterator& lhs, const rbtree_iterator& rhs)
				{return (lhs.__cur == rhs.__cur);}
			friend bool operator!=(const rbtree_iterator& lhs, const rbtree_iterator& rhs)
				{return (!(lhs == rhs));}
	};

template <typename T, class Key, class Comp, class Alloc>
	class rbtree
	{
		public:
			typedef T															value_type;
			typedef Key															key_type;
			typedef Comp														compare_type;
			typedef Node<value_type>											node_type;
			typedef Node<value_type>*											node_pointer;
			typedef rbtree_iterator<value_type, node_type>						iterator;
			typedef rbtree_iterator<const value_type, node_type>				const_iterator;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
			typedef std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;

		protected:
			node_pointer	__nill;
			node_pointer	__begin;
			node_pointer	__end;
			compare_type	__comp;
			node_allocator	__alloc;
			size_type		__size;


		public:
			// constructor
			rbtree(const compare_type& comp, const allocator_type& alloc) : __comp(comp), __alloc(alloc), __size(size_type())
			{
				__nill = __alloc.allocate(1);
				__alloc.construct(__nill, value_type());
				__nill->isBlack = true;
				__nill->parent = __nill;
				__nill->left = __nill;
				__nill->right = __nill;
				__end = createNode(value_type());
				__end->isBlack = true;
				__begin = __end;
			}
			// destructor
			~rbtree()
			{
				deleteAll(__end);
				deleteNode(__nill);
			}
			// copy
			rbtree(const rbtree& tree) : __comp(tree.__comp), __alloc(tree.__alloc), __size(size_type())
			{
				__nill = __alloc.allocate(1);
				__alloc.construct(__nill, value_type());
				__nill->isBlack = true;
				__nill->parent = __nill;
				__nill->left = __nill;
				__nill->right = __nill;
				__end = createNode(value_type());
				__end->isBlack = true;
				__begin = __end;
				insert(tree.begin(), tree.end());
			}
			// operator=
			rbtree& operator=(const rbtree& tree)
			{
				if (this != &tree)
				{
					rbtree tmp(tree);
					swap(tmp);
				}
				return *this;
			}
			//get allocator
			allocator_type get_allocator() const
				{return __alloc;}

			/* iterator */
			iterator begin()
				{return iterator(const_cast<node_pointer>(__begin), __nill);}
			iterator end()
				{return iterator(const_cast<node_pointer>(__end), __nill);}
			const_iterator begin() const
				{return const_iterator(__begin, __nill);}
			const_iterator end() const
				{return const_iterator(__end, __nill);}

			/* capacity */
			bool empty() const
				{return __size == 0;}
			size_type size() const
				{return __size;}
			size_type max_size() const
				{return __alloc.max_size();}

			/* modifier */
			ft::pair<iterator, bool> insert(const value_type& value)
			{
				node_pointer node = searchParent(value);

				// 같은 key 를 가진 노드가 존재하면 false
				if (node != __end && isEqual(node->value, value, __comp))
					return ft::make_pair(iterator(node, __nill), false);
				// 성공하면 true 를 반환
				return ft::make_pair(iterator(insertFunc(value, node), __nill), true);
			}
			iterator insert(iterator __pos, const value_type& value)
			{
				node_pointer node = searchParent(value, __pos.base());
				if (node != __end && isEqual(node->value, value, __comp))
					return (iterator(node, __nill));
				return iterator(insertFunc(value, node), __nill);
			}
			template <class InputIt>
			void insert(InputIt first, InputIt last)
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}
			iterator erase(iterator __pos)
			{
				if (__size == 0)
					return iterator(__nill, __nill);
				iterator tmp(__pos);
				tmp++;
				if (__pos == begin())
					__begin = tmp.base();
				__size--;
				removeFunc(__pos.base());
				deleteNode(__pos.base());
				return tmp;
			}
			size_type erase(const key_type& value)
			{
				iterator __tmp(findFunc(value), __nill);
				if (__tmp == end())
					return 0;
				if (__tmp == begin())
				{
					iterator tmp(__tmp);
					tmp++;
					__begin = tmp.base();
				}
				__size--;
				removeFunc(__tmp.base());
				deleteNode(__tmp.base());
				return 1;
			}
			iterator erase(iterator first, iterator last)
			{
				while (first != last)
					first = erase(first);
				return first;
			}
			void swap(rbtree& tree)
			{
				node_pointer	tmp_nill = __nill;
				node_pointer	tmp_begin = __begin;
				node_pointer	tmp_end = __end;
				compare_type	tmp_comp = __comp;
				node_allocator	tmp_alloc = __alloc;
				size_type		tmp_size = __size;

				__nill = tree.__nill;
				__begin = tree.__begin;
				__end = tree.__end;
				__comp = tree.__comp;
				__alloc = tree.__alloc;
				__size = tree.__size;

				tree.__nill = tmp_nill;
				tree.__begin = tmp_begin;
				tree.__end = tmp_end;
				tree.__comp = tmp_comp;
				tree.__alloc = tmp_alloc;
				tree.__size = tmp_size;
			}
			void clear()
			{
				rbtree tmp(__comp, __alloc);
				swap(tmp);
			}

			/* lookup */
			iterator find(const key_type& key)
				{return iterator(findFunc(key), __nill);}
			const_iterator find(const key_type& key) const
				{return iterator(findFunc(key), __nill);}
			iterator lower_bound(const Key& key)
				{return iterator(lower_boundFunc(key), __nill);}
			const_iterator lower_bound(const Key& key) const
				{return iterator(lower_boundFunc(key), __nill);}
			iterator upper_bound(const Key& key)
				{return iterator(upper_boundFunc(key), __nill);}
			const_iterator upper_bound(const Key& key) const
				{return iterator(upper_boundFunc(key), __nill);}
			ft::pair<iterator, iterator> equal_range(const Key& key)
				{return (ft::make_pair(lower_bound(key), upper_bound(key)));}
			ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
				{return (ft::make_pair(lower_bound(key), upper_bound(key)));}

			/* impliment function */
			private:
				node_pointer getRoot() const
					{return __end->left;}
				void setRoot(const node_pointer node)
				{
					node->parent = __end;
					__end->left = node;
				}
				node_pointer createNode(const value_type& value)
				{
					node_pointer node = __alloc.allocate(1);
					__alloc.construct(node, value);
					node->left = __nill;
					node->right = __nill;
					node->parent = __nill;
					node->isBlack = false;
					return node;
				}
				void deleteNode(node_pointer node)
				{
					__alloc.destroy(node);
					__alloc.deallocate(node, 1);
				}
				void deleteAll(node_pointer node)
				{
					if (node == __nill)
						return ;
					deleteAll(node->left);
					deleteAll(node->right);
					deleteNode(node);
				}
				node_pointer searchParent(const value_type& value, node_pointer __pos = 0)
				{
					if (__pos && __pos != __end)
					{
						if (__comp(value, __pos->value) && __pos->left == __nill)
						{
							iterator pre = iterator(__pos, __nill);
							if (pre == begin() || __comp(*--pre, value))
								return __pos;
						}
						else if (__pos->right == __nill)
						{
							iterator next = iterator(__pos, __nill);
							if (next == end() || __comp(value, *++next))
								return __pos;
						}
					}
					node_pointer cur = getRoot();
					node_pointer tmp = __end;
					while (cur != __nill)
					{
						tmp = cur;
						if (__comp(value, cur->value))
							cur = cur->left;
						else if (__comp(cur->value, value))
							cur = cur->right;
						else
							return cur;
					}
					return tmp;
				}
				node_pointer insertFunc(const value_type& value, node_pointer parent)
				{
					// 부모 찾기(넣을 위치 찾기)
					node_pointer node = createNode(value);

					// 부모가 없는경우
					if (parent == __end)
						setRoot(node);
					// value < parent->value
					else if (__comp(value, parent->value))
						parent->left = node;
					// parent->value < value
					else
						parent->right = node;
					node->parent = parent;
					// fixup
					insertFixUp(node);
					// root 를 추가했거나, 최소값을 추가한 경우
					if (__begin == __end || __comp(node->value, __begin->value))
						__begin = node;
					__size++;
					return node;
				}
				void insertFixUp(node_pointer node)
				{
					node_pointer uncle;
					// 부모가 red
					while (isRed(node->parent))
					{
						// node 가 부모의 right
						if (isRightChild(node->parent))
						{
							uncle = node->parent->parent->left;
							// case 3.1
							// 부모와 삼촌이 red
							if (isRed(uncle))
							{
								node->parent->isBlack = true;
								uncle->isBlack = true;
								uncle->parent->isBlack = false;
								node = uncle->parent;
							}
							// case 3.2
							// 부모는 red 삼촌은 black
							else
							{
								// case 3.2.2
								// 조상-부모-나 r-r-l
								if (isLeftChild(node))
								{
									node = node->parent;
									rightRotation(node);
								}
								// case 3.2.1
								// 조상-부모-나 r-r-r
								node->parent->isBlack = true;
								node->parent->parent->isBlack = false;
								leftRotation(node->parent->parent);
							}
						}
						// 부모가 left child
						else
						{
							uncle = node->parent->parent->right;
							// case 3.1
							// 부모와 삼촌이 red
							if (isRed(uncle))
							{
								node->parent->isBlack = true;
								uncle->isBlack = true;
								uncle->parent->isBlack = false;
								node = uncle->parent;
							}
							// case 3.2
							// 부모는 red 삼촌은 black
							else
							{
								// case 3.2.2
								// 조상-부모-나 l-l-r
								if (isRightChild(node))
								{
									node = node->parent;
									leftRotation(node);
								}
								// case 3.2.1
								// 조상-부모-나 l-l-l
								node->parent->isBlack = true;
								node->parent->parent->isBlack = false;
								rightRotation(node->parent->parent);
							}
						}
					}
					// root 는 무조건 black
					getRoot()->isBlack = true;
				}
				void removeFunc(node_pointer node)
				{
					node_pointer fixup_node;
					node_pointer del_node = node;
					bool origin_color = isBlack(node);

					// 자식이 right 하나
					if (node->left == __nill)
					{
						fixup_node = node->right;
						transplant(node, node->right);
					}
					// 자식이 left 하나
					else if (node->right == __nill)
					{
						fixup_node = node->left;
						transplant(node, node->left);
					}
					// 자식이 둘 혹은 0
					else
					{
						// successor 찾기
						del_node = getMinimum(node->right, __nill);
						// 삭제될 색은 successor 의 색
						origin_color = isBlack(del_node);
						fixup_node = del_node->right;
						// 삭제될 노드가 node 의 자식
						if (del_node->parent == node)
							fixup_node->parent = del_node;
						// 삭제될 노드가 node 의 손자 이상
						else
						{
							transplant(del_node, del_node->right);
							del_node->right = node->right;
							del_node->right->parent = del_node;
						}
						// del_node 를 node 위치에 이식
						transplant(node, del_node);
						del_node->left = node->left;
						del_node->left->parent = del_node;
						del_node->isBlack = isBlack(node);
					}
					// 삭제될 색이 black 인 경우 fixup 실시
					if (origin_color)
						removeFixUp(fixup_node);
				}
				void removeFixUp(node_pointer node)
				{
					node_pointer sibiling;
					while (node != getRoot() && isBlack(node))
					{
						// node 가 left child
						if (isLeftChild(node))
						{
							sibiling = node->parent->right;
							// case 3.1
							// 형제가 red
							if (isRed(sibiling)) {
								sibiling->isBlack = true;
								node->parent->isBlack = false;
								leftRotation(node->parent);
								sibiling = node->parent->right;
							}
							// case 3.2
							// 형제가 black, 형제의 두 자식도 black
							if (isBlack(sibiling->left) && isBlack(sibiling->right)) {
								sibiling->isBlack = false;
								node = node->parent;
							// case 3.3
							// 형제가 black, 형제의 왼쪽자식(꺾인 자식)이 red
							} else if (isBlack(sibiling->right)) {
								sibiling->left->isBlack = true;
								sibiling->isBlack = false;
								rightRotation(sibiling);
								sibiling = node->parent->right;
							}
							// case 3.4
							// 형제가 black, 형제의 오른쪽자식(펴진 자식)이 red
							if (isRed(sibiling->right)) {
								sibiling->isBlack = isBlack(node->parent);
								node->parent->isBlack = true;
								sibiling->right->isBlack = true;
								leftRotation(node->parent);
								node = getRoot();
							}
						}
						// node 가 right child
						else
						{
							sibiling = node->parent->left;
							// case 3.1
							// 형제가 red
							if (isRed(sibiling)) {
								sibiling->isBlack = true;
								node->parent->isBlack = false;
								rightRotation(node->parent);
								sibiling = node->parent->left;
							}
							// case 3.2
							// 형제가 black, 형제의 두 자식도 black
							if (isBlack(sibiling->right) && isBlack(sibiling->left)) {
								sibiling->isBlack = false;
								node = node->parent;
							// case 3.3
							// 형제가 black, 형제의 오른쪽자식(꺾인 자식)이 red
							} else if (isBlack(sibiling->left)) {
								sibiling->right->isBlack = true;
								sibiling->isBlack = false;
								leftRotation(sibiling);
								sibiling = node->parent->left;
							}
							// case 3.4
							// 형제가 black, 형제의 왼쪽자식(펴진 자식)이 red
							if (isRed(sibiling->left)) {
								sibiling->isBlack = isBlack(node->parent);
								node->parent->isBlack = true;
								sibiling->left->isBlack = true;
								rightRotation(node->parent);
								node = getRoot();
							}
						}
					}
					// fixup node 는 검정
					node->isBlack = true;
					// root 는 black
					getRoot()->isBlack = true;
				}
				node_pointer findFunc(const key_type& value) const
				{
					node_pointer node = getRoot();
					while (node != __nill)
					{
						if (__comp(value, node->value))
							node = node->left;
						else if (__comp(node->value, value))
							node = node->right;
						else
							return node;
					}
					return __end;
				}
				node_pointer lower_boundFunc(const key_type& value) const
				{
					node_pointer node = getRoot();
					node_pointer tmp = __end;
					while (node != __nill)
					{
						if (!__comp(node->value, value))
						{
							tmp = node;
							node = node->left;
						}
						else
							node = node->right;
					}
					return tmp;
				}
				node_pointer upper_boundFunc(const key_type& value) const
				{
					node_pointer node = getRoot();
					node_pointer tmp = __end;
					while (node != __nill)
					{
						if (__comp(value, node->value))
						{
							tmp = node;
							node = node->left;
						}
						else
							node = node->right;
					}
					return tmp;
				}
				/* utils */
				// rotate left(counterclockwise)
				// node 에는 내려갈 node 를 넣기
				// node->right 가 위로 올라감
				void leftRotation(node_pointer node)
				{
					node_pointer child = node->right;

					node->right = child->left;
					if (child->left != this->__nill)
						child->left->parent = node;
					child->parent = node->parent;
					if (node->parent == 0)
						setRoot(child);
					else if (node == node->parent->left)
						node->parent->left = child;
					else
						node->parent->right = child;

					node->parent = child;
					child->left = node;
				}

				// rotate right(clockwise)
				// node 에는 내려갈 node 를 넣기
				// node->left 가 위로 올라감
				void rightRotation(node_pointer node)
				{
					node_pointer child = node->left;

					node->left = child->right;
					if (child->right != this->__nill)
						child->right->parent = node;
					child->parent = node->parent;
					if (node->parent == 0)
						setRoot(child);
					else if (node == node->parent->right)
						node->parent->right = child;
					else
						node->parent->left = child;

					node->parent = child;
					child->right = node;
				}

				void transplant(node_pointer pos, node_pointer node)
				{
					if (pos->parent == __end)
						setRoot(node);
					else if (isLeftChild(pos))
						pos->parent->left = node;
					else
						pos->parent->right = node;
					node->parent = pos->parent;
				}
	};
}

#endif
