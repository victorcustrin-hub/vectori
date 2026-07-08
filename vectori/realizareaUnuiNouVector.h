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


//
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

//
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

//
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

//
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

//
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
	if (n <= 1) {
		return false;
	}

	int s = 0;

	for (int i = 1;i <= n / 2;i++) {
		if (n % i == 0) {
			s = s + i;
		}
	}

	if (s == n) {
		return true;
	}
	return false;

}