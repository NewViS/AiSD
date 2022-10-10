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
	//cout << S << "=[" << A << "]" << endl;
}

void Set::fillRand() {
	for (int i = 0; i < N; ++i)
		A[i] = rand()%2;
}

Set::Set() :
		n(0), S('A' + cnt++), A(new char[N + 1]) {
	A[0] = 0;
}

