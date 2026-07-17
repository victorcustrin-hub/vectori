#pragma once
#include <iostream>
using namespace std;
#include <cmath>

void afisare(int v[], int d) {

	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}

	cout << endl;

}



//functie ce primeste ca parametru un vector dimensiunea si pozitia si trebuie sa stearga elementul de pe pozitia respectiva
//v[100]={12,54,21,76,32,43,15}, dim=7, pozitie=3

//              0  1    2   3   4    5   6      i
// i<7         12  54   21  32  32  43   15     4
// 4<7 da      12  54   21  32  43  43   15     5
// 5<7 da      12  54   21  32  43  15   15     6    
// 6<6 da      12  54   21  32  43  15   0
//   dim--; => 12  54   21  32  43  15
void stergereElement(int v[],int&dim ,int poz) {
	
	for (int i =poz;i < dim;i++) {
		v[i] = v[i + 1];
	}

	dim--;
}

//v[100]={12,54,21,76,32,43,15}, dim=7, pozitie=3, elem=19

//  i=7          0   1   2   3   4   5    6   7        i
//  7>3 da       12  54  21  76  32  43  15   15       6
//  6>3 da       12  54  21  76  32  43  43   15       5
//  5>3 da       12  54  21  76  32  32  43   15       4
//  4>3 da       12  54  21  76  76  32  43   15       3
//  3>3 nu
void inserareElement(int v[], int& dim, int poz,int elem) {

	for (int i = dim;i > poz;i--) {
		v[i] = v[i-1];
	}
	dim++;
	v[poz] = elem;
}

//FISA
//ex1
//a)
bool prim(int n) {
	if(n <= 1) {
		return false;
	}
	for (int k = 2;k <= n / 2;k++) {
		if (n % k == 0) {
			return false;
		}
	}
	return true;
}

void solutie1a() {
	int v[100] = { 34, 17, 85, 29, 93, 71, 13, 44, 47, 62 };
	int d = 10;
	int ct = 0;
	int poz = -1;
	

	for (int i = 0;i < d&&poz==-1;i++) {
		if (prim(v[i])) {
			ct++;

		}
		if (ct == 3) {
			poz = i;
		}
	}
	cout << poz << endl;
	cout << ct << endl;
	stergereElement(v, d, poz);
	afisare(v, d);
}