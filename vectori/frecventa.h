#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//1e,2e

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
	int d = 6;
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
//

//1d
void solutie1d() {
	int v[100] = { 12,67,23,98,43,99 };
	int d = 6;
	int f[10] = {0};

	for (int i = 0; i < d; i++) {
		int nou = v[i];

		if (nou == 0) {
			f[0] = 1;
		}

		while (nou > 0) {
			int ultimaCif = nou % 10;
			f[ultimaCif] = 1;
			nou = nou / 10;
		}
	}

	cout << "cifrele care nu apar in elementele vectorului sunt: ";
	for (int i = 0; i <= 9; i++) {
		if (f[i] == 0) {
			cout << i << " ";
		}
	}
	cout << endl;
}
//

//
void solutie1e() {
	int v[100] = { 12,67,23,98,43,99 };
	int d = 6;
	int min = v[0];
	int f[10] = { 0 };

	for (int i = 1; i < d; i++) {
		if (v[i] < min) {
			min = v[i];
		}
	}

	int fr_minim = 0;
	for (int i = 0; i < d; i++) {
		if (v[i] == min) {
			fr_minim++;
		}
	}


	for (int i = 0; i < d; i++) {
		int nou = v[i];
		while (nou != 0) {
			int cif = nou % 10;
			f[cif]++;
			nou = nou / 10;
		}
	}

	int cifMax = -1;
	for (int i = 9; i >= 0; i--) {
		if (f[i] != 0) {
			cifMax = i;
			break;
		}
	}

	cout << "elementul minim este " << min << " si apare de " << fr_minim << " ori" << endl;
	if (cifMax != -1) {
		cout << "Cifra maxima este " << cifMax << " si apare de " << f[cifMax] << " ori." << endl;
	}
}
//

//2a

void frecventaCif(int n,int f[]) {
	while (n != 0) {
		int cif = n % 10;
		f[cif]++;
		n = n / 10;
	}
}

void solutie2a() {
	int n = 2534782;
	int f[10]={0};

	frecventaCif(n,f);

	for (int i = 0;i < 10;i++) {
		cout << i << " apare de " << f[i] << " ori" << endl;
	}
}
//

//2b
void solutie2b() {
	int n = 122233335;
	int k = 3;
	int f[10] = { 0 };

	frecventaCif(n, f);

	for (int i = 0;i < 10;i++) {
		if (f[i] > k) {
			cout << i << " apare de " << f[i] << " ori, cu "<< f[i] - k<<" ori mai mult decat k="<< k  << endl;
		}
	}
}
//

//2c
void solutie2c() {
	int n = 24680;
	int f[10] = { 0 };
	int aux = n;
	
	frecventaCif(n, f);
	int nou = 0;

	for (int i = 1; i <= 9; i = i+2) {
		if (f[i] == 0) {
			nou = nou * 10 + i;
		}
	}
	cout << nou;
}
//

//2d
void solutie2d() {
	int n = 14371252;
	int f[10] = { 0 };

	frecventaCif(n, f);
	
	int nou = 0;

	for (int i = 9; i >= 0; i--) {
		int ct = f[i];
		if (ct > 2) {
			ct = 2;
		}

		for (int j = 1; j <= ct; j++) {
			nou = nou * 10 + i;
		}
	}
	cout << nou;
}
//

//2e
void solutie2e() {
	int n = 1432313;
	int f[10] = { 0 };

	int aux = n;
	frecventaCif(aux, f);

	int fMax = 0;
	for (int i = 0; i <= 9; i++) {
		if (f[i] > fMax) {
			fMax = f[i];
		}
	}

	int cif = 0;
	for (int i = 0; i <= 9; i++) {
		if (f[i] > 0) {
			cif = cif + (fMax - f[i]);
		}
	}

	cout << cif;
}
//

//2f
void afisare(int v[], int d) {

	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}

}

void solutie2f() {
	int n = 2341;
	int f[10] = { 0 };
	int nou[100];
	int ct = 0;
   
	frecventaCif(n, f);

	for (int i = 1;i <= 9;i++) {
		if ((i == 2 || i == 3 || i == 5 || i == 7) && f[i] == 0) {
			nou[ct]=i;
			ct++;
		}
	}
	afisare(nou, ct);
}
//

//2g
void solutie2g() {
	int n = 431245;
	int f[10] = { 0 };

	frecventaCif(n, f);
	int nou = 0;
	for (int i = 1;i < 10;i++) {
		for (int j = 1; j <= f[i]; j++) {
			nou = nou * 10 + i;
		}
	}

	cout << nou;

}
//