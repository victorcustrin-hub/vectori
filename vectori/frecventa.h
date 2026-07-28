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
	int ct = 0;

	for (int i = 0;i < d;i++) {
		f[v[i]]++;
	}
	
	for (int i = 10;i < 99;i++) {
		if(f[i]!=0)
		cout << "in vector apare " << i << " de " << f[i] << " ori " << endl;
	}

}