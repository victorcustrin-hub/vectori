#pragma once
#include <iostream>
#include <cmath>
using namespace std;




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


bool isDivide2K(int n, int k) {
	int ct = 0;

	while (n % 2 == 0) {
		ct++;
		n = n / 2;
	}

	if (ct >= k) {
		return true;
	}
	return false;
}

void solutie3a() {
	int v[300] = { 32,643,657,32 };
	int d = 4;
	int k = 5;
	bool vf = true;

	for (int i = 0;i < d&&vf;i++) {
		if (v[i] % 2 == 0) {
			if (isDivide2K(v[i], k) == 0) {
				vf = false;
			}
		}
	}

	if (vf == 1) {
		cout << "Nr pare din vector se impart la 2^"<<k<< endl;
	}
	else {
		cout << "Numerele din vector nu indeplinesc cerinta" << endl;
	}
	



}


bool patratPerfect(int n) {
	
	return sqrt(n) == (int)sqrt(n);

}

 
//  k<=a/2         k=prim&&n%k==0              n%k==0          ct        n         k
//  2<=6 da       2=prim,12%2==0 da              da            1         6         2
//                                               da            2         3         2
//                                               nu            -         -         3
//  3<=6 da       3=prim,12%3==0 da              da            1         0         4
//  4<=6 da       4 nu e prim=>fals              -             -          -         -
//  5<=6 da       5=prim,12%6==0 da              nu            0         0         6
//  6<=6 da       6 nu e prim=>fals                                
void  afisareDescompunereFactoriPrimi(int n) {

	cout << n<<"=";
	int a = n;

	for (int k = 2;k <= a/ 2;k++) {

		if (prim(k)&&n%k==0) {
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


//Pentru fiecare numar ce NU este patrat perfect si are aceeasi paritate cu cel din dreapta
//dar si cel din stanga (in cazuri in care se poate verifica) afisati valoarea din descompunerea in factori primi
void solutie3b() {
	int v[300] = {12,24,27 };
	int d = 3;

    for (int i = 0;i < d;i++) {
		if (i>0&&i<d-1) {
			if (patratPerfect(v[i])==false&&v[i] % 2 == v[i - 1] % 2 && v[i - 1] % 2 == v[i + 1] % 2) {
				afisareDescompunereFactoriPrimi(v[i]);
			}
		}
		else {
			if (patratPerfect(v[i]) == false) {
				afisareDescompunereFactoriPrimi(v[i]);
			}
		}
		
	}

}


bool CifEgal(int n) {
	int ultim = n % 10;
	n = n / 10;
	while (n > 0) {
		int cif = n % 10;
		if (cif!=ultim) {
			return false;
		}
		n = n / 10;
	}

	return true;

}
// 12 34 54 76 86 12 32 43 690
void solutie3c() {
	int v[300] = { 23, 64, 12, 65, 12, 54, 12 };
	int d = 7;
	bool vf = true;

	for (int i = d / 7; i < (2 * d) / 7; i++) {
		if (!CifEgal(v[i])) {
			vf = false;
			break;
		}
	}

	if (vf) {
		cout << "Toate elementele din a doua septime au cifrele egale.";
	}
	else {
		cout << "Nu toate elementele din a doua septime au cifrele egale.";
	}

}

int par(int n) {
	int nou = 0;
	int p = 1;

	while (n != 0) {
		int cif = n % 10;
		if (cif % 2 != 0) {
			nou = cif * p + nou;
			p = p * 10;
		}

		n = n / 10;
	}

	return nou;


}

int div3(int n) {
	int nou = 0;
	int p = 1;

	while (n != 0) {
		int cif = n % 10;
		if (cif % 3 != 0) {
			nou = cif * p + nou;
			p = p * 10;
		}

		n = n / 10;
	}

	return nou;


}


void solutie3d() {
	int v[300] = { 332,5463,41,76,12,54 };
	int d = 5;

	for (int i = 0; i < d; i++) {
		int x = div3(par(v[i]));
		if (x != 0) {
			cout << x << " ";
		}


	}
}

bool primx(int n) {
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


void solutie3e() {
	int v[300] = { 5, 2, 12, 7, 5 };
	int d = 5;
	int ct = 0;

	for (int i = 0; i < d; i++) {
		int poz = i + 1;

		if (primx(v[i])) {
			ct++;
		}
	}

	cout << "nr de elemente care respecta conditia este: " << ct << endl;
}



//[a,b]*(a,b)=a*b =>[a,b]=a*b/(a,b)
int cmmdc(int a, int b) {
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int cmmmc(int a, int b) {
	if (a == 0 || b == 0) {
		return 0;
	}
	return a / cmmdc(a, b) * b;
}

void solutie3f() {
	int v[300] = { 23,52,341,56,12,1,52,84,125,213,756,12,196,13 };


	cout << "cmmmc al numerelor " << v[7] << " si " << v[12] << " este " << cmmmc(v[7],v[12]) << endl;

}