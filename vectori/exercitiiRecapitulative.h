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
	int d = 8;

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

//2.2
int oglindit(int n) {
	int nou = 0;

	while (n != 0) {
		int cif = n % 10;
		nou = nou * 10 + cif;
		n = n / 10;
	}

	return nou;

}

bool palindrom(int n) {
	int ogl = oglindit(n);

	if (ogl == n) {
		return true;
	}
	return false;
}

void solutie8() {
	int v[100] = { 121,45,707,89 };
	int d = 4;;

	for (int i = 0;i < d;i++) {
		if (palindrom(v[i])) {
			cout << v[i] << " ";
		}
	}

}
//

//2.3
int cifraMinVector(int v[],int d) {
	int min = 10;

	for (int i = 0;i < d;i++) {
		int n = v[i];
		while (n != 0) {
			int cif = n % 10;
			if (cif < min) {
				min = cif;
			}
			n = n / 10;
		}
	}
	return min;
}

int cifraMaxVector(int v[], int d) {
	int max = -1;

	for (int i = 0;i < d;i++) {
		int n = v[i];
		while (n != 0) {
			int cif = n % 10;
			if (cif > max) {
				max = cif;
			}
			n = n / 10;
		}
	}
	return max;
}

void solutie9() {
	int v[100] = { 32,250,216 };
	int d = 4;;


	cout <<"Cifra minima "<< cifraMinVector(v, d)<<", cifra maxima " << cifraMaxVector(v, d) << endl;

}
//

//2.4
int cifControl(int n) {
	int r = n % 9;
	if (r == 0) {
		return 9;
	}
	return r;
}

void solutie10() {
	int v[100] = { 542,741,999 };
	int d = 3;

	for (int i = 0;i < d;i++) {
		int cif = cifControl(v[i]);
		if (cif % 2 == 0) {
			cout << v[i] << " ";
		}
	}

}
//

//2.5
bool PrimaCifEgalCUltimaCif(int n) {
	int a = n % 10;

	while (n > 9) {
		n = n / 10;
	}
	if (a == n) {
		return true;
	}
	return false;
}

void solutie11() {
	int v[100] = { 19,7137,214,1301 };
	int d = 4;
	int nou[100];
	int ct = 0;


	for (int i = 0;i < d;i++) {
		if (PrimaCifEgalCUltimaCif(v[i])) {
			nou[ct] = oglindit(v[i]);
		}
		else {
			nou[ct] = v[i];
		}
		ct++;
	}
	afisare(nou, ct);
}
//

//2.6
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

bool superprim(int n) {

	while (n > 0) {
		if (prim(n) == false) {
			return false;
		}
		n = n / 10;
	}

	return true;

}

void solutie12() {
	int v[100] = { 12,239,45,23,7 };
	int d = 5;

	for (int i = 0;i < d;i++) {
		if (superprim(v[i])) {
			cout<<i+1<<" ";
		}
	}

}
//

//2.7
bool patratPerfect(int n) {
	return sqrt(n) == (int)sqrt(n);
}
                               
void descompunereFactoriPrimi(int n) {
    cout << n << "=";
    int aux = n;

	for (int k = 2;k <= aux / 2;k++) {
		if (prim(k) && n % k == 0) {
			int ct = 0;
			while (n % k == 0) {
				ct++;
				n = n / k;
			}
			cout << k << "^" << ct;
			if (n > 1) {
				cout << "*";
			}
		}
	}
	if (n > 1) {
		cout << n << "^1";
	}
	cout << endl;
}

void solutie13() {
	int v[100] = { 12,16,18 };
	int d = 3;

	for (int i = 0;i < d;i++) {	
		if (patratPerfect(v[i]) == false) {
			descompunereFactoriPrimi(v[i]);
		}
	}
}
//

//3.1
int contorCifre(int n) {
	int ct = 0;
	while (n != 0) {
		ct++;
		n = n / 10;
	}
	return ct;
}

void solutie14() {
	int v[100] = { 45,12,7,103,564 };
	int d = 5;

	for (int i = 0;i < d - 1;i++) {
		if (contorCifre(v[i]) == contorCifre(v[i + 1])) {
			cout << v[i] << " " << v[i + 1] << endl;
		}
	}
}
//

