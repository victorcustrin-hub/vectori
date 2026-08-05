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
        if (v[i] % 2 == 1)
        {
            int  j = i;
            while (j + 1 < dim && v[j + 1] % 2 == 1) {
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

void solutie1() {
    int v[100] = { 2,4,5,7,11,19,24,21,31,41 };
    int d = 10;
    
    ceaMaiLungaSecventaDeNumereImpare(v, d);
}

// vector cu n elemente,Calculați suma elementelor din secvența determinată de primul și ultimul element impar.
void secventaPrimulSiUltimulNumarImpar(int v[], int d) {
    int primul = -1;
    int ultimul = -1;

    for (int i = 0;i < d;i++) {
        if (v[i] % 2 == 1) {
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

void solutie2() {
    int v[100] = { 12,10,15,6,7,10,19,14 };
    int d = 8;
    secventaPrimulSiUltimulNumarImpar(v, d);
}

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
    cout << smax << " " << dmax;
}

void solutie3() {
    int v[100] = { 0,1,0,0,0,3,0,0,0,2 };
    int d = 10;

    secventaElementeNuleMaxima(v, d);
}