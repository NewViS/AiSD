//============================================================================
// Name        : lab1.cpp
// Author      : Pesterev
// Version     :
// Description : Анализ скорости работы алгоритмов над множествами
//============================================================================

#include <iostream>
#include <iomanip>
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

		~El(){
			delete next;
			next = nullptr;
			s = 0;
		};

		void push(char _val){
			next = new El(s, next);
			s = _val;
		}
	};

	const int N = 17;
	char univers[] = "0123456789abcdef";
	char a[N], b[N], c[N], d[N], e[N]{}, tmp[N]{};
	El *LA, *LB, *LD, *LC, *LE, *LTmp;
	bool bit_a[N-1]{}, bit_b[N-1]{}, bit_c[N-1]{}, bit_d[N-1]{}, bit_e[N-1]{};
	unsigned short us_a=0, us_b=0, us_c=0, us_d=0, us_e = 0;

	int n;
	bool elem_in_c;
	clock_t t[4];

	setlocale(LC_ALL, "");
	srand(time(0));

	n=0;
	for(int i = 0; i<N-1; i++){
		bool j = rand()%2;
		bit_a[i] = j;
		if(j) a[n++] = univers[i];
		us_a += j << i;
	}
	a[n] = 0;
	LA = new El(a);

	n=0;
	for(int i = 0; i<N-1; i++){
		bool j = rand()%2;
		bit_b[i] = j;
		if(j) b[n++] = univers[i];
		us_b += j << i;
	}
	b[n] = 0;
	LB = new El(b);

	n=0;
	for(int i = 0; i<N-1; i++){
		bool j = rand()%2;
		bit_c[i] = j;
		if(j) c[n++] = univers[i];
		us_c += j << i;
	}
	c[n] = 0;
	LC = new El(c);

	n=0;
	for(int i = 0; i<N-1; i++){
		bool j = rand()%2;
		bit_d[i] = j;
		if(j) d[n++] = univers[i];
		us_d += j << i;
	}
	d[n]=0;
	LD = new El(d);

	cout << "Множество А: ";
	for(int i = 0; a[i]; ++i){
		cout << a[i] << " ";
	}
	cout << endl;

	cout << "Множество B: ";
	for(int i = 0; b[i]; ++i){
		cout << b[i] << " ";
	}
	cout << endl;

	cout << "Множество C: ";
	for(int i = 0; c[i]; ++i){
		cout << c[i] << " ";
	}
	cout << endl;

	cout << "Множество D: ";
	for(int i = 0; d[i]; ++i){
		cout << d[i] << " ";
	}
	cout << endl;


	//обработка константных массивов
		//пересечение b и c
	t[0] = clock();
	for(int iterate = 0; iterate < 1000000; ++iterate){

	n = 0;

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
				tmp[n++]=e[i];
			}
		}
	}
	tmp[n]=0;

		//объединение a и b

	n = 0;

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

	for (int i = 0; e[i]; ++i) {
		for (int j = i + 1; e[j]; ++j) {
			if (e[i] > e[j]) {
				tmp[0] = e[i];
				e[i] = e[j];
				e[j] = tmp[0];
			}
		}
	}

	}
	t[0]=clock()-t[0];

	for(int i = 0; e[i]; ++i){
			cout << e[i] << " ";
		}
	cout << endl << t << endl;

	//обработка списков

	t[1] = clock();
	for(int iterate = 0; iterate < 1000000; ++iterate){

	LE = new El();
	LTmp = new El();

		//пересечение b и c
	LE->~El();
	for(El* p = LB; p; p = p->next)
		for(El* u = LC; u; u=u->next)
			if(p->s==u->s)
				LE->push(p->s);

		//пересечение e и d
	LTmp->~El();
	for(El* p = LE; p; p=p->next)
		for(El* u = LD; u; u=u->next)
			if(u->s==p->s)
				LTmp->push(u->s);

		//объединение a и b
	LE->~El();
	for(El* p = LA; p && p->s; p = p->next){
		LE->push(p->s);
	}
	for(El* p = LTmp; p; p = p->next){
		elem_in_c = false;
		for(El* u = LE; u; u = u->next)
			if(p->s==u->s)
				elem_in_c = true;

		if(!elem_in_c)	LE->push(p->s);
	}

	for (El* p = LE; p && p->s; p= p->next) {
		for (El* q = p->next; q && q->s; q=q->next) {
			if (p->s > q->s) {
				tmp[0] = p->s;
				p->s = q->s;
				q->s = tmp[0];
			}
		}
	}
	}
	t[1]=clock()-t[1];

	for(El* p = LE; p; p = p->next){
		cout << p->s << " ";
	}
	cout << endl<< t << endl;

	//массив битов
	t[2] = clock();
	for(int iterate = 0; iterate < 1000000; ++iterate){
	for(int i = 0; i<N-1; i++)
			bit_e[i] = bit_a[i]||(bit_b[i] && bit_c[i] && bit_d[i]);
	}
	t[2]=clock()-t[2];
	for(int i = 0; i<N-1; i++)
		if(bit_e[i])	cout << univers[i]<< " ";
	cout << endl<< t<< endl;

	//машинное слово
	t[3] = clock();
	for(int iterate = 0; iterate < 1000000; ++iterate){
	us_e = us_a|(us_b & us_c & us_d);
	}
	t[3]=clock()-t[3];
	for(int i = 0; i<N; i++)
		if(us_e & 1 << i)	cout << univers[i]<< " ";
	cout << endl<< t<< endl;

	cout.fill('-');
	cout << "+-----------------+"<<setw(50)<<"+-----------------+"<< endl;
	cout << "| Способ хранения | Множество E | Время обработки |"<<endl;
	cout << "| Способ хранения | Множество E | Время обработки |"<<setw(50)<<endl;

	delete(LA);
	delete(LB);
	delete(LC);
	delete(LD);
	delete(LE);
	delete(LTmp);
	return 0;
}
