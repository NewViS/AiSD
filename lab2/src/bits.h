/*
 * bits.h
 *
 *  Created on: 20 окт. 2022 г.
 *      Author: Pesterev
 */

#pragma once
using namespace std;

class Set {
private:
	static int N, cnt;
	static char univers[];
	int n;
	char S;
	unsigned short A;

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
	}

	void show();
	void fillRand();
	void printA();
};

int Set::N = 16;
int Set::cnt = 0;
char Set::univers[] = "0123456789abcdef";
bool Set::isOutput = false;

void Set::printA() {
	for (int i = 0; i < N; ++i)
		if (A & (1 << i))
			cout << univers[i];
}

void Set::show() {
	cout << S << "(" << n << ") = [";
	printA();
	cout << ']' << endl;
}

void Set::fillRand() {
	n = 0;
	A = rand() % UCHAR_MAX;
	for (int i = 0; i < N; ++i)
		if (A & (1 << i))
			++n;
}

Set::Set(char *B) :
		n(0), S('A' + cnt++), A(0) {
	for (int j = 0; j < N; ++j)
		for (int i = 0; B[i]; ++i)
			if (univers[j] == B[i]) {
				A += 1 << j;
				++n;
			}

	if (isOutput) {
		cout << "Создано " << S << "(" << n << ")" << " = [";
		printA();
		cout << "]" << endl;
	}
}

Set::Set() :
		n(0), S('A' + cnt++), A(0) {

	if (isOutput) {
		cout << "Создано пустое " << S << "(" << n << ")" << " = [";
		printA();
		cout << "]" << endl;
	}
}

Set::Set(const Set &B) :
		S('A' + cnt++), n(B.n), A(0) {
	A = B.A;
	if (isOutput) {
		cout << "Создано " << S << "(" << n << ")" << " = [";
		printA();
		cout << "] из " << B.S << "(" << B.n << ")" << " = [" << B.A << "]"
				<< endl;
	}
}

Set& Set::operator &=(const Set &B) {
	A &= B.A;

	n = 0;
	for (int i = 0; i < N; ++i)
		if (A & (1 << i))
			++n;

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
	A |= B.A;

	n = 0;
	for (int i = 0; i < N; ++i)
		if (A & (1 << i))
			++n;

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
		n = B.n;
		A = B.A;
	}
	if (isOutput) {
		cout << S << " = " << B.S << "(" << n << ") = [";
		printA();
		cout << "]" << endl;
	}
	return *this;
}
/* BITS_H_ */
