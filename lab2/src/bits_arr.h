/*
 * bits_arr.h
 *
 *  Created on: 10 окт. 2022 г.
 *      Author: vecto
 */

#pragma once
using namespace std;

class Set {
private:
	static int N, cnt;
	static char univers[];
	int n;
	char S;
	bool *A;

public:
	static bool isOutput;

	Set();
	Set(char *B);
	Set(const Set&);

	Set& operator &=(const Set &B);
	Set& operator |=(const Set &B);

	Set operator |(const Set&) const;
	Set operator &(const Set&) const;
	Set& operator =(const Set &B);

	~Set() {
		if (isOutput) {
			cout << "Удалено " << S << "(" << n << ") = [";
			printA();
			cout << "]" << endl;
		}
		delete[] A;
	}

	void show();
	void fillRand();
	void printA();
};

int Set::N = 16;
int Set::cnt = 0;
char Set::univers[] = "0123456789abcdef";
bool Set::isOutput = false;

void Set::show() {
	cout << S << "(" << n << ") = [";
	printA();
	cout <<']'<<endl;
}

void Set::fillRand() {
	n = 0;
	for (int i = 0; i < N; ++i)
		if(A[i] = rand()%2) ++n;
	if (isOutput) {
		cout << "Заполнено случайными числами " << S << "(" << n << ")"
				<< " = [";
		printA();
		cout << "]" << endl;
	}

}

void Set::printA(){
	for(int i =0; i<N; ++i) if(A[i]) cout << univers[i];
}

Set::Set(char *B) : n(0), S('A' + cnt++), A(new bool[N]{})  {
	for (int j = 0; j < N; ++j)
		for (int i = 0; B[i]; ++i)
			if(univers[j] == B[i]){
				A[j] = true;
				++n;
			}

	if (isOutput) {
		cout << "Создано " << S << "(" << n << ")" << " = [";
		printA();
		cout << "]" << endl;
	}
}

Set::Set() :
		n(0), S('A' + cnt++), A(new bool[N]{}){
	if (isOutput) {
		cout << "Создано пустое " << S << "(" << n << ")" << " = [";
		printA();
		cout << "]" << endl;
	}
}

Set::Set(const Set &B) :
		S('A' + cnt++), n(B.n), A(new bool[N]{}) {
	bool *dst(A), *src(B.A);
	for (int i = 0; i < N; ++i) (*dst++ = *src++);
	if (isOutput) {
		cout << "Создано " << S << "(" << n << ")" << " = [";
		printA();
		cout << "] из " << B.S << "(" << B.n << ")" << " = [" << B.A << "]"
				<< endl;
	}
}

Set& Set::operator &=(const Set &B) {
	n=0;
	for(int i = 0; i<N; ++i){
		if(A[i]&=B.A[i]) ++n;;
	}

	if (isOutput) {
		cout << "Вычислено " << S << "(" << n << ")" << " = [";
		printA();
		cout << "] = " << S << " & " << B.S << endl;
	}
		cnt--;

	return *this;
}

Set Set::operator &(const Set &B) const {
	Set C(*this);
	if (isOutput) {
		cout << "Вычислено " << C.S << "(" << C.n << ")" << " = [";
		C.printA();
		cout << "] = " << B.S << " & " << S << endl;
	}
	return (C &= B);
}

Set& Set::operator |=(const Set &B) {
	n=0;
	for (int i = 0; i < N; ++i) {
		if(A[i] |= B.A[i]) ++n;
	}
	if (isOutput) {
		cout << "Вычислено " << S << "(" << n << ")" << " = [";
		printA();
		cout << "] = " << S << " | " << B.S << endl;
	}
	return *this;
}

Set Set::operator |(const Set &B) const {
	Set C(*this);
	if (isOutput) {
		cout << "Вычислено " << C.S << "(" << C.n << ")" << " = [";
		C.printA();
		cout << "] = " << B.S << " | " << S << endl;
	}
	return (C |= B);

}

Set& Set::operator =(const Set &B) {
	if (this != &B) {
		bool *dst(A), *src(B.A);
		n = B.n;
		for (int i = 0; i < N; ++i) (*dst++ = *src++);
	}
	if (isOutput) {
		cout << S << " = " << B.S << "(" << n << ") = [";
		printA();
		cout << "]" << endl;
	}
	return *this;
}

