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
//

//1.6

//   i<d-1       v[i]==v[i+1]   ct    v[ct]==v[ct+1]     lungime     ct       i     i
//   0<5 da           nu         -          -               -         -       -     1
//   1<5 da           da         1        5=5 da            2         2       -     -
//     -               -         -        5=5 da            3         3       -     -
//     -               -         -        5=1 nu            3         3       3     3
//   4<5 da           da         4        1=1 da            2         5       -     -
//   5<5 nu       
void solutie6() {
	int v[100] = { 2,5,5,5,1,1,1,1};
	int d = 6;

	int lungimeMax = 1;
	int valoare = v[0];

	for (int i = 0;i < d - 1;i++) {
		int lungime = 1;
		if (v[i] == v[i + 1]) {
			int ct = i;
			while (v[ct] == v[ct + 1]) {
				lungime++;
				ct++;
			}
			i = ct;
		}
		
		if (lungime > lungimeMax) {
			lungimeMax = lungime;
			valoare = v[i];
		}
		
	}

	cout << "valoare " << valoare << ", lungime " << lungimeMax << endl;

}
//

//2.1
int sumaCifrelor(int n) {
	int s = 0;

	while (n != 0) {
		int cif = n % 10;
		s = s + cif;
		n = n / 10;
	}

	return s;

}

void solutie7() {
	int v[100] = { 213,45,1000 };
	int d = 3;
	int nou[100];
	int ct = 0;

	for (int i = 0;i < d;i++) {
		int suma = sumaCifrelor(v[i]);
		nou[ct] = suma;
		ct++;
	}

	afisare(nou, ct);

}


int oglindit(int n) {
	int nou = 0;

	while (n != 0) {
		int cif = n % 10;
		nou = nou * 10 + cif;
		n = n / 10;
	}

	return nou;

}

