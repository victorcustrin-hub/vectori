#pragma once
#include <iostream>
using namespace std;
#include <cmath>

bool prim(int n) {
	if (n <= 1) {
		return false;
	}
	for (int k = 2;k <= n/2;k++) {
		if (n % k == 0) {
			return false;
		}
	}
	return true;
}

int cmmdc(int a, int b) {

	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void solutie1a() {
	int v[100] = { 5};
	int d = 5;
	int ct = 0;

	for (int i = 0;i < d-1;i++) {
		if (cmmdc(v[i],v[i+1])==1) {
			ct++;
		}
	}
    
	cout << ct;

}
//

//b Afisati toate dubletele care au acelasi nr de cifre
int numarCifre(int n) {
	int ct = 0;
	n = abs(n);

	if (n == 0) {
		return 1;
	}

	while (n != 0) {
		ct++;
		n = n / 10;
	}
	return ct;
}

void solutie1b() {
	int v[100] = { -5, 0, 44, -12, 100 };
	int d = 5;

	for (int i = 0;i < d - 1;i++) {
		for (int j = i + 1;j < d;j++) {
			int x = numarCifre(v[i]);
			int y = numarCifre(v[j]);
			
			if (x == y) {
				cout << v[i] << " " << v[j] << endl;
			}

		}
	}
}

//c) alipiti toate perechile dublete de numere care au aceleasi cifre dar in ordine inversa
int oglindit(int n) {
	int ogl = 0;
	while (n != 0) {
		int cif = n % 10;
		ogl = ogl * 10 + cif;
		n = n / 10;
	}

	return ogl;
}

void solutie1c() {
	int v[100] = { 11, 22, 11, 34, 43 };
	int d = 5;

	for (int i = 0;i < d - 1;i++) {
		for (int j = i+1;j < d;j++) {
			if (v[i] == oglindit(v[j])) {
				cout << v[i] << v[j] << endl;
			}
		}
	}
}

//d)sa se afiseze dubletele alaturate ce sunt palindrome intre ele
bool palindrom(int n,int x) {
	int nou = 0;

	while (n != 0) {
		int cif = n % 10;
		nou = nou * 10 + cif;
		n = n / 10;
	}

	if (nou == x) {
		return true;
   }
	return false;

}

void solutie1d() {
	int v[100] = { 12, 34, 56, 78 };
	int d = 4;

	for (int i = 0;i < d-1;i++) {
		if (palindrom(v[i], v[i + 1])) {
			cout << v[i] << " " << v[i + 1] << endl;
		}
	}
}
