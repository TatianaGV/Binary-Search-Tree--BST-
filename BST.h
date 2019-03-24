#pragma once
#ifndef BST_H
#define BST_H
#include<iostream>
#include<iterator>
#include<stack>
#include<set>
#include<queue>


template <typename T>
class BST
{
	struct TreeNode
	{
		T data;
		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;

		TreeNode(T d, TreeNode* p, TreeNode* l, TreeNode* r) : data(d), parent(p), left(l), right(r) {}
	};

	TreeNode* root;

	class iterator : std::iterator<std::bidirectional_iterator_tag, T>
	{
		TreeNode* data;
		bool last = false;

	public:
		iterator(TreeNode* d, bool lst = false) : data(d), last(lst) {}

		TreeNode* operator*()
		{
			if (!last) return data;
			return nullptr;
		}

		friend bool operator==(const iterator& it1, const iterator& it2)
		{
			return (it1.data == it2.data && it1.last == it2.last) || (it1.last && it2.last);
		}

		friend bool operator!=(const iterator& it1, const iterator& it2)
		{
			return !(it1 == it2);
		}

		iterator operator++()
		{
			if (last)
				throw std::out_of_range("Imposible apply operator++ to end() iterator!");
			if (data == nullptr) return iterator(nullptr, false);
			TreeNode* it = data;
			if (it->right)
			{
				it = it->right;
				while (it->left) it = it->left;
				data = it;
				last = false;
				return (*this);
			}
			if (it->parent)
			{
				TreeNode* tmp = new TreeNode(it->data, it, nullptr, nullptr);
				while (it->parent && it->parent->left != it) it = it->parent;
				if (it->parent) it = it->parent;
				else
				{
					data = tmp;
					last = true;
					return (*this);
				}
				data = it;
				last = false;
				return (*this);
			}
		}

		iterator operator--()
		{
			TreeNode* it = data;
			if (last)
			{
				while (data->right) data = data->right;
				last = false;
				return *this;
			}
			if (!it->parent) throw std::out_of_range("Imposible apply operator-- to begin() iterator!");
			if (it->left)
			{
				it = it->left;
				while (it->right) it = it->right;
				data = it;
				last = false;
				return (*this);
			}
			if (it->parent)
			{
				if (last)
				{
					data = it;
					last = false;
					return (*this);
				}
				while (it->parent && it->parent->right != it) it = it->parent;
				if (it->parent) it = it->parent;
				else
				{
					data = nullptr;
					last = false;
					return (*this);
				}
				data = it;
				last = false;
				return (*this);
			}
		}

		iterator prev()
		{
			iterator it(data, last);
			return --it;
		}

		iterator next()
		{
			iterator it(data, last);
			return ++it;
		}
	};

	void print_LRR_help(TreeNode* root)
	{
		if (root)
		{
			print_LRR_help(root->left);
			std::cout << root->data << " ";
			print_LRR_help(root->right);
		}
	}

	bool equalNodes(TreeNode* r1, TreeNode* r2)
	{
		if (r1 && r2)
		{
			if (r1->parent == nullptr && r2->parent == nullptr || r1->parent && r2->parent && r1->parent->data == r2->parent->data)
			if (r1->left == nullptr && r2->left == nullptr || r1->left && r2->left && r1->left->data == r2->left->data)
			if (r1->right == nullptr && r2->right == nullptr || r1->right && r2->right && r1->right->data == r2->right->data)
				return true;
		}
		return false;
	}

	bool isEqual_help(TreeNode* root1, TreeNode* root2)
	{
		if (root1 == nullptr && root2 == nullptr) return true;
		if (equalNodes(root1, root2))
		{
			return isEqual_help(root1->left, root2->left) && isEqual_help(root1->right, root2->right);
		}
		return false;
	}

	void levelPrint(TreeNode* root)
	{
		if (root == nullptr) return;
		std::queue<TreeNode *> q;
		q.push(root);
		while (!q.empty())
		{
			TreeNode* tmp = q.front();
			q.pop();
			std::cout << tmp->data << " ";
			if (tmp->left != nullptr)
				q.push(tmp->left);
			if (tmp->right != nullptr)
				q.push(tmp->right);
		}
	}

	//for destructor
	void deleteTree(TreeNode* root)
	{
		if (root)
		{
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}
	}

public:
	BST(): root(nullptr) {}

	BST(T elem) { root = new TreeNode(elem, nullptr, nullptr, nullptr); }

	//Добавление элемента
	void Add(T elem)
	{
		TreeNode* tmp = new TreeNode(elem, nullptr, nullptr, nullptr);
		TreeNode* parent = nullptr;
		if (!root) root = tmp;
		else
		{
			TreeNode* current;
			current = root;
			while (current)
			{
				parent = current;
				if (tmp->data > current->data) current = current->right;
				else current = current->left;
			}
			if (tmp->data > parent->data) parent->right = tmp;
			else parent->left = tmp;
			tmp->parent = parent;
		}
	}

	//Инфиксный вывод дерева
	void printLRR() { print_LRR_help(root); }

	//Поиск минимального элемента
	iterator MinElem()
	{
		TreeNode* curr = root;
		while (curr->left) curr = curr->left;
		return iterator(curr, false);
	}

	//Поиск максимального элемента
	iterator MaxElem()
	{
		TreeNode* curr = root;
		while (curr->right) curr = curr->right;
		return iterator(curr, false);
	}

