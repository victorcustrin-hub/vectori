#pragma once
#include <iostream>
#include <cmath>
using namespace std;


int sumaCifrelor(int n) {
	int s = 0;
	while (n != 0) {
		int cif = n % 10;
		s = s + cif;
		n = n / 10;
	}

	return s;
}

void afisare(int v[],int d) {

	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}

}

//EXERCITIUL 1
//a
void solutie1a() {
	int v[200] = { 213,523,126,236,946,214 };
	int d = 6;
	int nou[200];


	for (int i = 0;i < d;i++) {
		nou[i] = sumaCifrelor(v[i]);
	}
	afisare(nou, d);

}

bool palindrom(int n) {
	int nou = 0;
	int x = n;
	while (n != 0) {
		int cif = n % 10;
		nou = nou * 10 + cif;
		n = n / 10;
	}

	if (x == nou) {
		return true;
	}
	return false;
}
//

//b
int cmmdc(int a, int b) {
	while (a != b) {
		if (a > b) {
			a = a - b;
		}
		if (b > a) {
			b = b - a;
		}
	}
	return a;
	
}

void solutie1b() {
	int v[200] = { 121,22,13,505,55,14};
	int d = 6;
	int nou[200];
	int ct = 0;
	for (int i = 0;i < d;i++) {
		int poz = i + 1;

		if (cmmdc(v[i],poz)==1&&palindrom(v[i])) {
			nou[ct] = v[i];
			ct++;
	   }

	}

	afisare(nou,ct);

}
//

//c
bool progresieAritmetica(int n,int r) {

	int cifu = n % 10;
	n = n / 10;
	while (n > 9) {
	
		int cifp = n % 10;
		if (cifp - cifu != r) {
			return false;
		}

		cifu = cifp;
		n = n / 10;


	}
	return true;

}

void solutie1c() {
	int ratie = 2;
	int v[200] = { 6420,8642,753,135,642 };
	int d = 5;
	int nou[200];
	int ct = 0;


	for (int i = 0;i < d;i++) {
		if (progresieAritmetica(v[i], ratie)) {
			nou[ct] = v[i];
			ct++;
		}
	}

	afisare(nou, ct);

}
//

//d
bool primCifEgalCuUltimCif(int n) {
	int cif = n % 10;

	while (n > 9) {
		n = n / 10;
	}

	if (cif == n) {
		return true;
	}
	return false;

}

bool cifreInBazaQ(int n, int q, int k, int t) {
	int ct = 0;
	while (n > 0) {
		if (n % q == t) {
			ct++;
		}
		n = n / q;
	}

	if (ct >= k) {
		return true;
	}
	return false;
}

void solutie1d() {
	int v[200] = { 121,54,303,4,9,414 };
	int d = 6;
	int nou[200];
	int ct = 0;
	int q = 2;
	int k = 2;
	int t = 1;

	for (int i = 0;i < d;i++) {
		if (cifreInBazaQ(v[i], q, k, t) && primCifEgalCuUltimCif(v[i])) {
			nou[ct] = v[i];
			ct++;
		}
	}

	afisare(nou, ct);

}
//

//INCEPUT TEMA
//e
bool prim(int n) {
	if (n <= 1) {
		return false;
	}

	for (int i = 2;i <= n / 2;i++) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;

}

bool superprim(int n) {

	while (n > 0) {
		if (prim(n) == false) {
			return false;
		}
		n = n / 10;
	}

	return true;
}

void solutie1e() {
	int v[] = { 12, 239, 45, 23, 100 };
	int d = 5;
	int nou[200];
	int ct = 0;

	for (int i = 0; i < d; i++) {
		if (superprim(v[i])) {
			nou[ct] = i + 1; 
			ct++;
		}
	}

	afisare(nou, ct);
}
//

