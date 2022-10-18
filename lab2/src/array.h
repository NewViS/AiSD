/*
 *  array.h
 *
 *  Created on: 9 окт. 2022 г.
 *      Author: Pesterev
 */

#include <cstdlib>
#include <random>
#include <cstring>

#pragma once
using namespace std;

class Set {
private:
	static int N, cnt;
	static char univers[];
	int n;
	char S, *A;
public:
	static bool isOutput;

	Set();
	Set(const Set&);
	Set(char *B);

	Set& operator &=(const Set &B);
	Set& operator |=(const Set &B);

	Set operator |(const Set&) const;
	Set operator &(const Set&) const;
	Set& operator =(const Set &B);

	~Set() {
		delete[] A;
		if(isOutput) cout << S <<" deleted"<< endl;
		//cnt--;
	}

	void show();
	void fillRand();
	void alphSort(const Set &B);

};
int Set::N = 16;
int Set::cnt = 0;
char Set::univers[] = "0123456789abcdef";
bool Set::isOutput = false;

void Set::show() {
	cout << S << "=[" << A << "]" << endl;
}

void Set::fillRand() {
	for (int i = 0; i < N; ++i)
		if (rand() % 2)
			A[n++] = univers[i];

	A[n] = 0;
}

void Set::alphSort(const Set &B){
	char tmp;
	for (int i = 0; B.A[i]; ++i) {
				for (int j = i + 1; B.A[j]; ++j) {
					if (B.A[i] > B.A[j]) {
						tmp = B.A[i];
						B.A[i] = B.A[j];
						B.A[j] = tmp;
					}
				}
			}

	if(isOutput) cout << B.S << " sorted" << endl;
}

Set::Set(char *B) : n(0), S('A' + cnt++), A(new char[N + 1])  {
	for (int i = 0; B[i]; ++i)
		A[n++] = B[i];

	A[n] = 0;
	if(isOutput) cout << S << " created"<<endl;
}

Set::Set() :
		n(0), S('A' + cnt++), A(new char[N + 1]) {
	A[0] = 0;

	if(isOutput) cout << S << " created"<<endl;
}

Set::Set(const Set &B) :
		S('A' + cnt++), n(B.n), A(new char[N + 1]) {
	char *dst(A), *src(B.A);
	while (*dst++ = *src++);
	if(isOutput) cout << S << " created"<<endl;
}

Set& Set::operator &=(const Set &B) {
	Set C(*this);
	n = 0;
	for (int i = 0; i < C.n; ++i) {
		for (int j = 0; j < B.n; j++) {
			if (C.A[i] == B.A[j])
				A[n++] = C.A[i];
		}
	}
	A[n] = 0;

	if(isOutput) cout << S << " &= " << B.S << endl;
	cnt--;
	return *this;
}

Set Set::operator &(const Set &B) const {
	Set C(*this);
	C &= B;
	if(isOutput) cout << C.S << " = " << B.S <<" & "<< S << endl;
	return C;
}

Set& Set::operator |=(const Set &B) {
	bool f;
	for (int i = 0; i < B.n; i++) {
		f = true;
		for (int j = 0; j < n; ++j)
			if (B.A[i] == A[j])
				f = false;
		if (f)
			A[n++] = B.A[i];
	}
	A[n] = 0;

	alphSort(*this);

	if(isOutput) cout << S << " |= " << B.S << endl;
	return *this;
}

Set Set::operator |(const Set &B) const {
	Set C(*this);
	C |= B;
	if(isOutput) cout << C.S << " = " << B.S <<" | "<< S << endl;
	return C;

}

Set& Set::operator =(const Set &B) {
	if (this != &B) {
		char *dst(A), *src(B.A);
		n = B.n;
		while (*dst++ = *src++)
			;
	}

	if(isOutput) cout << S << " = " << B.S << endl;
	return *this;
}

