#pragma once
#include <iostream>
using namespace std;
#include <cmath>

//1d,1e

//FISA
//ex1
//a)
void afisare(int v[], int d) {

	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}

	cout << endl;

}

void stergereElement(int v[], int& dim, int poz) {

	for (int i = poz;i < dim;i++) {
		v[i] = v[i + 1];
	}

	dim--;
}


bool prim(int n) {
	if (n <= 1) {
		return false;
	}
	for (int k = 2;k <= n / 2;k++) {
		if (n % k == 0) {
			return false;
		}
	}
	return true;
}

void inserareElement(int v[], int& dim, int poz, int elem) {

	for (int i = dim;i > poz;i--) {
		v[i] = v[i - 1];
	}
	dim++;
	v[poz] = elem;
}


void solutie1a() {
	int v[100] = { 34, 17, 85, 29, 93, 71, 13, 44, 47, 62 };
	int d = 10;
	int ct = 0;
	int poz = -1;


	for (int i = 0;i < d && poz == -1;i++) {
		if (prim(v[i])) {
			ct++;

		}
		if (ct == 3) {
			poz = i;
		}
		stergereElement(v, d, poz);
		afisare(v, d);
	}
}
//

//b)
bool primEgalCuUltimCif(int n) {
		int x = n % 10;


		while (n >9 ) {
			n = n / 10;
		}
        
		if (n == x) {
			return true;
		}
		return false;
	}


void solutie1b() {	
	int v[100] = { 5, 11, 23, 121, 7, 88, 90, 505, 12 };
	int d = 9;
	int ct = 0;

	for (int i = 0;i < d;i++) {
		if (v[i] > 9 && primEgalCuUltimCif(v[i])) {
			stergereElement(v, d, i);
			i--;
		}
	}
	afisare(v, d);
}
//

//c)
bool nul(int n) {
	if (n == 0) {
		return true;
	}
	return false;
}

void solutie1c() {
	int v[100] = { 9, 0, 0, 5 };
	int d = 4;

	for (int i = 0; i < d; i++) {
		if (nul(v[i])) {
			stergereElement(v, d, i); 
			i--;
		}
	}

	afisare(v, d);
}
//

//d)
bool seAflainInterval(int n, int min, int max) {
	if (n >= min&& n <= max) {
		return true;
	}
	return false;
}

void solutie1d() {
	int v[100] = { 5, 11, 23, 121, 7, 88, 90, 505, 12 };
	int d = 9;
	int a = 3;
	int b = 5;
	int min = a;
	int max = b;

	if (a > b) {
		min = b;
		max = a;
	}

	for (int i = 0; i < d; i++) {
		if (seAflainInterval(v[i], min, max)) {
			stergereElement(v, d, i);
			i--;
		}
	}

	afisare(v, d);
}
//

//e)
bool patratPerfect(int n) {
	int rad = sqrt(n);

	if (rad * rad == n) {
		return true;
	}
	return false;
}

void solutie1e() {
	int v[100] = { 49, 145, 1254, 64, 7, 89, 16, 26, 81, 36 };
	int d = 10;

	for (int i = 0; i < d; i++) {
		if (patratPerfect(v[i])) {
			stergereElement(v, d, i);
			i--;
		}
	}

	afisare(v, d);
}
//

//f)
bool superPrim(int n) {
	if (n <= 1) return false;

	while (n != 0) {
		if (prim(n) == 0) {
			return false;
		}
		n = n / 10;
	}
	return true;
}

void solutie1f() {
	int v[100] = { 239, 5, 12, 23, 8, 29 };
	int d = 6;
	bool sPrim = false;

	
	for (int i = 0; i < d; i++) {
		if (superPrim(v[i])) {
			sPrim = true;
			stergereElement(v, d, i);
			i--;
		}
	}

	if (sPrim==false) {
		cout << "nu sunt elemente super prime in vector"<<endl;
	}
	else if (d == 0) {
		cout << "Toate elementele sunt prime, toate au fost sterse"<<endl;
	}
	else {
		afisare(v, d);
	}
}

