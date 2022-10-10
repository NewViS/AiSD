//============================================================================
// Name        : lab2.cpp
// Author      : Pesterev
// Version     :
// Description : Исследование возможностей обработки множеств как объектов
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;
#include "array.h"

int main() {
	locale::global(locale("Russian"));
	srand(time(0));

	int iterate = 1;

	Set A, B, C, D, E;

	A.fillRand();
	B.fillRand();
	C.fillRand();
	D.fillRand();

	A.show();
	B.show();
	C.show();
	D.show();

	for(int i = 0; i < (A.isOutput ? 1 : iterate); i++) E = (A | (B & C & D));

	E.show();

	return 0;
}
