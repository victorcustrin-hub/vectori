#pragma once
#include <iostream>
#include <cmath>
using namespace std;


//PARTEA 1

//1
void ceaMaiLungaSecventaStrictCrescatoare(int v[], int d) {
    int smax = 0;
    int dmax = -1;
    int ct = 0;

    for (int i = 0; i < d; i++) {
        int j = i;

        while (j + 1 < d && v[j + 1] > v[j]) {
            j++;
        }

        if (j - i >= dmax - smax) {
            smax = i;
            dmax = j;
        }

        i = j;
    }
    cout << "secventa = ";
    for (int k = smax; k <= dmax; k++) {
        cout << v[k] << " ";
        ct++;
    }
    cout << endl;
    cout <<"Lungime = "<< ct;
}

void solutie1() {
    int v[100] = { 4,7,9,2,3,5,8,12,6 };
    int d = 9;

    ceaMaiLungaSecventaStrictCrescatoare(v, d);
}
//

//2
void contineCifraC(int v[],int d,int c) {
    int ct = 0;

    cout << "contin cifra " << c << ": ";

    for (int i = 0; i < d; i++) {
        int f[10] = { 0 };
        int aux = v[i];

        if (aux == 0) {
            f[0] = 1;
        }

        while (aux != 0) {
            int cif = aux % 10;
            f[cif] = 1;
            aux = aux / 10;
        }

        if (f[c] == 1) {
            cout << v[i] << " ";
            ct++;
        }
    }
    cout << endl;
    cout << "total: " << ct << endl;
}

void solutie2() {
    int v[100] = { 172,45,717,30,27,88 };
    int d = 6;
    int c = 7;

    contineCifraC(v, d, c);

}
//

//3
void apareDeMinimDouaOri(int v[], int d) {
    int f[101] = { 0 };

    for (int i = 0;i < d;i++) {
        f[v[i]]++;
    }

    int vf = -1;

    for (int i = 1;i <= 100;i++) {
        if (f[i] >= 2) {
            vf = i;
            break;
        }
    }

    if (vf != -1) {
        cout << "cel mai mic numar repetat = " << vf << ", apare de " << f[vf] << " ori." << endl;
    }
    else {
        cout << "Nu exista dublete" << endl;
    }

}

void solutie3() {
    int v[100] = { 42,17,8,42,17,91,17 };
    int d = 7;

    apareDeMinimDouaOri(v, d);
}
//

//4
int sumaCifrelor(int n) {
    int s = 0;

    while (n != 0) {
        int cif = n % 10;
        s = s + cif;
        n = n / 10;
    }

    return s;

}

void secventaCuSumaCifrelorEgala(int v[], int d) {
    int smax = 0;
    int dmax = -1;
    int suma_total = 0;

    for (int i = 0;i < d;i++) {
        int j = i;
        int suma = sumaCifrelor(v[i]);

        while (j + 1 < d && sumaCifrelor(v[j + 1]) == suma) {
            j++;
        }

        if (j - i >= dmax - smax) {
            smax = i;
            dmax = j;
            suma_total = suma;
        }

        i = j;
    }

    if (dmax != -1) {
        cout << "suma cifrelor: " << suma_total << endl;
        cout << "secventa: ";
        for (int k = smax; k <= dmax; k++) {
            cout << v[k] << " ";
        }
        cout << endl;
        cout << "lungime: " << (dmax - smax + 1) << endl;
    }
}

void solutie4() {
    int v[100] = { 23,41,50,14,7,61,106,90,12 };
    int d = 9;

    secventaCuSumaCifrelorEgala(v, d);
}