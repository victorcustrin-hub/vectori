#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//1.1
int medieAritmetica(int v[], int d) {
	double suma = 0;

	for (int i = 0;i < d;i++) {
		suma = suma + v[i];
	}

	if (d == 0) {
		return 0;
	}

	return suma/d;
}

void solutie1() {
	int v[100] = { 13,19,32,54,99 };
	int d = 5;
	int medie = medieAritmetica(v, d);
	int ct = 0;

	for (int i = 0;i < d;i++) {
		if (v[i] > medie) {
			ct++;
		}
	}

	cout << ct << endl;

}
//

//1.2
void afisare(int v[],int d) {

	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}


}

void solutie2() {
	int v[100] = { 7,4,9,6,2,5 };
	int d = 6;
	int nou[100];
	int ct = 0;

	for (int i = 0;i < d;i++) {
		if (i % 2 == 0) {
			nou[ct] = v[i];
			ct++;
		}
	}

	afisare(nou, ct);

}
//

//1.3
void solutie3() {
	int v[100] = { 3,8,5,9,4 };
	int d = 5;

	for (int i = 0;i < d;i++) {
		if (i != 0 && i != d - 1) {
			if (v[i] > v[i + 1] && v[i] > v[i - 1]) {
				cout << v[i] << " ";
			}
		}
	}

}
//

//1.4
int divProprii(int n) {
	int ct = 0;

	for (int i = 2;i <= n/2;i++) {
		if (n % i == 0) {
			ct++;
		}
	}

	return ct;

}

void solutie4() {
	int v[100] = { 6,7,12 };
	int d = 3;
	int nou[100];
	int ct = 0;

	for (int i = 0;i < d;i++) {
		nou[ct] = divProprii(v[i]);
		ct++;
	}

	afisare(nou, ct);

}
//

//1.5
void solutie5() {
	int v[100] = { 3,9,4,12,5 };
	int d = 5;
	int primul = v[0];

	if (primul != 0) {
		for (int i = 0;i < d;i++) {
			if (v[i] % primul == 0) {
				v[i] = 0;
			}
		}
	}

	afisare(v, d);

}
