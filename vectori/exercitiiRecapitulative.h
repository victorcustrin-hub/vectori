#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//intrebari:4.2


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
			cout << k << "^" << ct << "*";
		}
	}
	cout << "1";
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
void bubbleSortCrescatornrPrime(int v[], int d) {
	bool sortat = true;

	do {
		sortat = true;
		for (int i = 0;i < d - 1;i++) {

			if (prim(v[i])&&v[i] > v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}

	} while (sortat == false);

}

void solutie19() {
	int v[100] = { 29,12,7,113,4 };
	int d = 5;


	bubbleSortCrescatornrPrime(v, d);
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
	int v[100] = { 25,43,16 };
	int d = 4;


	bubbleSortCrescatorSumaCifre(v, d);
	afisare(v, d);

}
//