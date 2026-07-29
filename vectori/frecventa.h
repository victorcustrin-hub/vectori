#pragma once
#include <iostream>
#include <cmath>
using namespace std;

void frecventaCifraNumar(int numar) {

	int f[10]{};
	while (numar != 0) {
		int cifra = numar % 10;
		f[cifra]++;
		numar = numar / 10;
	}

	for (int i = 0;i < 10;i++) {

		cout << i << " apare de " << f[i] << " ori" << endl;
	}
}

//algoritm de frecventa numar vector de 2 cifre din vector apare 10 de 3 ori
void frecventaNumarVector(int v[],int d) {
	int f[100]{};

	for (int i = 0;i < d;i++) {
		f[v[i]]++;
	}
	
	for (int i = 10;i < 99;i++) {
		if(f[i]!=0)
		cout << "in vector apare " << i << " de " << f[i] << " ori " << endl;
	}

}

//Fisa exercitii
//1a)
//pozitia minimului diferit de zero dintr-un vector oarefcare
int pozElemMinVec(int v[], int d) {
	int poz = -1;
	int minim = 100;
	for (int i = 0;i < d;i++) {
		if (v[i] != 0 && v[i]<minim) {
			minim = v[i];
			poz = i;
		}
	}
	return poz;
	
}

//pozitia maximultui dintr-un vector oarecare
int pozElemMaxVec(int v[], int d) {
	int poz = -1;
	int maxim = -1;

	for (int i = 0;i < d;i++) {
		if (v[i] > maxim) {
			maxim = v[i];
			poz = i;
		}
	}
	return poz;
}


void solutie1a() {
	int v[100] = {5,5,5,2,2,7,8,9};
	int d = 8;

	int f[101]{};

	for (int i = 0;i < d;i++) {
		f[v[i]]++;
	}

	int maxi = pozElemMaxVec(f, 100);
	int min = pozElemMinVec(f, 100);

	cout << "Maximul din vector este " << maxi << " si apare de " << f[maxi] << " ori" << endl;
	cout << "Minimul  din vector este " << min << " si apare de " << f[min] << " ori" << endl;


}
//

//1b
// v[100]={13,24,12,443,3333444}
    
//  0 1 2 3 4 5 6 7 8 9
//  0 0 0 0 0 0 0 0 0 0
//    1   1
//      1   1
//    2 2
//        2 2
//        6 5

void solutie1b() {
	int v[100] = { 21,42,21 };
	int d = 3;
	
	int f[10]{};

	for (int i = 0;i < d;i++) {
		int aux = v[i];
		while (aux != 0) {
			int cifra = aux % 10;
			f[cifra]++;
			aux = aux / 10;
		}
	}
	int minim = pozElemMinVec(f, 10);
	int maxim = pozElemMaxVec(f, 10);
	cout << "Frecventa minima = " << minim << endl;
	cout << "Frecventa maxima = " << maxim << endl;
}
//

//1c
void solutie1c() {
	int v[100] = { 12,67,23,98,43,99 };
	int d = 5;
	int f[101]{};
	
	for (int i = 0;i < d;i++) {
		f[v[i]]++;
	}

	//todo:
	for (int i = 99;i>=10;i--) {
		if (f[i] == 0) {
			cout << "Cel mai mare nr de 2 cifre care lipseste este " << i << endl;
			break;
		}
	}

}