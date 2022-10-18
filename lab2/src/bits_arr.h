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
		delete[] A;
		if(isOutput) cout << S <<" deleted"<< endl;
	}

	void show();
	void fillRand();
};

int Set::N = 16;
int Set::cnt = 0;
char Set::univers[] = "0123456789abcdef";
bool Set::isOutput = false;

void Set::show() {
	cout << S << "=[";
	for(int i =0; i<N; ++i) if(A[i]) cout << univers[i];
	cout <<']'<<endl;
}

void Set::fillRand() {
	for (int i = 0; i < N; ++i)
		if(A[i] = rand()%2) ++n;
}

Set::Set(char *B) : n(0), S('A' + cnt++), A(new bool[N]{})  {
	for (int j = 0; j < N; ++j)
		for (int i = 0; B[i]; ++i)
			if(univers[j] == B[i]){
				A[j] = true;
				++n;
			}

	if(isOutput) cout << S << " created"<<endl;
}

Set::Set() :
		n(0), S('A' + cnt++), A(new bool[N]{}){
	if(isOutput) cout << S << " created"<<endl;
}

Set::Set(const Set &B) :
		S('A' + cnt++), n(B.n), A(new bool[N]{}) {
	bool *dst(A), *src(B.A);
	for (int i = 0; i < N; ++i) (*dst++ = *src++);
	if(isOutput) cout << S << " created"<<endl;
}

Set& Set::operator &=(const Set &B) {
	for(int i = 0; i<N; ++i){
		A[i]&=B.A[i];
	}

	if(isOutput) cout << S << " &= " << B.S << endl;
		cnt--;

	return *this;
}

Set Set::operator &(const Set &B) const {
	Set C(*this);
	if(isOutput) cout << C.S << " = " << B.S <<" & "<< S << endl;
	return (C &= B);
}

Set& Set::operator |=(const Set &B) {
	for (int i = 0; i < N; ++i) {
		A[i] |= B.A[i];
	}
	if(isOutput) cout << S << " |= " << B.S << endl;
	return *this;
}

Set Set::operator |(const Set &B) const {
	Set C(*this);
	if(isOutput) cout << C.S << " = " << B.S <<" | "<< S << endl;
	return (C |= B);

}

Set& Set::operator =(const Set &B) {
	if (this != &B) {
		bool *dst(A), *src(B.A);
		n = B.n;
		for (int i = 0; i < N; ++i) (*dst++ = *src++);
	}
	if(isOutput) cout << S << " = " << B.S << endl;
	return *this;
}