//3.2
int cmmdc(int a, int b) {
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void solutie15() {
	int v[100] = { 12,25,10,21 };
	int d = 4;
	int ct = 0;

	for (int i = 0;i < d - 1;i++) {
		if (cmmdc(v[i], v[i + 1]) == 1) {
			ct++;
		}
	}
	cout << ct;
}
//

//3.3
void solutie16() {
	int v[100] = { 123,34,321,4563,43,56,65,4513 };
	int d = 8;

	for (int i = 0;i < d - 1;i++) {
		for (int j = i + 1;j < d;j++) {
			if (v[i] == oglindit(v[j])) {
				cout << v[i] << " " << v[j] << endl;
			}
		}
	}

}
//

//3.4
void solutie17() {
	int v[100] = { 4,7,10,13,6 };
	int d = 5;

	int sMax = -1;
	int nr1 = 0;
	int nr2 = 0;

	for (int i = 0; i < d - 1; i++) {
		for (int j = i + 1; j < d; j++) {

			if (prim(v[i]) && prim(v[j])) {
				int suma = v[i] + v[j];

				if (suma > sMax) {
					sMax = suma;
					nr1 = v[i];
					nr2 = v[j];
				}
			}
		}
	}


	if (sMax != -1) {
		cout << nr1 << " + " << nr2 << " = " << sMax << endl;
	}
	else {
		cout << "Nu exista doua numere prime in vector." << endl;
	}
}
//

//4.1
void bubbleSortCrescator(int v[], int d) {
	bool sortat = true;

	do {
		sortat = true;
		for (int i = 0;i < d - 1;i++) {
			
			if (v[i] > v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
	   }

	} while (sortat == false);

}

void solutie18() {
	int v[100] = { 32,56,19,42 };
	int d = 4;

	bubbleSortCrescator(v, d);
	afisare(v, d);

}
//

//4.2
void sortarePrinSelectieNrPrime(int v[], int d) {

	for (int i = 0;i < d-1;i++) {
		if (prim(v[i])) {
			for (int j = i + 1;j < d;j++) {
				if (prim(v[j])&&v[i] > v[j]) {
					int aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
			}
		}
		
	}
}

void solutie19() {
	int v[100] = { 29,12,7,113,4 };
	int d = 5;


	sortarePrinSelectieNrPrime(v, d);
	afisare(v, d);

}
//

//4.3
void bubbleSortCrescatorSumaCifre(int v[], int d) {
	bool sortat = true;

	do {
		sortat = true;
		for (int i = 0;i < d - 1;i++) {

			if (sumaCifrelor(v[i]) > sumaCifrelor(v[i + 1])) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}

	} while (sortat == false);

}

void solutie20() {
	int v[100] = { 89,22,51};
	int d = 3;


	bubbleSortCrescatorSumaCifre(v, d);
	afisare(v, d);

}
//

//4.4
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

int pozMax(int v[],int d) {
	int pozMax = 0;

	for (int i = 1; i < d; i++) {
		if (v[i] > v[pozMax]) {
			pozMax = i;
		}
	}
	return pozMax;
}


void solutie21() {
	int v[100] = { 3,9,5,2,8,1 };
	int d = 6;
	int poz = pozMax(v,d);


	sortatCrescatorInterval(v, 0, poz);
	sortatDescrescatorInterval(v, poz, d - 1);
	afisare(v, d);
}
//

//4.5
void bubbleSortCrescatorCuIndici(int v[], int d,int poz[]) {
	bool sortat = true;

	do {
		sortat = true;
		for (int i = 0;i < d - 1;i++) {

			if (v[i] > v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				int aux2 = poz[i];
				poz[i] = poz[i + 1];
				poz[i + 1] = aux2;
				sortat = false;
			}
		}

	} while (sortat == false);

}

void solutie22() {
	int v[100] = { 8,20,16,14 };
	int d = 4;
	int pozitii[100];

	for (int i = 0;i < d;i++) {
		pozitii[i] = i + 1;
	}

	bubbleSortCrescatorCuIndici(v, d, pozitii);
	afisare(v, d);
	cout << endl;
	afisare(pozitii, d);
}
//

//4.6
void SortarePrinSelectieNumerePare(int v[], int d) {

	for (int i = 0;i < d;i++) {
		if (v[i] % 2 == 0) {
			for (int j = i + 1;j < d;j++) {
				if (v[j] % 2 == 0) {
					if (v[i] > v[j]) {
						int aux = v[i];
						v[i] = v[j];
						v[j] = aux;
					}
				}
			}
		}
	}

}

void SortarePrinSelectieNumereImpare(int v[], int d) {
	
	for (int i = 0;i < d;i++) {
		if (v[i] % 2 != 0) {
			for (int j = i + 1;j < d;j++) {
				if (v[j] % 2 != 0) {
					if (v[i] < v[j]) {
						int aux = v[i];
						v[i] = v[j];
						v[j] = aux;
					}
				}
			}
		}
	}

}

void solutie23() {
	int v[100] = { 5,4,3,2,1,6 };
	int d = 6;

	SortarePrinSelectieNumerePare(v, d);
	SortarePrinSelectieNumereImpare(v, d);
	afisare(v, d);

}
//

//5.1
void stergereElement(int v[], int& d, int poz) {

	for (int i = poz;i < d;i++) {
		v[i] = v[i + 1];
	}
	d--;
}

void solutie24() {
	int v[100] = { 9,0,0,5,0 };
	int d = 5;
	int ct = 0;

	for (int i = 0;i < d;i++) {
		if (v[i] == 0) {
			stergereElement(v, d, i);
			i--;
		}
	}
	afisare(v, d);
}
//

//5.2
void solutie25() {
	int v[100] = { 5,11,23,4,7 };
	int d = 5;
	int a = 3;
	int b = 7;

	if (a > b) {
		int aux = a;
		a = b;
		b = aux;
	}

	for (int i = 0;i < d;i++) {
		if (v[i] >= a && v[i] <= b) {
			stergereElement(v, d, i);
			i--;
		}
	}
	afisare(v, d);
}
//

//5.3
void inserareElement(int v[], int& d, int poz, int elem) {
	for (int i = d;i > poz;i--) {
		v[i] = v[i - 1];
	}
	d++;
	v[poz] = elem;
}

void solutie26() {
	int v[100] = { 4,-2,5 };
	int d = 3;

	for (int i = 0;i < d;i++) {
		if (v[i] < 0) {
			int x = v[i] * v[i] * v[i];
			inserareElement(v, d, i + 1, x);
			i++;
		}
	}
	afisare(v, d);
}
//

//5.4
void solutie27() {
	int v[100] = { 4,7,10,13,8,5 };
	int d = 6;
	int ct = 0;

	for (int i = 0;i < d;i++) {
		if (prim(v[i])) {
			ct++;
		}

		if (ct == 3) {
			stergereElement(v, d, i);
			break;
		}

	}
	afisare(v, d);
}
//

//5.5
void solutie28() {
	int v[100] = { 45,121,7 };
	int d = 3;

	for (int i = 0;i < d;i++) {
		if (PrimaCifEgalCUltimaCif(v[i])&&v[i]>9) {
			int cif = v[i] % 10;
			inserareElement(v, d, i, cif);
			inserareElement(v, d, i+2, cif);
			i=i+2;
		}
	}
	afisare(v, d);
}
//

//P1
void bubbleSortDescrescatorSumaCifre(int v[], int d) {
	bool sortat = true;

	do {
		sortat = true;
		for (int i = 0;i < d - 1;i++) {
			if (sumaCifrelor(v[i]) < sumaCifrelor(v[i + 1])) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}

	} while (sortat == false);

}

void solutie29() {
	int v[100] = { 121,45,707,33,89 };
	int d = 5;
	int nou[100];
	int ct = 0;


	for (int i = 0;i < d;i++) {
		if (palindrom(v[i])) {
			nou[ct] = v[i];
			ct++;
		}
	}

	bubbleSortDescrescatorSumaCifre(nou,ct);
	
	afisare(nou, ct);

}
//

//P2
int alipire(int a, int b) {
	int aux = b;
	int p = 1;

	while (aux > 0) {
		p = p * 10;
		aux = aux / 10;
	}

	if (b == 0) {
		p = 10;
	}

	return a * p + b;
}

void solutie30() {
	int v[100] = { 1,3,20,7 };
	int d = 4;

	for (int i = 0;i < d - 1;i++) {
		if (prim(alipire(v[i], v[i + 1]))) {
			cout << v[i] << " " << v[i + 1] << endl;
		}
	}

}
//

//P3
int cmmmc(int a, int b) {
	if (a == 0 || b == 0) {
		return 0;
	}

	return (a / cmmdc(a, b)) * b;
}

void solutie31() {
	int v[100] = { 4,5,6,8,12 };
	int d = 5;
	int rez = -1;

	for (int i = 0; i < d; i++) {
		if (v[i] % 2 == 0) {
			if (rez == -1) {
				rez = v[i];
			}
			else {
				rez = cmmmc(rez, v[i]);
			}
		}
	}

	cout << rez;

}
//

//P4
bool vfCifre(int n) {
	
	while (n != 0) {
		int cif = n % 10;
		if (cif == 0) {
			return true;
		}
		n = n / 10;
	}

	return false;

}

void solutie32() {
	int v[100] = { 12,40,305,7,88 };
	int d = 5;
	int ct = 0;

	for (int i = 0; i < d; i++) {
		if (vfCifre(v[i])) {
			stergereElement(v, d, i);
			ct++;
			i--;
		}
	}
	inserareElement(v, d, 0, d);
	afisare(v, d);
}
//

//P5
void solutie33() {
	int v[100] = { 7,3,16,2,9,1 };
	int d = 6;
	bool vf = false;
	int ct = 0;

	for (int i = 0; i < d; i++) {
		if (patratPerfect(v[i])) {
			vf = true;
			sortatCrescatorInterval(v, 0, i - 1);
			sortatDescrescatorInterval(v, i + 1, d - 1);
			break;
		}
	}

	if (vf == false) {
		cout << "nu exista nici un patrat perfect in sirul de numere";
	}
	else {
		afisare(v, d);
	}
}
//
