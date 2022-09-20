//============================================================================
// Name        : lab1.cpp
// Author      : Pesterev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>

using namespace std;

int main() {
	const int N = 17;
	char a[] = "";
	char b[] = "bdf";
	char c[] = "12df";
	char d[] = "acdf";
	char e[N]{};
	int n = 0;
	bool elem_in_c;

	struct El{
		char s;
		El* next;
	};

	//обработка константных массивов
		//пересечение b и c
	for(int i = 0; b[i]; ++i){
		for(int j = 0; c[j]; ++j){
			if(b[i]==c[j]){
				e[n++]=b[i];
			}
		}
	}
	e[n]=0;

		//пересечение e и d
	n = 0;
	for(int i = 0; e[i]; ++i){
		for(int j = 0; d[j]; ++j){
			if(e[i]==d[j]){
				b[n++]=e[i];
			}
		}
	}
	b[n]=0;

		//объединение a и b

	n = 0;
	memset(e, 0, sizeof(e));

	for(int i = 0; a[i]; ++i){
		e[n++]=a[i];
	}
	e[n]=0;
	for(int i = 0; b[i]; ++i){
		elem_in_c = false;
		for(int j = 0; e[j]; ++j){
			if(b[i]==e[j]){
				elem_in_c = true;
			}
		}
		if(!elem_in_c)	e[n++]=b[i];
	}
	e[n]=0;

	//обработка списков

	for(int i = 0; e[i]; ++i){
		cout << e[i] << " ";
	}
	return 0;
}
