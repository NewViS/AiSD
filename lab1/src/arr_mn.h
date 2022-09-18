/*
 * arr_mn.cpp
 *
 *  Created on: 18 сент. 2022 г.
 *      Author: vecto
 */
#include <iterator>
using namespace std;

class ArrMn{
public:
	void intersect(char* a, char* b, char* c){

		int n = 0;

		for(int i = 0; a[i]; ++i){
			for(int j = 0; b[j]; ++j){
				if(a[i]==b[j]){
					c[n++]=a[i];
				}
			}
		}
		c[n]=0;
	};

	void unite(char* a, char* b, char* c){
		bool elem_in_c;
		int n = 0;

		for(int i = 0; a[i]; ++i){
			c[n++]=a[i];
		}
		for(int i = 0; b[i]; ++i){
			elem_in_c = false;
			for(int j = 0; c[j]; ++j){
				if(b[i]==c[j]){
					elem_in_c = true;
				}
			}
			if(!elem_in_c)	c[n++]=b[i];
		}
		c[n]=0;
	}

};


