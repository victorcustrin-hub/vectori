#pragma once
#include <iostream>
#include <cmath>
using namespace std;

// int v[100] = { 2,4,5,7,11,19,24,21,31,41 },  d=10

//  i<dim      v[i]%2==1     j    j+i<dim && v[j+1]%2==1      j      smax           dmax     i
//  0<10 da      2 nu        -           -                    -       -               -      1
//  1<10 da      4 nu        -           -                    -       -               -      2
//  2<10 da      5 da        2       3<10 da, 7=impar         3       -               -      -  
//   -             -         -       4<10 da, 11=impar        4       -               -      -
//   -             -         -       5<10 da, 19=impar        5       -               -      -
//   -             -         -       6<10 da, 24=par          -       2               5      5
//  6<10 da      24 nu       -           -                    -       -               -      7
//  7<10 da      21 da       7       8<10 da, 31=impar        8       -               -      -
//   -             -         -       9<10 da, 41=impar        10      -               -      -
//   -             -         -       10<10 nu                 -       2 (if==false)   5      10
//  10 < 10 nu   
void ceaMaiLungaSecventaDeNumereImpare(int v[], int dim) {
    int smax, dmax;
    smax = 1, dmax = 0;
    for (int i = 0; i < dim; i++){
        if (v[i] % 2 != 0)
        {
            int  j = i;
            while (j + 1 < dim && v[j + 1] % 2 != 0) {
                j++;
            }
                
            if (j - i > dmax - smax) {
                smax = i, dmax = j;
            }
            i = j;
        }
    }
    for (int i = smax;i <= dmax;i++) {
        cout << v[i] << " ";
    }
}

void solutie() {
    int v[100] = { 2,4,5,7,11,19,24,21,31,41 };
    int d = 10;
    
    ceaMaiLungaSecventaDeNumereImpare(v, d);
}
//

//#516
// vector cu n elemente,Calculați suma elementelor din secvența determinată de primul și ultimul element impar.
void secventaPrimulSiUltimulNumarImpar(int v[], int d) {
    int primul = -1;
    int ultimul = -1;

    for (int i = 0;i < d;i++) {
        if (v[i] % 2 != 0) {
            if (primul == -1) {
                primul = i;
            }
            ultimul = i;
        }
    }
    if (primul != -1) {
        int s = 0;
        for (int i = primul;i <= ultimul;i++) {
            s = s + v[i];
        }
        cout << "Suma dintre " << v[primul] << ", primul nr impar din sir cu " << v[ultimul] << ", ultimul nr impar din sir, este " << s << endl;
    }
    else {
        cout << "Nu exista elemente impare in vector" << endl;
    }
}

void solutie516() {
    int v[100] = { 12,10,15,6,7,10,19,14 };
    int d = 8;
    secventaPrimulSiUltimulNumarImpar(v, d);
}
//

//#518
//Determinați cea mai lungă secvență de elemente nule din vector.
//Dacă în vector există mai multe secvențe de elemente nule de lungime maximă se va determina cea mai din stânga.
void secventaElementeNuleMaxima(int v[], int d) {
    int smax = 0;
    int dmax = -1;

    for (int i = 0;i < d;i++) {
        if (v[i] == 0) {
            int j = i;
            while (j + 1 < d && v[j + 1] == 0) {
                j++;
            }

            if (j - i > dmax - smax) {
                smax = i + 1;
                dmax = j + 1;;
            }
            i = j;
        }

    }
    if (dmax == -1) {
        cout << "Nu exista elemente nule in vector.";
        return;
   }
    
    cout << smax << " " << dmax << endl;
}

void solutie518() {
    int v[100] = { 0,1,0,0,0,3,0,0,0,2 };
    int d = 10;

    secventaElementeNuleMaxima(v, d);
}
//

//#523
//determinati cea mai lungă secvență de elemente egale din vector. 
//Dacă în vector există mai multe secvențe de elemente egale de lungime maximă se va determina cea mai din dreapta.
void secventaElementeEgale(int v[], int d) {
    int smax = 1;
    int dmax = 0;

    for (int i = 0;i < d;i++) {
        int j = i;
        while (j + 1 < d && v[j + 1] == v[i]) {
            j++;
        }

        if (j - i >= dmax - smax) {
            smax = i + 1;
            dmax = j + 1;
        }
        i = j;
    }

    cout << smax << " " << dmax << endl;

}

void solutie523() {
    int v[100] = { 5,5,1,1,1,1,2,2,2,2 };
    int d = 10;

    secventaElementeEgale(v, d);

}
//

//#981
//determinati lungimea maximă a unei secvenţe de numere care în scrierea binară au numai cifra 1.
bool nr1InBaza2(int n) {
    int ct = 0;
    int total = 0;

    while (n != 0) {
        total++;
        if (n % 2 != 0) {
            ct++;
        }
        n = n / 2;
    }
    if (ct == total) {
        return true;
    }
    return false;
}

void secventaScriereBinara(int v[], int d) {
    int lungime = 0;
    int lMax = 0;

    for (int i = 0;i < d;i++) {
        if (nr1InBaza2(v[i])) {
            int j = i;
            while (j + 1 < d && nr1InBaza2(v[j + 1])) {
                j++;
            }

            int lungime = j - i + 1;
            if (lungime > lMax) {
                lMax = lungime;
            }
            i = j;
        }
    }
    cout << lMax << endl;
}

void solutie981() {
    int v[100] = {4,6,7,15,88};
    int d = 5;
    secventaScriereBinara(v, d);
}
//


