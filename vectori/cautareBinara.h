#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//Obs cautarea binara se face tot timpul pe un vector sortat

//   4<4 nu                          
void sortareaPrinSelectie(int v[], int d) {

	for (int i = 0;i < d;i++) {
		for (int j = i + 1;j < d;j++) {
			if (v[i] > v[j]) {
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}

}

//Obs ve sa fie sortat crescator primna oara



// v[100] = { 2,9,13,16,18,21,33,49 };     d = 8;     key = 21;

//  inf<=sup   mij   v[mij]==key     v[mij]>key     v[mij]<key       inf       sup 
//   0<8 da     4    18==21 false     18>21 false    18<21 true       5         -
//   5<=8da     6    33==21 false     33>21 true     33<21 false      -         5
//   5<=5 da    5    21==21 true       -                -             -         -


//int v[100] = { 5,10,14,16,19,21,26 };
//int d = 8;
//int key = 20;
int cautareaBinara(int v[], int dim, int key) {
	int inf = 0;
	int sup = dim;

	while (inf <= sup) {
		int mij = (inf + sup) / 2;
		if (v[mij] == key) {
			return mij;
		}
		if (v[mij] > key) {
			sup = mij - 1;
		}
		if (v[mij] < key) {
			inf = mij + 1;
		}

	}
	return -1;
}

void verificare() {
	int v[100] = { 5,10,14,16,19,21,26 };
	int d = 6;
	int key = 20;
	int poz = cautareaBinara(v, d, key);

	if (poz != -1) {
		cout << "elementul " << key << " a fost gasit pe pozitia " << poz << endl;
	}
	else {
		cout << "elementul " << key << " nu exista in vector" << endl;
	}
}
