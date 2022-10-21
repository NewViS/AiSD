//============================================================================
// Name        : lab3.cpp
// Author      : Pesterev
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale>
using namespace std;

class Node {
	char d;
	Node *lft, *mdl, *rgt;
public:
	Node() :
			lft(nullptr), mdl(nullptr), rgt(nullptr) {
	}
	;
	~Node() {
		if (lft)
			delete lft;
		if (mdl)
			delete mdl;
		if (rgt)
			delete rgt;
	}

	friend class Tree;
};

class Tree {
	Node *root;
	char num, maxnum;
	int maxrow;

	Node* makeNode(int depth);
	Tree(const Tree&);
	Tree(Tree&&);

	Tree operator =(Tree&&) const = delete;

public:
	Tree(char num, char maxnum, int maxrow);
	~Tree();
	void makeTree() {
		root = makeNode(0);
	}
	bool exist() {
		return root != nullptr;
	}
	int BFS();
	void printBT();
	void printBT(const string &prefix, const Node *node, int dim, bool hasSib);
	int midLen();
	int heigh(Node *nd);
};

Tree::Tree(char nm, char mnm, int mxr) :
		num(nm), maxnum(mnm), root(nullptr), maxrow(mxr) {
}

Tree::~Tree() {
	delete root;
}

Node* Tree::makeNode(int depth) {
	Node *v = nullptr;
	int Y = (depth < rand() % maxrow + 1) && (num <= maxnum);
	if (Y) { // создание узла, если Y = 1
		v = new Node;
		v->d = num++;
		if (depth < maxrow) {
			v->lft = makeNode(depth + 1);
			v->mdl = makeNode(depth + 1);
			v->rgt = makeNode(depth + 1);
		}
	}
	return v;
}

int Tree::BFS() {
	int count = 0;
	queue<Node*> Q;  //создание очереди указателей на узлы
	Q.push(root); // поместить в очередь корень дерева
	while (!Q.empty()) //пока очередь не пуста
	{
		Node *v = Q.front();
		Q.pop(); // взять из очереди,
		cout << v->d << '_';
		++count; // выдать тег, счёт узлов
		if (v->lft)
			Q.push(v->lft); // Q <- (левый сын)
		if (v->mdl)
			Q.push(v->mdl);
		if (v->rgt)
			Q.push(v->rgt); // Q <- (правый сын)
	}
	return count;
}

void Tree::printBT(const string &prefix, const Node *node, int dim,
		bool hasSib) {
	if (node != nullptr) {
		cout << prefix;
		switch (dim) {
		case 0: {
			cout << ("┌──");
			cout << node->d << endl;
			break;
		}
		case 1: {
			cout << ("├──");
			cout << node->d << endl;
			break;
		}
		case 2: {
			cout << ("└──");
			cout << node->d << endl;
			break;
		}
		case 3: {
			cout << ("───");
			cout << node->d << endl;
			break;
		}
		}
		printBT(prefix + (hasSib ? "│   " : "    "), node->rgt, 0,
				(node->mdl != nullptr) || (node->lft != nullptr));
		printBT(prefix + (hasSib ? "│   " : "    "), node->mdl, 1,
				node->lft != nullptr);
		printBT(prefix + (hasSib ? "│   " : "    "), node->lft, 2, false);
	}
}

void Tree::printBT() {
	printBT("", root, 3, false);
}

int Tree::heigh(Node *nd) {
	int len = -1;
	if (nd) {
		if (nd->lft != nullptr || nd->mdl != nullptr || nd->rgt != nullptr) {
			len = max(max(heigh(nd->lft), heigh(nd->mdl)), heigh(nd->rgt));
		} else
			len = 0;
	}
	return len + 1;
}

int Tree::midLen() {
	int len = 0;
	if (root) {
		len = heigh(root->mdl);
	}
	return len;
}

int main() {
	int n = 0;
	Tree Tr('a', 'z', 8);
	srand(time(nullptr));
	setlocale(LC_ALL, "Russian");

	Tr.makeTree();
	if (Tr.exist()) {
		Tr.printBT();
		cout << '\n' << "Обход графа в ширину: ";
		n = Tr.BFS();
		cout << " Количество узлов: " << n << endl;
		cout <<"Длина среднего поддерева: " << Tr.midLen();
	} else
		cout << "Пусто!";

	return 0;
}
