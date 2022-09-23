//============================================================================
// Name        : lab1.cpp
// Author      : Pesterev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;

int main() {
	struct El{
		char s = 0;
		El* next = nullptr;

	public:
		El(){};

		El(char s, El* ptr): s(s), next(ptr){};

		El(char* _val){
			for(int i = 0; _val[i]; ++i) push(_val[i]);
		};

		~El(){delete next;};

		void push(char _val){
			next = new El(s, next);
			s = _val;
		}
	};

	const int N = 17;
	char univers[] = "0123456789abcdef";
	char a[N], b[N], c[N], d[N], e[N]{}, tmp[N]{};
	El *LA, *LB, *LD, *LC, *LE, *LTmp;

	int n;
	bool elem_in_c;

	srand(time(0));

	n=0;
	for(int i = 0; i<N; i++){
		if(rand()%2) a[n++] = univers[i];
	}
	a[n] = 0;

	n=0;
	for(int i = 0; i<N; i++){
		if(rand()%2) b[n++] = univers[i];
	}
	b[n] = 0;

	n=0;
	for(int i = 0; i<N; i++){
		if(rand()%2) c[n++] = univers[i];
	}
	c[n] = 0;

	n=0;
	for(int i = 0; i<N; i++){
		if(rand()%2) d[n++] = univers[i];
	}
	d[n]=0;


	for(int i = 0; a[i]; ++i){
		cout << a[i] << " ";
	}
	cout << endl;

	for(int i = 0; b[i]; ++i){
		cout << b[i] << " ";
	}
	cout << endl;

	for(int i = 0; c[i]; ++i){
		cout << c[i] << " ";
	}
	cout << endl;

	for(int i = 0; d[i]; ++i){
		cout << d[i] << " ";
	}
	cout << endl;


	//обработка константных массивов
		//пересечение b и c
	n = 0;
	memset(e, 0, sizeof(e));
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
	memset(tmp, 0, sizeof(tmp));
	for(int i = 0; e[i]; ++i){
		for(int j = 0; d[j]; ++j){
			if(e[i]==d[j]){
				tmp[n++]=e[i];
			}
		}
	}
	tmp[n]=0;

		//объединение a и b

	n = 0;
	memset(e, 0, sizeof(e));

	for(int i = 0; a[i]; ++i){
		e[n++]=a[i];
	}
	e[n]=0;
	for(int i = 0; tmp[i]; ++i){
		elem_in_c = false;
		for(int j = 0; e[j]; ++j){
			if(tmp[i]==e[j]){
				elem_in_c = true;
			}
		}
		if(!elem_in_c)	e[n++]=tmp[i];
	}
	e[n]=0;

	for(int i = 0; e[i]; ++i){
			cout << e[i] << " ";
		}
	cout << endl<< endl;

	//обработка списков
	LA = new El(a);
	LB = new El(b);
	LC = new El(c);
	LD = new El(d);
	LE = new El();
	LTmp = new El();

	//пересечение b и c
	for(El* p = LB; p; p = p->next)
		for(El* u = LC; u; u=u->next)
			if(p->s==u->s)
				LE->push(p->s);

		//пересечение e и d
	for(El* p = LE; p; p=p->next)
		for(El* u = LD; u; u=u->next)
			if(u->s==p->s)
				LTmp->push(u->s);

		//объединение a и b
	LE = LA;
	for(El* p = LTmp; p; p = p->next){
		elem_in_c = false;
		for(El* u = LE; u; u = u->next)
			if(p->s==u->s)
				elem_in_c = true;

		if(!elem_in_c)	LE->push(p->s);
	}

	for(El* p = LE; p; p = p->next){
		cout << p->s << " ";
	}
	cout << endl;


	delete(LA);
	delete(LB);
	delete(LC);
	delete(LD);
	delete(LE);
	delete(LTmp);
	return 0;
}
