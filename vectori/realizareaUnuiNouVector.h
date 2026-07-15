#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//3e

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
//

//f
int alipire(int a, int b) {
	int aux = b;
	int p = 1;

	while (aux != 0) {
		p = p * 10;
		aux=aux / 10;
	}

	return a * p + b;
}

void solutie2f() {
	int v[100] = { 12, 1234, 34, 5, 35, 3 };
	int d = 6;
	int ct = 0;

	for (int i = 0; i < d - 2; i++) {
		int nr1 = v[i];
		int nr2 = v[i + 1];
		int nr3 = v[i + 2];

		int nrAlipit = alipire(nr1, nr3);

		if (nrAlipit == nr2 || nrAlipit == ogl(nr2)) {
			ct++;
		}
	}
	cout << ct;
}
//

//g
void solutie2g() {
	int v[100] = { 121, 45, 77, 123, 9 };
	int d = 5;
	int nou[100];
	int ct = 0;

	for (int i = 0; i < d; i++) {
		if (palindrom(v[i])) {
			nou[ct] = v[i];
			ct++;
		}
	}

	afisare(nou, ct);

}
//

//EXERCITIUL 3

//a
//incorect
int minim(int v[],int d) {
	 int min = 9999;


	for (int i = 0;i < d;i++) {
		v[i] = abs(v[i]);
		if (v[i] < min) {
			min = v[i];
		}
	}
	
	return min;

}

int maxim(int v[], int d) {
	int max = -9999;

	for (int i = 0;i < d;i++) {
		v[i] = abs(v[i]);
		if (v[i] > max) {
			max = v[i];
		}
	}

	return max;

}

void solutie3a() {
	int v[250] = { -15, -5, 0, 35, 45, 25 };
	int d = 6;
	int min = minim(v, d);
	int max = maxim(v, d);
	int rez = cmmdc(min, max);

	cout << rez << endl;



}
//

//b
int cmmdcNrPareDinVector(int v[], int d) {
	int rez = 0;

	for (int i = 0; i < d; i = i + 2) {
		if (v[i] % 2 == 0) {
			if (rez == 0) {
				rez = v[i];
			}
			else {
				rez = cmmdc(rez, v[i]);
			}
		}
	}
	return rez;
}


void solutie3b() {
	int v[250] = { 3, 4, 5, 8, 7, 12 };
	int d = 6;
	int rez = cmmdcNrPareDinVector(v,d);
	cout << rez << endl;

}
//

//c
int parcursADouaTreime(int v[], int start, int finish) {
	int rez = 0;

	for (int i = start; i < finish; i++) {
		if (prim(v[i])) {
			if (rez == 0) {
				rez = v[i];
			}
			else {
				rez = cmmdc(rez, v[i]);
			}
		}
	}
	return rez;
}

void solutie3c() {
	int v[200] = { 2, 3, 4, 6, 7, 11 };
	int d = 6;
	int start = d / 3;
	int finish = 2 * d / 3;
	int rez = parcursADouaTreime(v, start, finish);
	cout << rez;
}
//

//d
bool crescator(int n) {
	int cif = n % 10;
	n = n / 10;

	while (n != 0) {
		int cif2 = n % 10;
		if (cif2 > cif) {
			return false;
		}

		cif = cif2;
		n = n / 10;
	}

	return true;


}

//gresit
void solutie3d() {
	int v[250] = { 135, 246, 357 };
	int d = 2;
	int rez = 0;

	for (int i = 0; i < d; i++) {
		if (crescator(v[i])) {
			if (rez == 0) {
				rez = v[i];
			}
			else {
				rez = cmmdc(rez, v[i]);
			}
		}
	}

	cout << rez;

}
//

//e
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

void solutie3e() {
	int v[250] = { 12, 8, 24, 15, 36 };
	int d = 5;
	int rez = 0;

	for (int i = 0;i < d;i++) {
		int b2 = baza2(v[i]);

		if (b2 > 2) {
			if (rez == 0) {
				rez = v[i];
			}
			else {
				rez = cmmdc(rez, v[i]);
			}
		}
	}


	cout << rez;

}
//

//f
void solutie3f() {
	int v[250] = {42, 15, 33, 20};
	int d = 4;
	int rez = 0;

	for (int i = 0; i < d; i++) {
		if (cifControl(v[i]) == 6) {
			if (rez == 0) {
				rez = v[i];
			}
			else {
				rez = cmmdc(rez, v[i]);
			}
		}
	}

	cout << rez << endl;
}
//


//CORECTAREA TEMEI

//3 e) care este cmmdc-ul tuturor elementelor ce au mai mult de 2 de 1 dupa conversia lor in baza 2?

int nrInbaza2(int n) {
	int nou = 0;
	int p = 1;

	while (n != 0) {
		int cif = n % 2;
		nou = cif * p + nou;
		p = p * 10;
		n = n / 2;
	}

	return nou;

}

//functie ce  contorizeaza numarul de apaitii a unei cifre in numar

int verificareNrCifrelor(int n, int x) {
	int ct = 0;

	while (n != 0) {
		int cif = n % 10;
		if (cif == x) {
			ct++;
		}
		n = n / 10;

	}
	return ct;
}

void solutieEx3e() {
	int v[100] = { 112, 176, 240 };
	int d = 3;
	int rez = 0;

	for (int i = 0;i < d;i++) {
		int x = nrInbaza2(v[i]);
		if (verificareNrCifrelor(x,1)>2) {
			if (rez == 0) {
				rez = v[i];
			}
			else {
				rez = cmmdc(rez,v[i]);
			}
		}

	}

	cout << rez << endl;

}

//EX3,a
//realizati cmmdc-ul dintre elekentul minim si elementul maxiim
int min(int v[], int d) {
	long long int minim = 999999;

	for (int i = 0;i < d;i++) {
		if (v[i] < minim) {
			minim = v[i];
		}
	}
	minim = abs(minim);
	return minim;

}

int max(int v[], int d) {
	long long int maxim = -999999;

	for (int i = 0;i < d;i++) {
		if (v[i] > maxim) {
			maxim = v[i];
		}
	}
	
	return maxim;
}

void solutieEx3a() {
	int v[100] = { -15, -5, 0, 35, 45, 25 };
	int d = 6;
	int nrMin = min(v, d);
	int nrMax = max(v, d);
	int rez = cmmdc(nrMin, nrMax);
	cout << rez;
}