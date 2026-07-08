#pragma once
#include <iostream>
#include <cmath>
using namespace std;
//185,4102,4106,1911

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

void afisare(int v[], int d) {

	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}

}

void solutie129() {
	int v[100] = { 8, 2, 9, 4, 5, 7 };
	int d = 6;

	sortatPrinBubbleSortDescrescator(v, d);
	afisare(v, d);
}

//2
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


//3
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

//4
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

//5
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

//6
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

//7
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

//8
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


//9
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

//10
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

//11
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

//12
int cifMin(int n) {
	if (n == 0) {
		return 0;
	}
	int min = 10;
	while (n != 0) {
		int cif = n % 10;
		if (cif < min) {
			min = cif;
		}
		n = n / 10;
	}
	return min;
}

void solutie186() {
	int v[100] = { 100, 312, 276, 985, 5021 };
	int d = 5;
	int cif[100];

	for (int i = 0; i < d; i++) {
		cif[i] = cifMin(v[i]);
	}
	BubbleSortCrescator(cif, d);

	if (cif[0] == 0) {
		int poz = 0;
		for (int i = 0; i < d; i++) {
			if (cif[i] != 0) {
				poz = i;
				break;
			}
		}

		int aux = cif[0];
		cif[0] = cif[poz];
		cif[poz] = aux;
	}

	for (int i = 0; i < d; i++) {
		cout << cif[i];
	}

}
//

//13
void solutie86() {
	int v[100] = { 8, 2, 9, 4, 5, 7 };
	int d = 6;
	int mijloc = d / 2;
    
	sortatCrescatorPartial(v, 0, mijloc - 1);
	sortatDescrescatorPartial(v, mijloc, d - 1);
	afisare(v,d);

}

//14
int suma(int n) {
	int sum = 0;
	while (n != 0) {
		int cif = n % 10;
		sum = sum + cif;
		n = n / 10;
	}

	return sum;
}

void sortatCrescatorSuma(int v[], int d) {

	bool sortat = true;
	do {
		sortat = true;

		for (int i = 0;i < d - 1;i++) {

			if (suma(v[i]) > suma(v[i + 1])) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}

		}

	} while (sortat == false);
}

void solutie130() {
	int v[100] = { 89, 22, 91, 4005, 51, 721 };
	int d = 6;

	sortatCrescatorSuma(v, d);
	afisare(v, d);




}
//

//15
void sortatCrescator(int v[], int d) {

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
void solutie2594() {
	int v[100] = { 5, 4, 3, 2, 1, 6, 7, 8, 9, 18 };
	int d = 10;
	int par[100];
	int imp[100];
	int ctpar = 0; 
	int ctimp = 0;

	for (int i = 0; i < d; i++) {

		if (v[i] % 2 == 0) {
			par[ctpar] = v[i];
			ctpar++;
		}
		else {
			imp[ctimp] = v[i];
			ctimp++;
		}
	}

	BubbleSortCrescator(par, ctpar);
	BubbleSortCrescator(imp, ctimp);
	afisare(par,ctpar);
	afisare(imp, ctimp);

}
//

//16
int primaCifra(int n) {

	while (n > 9) {
		n = n / 10;
	}
	return n;
}

void sortatCrescatorPrimaCifra(int v[], int d) {
	bool sortat = true;
	do {
		sortat = true;
		for (int i = 0; i < d - 1; i++) {
			int pc1 = primaCifra(v[i]);
			int pc2 = primaCifra(v[i + 1]);

			if (pc1 > pc2 || (pc1 == pc2 && v[i] > v[i + 1])) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sortat = false;
			}
		}
	} while (sortat == false);
}

void solutie131() {
	int v[100] = { 89, 2246, 91, 4005, 51, 721 };
	int d = 6;
	sortatCrescatorPrimaCifra(v, d);
	afisare(v,d);

}
//

//17
void sortat(int v[], int d) {

	for (int i = 0; i < d - 1; i += 2) {
		for (int j = i + 2; j < d; j += 2) {
			if (v[i] < v[j]) {
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	
	for (int i = 1; i < d - 1; i += 2) {
		for (int j = i + 2; j < d; j += 2) {
			if (v[i] > v[j]) {
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

void solutie164() {
	int v[100] = { 8, 9, 9, 4, 5, 7 };
	int d = 6;

	sortat(v, d);
	afisare(v, d);
}
//

//18
void sortat4102(int v[], int n) {
	for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (v[j] % 2 == 0 && v[i] > v[j]) {
					int aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
			}
		
	}

	for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (v[j] % 2 != 0 && v[i] < v[j]) {
					int aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
			}
	}
}

void solutie4102() {
	int v[100] = { 8, 9, 9, 4, 5, 7 };
	int d = 8;

	sortat4102(v, d);
	afisare(v, d);
}
//

//19
void sortatNegativPozitiv(int v[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (v[i] < 0) {
			for (int j = i + 1; j < n; j++) {
				if (v[j] < 0 && v[i] > v[j]) {
					int aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
			}
		}
	}




	for (int i = 0; i < n - 1; i++) {
		if (v[i] > 0) {
			for (int j = i + 1; j < n; j++) {
				if (v[j] > 0 && v[i] < v[j]) {
					int aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
			}
		}
	}
}


void solutie4106() {
	int v[100] = { 2 ,- 1, 9, - 4, 5, 7 };
	int d = 6;

	sortatNegativPozitiv(v, d);
	afisare(v, d);
}
//

//20
void sortatIndiciCrescator(int v[], int poz[], int d) {
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

void solutie1911() {
	int v[100] = { 12, 8, 9, 0, 19, 2, 8 };
	int d = 7;
	int poz[100];

	for (int i = 0; i < d; i++) {
		poz[i] = i + 1;
	}

	sortatIndiciCrescator(v, poz, d);


	for (int i = 0; i < d; i++) {
		cout << v[i] << ", Pozitia " << poz[i] << endl;
	}
}
//