	iterator begin() { return MinElem(); }

	iterator end() { return iterator(root, true); }

	//Поиск элемента
	iterator Find(T elem)
	{
		if (!root) return end();
		TreeNode* curr = root;
		while (curr)
		{
			if (curr->data > elem) curr = curr->left;
			else if (curr->data < elem) curr = curr->right;
			else return iterator(curr, false);
		}
		return end();
	}

	//Поиск первого элемента, больше заданного
	iterator upperBound(T x)
	{
		TreeNode* tmp = nullptr;
		TreeNode* curr = root;
		while (curr)
		{
			if (x > curr->data)
				curr = curr->right;
			else if (x < curr->data)
			{
				tmp = curr;
				curr = curr->left;
			}
			else
			{
				tmp = curr;
				curr = nullptr;
			}
		}
		if (tmp) return iterator(tmp, false);
		return end();
	}

	//Поиск первого элемента, меньше заданного
	iterator lowerBound(T x)
	{
		TreeNode* tmp = nullptr;
		TreeNode* curr = root;
		while (curr)
		{
			if (x < curr->data)
				curr = curr->left;
			else if (x > curr->data)
			{
				tmp = curr;
				curr = curr->right;
			}
			else
			{
				tmp = curr;
				curr = nullptr;
			}
		}
		if (tmp) return iterator(tmp, false);
		return end();
	}

	//Удаление элемента
	void Remove(T elem)
	{
		TreeNode* curr;
		curr = *(Find(elem));
		if (Find(elem) == end()) return;
		TreeNode* parent = curr->parent;

		// Node with single child
		if ((curr->left == nullptr && curr->right != nullptr) || (curr->left != nullptr && curr->right == nullptr))
		{
			if (curr->left == nullptr && curr->right != nullptr)
			{
				if (parent->left == curr)
				{
					parent->left = curr->right;
					curr->right->parent = parent;
					delete curr;
				}
				else
				{
					parent->right = curr->right;
					curr->right->parent = parent;
					delete curr;
				}
			}
			else
			{
				if (parent->left == curr)
				{
					parent->left = curr->left;
					curr->left->parent = parent;
					delete curr;
				}
				else
				{
					parent->right = curr->left;
					curr->left->parent = parent;
					delete curr;
				}
			}
			return;
		}

		//a leaf node
		if (curr->left == nullptr && curr->right == nullptr)
		{
			if (parent->left == curr) parent->left = nullptr;
			else parent->right = nullptr;
			delete curr;
			return;
		}

		//Node with 2 children
		// replace node with smallest value in right subtree
		if (curr->left != nullptr && curr->right != nullptr)
		{
			if ((curr->right->left == nullptr) && (curr->right->right == nullptr))
			{
				curr->right->left = curr->left;
				curr->right->parent = curr->parent;
				parent->right = curr->right;
				curr->left->parent = curr->right;
				curr->right = nullptr;
				delete curr;
			}
			else
			{
				// right child has children
				//if the node's right child has a left child
				// Move all the way down left to locate smallest element

				if ((curr->right)->left != nullptr)
				{
					TreeNode* lcurr;
					TreeNode* lcurrp;
					lcurrp = curr->right;
					lcurr = (curr->right)->left;
					while (lcurr->left != nullptr)
					{
						lcurrp = lcurr;
						lcurr = lcurr->left;
					}
					curr->data = lcurr->data;
					delete lcurr;
					lcurrp->left = nullptr;
				}
				else if ((curr->right)->right != nullptr)
				{
					curr->right->left = curr->left;
					curr->right->parent = curr->parent;
					parent->right = curr->right;
					curr->left->parent = curr->right;
					curr->right = curr->right->right;
					delete curr;
				}
			}
		}
	}

	//Вывод дерева на экран с использованием стека (ПКЛ)
	void printStack()
	{
		std::set<TreeNode*> vert;
		std::stack<TreeNode*> st;
		st.push(root);
		vert.insert(root);
		while (!st.empty())
		{
			TreeNode* node = st.top();
			if (node->right && vert.find(node->right) == vert.end())
			{
				st.push(node->right);
				continue;
			}
			TreeNode* curr = st.top();
			if (curr)
			{
				std::cout << curr->data << " ";
				vert.insert(curr);
			}
			st.pop();
			if (node->left && vert.find(node->left) == vert.end()) st.push(node->left);
		}
	}

	//Сравнение двух деревьев на равенство
	bool isEqual(const BST* tree) { return isEqual_help(root, tree->root); }

	//Вывод на экран «по слоям» – с использованием очереди
	void printQueue() { levelPrint(root); }


	//Destructor
	~BST()
	{
		deleteTree(root);
	}
};


template <typename T>
class mySet
{
	BST<T> set;
public:
	mySet() {}

	void insert(T x) { set->Add(x); }
	void erase(T x) { set->Delete(x); }
	bool find(T x) { return set.Find(x) != set.end(); }

	void erastofen(int n)
	{
		for (int i = 2; i <= n; i++)
			set.Add(i);
		for (int i = 2; i < sqrt(n); i++)
		{
			if (find(i))
			{
				int x = i * i;
				while (x <= n)
				{
					set.Remove(x);
					x += i;
				}
			}
		}
	}
};

#endif // !BST_H
