#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//intrebari:1e

bool prim(int n) {
	if (n<=1) {
		return false;
	}
	for (int k = 2;k <= n / 2;k++) {
		if (n % k == 0) {
			return false;
		}
	}
	return true;
}

//i<d         v[i]     prim(v[i])    ct
//0<6 da       13         da          1
//1<6 da        1          nu         1
//2<6 da        3         da          2
//3<6 da       19         da          3
//4<6 da       23         da          4
//5<6 da       24          nu         4
//6<6 nu
void solutie1a() {
	int v[200] = { 13,1,3,19,23,24 };
	int d = 6;
	int ct = 0;
	for (int i = 0;i < d;i++) {
		if (prim(v[i])) {
			ct++;
		}
	}
	cout << ct;
}

int cifMax(int n) {
	int max = -1;
	if (n == 0) {
		return 0;
	}
	n = abs(n);
	while (n != 0) {
		int cif = n % 10;
		if (cif > max) {
			max = cif;
		}
		n = n / 10;
	}
	return max;
}

int cifMin(int n) {
	int min = 10;
	if (n == 0) {
		return 0;
	}
	n = abs(n);
	while (n != 0) {
		int cif = n % 10;
		if (cif < min) {
			min = cif;
		}
		n = n / 10;
	}
	return min;
}

//i<d        v[i]     cifMax(v[i])    max     cifMin(v[i])    min
//            -        -              -1       -              10
//0<6 da      3        3               3       3               3
//1<6 da      9        9               9       9               3
//2<6 da      3        3               9       3               3
//3<6 da      2        2               9       2               2
//4<6 da      23       3               9       2               2
//5<6 da      24       4               9       2               2
//6<6 nu
void solutie1b() {
	int v[200] = { 3,9,3,2,23,24 };
	int d = 6;
	int min = 10;
	int max = -1;
	for (int i = 0;i < d;i++) {
		if (cifMax(v[i]) > max) {
			max = cifMax(v[i]);
		}
		if (cifMin(v[i]) < min) {
			min = cifMin(v[i]);
		}
	}
	cout << "Cifra maxima:" << max << endl;
	cout << "Cifra minima:" << min << endl;
}

int rasturnat(int n) {
	int nou = 0;

	while (n != 0) {
		int cif = n % 10;
		nou = nou * 10 + cif;
		n = n / 10;

	}
	return nou;

}

bool primCifEgalultimCif(int n) {
	int ultim = n % 10;
	int prim = n;

	while (prim > 9) {
		prim = prim / 10;
	}
	

	if (prim == ultim) {
		return true;
	}
	
	return false;

}

    // i < d        v[i]     primCifEgalultimCif(v[i])    rasturnat                cout
	//0<5 da          3         (3 == 3) da                  3                       3
	//1<5 da          3123      (3 == 3) da                 3213                   3213 
	//2<5 da          7167      (7 == 7) da               7617                    7617 
	//3<5 da          3124      (3 != 4) nu               v[3] -> 3124            3124 
	//4<5 da          14        (1 != 4) nu               v[4] -> 14                14 
	//5<5 nu
void solutie1c() {
	int v[200] = { 3,3123,7167,3124,14 };
	int d = 5;
	
	for (int i = 0;i < d;i++) {
		if (primCifEgalultimCif(v[i])) {
			cout << rasturnat(v[i])<<" ";
		}
		else {
			cout << v[i]<<" ";
		}
	}

}

bool ctdivproprii(int n,int k) {
	int ct = 0;

	for (int i = 2; i <= n / 2; i++) {
		if (n % i == 0) {
			ct++;
		}
	}
	
	if (ct == k) {
		return true;
	}

	return false;

}


