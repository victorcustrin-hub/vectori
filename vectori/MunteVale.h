#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//todo functie ce sorteaza crescator pana la un  index

void sortatCrescatorInterval(int v[], int start, int finish) {
	bool sortat = true;
	do {
		sortat = true;
		for (int i = start;i < finish;i++) {
			if (v[i] > v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}
	} while (sortat == false);

}

void sortatDescrescatorInterval(int v[], int start, int finish) {
	bool sortat = true;

	do {
		sortat = true;
		for (int i = start;i < finish;i++) {
			if (v[i] < v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}
	} while (sortat == false);

}

void afisare(int v[],int d) {

	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}

	cout << endl;
}


void solutie() {
	int v[100] = { 99,31,54,16,17,63 };
	int d = 6;
	int start = 2;
	int finish = 4;
	int poz = 4;


	sortatCrescatorInterval(v,0,poz);
	sortatDescrescatorInterval(v,poz,d-1);
	afisare(v, d);
}


//Exercitii poza


//1
int divProprii(int n) {
	if (n <= 3) {
		return 0;
	}

	int ct = 0;

	for (int i = 2;i <=n/2;i++) {
		if (n % i == 0) {
			ct++;
			
		}
	}
	return ct;
}

int deterPozitie1Ex1(int v[],int d) {
	int ct = 0;
	int pozitie = -1;

	for (int i = 0;i < d;i++) {
		int div = divProprii(v[i]);
		if (div >= 3 && div <= 5) {
			ct++;
			if (ct == 4) {
				pozitie = i;
				break;
			}
		}
	}

	if (pozitie == -1) {
		return 0;
	}
	return pozitie;
}

void sortareMunte(int v[], int dim, int pozControl) {
	
	
	sortatCrescatorInterval(v, 0, pozControl);
	sortatDescrescatorInterval(v, pozControl, dim - 1);
}

void sortareVale(int v[], int dim, int pozControl) {

	sortatDescrescatorInterval(v, 0, pozControl);
	sortatCrescatorInterval(v, pozControl, dim - 1);



}


void solutie1() {
	int v[100] = { 12,16,7,18,28,20,13,9,11,27 };
	int d = 10;
	
	int poz=deterPozitie1Ex1(v,d);
	if (poz == -1) {
		cout << "Nu exista al 4-lea element cu 3-5 divizori proprii" << endl;
		return;
	}
	sortatCrescatorInterval(v, 0, poz);
	sortatDescrescatorInterval(v, poz, d - 1);
	afisare(v,d);

}
//

//2
int baza2(int n) {
	int ct = 0;

	while (n != 0) {

		if (n % 2 == 1) {
			ct++;
		}
		n = n / 2;
	}
	return ct;
}

int ctCifre1(int n) {
	int ct = 0;
	while (n != 0) {
		int cif = n % 10;
		if (cif == 1) {
			ct++;
		}
		n = n / 10;
	}
	return ct;
}



