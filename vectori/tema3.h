#pragma once
#include <iostream>
#include <cmath>
using namespace std;
//185


//1
void sortatPrinBubbleSortDescrescator(int v[], int d) {
	bool sortat = true;
	do {
		sortat = true;
		for (int i = 0; i < d - 1; i++) {

			if (v[i] < v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}
	} while (sortat == false);
}

void afisarediv10(int v[], int d) {

	for (int i = 0;i < d;i++) {
		if (v[i] % 10 == 0) {
			cout << v[i] << " ";
		}

	}

}

void solutie4146() {
	int v[100] = { 29,10,7,115,53,32 };
	int d = 6;



	sortatPrinBubbleSortDescrescator(v, d);
	afisarediv10(v, d);


}
//


//2
void sortatPrinBubbleSortInaltimi(int v[], int poz[], int d) {
	bool sortat = true;
	do {
		sortat = true;
		for (int i = 0; i < d - 1; i++) {

			if (v[i] > v[i + 1]) {

				int auxv = v[i];
				v[i] = v[i + 1];
				v[i + 1] = auxv;


				int auxp = poz[i];
				poz[i] = poz[i + 1];
				poz[i + 1] = auxp;

				sortat = false;
			}
		}
	} while (sortat == false);
}

void afisare(int v[], int d) {

	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}

}

void solutie618() {
	int v[100] = { 8, 20, 16, 14, 10, 4, 12 };
	int poz[100];
	int d = 7;

	for (int i = 0; i < d; i++) {
		poz[i] = i + 1;
	}

	sortatPrinBubbleSortInaltimi(v, poz, d);

	afisare(poz, d);
}
//

//3
int div(int n) {
	int ct = 0;
	for (int i = 1;i <= n;i++) {
		if (n % i == 0) {
			ct++;
		}
	}
	return ct;
}

void SortareBubbleSortDiv(int v[], int d) {
	bool sortat = true;

	do {
		sortat = true;

		for (int i = 0;i < d - 1;i++) {
			int divizor = div(v[i]);
			int divizor2 = div(v[i + 1]);

			if (divizor < divizor2) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}


		}



	} while (sortat == false);


}

void solutie1608() {
	int v[100] = { 12, 20, 4, 100, 13 };
	int d = 5;

	SortareBubbleSortDiv(v, d);
	afisare(v, d);

}
//

//4
int cmmdc(int a, int b) {
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void solutie514() {
	int v[100] = { 16, 7, 6, 3, 1, 5, 9, 14 };
	int d = 8;

	int ultim = v[d - 1];
	sortatPrinBubbleSortDescrescator(v, d);

	for (int i = 0; i < d; i++) {
		if (cmmdc(v[i], ultim) == 1) {
			cout << v[i] << " ";
		}
	}


}
//

//5
void sortatCrescatorPartial(int v[], int start, int end) {
	bool sortat = true;
	do {
		sortat = true;
		for (int i = start; i < end; i++) {
			if (v[i] > v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}
	} while (sortat == false);
}

void sortatDescrescatorPartial(int v[], int start, int end) {
	bool sortat = true;
	do {
		sortat = true;
		for (int i = start; i < end; i++) {
			if (v[i] < v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}
	} while (sortat == false);
}

void solutie511() {
	int v[100] = { 13, 1, 10, 15, 3, 7, 11 };
	int d = 7;
	int k = 5;

	sortatCrescatorPartial(v, 0, k - 1);
	sortatDescrescatorPartial(v, k, d - 1);
	afisare(v, d);

}
//

//6
void solutie512() {
	int v[100] = { 13, 1, 10, 15, 3, 7, 11 };
	int d = 7;
	int max = -1;
	int ct = 0;
	for (int i = 0;i < d;i++) {
		if (v[i] > max) {
			max = v[i];
			ct++;
		}
	}

	sortatCrescatorPartial(v, 0, ct);
	sortatDescrescatorPartial(v, ct+1, d - 1);
	afisare(v,d);

}
//

//7
void solutie180() {
	int v[100] = { 10, 20, 15, 7, 12 };
	int d = 5;
	int ct = 0;
	int ct2 = 0;

	for (int i = 1; i < d; i++) {
		if (v[i] < v[ct]) {
			ct = i;
		}
		if (v[i] > v[ct2]) {
			ct2 = i;
		}
	}

	int st = ct;
	int dr = ct2;

	if (st > dr) {
		int aux = st;
		st = dr;
		dr = aux;
	}

	sortatCrescatorPartial(v, st, dr);
	afisare(v, d);
}
//


//8
bool patratPerfect(int n) {

	return sqrt(n) == (int)sqrt(n);

}

void bubbleSortPatratPerfectCrescator(int v[],int d) {

	for (int i = 0;i < d;i++) {
		if (patratPerfect(v[i])) {
			for (int j = i + 1; j < d; j++) {
				if (patratPerfect(v[j]) && v[i] > v[j]) {
					int aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
			}
		}
		
	}
}

void solutie183() {
	int v[100] = {9, 15, 16, 4, 5, 1, 7, 9};
	int d = 8;

	bubbleSortPatratPerfectCrescator(v, d);
	afisare(v, d);
}
//

//9
int div2(int n) {
	int s = 0;

	for (int i = 1; i <= n; i++) {
		if (n % i == 0) {
			s = s + i;
		}
	}
	return s;
}

void BubbleSortCrescatorDivizori(int v[], int d) {
	bool sortat = true;
	do {
		sortat = true;

		for (int i = 0;i < d - 1;i++) {

			if (div2(v[i]) > div2(v[i + 1]) || (div2(v[i]) == div2(v[i + 1]) && v[i] > v[i + 1])) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}

		}

	} while (sortat == false);
}

void solutie515() {
	int v[100] = { 24, 46, 11, 36, 48, 35, 27, 28, 49, 6 };
	int d = 10;

	BubbleSortCrescatorDivizori(v, d);
	afisare(v, d);
}
//

//10
int primaCif(int n) {

	while (n > 9) {
		n = n / 10;
	}
	return n;
}

void BubbleSortCrescator(int v[], int d) {
	bool sortat = true;
	do {
		sortat = true;
		for (int i = 0; i < d - 1; i++) {
			if (v[i] > v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}
	} while (sortat == false);
}

void solutie185() {
	int v[100] = { 100, 312, 276, 985, 5021 };
	int d = 5;
	int cif[100];

	for (int i = 0; i < d; i++) {
		cif[i] = primaCif(v[i]);
	}
	BubbleSortCrescator(cif, d);


	for (int i = 0; i < d; i++) {
		cout << cif[i];
	}

}
//