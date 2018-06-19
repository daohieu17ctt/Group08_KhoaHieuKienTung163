#include "RBT_Header.h"


Node::Node() {
	color = black;
	parent = left = right = NULL;
}

Node *creNode(string value) {
	Node *temp = new Node;
	temp->data = value;
	temp->color = red;
	temp->parent = temp->left = temp->right = NULL;
	return temp;
}

RBTree::RBTree() {
	root = NULL;
}

Node *RBTree::grandParent(Node *cur) {
	if (!cur && !cur->parent)	return NULL;
	return (cur->parent->parent);
}

Node *RBTree::uncle(Node *cur) {
	Node *grPa = grandParent(cur);
	if (!cur && !grPa)	return NULL;
	else {
		if (cur->parent == grPa->left)
			return grPa->right;
		else
			return grPa->left;
	}
}

int RBTree::blackHeight(Node *cur) {
	if (!cur)	return 0;
	int a = blackHeight(cur->left);
	int b = blackHeight(cur->right);
	int temp = max(a, b);
	if (cur->color == black)	return temp + 1;
	else
		return temp;
}

void RBTree::insertNode(Node *&cur) {
	if (!cur || cur->color == black)	return;
	//insertcase1
	if (cur == root) {
		cur->color = black;
	}
	//insertcase2
	else { 
		if (!cur->parent)	return;
		if (cur->parent->color == black) {
			return;
		}
		//insertcase3
		else {
			if (!grandParent(cur) || !uncle(cur))	return;
			if (uncle(cur)->color == red) {
				cur->parent->color = uncle(cur)->color = black;
				grandParent(cur)->color = red;
				Node *ttt = grandParent(cur);
				insertNode(ttt);
				cur->parent->parent = ttt;
			}
			//insertcase4
			else {
				if (cur == cur->parent->right && cur->parent == grandParent(cur)->left) {
					leftRotate(cur->parent);
					cur = cur->left;
				}
				else if (cur == cur->parent->left && cur->parent == grandParent(cur)->right) {
					rightRotate(cur->parent);
					cur = cur->right;
				}
				//insertcase5
				cur->parent->color = black;
				grandParent(cur)->color = red;
				if (cur == cur->parent->left && cur->parent == grandParent(cur)->left) {
					if (grandParent(cur) == root) {
						root = cur->parent;
					}
					rightRotate(grandParent(cur));
				}
				else if (cur == cur->parent->right && cur->parent == grandParent(cur)->right) {
					if (grandParent(cur) == root) {
						root = cur->parent;
					}
					leftRotate(grandParent(cur));
				}
			}
		}
	}
}


void rightRotate(Node *cur) {
	if (cur->left) {
		Node *temp = cur->left;
		temp->parent = cur->parent;
		if (cur->parent) {
			if (cur->parent->left == cur->parent) {
				cur->parent->left = temp;
			}
			else {
				cur->parent->right = temp;
			}
		}
		cur->left = temp->right;
		temp->right->parent = cur;
		temp->right = cur;
		cur->parent = temp;
	}
}

void leftRotate(Node *cur) {
	if (cur->right) {
		Node *temp = cur->right;
		temp->parent = cur->parent;
		if (cur->parent) {
			if (cur->parent->left == cur->parent) {
				cur->parent->left = temp;
			}
			else {
				cur->parent->right = temp;
			}
		}
		cur->right = temp->left;
		temp->left->parent = cur;
		temp->left = cur;
		cur->parent = temp;
	}
}

bool RBTree::insert(string X) {
	if (!root) {
		Node *add = creNode(X);
		root = add;
		insertNode(root);
	}
	else {
		Node *cur = root;
		char pos;
		Node *pCur = NULL;
		while (cur) {
			pCur = cur;
			if (cur->data > X) {
				cur = cur->left;
				pos = 'l';
			}
			else if (cur->data < X) {
				cur = cur->right;
				pos = 'r';
			}
			else {
				return false;
			}
		}
		Node *add = creNode(X);
		if (pCur && pos == 'l') {
			pCur->left = add;
		}
		else if (pCur) {
			pCur->right = add;
		}
		add->parent = pCur;
		insertNode(add);
	}
	return true;
}

void RBTree::print(Node *cur, int level) {
	if (!cur)	return;
	for (int i = 0; i < level; i++) {
		cout << " ";
	}
	cout << cur->data;
	/*if (cur->color == red) {
		cout << "R";
	}
	else {
		cout << "B";
	}*/
	cout << endl;
	print(cur->left, level + 1);
	print(cur->right, level + 1);
}

void RBTree::removeAll_Internal(Node *&cur){
	if (!cur)	return;
	removeAll_Internal(cur->left);
	removeAll_Internal(cur->right);
	delete cur;
	cur = NULL;
}

RBTree::~RBTree() {
	removeAll_Internal(root);
}

void RBTree::print() {
	if (!root) {
		cout << "NULL\n";
		return;
	}
	cout << "root: " << root->data << endl;
	print(root, 0);
}

Node *RBTree::search(string X) {
	return search(root, X);
}

Node *RBTree::search(Node *cur, string X) {
	if (!cur || cur->data == X)	return cur;
	if (cur->data > X) {
		return search(cur->left, X);
	}
	else {
		return search(cur->right, X);
	}
}