//f
int sumaPuteri(int n) {
	int s = 0;
	int d = 2;

	while (n > 1) {
		int p = 0;
		while (n % d == 0) {
			p++;
			n = n / d;
		}
		if (p > 0) {
			s = s + p;
		}
		d++;
	}
	return s;
}

void solutie1f() {
	int v[100] = { 12, 100, 7, 30, 27 };
	int d = 5;
	int nou[200];
	int ct = 0;

	for (int i = 0; i < d; i++) {
		nou[ct] = sumaPuteri(v[i]);
		ct++;
	}


	afisare(nou, ct);
}
//

//g
bool cifMin(int n, int k) {
	int min = 10;

	while (n != 0) {
		int cif = n % 10;
		if (cif < min) {
			min = cif;
		}
		n = n / 10;
	}

	if (min == k) {
		return true;
	}
	return false;
}

void solutie1g() {
	int v[100] = { 652,43,634,195,439};
	int d = 5;
	int k = 3;
	int nou[200];
	int ct = 0;

	for (int i = 0; i < d; i++) {
		if (cifMin(v[i],k)) {
			nou[ct] = i;
			ct++;
		}
	}


	afisare(nou, ct);
}
//

//h
int cifControl(int n) {
	int r = n % 9;
	if (r == 0) {
		return 9;
	}
	return r;
}

void solutie1h() {
	int v[100] = { 542,741,834,4561,999 };
	int d = 5;
	int nou[200];

	for (int i = 0; i < d; i++) {
		nou[i] = cifControl(v[i]);
	}


	afisare(nou, d);
}
//

//EXERCITIUL 2

//a
int nrDubletePrime(int v[], int d) {
	int ct = 0;

	for (int i = 0; i < d - 1; i++) {
		if (cmmdc(v[i], v[i + 1]) == 1) {
			ct++;
		}
	}

	return ct;
}

void solutie2a() {
	int v[100] = { 12, 25, 10, 21 };
	int d = 4;

	cout << nrDubletePrime(v, d);

}
//

//b
int nrCifre(int n) {
	int ct = 0;

	while (n != 0) {
		ct++;
		n = n / 10;
	}
	return ct;
}

void solutie2b() {
	int v[100] = { 45, 12, 7, 103, 564 };
	int d = 5;

	for (int i = 0; i < d; i++) {
		if (nrCifre(v[i]) == nrCifre(v[i + 1])) {
			cout << v[i] << "," << v[i + 1] << endl;
		}
	}
}
//

//c
int ogl(int n) {
	int nou = 0;
	int aux = n;
	while (n != 0) {
		int cif = n % 10;
		nou = nou * 10 + cif;
		n = n / 10;
	}

	return nou;

}
void solutie2c() {
	int v[100] = { 213,312,564,153,673,376};
	int d = 6;

	for (int i = 0; i < d; i++) {
		for (int j = i + 1; j < d; j++) {
			if (v[i] == ogl(v[j])) {
				cout << v[i] << v[j] << endl;
			}
		}
	}
}
//

//d
bool palindrom(int n,int k) {
	int ogl = 0;

	while (n != 0) {
		int cif = n % 10;
		ogl = ogl * 10 + cif;
		n = n / 10;
	}

	if (ogl == k) {
		return true;
	}
    
	return false;

}

void solutie2d() {
	int v[100] = { 4321,1234,5414,6531,6425,5246 };
	int d = 5;

	for (int i = 0; i < d; i++) {
		if (palindrom(v[i],v[i+1])) {
			cout << v[i] << "," << v[i + 1] << endl;
		}
	}
}
//

//e
void solutie2e() {
	int v[] = { 12, 458, 73, 90, 5 };
	int d = 5;
	int nou[100];
	int ct = 0;

	for (int i = 0; i < d; i++) {
		int numarOglindit = ogl(v[i]);
		if (cifControl(v[i]) == cifControl(numarOglindit)) {
			nou[ct] = numarOglindit;
			ct++;
		}
	}

	afisare(nou, ct);
}