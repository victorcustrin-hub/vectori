#pragma once
#include <iostream>
using namespace std;
#include <cmath>

//1d,1e,2d,2g

//FISA
//ex1
//a)
void afisare(int v[], int d) {

	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}

	cout << endl;

}

void stergereElement(int v[], int& dim, int poz) {

	for (int i = poz;i < dim;i++) {
		v[i] = v[i + 1];
	}

	dim--;
}


bool prim(int n) {
	if (n <= 1) {
		return false;
	}
	for (int k = 2;k <= n / 2;k++) {
		if (n % k == 0) {
			return false;
		}
	}
	return true;
}

void inserareElement(int v[], int& dim, int poz, int elem) {

	for (int i = dim;i > poz;i--) {
		v[i] = v[i - 1];
	}
	dim++;
	v[poz] = elem;
}


void solutie1a() {
	int v[100] = { 34, 17, 85, 29, 93, 71, 13, 44, 47, 62 };
	int d = 10;
	int ct = 0;
	int poz = -1;


	for (int i = 0;i < d && poz == -1;i++) {
		if (prim(v[i])) {
			ct++;

		}
		if (ct == 3) {
			poz = i;
		}
		stergereElement(v, d, poz);
		afisare(v, d);
	}
}
//

//b)
bool primEgalCuUltimCif(int n) {
		int x = n % 10;


		while (n >9 ) {
			n = n / 10;
		}
        
		if (n == x) {
			return true;
		}
		return false;
	}


void solutie1b() {	
	int v[100] = { 5, 11, 23, 121, 7, 88, 90, 505, 12 };
	int d = 9;
	int ct = 0;

	for (int i = 0;i < d;i++) {
		if (v[i] > 9 && primEgalCuUltimCif(v[i])) {
			stergereElement(v, d, i);
			i--;
		}
	}
	afisare(v, d);
}
//

//c)
bool nul(int n) {
	if (n == 0) {
		return true;
	}
	return false;
}

void solutie1c() {
	int v[100] = { 9, 0, 0, 5 };
	int d = 4;

	for (int i = 0; i < d; i++) {
		if (nul(v[i])) {
			stergereElement(v, d, i); 
			i--;
		}
	}

	afisare(v, d);
}
//

//d)
bool seAflainInterval(int n, int min, int max) {
	if (n >= min&& n <= max) {
		return true;
	}
	return false;
}

void solutie1d() {
	int v[100] = { 5, 11, 23, 121, 7, 88, 90, 505, 12 };
	int d = 9;
	int a = 3;
	int b = 5;
	int min = a;
	int max = b;

	if (a > b) {
		min = b;
		max = a;
	}

	for (int i = 0; i < d; i++) {
		if (seAflainInterval(v[i], min, max)) {
			stergereElement(v, d, i);
			i--;
		}
	}

	afisare(v, d);
}
//

//e)
bool patratPerfect(int n) {
	int rad = sqrt(n);

	if (rad * rad == n) {
		return true;
	}
	return false;
}

void solutie1e() {
	int v[100] = { 49, 145, 1254, 64, 7, 89, 16, 26, 81, 36 };
	int d = 10;

	for (int i = 0; i < d; i++) {
		if (patratPerfect(v[i])) {
			stergereElement(v, d, i);
			i--;
		}
	}

	afisare(v, d);
}
//

//f)
bool superPrim(int n) {
	if (n <= 1) return false;

	while (n != 0) {
		if (prim(n) == 0) {
			return false;
		}
		n = n / 10;
	}
	return true;
}

void solutie1f() {
	int v[100] = { 239, 5, 12, 23, 8, 29 };
	int d = 6;
	bool sPrim = false;

	
	for (int i = 0; i < d; i++) {
		if (superPrim(v[i])) {
			sPrim = true;
			stergereElement(v, d, i);
			i--;
		}
	}

	if (sPrim==false) {
		cout << "nu sunt elemente super prime in vector"<<endl;
	}
	else if (d == 0) {
		cout << "Toate elementele sunt prime, toate au fost sterse"<<endl;
	}
	else {
		afisare(v, d);
	}
}
//

//g)
int cmmdc(int a, int b) {
	while (b != 0) {
		int r = a % b;
		a = b;
	    b = r;
	}
	return a;
}

void solutie1g() {
	int v[100] = { 2, 3, 5, 7 };
	int d = 6;

	for (int i = 0; i < d-1; i++) {
		if (cmmdc(v[i], v[i + 1]) == 1) {
			stergereElement(v, d, i);
			stergereElement(v, d, i);
			i--;
		}
	}

	afisare(v, d);
}
//

//EXERCITIUL 2

//a)
bool nrNegativ(int n) {
	if (n < 0) {
		return true;
	}
	return false;
}

