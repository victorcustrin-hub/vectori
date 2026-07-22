#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//intrebari:1e,2b,2d,3a,3b,3c,3e,3f

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
	long long b2 = 0;
	long long p = 1;

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


int cifraMin(int n) {
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

void solutie2a() {
	int v[300] = { 45,634,234,876,23 };
	int d = 5;
	int minGlobal = 10;

	for (int i = 0;i < d;i++) {
		int minim = cifraMin(v[i]);
		if (minim < minGlobal) {
			minGlobal = minim;
		}
	}
	cout << "cea mai mica cifra globala=" << minGlobal << endl;
	cout << "numerele din vector care contin aceasta cifra sunt:";
	for (int i = 0; i < d; i++) {
		if (cifraMin(v[i]) == minGlobal) {
			cout << v[i] << " ";
		}
	}
	cout << endl;

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


// copie != 0       nrCif       copie
// 141 != 0 da      1           14
// 14 != 0 da       2           1
// 1 != 0 da        3           0
// 0 != 0 nu

// i < pasi         n 
// i = 0 < 1 da     14
// i = 1 < 1 nu

// cifraMijl = 14 % 10 = 4
bool mijlocPatratPerfect(int n) {
	int copie = n;
	int nrCif = 0;

	while (copie != 0) {
		nrCif++;
		copie = copie / 10;
	}

	int pasi = (nrCif - 1) / 2;
	for (int i = 0; i < pasi; i++) {
		n =n/ 10;
	}

	int cifraMijloc = n % 10;

	if (cifraMijloc == 0 || cifraMijloc == 1 || cifraMijloc == 4 || cifraMijloc == 9) {
		return true;
	}
	return false;
}

void solutie2b() {
	int v[300] = { 141, 634, 5995, 876, 23 };
	int d = 5;

	for (int i = d - 1; i >= 0; i--) {
		if (palindrom(v[i])&&mijlocPatratPerfect(v[i])) {
			cout << v[i] << " ";
		}

	}
	cout << endl;

}

void solutie2c() {
	int v[300] = { 141, 634, 5995, 876, 23 };
	int d = 5;
	int p = 1;
	int nou = 0;
	for (int i = d-1; i >=0 ; i--) {
		int min = cifraMin(v[i]);
	    nou = min * p + nou;
		p = p * 10;
	}
	cout << nou << endl;

}
// n > 9          cif            cif2         n 
// 456 > 9 da     6               5           45
// 45 > 9 da      5               4           4
// 4 > 9 nu
bool consec(int n) {

	while (n > 9) {
		int cif = n % 10;
		int cif2 = n / 10 % 10;

		if (cif != cif2 + 1) {
			return false;
		}
		n = n / 10;
	}
	return true;
}

void solutie2d() {
	int v[300] = { 123, 45, 789, 2345, 67 };
	int d = 5;

	bool consecutiv = true;

	for (int i = 0; i < d; i++) {
		if (consec(v[i]) == false) {
			consecutiv = false;
			break;
		}
	}

	consecutiv ? cout << "Toate nr din vector au cifre consecutive" << endl : cout << "Cifrele din nr vectorului nu sunt consecutive" << endl;
   
}


void solutie3a() {
	int m = 0;
	int ct = 1;
	cout << "m=";
	cin >> m;
	cout << "Introduceti " << m << " numere cu valori intre 200-300 sau 2000-3000." << endl;

	while (m != 0) {
		int x = 0;
		cout << "nr" << ct << "=";
		cin >> x;




		ct++;
		m--;
	}
	cout << endl;
}

bool patratPerfect(int n) {
	int radacina = sqrt(n);

	if (radacina * radacina == n) {
		return true;
	}
	return false;
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


void solutie3b() {
	int v[300] = { 12,24,27 };
	int d = 3;

	for (int i = 0;i < d;i++) {
		if (i > 0 && i < d - 1) {
			if (patratPerfect(v[i]) == false && v[i] % 2 == v[i - 1] % 2 && v[i - 1] % 2 == v[i + 1] % 2) {
				descompunereFactoriPrimi(v[i]);
			}
		}
		else {
			if (patratPerfect(v[i]) == false) {
				descompunereFactoriPrimi(v[i]);
			}
		}

	}

}

void solutie3c() {
	int v[300] = { 123, 456, 77, 777, 200, 201, 202 };
	int d = 7;
	int s = d / 7;
	int start = s;
	int end= 2 * s - 1;
	bool egal= true;
	int primulnr = v[start];
	int copiecif = primulnr % 10;

	for (int i = start; i <= end; i++) {
		int n = v[i];

		
		while (n > 0) {
			int cif = n % 10;
			if (cif != copiecif) {
				egal = false;
				break;
			}
			n = n / 10;
		}

		if (egal == false) {
			break;
		}
	}

	
	egal ? cout << "cifrele din a doua septime sunt egale" << endl : cout << "cifrele din a doua septime nu sunt egale" << endl;
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

int cmmdc(int a, int b) {
	while (b!=0) {
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

