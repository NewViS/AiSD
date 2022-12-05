//===========================================================================
// Name        : coursework.cpp
// Author      : Pesterevc Victor
// Version     :
// Copyright   :
// Description : Применение алгоритма Куна для поиска трансверсали наибольшей
//               мощности частично пересекающихся подмножеств
//===========================================================================
#include <vector>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <time.h>

using namespace std;

class Graph {
	int n, k; //кол-во эл-тов в первой и второй доле
	vector<int> elems; //элементы второй доли
	vector<vector<int>> g; //вектор номеров вершин второй доли, в которые можно прийти из вершины первой
	vector<int> mt; //вершины первой доли, связанные с вершинами второй
	vector<char> used; //использованные вершины
public:
	Graph(string filename); //файл входных значений
	Graph():n(0),k(0){}; //пустой граф
	~Graph() {
		elems.clear();
		g.clear();
		mt.clear();
		used.clear();
		//cout << "cleaned!";
	};
	bool try_kuhn(int v);
	void find_couples();
	void fillRand(int n, int k);
	void printGraph();
	void write_couples(string filename);
};

void Graph::write_couples(string filename){
	ofstream outfile(filename);
	if (outfile.bad()) {
			cout << "\nФайл in.txt недоступен";
			exit(1);
		}
	else{
		this->find_couples();
		for (int i=0; i<k; ++i)
					if (mt[i] != -1)
						outfile << mt[i]+1 <<";"<< *next(elems.begin(), i)<<endl;
	}
}

void Graph::printGraph(){
	for(int i =0; i<n; ++i){
		printf("%d: ", i+1);
		for(size_t j =0; j<g[i].size(); ++j){
			cout << *next(elems.begin(), g[i][j]) << " ";
		}
		cout <<endl;
	}
}

void Graph::fillRand(int n, int k){
	this->n=n; this->k=k;
	for(int i = 0; i<k; ++i){
		elems.push_back(i);
	}

	for(int i = 0; i<n; ++i){
		g.push_back({});
		for(int j = 0; j<k; ++j){
			if(rand()%2){
				g[i].push_back(j);
				//cout << j << " ";
			}
		}
		//cout <<endl;
	}
}

Graph::Graph(string filename){
	n = 0; k = 0;
	int tmp, dist;
	bool isFirstElem;
	string line;
	ifstream infile(filename);

	if (infile.bad()) {
		cout << "\nФайл in.txt недоступен";
		exit(1);
	}
	else{

		while (infile>>line)
		{
			isFirstElem = true;
			//cout << line << endl;
			stringstream ss(line);
			while(getline(ss, line, ';')){
			    tmp = atoi(line.c_str());
			    if(find(elems.begin(), elems.end(), tmp) == elems.end()){//{
			    	elems.push_back(tmp);
			    	k++;
			    }

			    dist = distance(elems.begin(), find(elems.begin(), elems.end(), tmp));
			    if(isFirstElem){
			    	g.push_back({dist});
			    	n++;
			    	isFirstElem = false;
			    }else{

			    	if(find(g[n-1].begin(), g[n-1].end(), dist) == g[n-1].end()){
			    		g[n-1].push_back(dist);
			    	}
			    }
			}
		}
	}
}

bool Graph::try_kuhn (int v) {
	if (used[v])  return false;
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn (mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

void Graph::find_couples(){
	int power =0;
	mt.assign (k, -1);
		vector<char> used1 (n);
		for (int i=0; i<n; ++i)
			for (size_t j=0; j<g[i].size(); ++j)
				if (mt[g[i][j]] == -1) {
					mt[g[i][j]] = i;
					used1[i] = true;
					break;
				}
		for (int i=0; i<n; ++i) {
			if (used1[i])  continue;
			used.assign (n, false);
			try_kuhn (i);
		}

		for (int i=0; i<k; ++i)
			if (mt[i] != -1)
				{
				printf ("%d — %d\n", mt[i]+1, *next(elems.begin(), i));
				++power;
				}
		cout<<"Мощность: "<<power<<endl;
}

void print_menu() {
	cout
			<< "Выберите действие:\n1—Чтение подмножеств из файла"
					"\n2—Случайный набор подмножеств"
					"\n3—Вывод подмножеств"
					"\n4—Найти трансверсаль"
					"\n5—Записать трансверсаль в файл"
					"\n0—Выход"
			<< endl;
}

int main() {
	int tmp=-1;
	int n=0, k=0;
	Graph gr;

	srand(time(nullptr));

	while (tmp) {
		print_menu();
		cin >> tmp;
		switch (tmp) {
		case 0: break;
		case 1: {
			gr = Graph("in.txt");
			break;
		}
		case 2: {
			gr = Graph();
			cout << "Введите число множеств и элементов:" << endl;
			cin >> n >> k;
			gr.fillRand(n, k);
			break;
		}
		case 3:{
			gr.printGraph();
			break;
		}
		case 4:{
			gr.find_couples();
			break;
		}
		case 5:{
			gr.write_couples("out.txt");
			break;
		}
		default: {
			cout << "Введено неверное значение!" << endl;
		}
		}
	}

	return 0;
}
