//============================================================================
// Name        : coursework.cpp
// Author      : Pesterev
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <stack>
#include <string.h>

using namespace std;

class Elem {
	int id =0, numParents=1;
	bool isUsed = false;

public:
	Elem(int ID):id(ID){}
	void increasePar(){++numParents;}
	void decreasePar(){--numParents;}
	void dShow(){cout << "id = " << id << " par = "<< numParents<< " Used = " << isUsed<<endl;}
	friend class Set;
	friend class Graph;
};

class Set {
	char name;
	vector<Elem*> elems;
	static vector<Elem*> univers;

public:
	Set(char nm, vector<string> els);
	~Set(){
		elems.clear();
		for (vector<Elem*>::iterator iter = univers.begin(); iter != univers.end();
						iter++) {
				delete(*iter);
			}
		univers.clear();
	}

	Elem* findElem(int, vector<Elem*>);
	Elem* findMinPar();
	void decreaseChild();
	friend class Graph;
};
vector<Elem*> Set::univers = {};

Elem* Set::findMinPar(){
	Elem* A = nullptr;
	int minPar = INT_MAX;
	for (vector<Elem*>::iterator iter = elems.begin(); iter != elems.end();
					iter++){
			if((*iter)->numParents < minPar && !(*iter)->isUsed){
				A = *iter;
				minPar = (*iter)->numParents;
			}
		}
	return A;
}

Elem* Set::findElem(int ID, vector<Elem*> vec){
	Elem *A = nullptr;
	for (vector<Elem*>::iterator iter = vec.begin(); iter != vec.end();
				iter++){
		if((*iter)->id == ID) A = *iter;
	}
	return A;
}

void Set::decreaseChild(){
	for (vector<Elem*>::iterator iter = elems.begin(); iter != elems.end();
				iter++){
		(*iter)->decreasePar();
	}
}

Set::Set(char nm, vector<string> els):name(nm){
	int id;
	Elem *A;
	for (vector<string>::iterator iter = els.begin(); iter != els.end();
			iter++) {
		id = atoi((*iter).c_str());
		if (id) {
			if (!findElem(id, elems)) {
				A = findElem(id, univers);
				if (A) {
					elems.push_back(A);
					A->increasePar();
				} else {
					univers.push_back(A = new Elem(id));
					elems.push_back(A);
				}

				A->dShow();
			}
		}
	}
}

class Graph {
	vector<Set*> sets;
public:
	Graph(vector<vector<string>> v);
	~Graph(){
		for (vector<Set*>::iterator iter = sets.begin();
				iter != sets.end(); iter++) {
			(*iter)->~Set();
		}
		sets.clear();
	}
	string transversal();
};

Graph::Graph(vector<vector<string>> v){
	for (vector<vector<string>>::iterator iter = v.begin(); iter != v.end();
				iter++) {
		sets.push_back(new Set('A', *iter));
	}
}

string Graph::transversal(){
	string trans = "";
	Elem* A = nullptr;
	for (vector<Set*>::iterator iter = sets.begin(); iter != sets.end();
			iter++) {
		A = (*iter)->findMinPar();
		if(A){
			trans += to_string(A->id) + " ";
			A->isUsed = true;
			(*iter)->decreaseChild();
		}
	}
	return trans;
}



int main() {
	Graph gr =Graph({{"1","4","5"},{"1"},{"2","3","4"},{"2","4"},{"2"},{"3"}});

	cout << setw(10) << gr.transversal() << endl; // prints
	return 0;
}
