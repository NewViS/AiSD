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
	for(int i =0; i<N; ++i) if(A & (1<<i)) cout << univers[i];
	cout <<']'<<endl;
}

void Set::fillRand() {
	A = rand()%UCHAR_MAX;
}

Set::Set(char *B) : n(0), S('A' + cnt++), A(0)  {
	for (int j = 0; j < N; ++j)
		for (int i = 0; B[i]; ++i)
			if(univers[j] == B[i]){
				A += 1<<j;
				++n;
			}

	if(isOutput) cout << S << " created"<<endl;
}

Set::Set() :
		n(0), S('A' + cnt++), A(0){
	if(isOutput) cout << S << " created"<<endl;
}

Set::Set(const Set &B) :
		S('A' + cnt++), n(B.n), A(0) {
	A = B.A;
	if(isOutput) cout << S << " created"<<endl;
}

Set& Set::operator &=(const Set &B) {
	A &= B.A;

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
	A |= B.A;
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
		n = B.n;
		A = B.A;
	}
	if(isOutput) cout << S << " = " << B.S << endl;
	return *this;
}
 /* BITS_H_ */
