//============================================================================
// Name        : lab1.cpp
// Author      : Pesterev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "arr_mn.h"
using namespace std;

int main() {
	ArrMn mn;
	const int N = 17;
	char a[] = "";
	char b[] = "bdf";
	char c[] = "dfgh";
	char d[] = "acf";
	char e[N];

	mn.intersect(b, c, e);
	mn.intersect(e, d, b);
	mn.unite(a, b, e);

	for(int i = 0; e[i]; ++i){
		cout << e[i] << " ";
	}
	return 0;
}
