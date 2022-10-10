/*
 *  array.h
 *
 *  Created on: 9 окт. 2022 г.
 *      Author: Pesterev
 */

#include <cstdlib>
#include <random>

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

	Set& operator &=(const Set &B);
	Set& operator |=(const Set &B);

	Set operator |(const Set&) const;
	Set operator &(const Set&) const;
	Set& operator =(const Set &B);

	~Set() {
		delete[] A;
	}

	void show();
	void fillRand();

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

Set::Set() :
		n(0), S('A' + cnt++), A(new char[N + 1]) {
	A[0] = 0;
}

Set::Set(const Set &B) :
		S('A' + cnt++), n(B.n), A(new char[N + 1]) {
	char *dst(A), *src(B.A);
	while (*dst++ = *src++);
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

	return *this;
}

Set Set::operator &(const Set &B) const {
	Set C(*this);
	return (C &= B);
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
	return *this;
}

Set Set::operator |(const Set &B) const {
	Set C(*this);
	return (C |= B);

}

Set& Set::operator =(const Set &B) {
	if (this != &B) {
		char *dst(A), *src(B.A);
		n = B.n;
		while (*dst++ = *src++)
			;
		S = 'A' + cnt++;
	}
	return *this;
}