void solutie2a() {
	int v[100] = { 4, -2, 5, -3, -3, 8 };
	int d = 6;

	for (int i = 0; i < d; i++) {
		if (nrNegativ(v[i])) {
			int cub = v[i] * v[i] * v[i];

			inserareElement(v, d, i + 1, cub);
            i++;
		}
	}

	afisare(v, d);
}
//

//b)
bool cifreConsecutive(int n) {
	int cif = n % 10;
	n = n / 10;

	while (n != 0) {
		int cif2 = n % 10;
		if (cif2 + 1 != cif) {
			return false;
		}
		n = n / 10;
		cif = cif2;
	}

	return true;

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

void solutie2b() {
	int v[100] = { 123, 58, 234, 456, 89, 789 };
	int d = 6;
	int k = 4;
    int ct = 0;

	for (int i = 0; i < d; i++) {
		if (cifreConsecutive(v[i])) {
			ct++;

			if (ct == k) {
				int ogl = oglindit(v[i]);
				inserareElement(v, d, i + 1, ogl);
				break;
			}
		}
	}

	afisare(v, d);
}
//

//c)
bool palindromDouaNumere(int a, int b) {
	int ogl = oglindit(a);

	if (ogl == b) {
		return true;
	}
	return false;
}

int alipire(int a, int b) {
	int p = 1;
	int aux = b;
	while (b != 0) {
		p = p * 10;
		b = b / 10;
	}
	b = aux;
	return a * p + b;

}

void solutie2c() {
	int v[100] = { 3, 3, 9, 14 };
	int d = 4;
	int ct = 0;

	for (int i = 0;i < d;i++) {
		if (palindromDouaNumere(v[i], v[i + 1])) {
			inserareElement(v, d, i + 1, alipire(v[i], v[i + 1]));
			i++;
		}
	}
	afisare(v, d);
}
//

//d)
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

int UltimaCifra(int n) {
	return n % 10;
}

int PrimaCifra(int n) {
	while (n > 9) {
		n = n / 10;
	}
	return n;
}

void solutie2d() {
	int v[100] = { 45, 121, 7, 83, 404 };
	int d = 5;

	for (int i = 0; i < d; i++) {
		if (primCifEgalCuUltimCif(v[i])) {
			int p_cif = PrimaCifra(v[i]);
			int u_cif = UltimaCifra(v[i]);

			inserareElement(v, d, i, p_cif);
			inserareElement(v, d, i + 2, u_cif);
			i = i + 2;
		}
	}

	afisare(v, d);
}

//e)
bool trei_Div(int n) {
	int ct = 0;

	for (int i = 1;i <= n;i++) {
		if (n % i == 0) {
			ct++;
		}
	}

	if (ct == 3) {
		return true;
	}
	return false;
}

int sumaDivizori(int n) {
	int s = 0;
	int ct = 0;

	for (int i = 1;i <= n;i++) {
		if (n % i == 0) {
			s = s + i;
		}
	}
	return s;
}

void solutie2e() {
	int v[100] = { 12, 4, 7, 9, 25, 16 };
	int d = 6;
	int k = 2;
	int ct= 0;

	for (int i = 0; i < d; i++) {
		if (trei_Div(v[i])) {
			ct++;

			if (ct == k) {
				int s = sumaDivizori(v[i]);
				inserareElement(v, d, i + 1, s);
		        break;
			}
		}
	}

	afisare(v, d);
}
//

//f)
int produsCifre(int n) {
	int p = 1;

	while (n != 0) {
		int cif = n % 10;
		p = p * cif;
		n = n / 10;
	}

	return p;

}

bool cifPatratePerfecte(int n) {

	while (n != 0) {
		int cif = n % 10;
		if (cif != 0 && cif != 1 && cif != 4 && cif != 9) {
			return false;
		}
		n = n / 10;
	}
	return true;
}

void solutie2f() {
	int v[100] = {149, 25, 41, 104, 7};
	int d = 5;

	for (int i = 0;i < d;i++) {
		if (cifPatratePerfecte(v[i])) {
			int p = produsCifre(v[i]);
			inserareElement(v, d, i, p);
			i++;
		}
	}
	afisare(v, d);

}
//

//g)
int cifraMinima(int n) {
	int min = 9;
	
	while (n != 0) {
		int cif = n % 10;
		if (min > cif) {
			min = cif;
		}
		n = n / 10;
	}
	return min;
}

void solutie2g() {
	int v[100] = { 122, 21, 45, 544, 78 };
	int d = 5;
	

	for (int i = 0;i < d-1;i++) {
        int minim = cifraMinima(v[i]);
		inserareElement(v, d, i + 1, minim);
		i++;
	
	}
	afisare(v, d);
}

	
