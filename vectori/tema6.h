#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//5,7


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
    const int valoareMax = 100;
    int f[valoareMax + 1] = { 0 };

    for (int i = 0;i < d;i++) {
        f[v[i]]++;
    }

    int vf = -1;

    for (int i = 0;i <= valoareMax;i++) {
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
    int v[100] = { 0,5,0,7 };
    int d = 4;

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
//

//5
void nrNou(int v[],int d) {
    int ct[10] = { 0 };

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

        for (int k = 0; k <= 9; k++) {
            if (f[k] == 1) {
                ct[k]++;
            }
        }
    }

    int nr = 0;
    bool cifComune = false;

    for (int c = 0; c <= 9; c++) {
        if (ct[c] == d) {
            nr = nr * 10 + c;
            cifComune = true;
        }
    }

    if (cifComune) {
        cout << "numarul format = " << nr << endl;
    }
    else {
        cout << "0" << endl;
    }

}

void solutie5() {
    int v[100] = { 1234, 4321, 5142, 9413 };
    int d = 4;

    nrNou(v, d);

}
//

//6
void secventePare(int v[], int d) {
    int ctSecvente = 0;
    int smax = 0;
    int dmax = -1;

    for (int i = 0; i < d; i++) {
        if (v[i] % 2 == 0) {
            int j = i;

            while (j + 1 < d && v[j + 1] % 2 == 0) {
                j++;
            }

            ctSecvente++;


            if (j - i > dmax - smax) {
                smax = i;
                dmax = j;
            }

            i = j;
        }
    }

    cout << "nr de secvente de numere pare = " << ctSecvente << endl;

    if (dmax != -1) {
        int lungimeMax = dmax - smax + 1;
        cout << "cea mai lunga are lungimea " << lungimeMax << " si incepe pe pozitia " << smax << endl;
    }
    else {
        cout << "nu exista secvente de numere pare." << endl;
    }
}

void solutie6() {
    int v[100] = { 3, 8, 4, 6, 7, 2, 5, 10, 12, 14, 16, 9 };
    int d = 12;

    secventePare(v, d);
}
//

//7
void ceaMaiLungaSecventaElementeDistincte(int v[], int d) {
    int smax = 0;
    int dmax = -1;

    for (int i = 0; i < d; i++) {
        int f[101] = { 0 };

        int j = i;

        while (j < d && f[v[j]] == 0) {
            f[v[j]] = 1;
            j++;
        }

        int d = j - 1;

        if (d - i > dmax - smax) {
            smax = i;
            dmax = j - 1;
        }
    }


    if (dmax != -1) {
        cout << "secventa: ";
      
        for (int k = smax; k <= dmax; k++) {
            cout << v[k] << " ";
        
        }

        cout << endl;
        cout << "lungime: " << (dmax - smax + 1) << endl;
    }
    else {
        cout << "vectorul e gol" << endl;
    }
}

void solutie7() {
    int v[100] = { 5, 2, 7, 2, 9, 4, 1, 9, 3 };
    int d = 9;

    ceaMaiLungaSecventaElementeDistincte(v, d);
}
//

//8
void ceaMaiLungaSecventaParitatiDiferite(int v[], int d) {
    int smax = 0;
    int dmax = -1;

    for (int i = 0; i < d; i++) {
        int j = i;

        while (j + 1 < d && (abs(v[j] % 2) != abs(v[j + 1] % 2))) {
            j++;
        }

        if (j - i > dmax - smax) {
            smax = i;
            dmax = j;
        }

        i = j;
    }


    if (dmax != -1) {
        cout << "secventa = ";
        for (int k = smax; k <= dmax; k++) {
            cout << v[k] << " ";
        }
        cout << endl;
        cout << "lungime = " << (dmax - smax + 1) << endl;
    }
    else {
        cout << "Vectorul este gol." << endl;
    }
}

void solutie8() {
    int v[100] = { -3, 5, -7, 9 };
    int d = 4;

    ceaMaiLungaSecventaParitatiDiferite(v, d);
}
//



//CORECTAREA TEMEI
