#pragma once
#include <iostream>
#include <cmath>
using namespace std;



void afisare(int v[],int dim) {
	

	for (int i = 0;i < dim;i++) {
		cout << v[i] << " ";
	}
	cout << endl;


}

int nrPar(int v[], int n) {
	int ctPar = 0;

	for (int i = 0;i < n;i++) {
		if (v[i] % 2 == 0) {
			ctPar++;
		}
	}

	return ctPar;

}

int nrImp(int v[], int n) {
	int ctImp = 0;

	for (int i = 0;i < n;i++) {
		if (v[i] % 2 == 1) {
			ctImp++;
		}
	}
	return ctImp;
}

void solutie1() {
	int v[100] = { 15,245,28,33,11 };
	int dim = 5;
	int par = nrPar(v, dim);
	int imp = nrImp(v, dim);

	cout << abs(par - imp) << endl;;

}

//sa se afiseze elementele din vectori care sunt multiplii ai ultimului element
void solutie2() {
	int v[100] = { 7,4,9,6,2 };
	int d = 5;
	int numar = v[d-1];

	for (int i = 0;i < d;i++) {
		if (numar!=0&&v[i] % numar == 0) {
			cout << v[i] << " ";
		}
	}


}

// Să se înlocuiască ultimul element prim din vector cu 0, apoi să se afișeze vectorul.

bool prim(int n) {
	
	if (n == 0 || n == 1) {
		return false;
	}

	for (int k = 2;k <= n / 2;k++) {
		if (n % k == 0) {
			return false;
		}
	}
	return true;

}


int ultimPrim(int v[], int n) {
	for (int i = n - 1;i >= 0;i--) {
		if (prim(v[i])) {
			return i;
		}
	}
	return -1;
}

void solutie3() {
	int v[100] = { 12,1,3,19,23,24 };
	int d = 6;

	int rez = ultimPrim(v, d);
	for (int i = 0;i < d;i++) {
		if (i == rez) {
			v[i] = 0;
		}
		cout << v[i] << " ";
	}
		
}

// Să se înlocuiască fiecare element prim din vector cu 0, apoi să se afișeze vectorul.
void solutie4() {
	int v[100] = { 5,22,31,33,41 };
	int d = 5;

	for (int i = 0;i < d;i++) {
		if (prim(v[i])) {
			v[i] = 0;
		}
		cout << v[i] << " ";
	}
}

