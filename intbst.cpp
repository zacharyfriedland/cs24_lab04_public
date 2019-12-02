// intbst.cpp
// Implements class IntBST
// Zachary Friedland remake generalized 5/22 extracredit 


#include <iostream>
using std::cout;

// constructor sets up empty tree
template<class T>
IntBST<T>::IntBST() : root(0) { }

// destructor deletes all nodes
template<class T>
IntBST<T>::~IntBST() {
    clear(root);
}

// recursive helper for destructor
template<class T>
void IntBST<T>::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
template<class T>
bool IntBST<T>::insert(T value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
template<class T>
bool IntBST<T>::insert(T value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
template<class T>
void IntBST<T>::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
template<class T>
void IntBST<T>::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
template<class T>
void IntBST<T>::printInOrder() const {
    printInOrder(root);
}
template<class T>
void IntBST<T>::printInOrder(Node *n) const {
	if(n){
		printInOrder(n->left);
		cout << n->info << " ";
		printInOrder(n->right);
	}
}

// prints tree data post-order, with helper
template<class T>
void IntBST<T>::printPostOrder() const {
    printPostOrder(root);
}

template<class T>
void IntBST<T>::printPostOrder(Node *n) const {
    if(n){
		printPostOrder(n->left);
		printPostOrder(n->right);
		cout << n->info << " ";
    }
}

// return sum of values in tree
template<class T>
T IntBST<T>::sum() const {
    return sum(root);
}

// recursive helper for sum
template<class T>
T IntBST<T>::sum(Node *n) const {
	if(n == nullptr)
		return 0;
	if(n){
		return n->info + sum(n->left) + sum(n->right);
	}
	return 0;
}

// return count of values
template<class T>
int IntBST<T>::count() const {
    return count(root);
}

// recursive helper for count
template<class T>
int IntBST<T>::count(Node *n) const {
    if(n == nullptr)
	    return 0;
    if(n)
	    return 1 + count(n->left) + count(n->right);
    return 0;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
template<class T>
typename IntBST<T>::Node* IntBST<T>::getNodeFor(T value, Node* n) const{
	if(n == nullptr)
		return 0;
	if(n){
		if(n->info == value)
			return n;
		else if(n->info > value)
			return getNodeFor(value, n->left);
		else
			return getNodeFor(value, n->right);
	}
	return 0;
}

// returns true if value is in the tree; false if not
template<class T>
bool IntBST<T>::contains(T value) const {
	if(this->getNodeFor(value, root) != 0)
		return true;
	return false;
}

// returns the Node containing the predecessor of the given value
template<class T>
typename IntBST<T>::Node* IntBST<T>::getPredecessorNode(T value) const{
	Node* t = this->getNodeFor(value, root);
	if(!t)
		return 0;
	if(t->left){
		t = t->left;
		while(t->right)
			t = t->right;
		return t;
	}
	while(t->parent && t->parent->left == t)
		t = t->parent;
	return t->parent;
}

// returns the predecessor value of the given value or 0 if there is none
template<class T>
T IntBST<T>::getPredecessor(T value) const{
	Node* z = getPredecessorNode(value);
	if(z)
		return z->info;
	return 0;
}

// returns the Node containing the successor of the given value
template<class T>
typename IntBST<T>::Node* IntBST<T>::getSuccessorNode(T value) const{
	Node* n = getNodeFor(value, root);
	if(!n)
		return 0;
	if(n->right){
		n = n->right;
		while(n->left){
			n = n->left;
		}
		return n;
	}
	
	while(n->parent && n->parent->right == n){
		n = n->parent;
	}
	return n->parent;
}

// returns the successor value of the given value or 0 if there is none
template<class T>
T IntBST<T>::getSuccessor(T value) const{
	Node* x = getSuccessorNode(value);
	if(x)
		return x->info;
	return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
template<class T>
bool IntBST<T>::remove(T value){
	Node* a = getNodeFor(value, root);
	Node* p = getPredecessorNode(value);
	if(!a)
		return false;
	if(a->left && a->right){ //two children
		T temp = a->info;
		a->info = p->info;
		p->info = temp;
		//swap the values of target(a) and predecessor(p)
		//predecessor will have 0 or 1 child
		if(p->left){ //child on the left
			if(p->parent->left == p){
				p->parent-> left = p->left;
				delete p;
				return true;
			}
			else{
				p->parent->right = p->left;
				delete p;
				return true;
			}

		}
		else if(p->right){ //child on the right
			if(p->parent->left == p){
				p->parent->left = p->right;
				delete p;
				return true;
			}
			else{
				p->parent->right = p->right;
				delete p;
				return true;
			}
		}
		else{ //0 childen (leaf)
			if(p->parent->left == p){
				p->parent->left = nullptr;
				delete p;
				return true;
			}
			else{
				p->parent->right = nullptr;
				delete p;
				return true;
			}
		}


	
	}
	else if(a->left){ //child on the left
		if(this->root == a){
			this->root = a->left;
			root->parent = nullptr;
			delete a;
			return true;
		}
		if(a->parent->left == a){
			a->parent-> left = a->left;
			delete a;
			return true;
		}
		else{
			a->parent->right = a->left;
			delete a;
			return true;
		}

	}
	else if(a->right){ //child on the right
		if(this->root == a){
			this->root = a->right;
			root->parent = nullptr;
			delete a;
			return true;
		}
		if(a->parent->left == a){
			a->parent->left = a->right;
			delete a;
			return true;
		}
		else{
			a->parent->right = a->right;
			delete a;
			return true;
		}

		
	}
	else{ //0 childen (leaf)
		if(this->root == a){
			root = nullptr;
			delete a;
			return true;
		}
		if(a->parent->left == a){
			a->parent->left = nullptr;
			delete a;
			return true;
		}
		else{
			a->parent->right = nullptr;
			delete a;
			return true;
		}
	}

}
