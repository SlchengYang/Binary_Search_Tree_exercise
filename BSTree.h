#include<iostream>
#include<vector>
#include<queue>
using namespace std;

template<typename T>
struct Node
{
	T key;
	Node<T>* p;
	Node<T>* l;
	Node<T>* r;

	Node(T k, Node<T>* p_, Node<T>* l_ = nullptr, Node<T>* r_ = nullptr) :
		key(k), p(p_), l(l_), r(r_) {};
};



template<typename T>
class BSTree    //indexes must be different
{
private:
	Node<T>* root;  //if key==root, k belong to left tree. 
	int height;  //height==-1 means unknown ;
	void deepcpy(Node<T>*& to, const Node<T>* from);
	void clear(Node<T>* root);
public:
	BSTree();
	BSTree(Node<T>* root);
	BSTree(const BSTree& other);//checked
	~BSTree();//checked??
	Node<T>* get_root(){ return root; }//checked
	int get_height();//checked
	Node<T>* search(T k);//checked
	Node<T>* maximum(Node<T>* ro);//checked
	Node<T>* minimum(Node<T>* ro);//checked
	Node<T>* predecessor(T k);//checked
	Node<T>* predecessor(Node<T>* k);//checked
	Node<T>* successor(T k);//checked
	Node<T>* successor(Node<T>* k);//checked
	bool delete_index(T k);//checked
	bool insert(T k);//checked
	void inorder_walk(vector<T>& res);//checked
	void preorder_walk(vector<T>& res);//checked
	void postorder_walk(vector<T>& res);//checked
	void see();//checked
};


template<typename T>
inline void BSTree<T>::deepcpy(Node<T>*& to, const Node<T>* from)
{
	if (from == nullptr)
		return;
	to = new Node<T>(from->key, from->p, from->l, from->r);
	deepcpy(to->l, from->l);
	deepcpy(to->r, from->r);
}

template<typename T>
inline void BSTree<T>::clear(Node<T>* root)
{
	if (root == nullptr)
		return;

	clear(root->l);
	clear(root->r);
	delete root;
}

template<typename T>
BSTree<T>::BSTree()
{
	root = nullptr;
	height = 0;
}

template<typename T>
BSTree<T>::BSTree(Node<T>* r)
{
	height = -1;
	deepcpy(root, r);
	root->p = nullptr;
}

template<typename T>
inline BSTree<T>::BSTree(const BSTree& other)
{
	height = -1;
	deepcpy(root, other.root);
}

template<typename T>
inline BSTree<T>::~BSTree()
{
	clear(root);
}

template<typename T>
bool BSTree<T>::insert(T k)
{
	if (root == nullptr)
	{
		root = new Node<T>(k, nullptr);
		return true;
	}

	Node<T>* pre = nullptr;
	Node<T>* tem = root;
	while (tem != nullptr)
	{
		if (k > tem->key)
		{
			pre = tem;
			tem = tem->r;
		}
		else
		{
			pre = tem;
			tem = tem->l;
		}
	}

	if (k > pre->key)
	{
		pre->r = new Node<T>(k, pre);
		return true;
	}
	else
	{
		pre->l = new Node<T>(k, pre);
		return true;
	}

	return false;
}

template<typename T>
void BSTree<T>::inorder_walk(vector<T>& res)
{
	if (root == nullptr)
	{
		return;
	}

	BSTree(root->l).inorder_walk(res);
	res.push_back(root->key);
	BSTree(root->r).inorder_walk(res);
}

template<typename T>
inline void BSTree<T>::preorder_walk(vector<T>& res)
{
	if (root == nullptr)
	{
		return;
	}
	res.push_back(root->key);
	BSTree(root->l).preorder_walk(res);
	BSTree(root->r).preorder_walk(res);
}

template<typename T>
inline void BSTree<T>::postorder_walk(vector<T>& res)
{
	if (root == nullptr)
	{
		return;
	}
	BSTree(root->l).postorder_walk(res);
	BSTree(root->r).postorder_walk(res);
	res.push_back(root->key);
}

template<typename T>
inline void BSTree<T>::see()
{
	if (root == nullptr)
		return;
	queue<Node<T>*> walk;
	walk.push(root);
	walk.push(nullptr);  //means \n
	while (!walk.empty())
	{
		while (walk.front() != nullptr)
		{
			if (walk.front()->l != nullptr)
			{
				walk.push(walk.front()->l);
			}
			if (walk.front()->r != nullptr)
			{
				walk.push(walk.front()->r);
			}
			cout << walk.front()->key << "  ";
			walk.pop();
		}
		cout << '\n';
		walk.pop();
		if (!walk.empty())
			walk.push(nullptr);
	}
}

template<typename T>
inline int BSTree<T>::get_height()
{
	if (root == nullptr)
		return 0;
	queue<Node<T>*> walk;
	walk.push(root);
	int count = 0;
	walk.push(nullptr);  //means \n
	while (!walk.empty())
	{
		while (walk.front() != nullptr)
		{
			if (walk.front()->l != nullptr)
			{
				walk.push(walk.front()->l);
			}
			if (walk.front()->r != nullptr)
			{
				walk.push(walk.front()->r);
			}
			walk.pop();
		}
		walk.pop();
		if (!walk.empty())
		{
			walk.push(nullptr);
			count++;
		}
	}
	height = count;
	return count;
}

