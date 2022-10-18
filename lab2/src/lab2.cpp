//============================================================================
// Name        : lab2.cpp
// Author      : Pesterev
// Version     :
// Description : Исследование возможностей обработки множеств как объектов
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

using namespace std;
//#include "array.h"
#include "bits_arr.h"

int main() {
	locale::global(locale("Russian"));
	srand(time(nullptr));

	int iterate = 1000000;

	Set::isOutput = false;

	//Set A("034789ab"), B("01245789cf"), C("345678abf"), D("0489bcdf"), E;
	//Set A("14689ef"), B("68bcdf"), C("02479abcd"), D("01389abe"), E;
	Set A("3ef"), B("1589ef"), C("4578bde"), D("012345678bcf"), E;

	clock_t t;

	/*
	A.fillRand();
	B.fillRand();
	C.fillRand();
	D.fillRand();
	 */
	A.show();
	B.show();
	C.show();
	D.show();

	t = clock();
	for(int i = 0; i < (A.isOutput ? 1 : iterate); i++) E = (A | (B & C & D));
	t = clock() - t;

	E.show();

	cout <<"time: "<< t;

	return 0;
}