//i<d        v[i]     ctdivproprii(v[i], 3)                        vf
//            -                -                                   1
//0<4 da      16              true                                 1
//1<4 da      81              true                                 1
//2<4 da      16              true                                 1
//3<4 da      81              true                                 1
//4<4 nu
void solutie1d() {
	int v[200] = { 16, 81, 16, 81 };
	int d = 4;
	int k = 3;
	bool vf = 1;

	for (int i = 0;i < d;i++) {
		if (ctdivproprii(v[i], k)==false) {
			vf = 0;
			break;
		}
	}
	if (vf == 1) {
		cout << "DA" << endl;
	}
	else {
		cout << "NU" << endl;
	}

}


// i < end     i     v[i]     v[i] % 2      i % 2     v[i]%2 == i%2        p        vf
//             -      -          -            -             -              1       false
// 2 < 4 da    2      4          0            0          0 == 0 (da)       4       true
// 3 < 4 da    3     21          1            1          1 == 1 (da)      84       true
// 4 < 4 nu
void solutie1e() {
	int v[200] = { 10, 15, 4, 21, 8, 30 };
	int d = 6;
	int start = d / 3;
	int end = 2 * d / 3;
	int p = 1;
	bool vf = 0;
	for (int i = start; i < end; i++) {
		if (abs(v[i]) % 2 == i % 2) {
			p = p * v[i];
			vf = true;
		}

	}

	if (vf) {
		cout << "produs=" << p << endl;
	}
	else {
		cout << "nu exista numere care sa respecte conditia. Produs: 0" << endl;
	}

}


// n > 0           r           b2 = r * p + b2            p          n = n / 2
// 13 > 0 da       1                  1                   10           6
// 6 > 0 da        0                  1                   100           3
// 3 > 0 da        1                  101                 1000          1
// 1 > 0 da        1                  1101                10000         0
// 0 > 0 nu 
long long baza2(int n) {
	int b2 = 0;
	int p = 1;

	while (n > 0) {
		int r = n % 2;
		b2 = r * p + b2;
		p = p * 10;
		n = n / 2;
	}
	return b2;
}

bool cif0egalcif1(int n) {
	int zero = 0;
	int unu = 0;

	while (n != 0) {
		int cif=n%10;
		if (cif == 0) {
			zero++;
		}
		else if(cif == 1) {
			unu++;
		}
		n = n / 10;
	}

	if (zero == unu) {
		return true;
	}
	return false;
}

void solutie1f() {
    int v[8] = { 5, 12, 7, 3, 10, 9, 8, 2 };
	int d = 8;
	int start = 2 * (d / 4);
	int end = 3 * (d / 4);
	int s = 0;

	for (int i = start; i < end; i++) {
		if (cif0egalcif1(v[i])) {
			s = s + v[i];
		}
	}

	cout << s << endl;
}

int cifControl(int n) {
	int rest = n % 9;
	return (rest == 0) ? 9 : rest;
}

int produsCif(int n) {
	int p = 1;

	while (n != 0) {
		int cif = n % 10;
		p = p * cif;
		n = n / 10;
	}
	return p;


}

void solutie1g() {
	int v[8] = { 51, 12, 72, 31, 130, 29, 81, 21 };
	int d = 8;


	for (int i = 0; i < d; i++) {
		if (cifControl(v[i])%2==0) {
			int p=produsCif(v[i]);
			cout << "nr " << v[i] << " cu cifra de control " << cifControl(v[i]) << " are produsul cifrelor " << p << endl;
		}
	}


}

bool superprim(int n) {
	int pozitie = 0;
	if (prim(n) == false) {
		return false;
	}
	for (int i = 2; i <= n; i++) {
		if (prim(i)) {
			pozitie++;
		}
	}

	if (prim(pozitie)) {
		return true;
	}
	return false;
}

void solutie1h() {
	int v[8] = { 11, 4, 17, 9, 3, 12, 5 };
	int d = 7;


	for (int i = d - 1; i >= 0; i--) {
		if (superprim(v[i])) {
			cout << v[i] << " ";

		}

	}

	cout << endl;
}