template<typename T>
Node<T>* BSTree<T>::search(T k)
{
	if (root == nullptr)
		return nullptr;

	Node<T>* tem = root;
	while (tem != nullptr && tem->key != k)
	{
		if (k > tem->key)
			tem = tem->r;
		else
			tem = tem->l;
	}
	return tem;
}

template<typename T>
Node<T>* BSTree<T>::maximum(Node<T>* ro)
{
	if (ro == nullptr)
		return nullptr;

	Node<T>* tem = ro;
	while (tem->r != nullptr)
	{
		tem = tem->r;
	}
	return tem;
}

template<typename T>
Node<T>* BSTree<T>::minimum(Node<T>* ro)
{
	if (ro == nullptr)
		return nullptr;

	Node<T>* tem = ro;
	while (tem->l != nullptr)
	{
		tem = tem->l;
	}
	return tem;
}

template<typename T>
Node<T>* BSTree<T>::predecessor(T k)
{
	Node<T>* target = this->search(k);
	if (target == nullptr)
		return nullptr;

	if (target->l == nullptr)
	{
		Node<T>* tem = target;
		while (tem->p != nullptr && tem->p->l == tem)
		{
			tem = tem->p;
		}
		return tem->p;
	}

	return this->maximum(target->l);
}

template<typename T>
Node<T>* BSTree<T>::predecessor(Node<T>* k)
{
	Node<T>* target = k;
	if (target == nullptr)
		return nullptr;

	if (target->l == nullptr)
	{
		Node<T>* tem = target;
		while (tem->p != nullptr && tem->p->l == tem)
		{
			tem = tem->p;
		}
		return tem->p;
	}

	return this->maximum(target->l);
}

template<typename T>
Node<T>* BSTree<T>::successor(T k)
{
	Node<T>* target = this->search(k);
	if (target == nullptr)
		return nullptr;

	if (target->r == nullptr)
	{
		Node<T>* tem = target;
		while (tem->p != nullptr && tem->p->r == tem)
		{
			tem = tem->p;
		}
		return tem->p;
	}

	BSTree rightchild(target->r);
	return rightchild.minimum(target->r);
}

template<typename T>
Node<T>* BSTree<T>::successor(Node<T>* k)
{
	Node<T>* target = k;
	if (target == nullptr)
		return nullptr;

	if (target->r == nullptr)
	{
		Node<T>* tem = target;
		while (tem->p != nullptr && tem->p->r == tem)
		{
			tem = tem->p;
		}
		return tem->p;
	}

	return this->minimum(target->r);
}

template<typename T>
bool BSTree<T>::delete_index(T k)
{
	Node<T>* target = this->search(k);
	if (target == nullptr)
		return false;

	if (target == root)
	{
		if (target->l == nullptr && target->r == nullptr)
		{
			delete target;
			root = nullptr;
			return true;
		}
		if (target->l == nullptr)
		{
			root = target->r;
			delete target;
			root->p = nullptr;
			return true;
		}
		if (target->r == nullptr)
		{
			root = target->l;
			delete target;
			root->p = nullptr;
			return true;
		}
		Node<T>* tem = target->l;
		Node<T>* newroot = this->successor(target);
		root = target->r;
		target->r->p = nullptr;
		delete target;
		newroot->l = tem;
		tem->p = newroot;
		return true;
	}

	if (target->l == nullptr && target->r == nullptr)
	{
		if (target->p->l == target)
		{
			target->p->l = nullptr;
			delete target;
		}
		else
		{
			target->p->r = nullptr;
			delete target;
		}
		return true;
	}

	if (target->l == nullptr)
	{
		if (target->p->l == target)
		{
			target->p->l = target->r;
			target->r->p = target->p;//warning!!
			delete target;
		}
		else
		{
			target->p->r = target->r;
			target->r->p = target->p;
			delete target;
		}
		return true;
	}

	if (target->r == nullptr)
	{
		if (target->p->l == target)
		{
			target->p->l = target->l;
			target->l->p = target->p;//warning!!
			delete target;
		}
		else
		{
			target->p->r = target->l;
			target->l->p = target->p;
			delete target;
		}
		return true;
	}

	if (target->p->r == target)
	{
		Node<T>* tem = target->l;
		Node<T>* newroot = this->successor(target);
		target->p->r = target->r;
		target->r->p = target->p;
		delete target;
		newroot->l = tem;
		tem->p = newroot;
		return true;
	}

	if (target->p->l == target)
	{
		Node<T>* tem = target->r;
		Node<T>* newroot = this->predecessor(target);
		target->p->l = target->l;
		target->l->p = target->p;
		delete target;
		newroot->r = tem;
		tem->p = newroot;
		return true;
	}
	return false;
}