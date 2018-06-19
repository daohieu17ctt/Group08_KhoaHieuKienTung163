#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

enum Color {red, black};
struct Node {
	string data;
	Color color;
	Node *parent;
	Node *left;
	Node *right;
	Node();
};

class RBTree {
public:
	RBTree();
	~RBTree();
	bool insert(string X);
	void print();
	Node *search(string X);
	//void removeAll();
private:
	Node * root;
	Node *grandParent(Node *cur);
	Node *uncle(Node *cur);
	int blackHeight(Node *cur);
	void insertNode(Node *&cur);
	void print(Node *cur, int level);
	void removeAll_Internal(Node *&cur);
	Node *search(Node *cur, string X);
};
void rightRotate(Node *cur);
void leftRotate(Node *cur);
#endif // !_HEADER_H_
