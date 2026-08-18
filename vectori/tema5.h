#pragma once
#include <iostream>
#include <cmath>
using namespace std;
//519,520,300,862,981,4148,2921,297

//1
//519
// Se dă un vector x cu n elemente, numere naturale, și un vector y cu m elemente, numere naturale.
// Să se verifice dacă vectorul y este secvență în vectorul x.
void ySecventaInX(int x[], int y[], int dimX, int dimY) {
    bool vf = false;
    int mem = 0;
    for (int i = 0; i <= dimX - dimY; i++) {
        bool potrivire = true;

        for (int j = 0; j < dimY; j++) {
            if (x[i + j] != y[j]) {
                potrivire = false;
                break;
            }
        }

        if (potrivire) {
            vf = true;
            mem = i + 1;
            break;
        }
    }

    if (vf) {
        cout << "vectorul y este secventa in vectorul x, incepand pe pozitia "<< mem << endl;
    }
    else {
        cout << "vectorul y nu este este secventa in vectorul x" << endl;
    }
}

void solutie519() {
    int x[100] = { 8, 5, 8, 5, 2, 3, 10, 7, 1, 6 };
    int n = 10;

    int y[100] = { 5, 2, 3, 10, 7 };
    int m = 5;

    ySecventaInX(x, y, n, m);
}
//

//2
//520
//Se dă un vector x cu n elemente, numere naturale și un vector y cu m elemente, numere naturale.
// Să se determine de câte ori este vectorul y secvență în vectorul x.
int ctSecventa(int x[], int y[], int dimX, int dimY) {
    int ct = 0;

    for (int i = 0; i <= dimX - dimY; i++) {
        bool vf = true;

        for (int j = 0; j < dimY; j++) {
            if (x[i + j] != y[j]) {
                vf = false;
                break;
            }
        }

        if (vf) {
            ct++;
        }
    }

    return ct;
}

void solutie520() {
    int n = 10;
    int x[100] = { 8, 5, 8, 5, 8, 3, 8, 5, 8, 6 };

    int y[100] = { 8, 5, 8 };
    int m = 3;

    int rez = ctSecventa(x, y, n, m);

    cout << "y apare ca secventa in x de " << rez << " ori" << endl;
}
//


//3
//522
//Se dă un vector cu n elemente, numere naturale, și un număr k.
//Să se stabilească dacă în vector există două secvențe de lungime k identice.
void verificaKSecventa1(int v[], int n, int k) {
    bool vf = false;

    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n - k; j++) {
            if (v, i, j, k) {   //???
                vf = true;
                break;
            }
        }
        if (vf) {
            break;
        }
    }

    if (vf) {
        cout << "DA" << endl;
    }
    else {
        cout << "NU" << endl;
    }
}

void solutie522() {
    int v[8] = { 1, 2, 3, 4, 2, 3, 4, 5 };
    int n = 8;
    int k = 3;

    verificaKSecventa1(v, n, k);

}
//

//4
//Se dă un vector cu n elemente, numere naturale. 
//Determinați câte secvențe ale vectorului au toate elementele egale.
void contorSecventeElementeEgale(int v[], int d) {
    int secvente = 0;

    for (int i = 0; i < d; i++) {
        int j = i;
        while (j + 1 < d && v[j + 1] == v[i]) {
            j++;
        }
        int lungime = j - i + 1;
        secvente = secvente + (lungime * (lungime + 1)) / 2;
        i = j;
    }

    cout << "nr total de secvente cu elemente egale este " << secvente << endl;
}

void solutie578() {
    int v[100] = { 4, 3, 3, 3, 5 };
    int d = 5;
    contorSecventeElementeEgale(v, d);
}
//

//5
//854
//Se dă un șir cu n elemente, numere naturale și un număr k.
// Determinați numărul minim de secvențe disjuncte în care trebuie împărțit șirul astfel încât fiecare element
// al șirului să aparțină unei secvențe și fiecare secvență să conțină cel mult k elemente impare.
int numarMinimSecvente(int v[], int n, int k) {
    int nrSecvente = 1;
    int nrImp = 0;

    if (n == 0) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (v[i] % 2 != 0) {
            nrImp++;

            if (nrImp > k) {
                nrSecvente++;        
                nrImp = 1; 
            }
        }
    }

    return nrSecvente;
}


void solutie854() {
    int v[] = { 2, 4, 1, 3, 6, 5, 7, 8 };
    int n = 8;
    int k = 2;

    int rezultat = numarMinimSecvente(v, n, k);

    cout << "Numarul minim de secvente disjuncte este: " << rezultat << endl;
}
//

//6
//#523
//Se dă un vector cu n elemente, numere naturale. Determinați cea mai lungă secvență de elemente egale din vector. 
//Dacă în vector există mai multe secvențe de elemente egale de lungime maximă se va determina cea mai din dreapta.
void ElementeEgale(int v[], int d) {
    int smax = 1;
    int dmax = 0;


    for (int i = 0;i < d;i++) {
        int j = i;
        while (j + 1 < d && v[j + 1] == v[i]) {
            j++;
        }

        if (j - i >= dmax - smax) {
            dmax = j + 1;
            smax = i + 1;
        }
        i = j;
    }

    cout << smax << " " << dmax << endl;

}

void solutie523() {
    int v[100] = { 5, 5, 1, 1, 1, 1, 2, 2, 2, 2 };
    int d = 10;

    ElementeEgale(v, d);
}
//

//7
//298
//Se dă un şir format din n elemente, numere naturale. 
//Calculaţi suma elementelor din secvenţa determinată de primul şi ultimul element prim.
bool prim(int n) {
    if (n <= 1) {
        return false;
    }
    for (int k = 2; k <= n / 2; k++) {
        if (n % k == 0) {
            return false;
        }
    }
    return true;
}

void secventaPrimulSiUltimulElementPrim(int v[], int d) {
    int smax = -1;
    int dmax = -1;

    for (int i = 0; i < d; i++) {
        if (prim(v[i])) {
            if (smax == -1) {
                smax = i;
            }
            dmax = i;
        }
    }

    if (smax != -1) {
        int s = 0;
        for (int i = smax; i <= dmax; i++) {
            s = s + v[i];
        }
        std::cout << "suma elementelor din secventa este " << s << endl;
    }
    else {
        std::cout << "nu exista elemente prime in vector" << endl;
    }
}

void solutie298() {
    int v[100] = { 12, 10, 15, 7, 17, 10, 19, 14 };
    int d = 8;

    secventaPrimulSiUltimulElementPrim(v, d);
}
//

//8
//166
//Să se determine cea mai lungă secvență de elemente pare dintr-un vector.
void ceaMaiLungaSecventaElementePare(int v[], int d) {
    int smax = 0;
    int dmax = -1;

    for (int i = 0; i < d; i++) {
        if (v[i] % 2 == 0)
        {
            int  j = i;
            while (j + 1 < d && v[j + 1] % 2 == 0) {
                j++;
            }

            if (j - i >= dmax - smax) {
                smax = i, dmax = j;
            }
            i = j;
        }
    }
    smax++;
    dmax++;
    cout << smax << " " << dmax << endl;
}

void solutie166() {
    int v[100] = { 2, 6, 4, 5, 8, 8, 6, 3, 4 };
    int d = 9;

    ceaMaiLungaSecventaElementePare(v, d);
}
//

//9
//181
//Să se determine cea mai lungă secvență de elemente ordonate strict crescător dintr-un vector.
void ceaMaiLungaSecventaCrescatoare(int v[], int d) {
    int smax = 0;
    int dmax = -1;

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
    smax++;
    dmax++;
    cout << smax << " " << dmax << endl;

}

void solutie181() {
    int v[100] = { 2, 6, 4, 5, 8, 9, 6, 3, 4 };
    int d = 9;

    ceaMaiLungaSecventaCrescatoare(v, d);
}
//

//10
//300
//Se dă un vector format din n elemente, numere naturale nenule, şi un număr natural S.
//Determinaţi, dacă există o secvenţă de elemente din şir cu suma elementelor egală cu S.
void vfSecventaSuma(int v[], int n, int s) {
    int ct = 0;
    int suma = 0;
    int smax = -1;
    int dmax = -1;
    bool vf = false;

    for (int i = 0; i < n; i++) {
        suma = suma + v[i];

        while (suma > s && ct <= i) {
            suma = suma - v[ct];
            ct++;
        }

        if (suma == s) {
            smax = ct;
            dmax = i;
            vf = true;
            break;
        }
    }

    if (vf) {
        cout << smax + 1 << " " << dmax + 1 << endl;
    }
    else {
        cout << "nu exista o secventa care indeplineste cerinta" << endl;
    }
}

void solutie300() {
    int v[100] = { 12, 10, 15, 7, 17, 13, 19, 14 };
    int d = 9;
    int s = 32;
    
    vfSecventaSuma(v,d,s);
}
//

//11
void secventeMaximaleCrescatoare(int v[], int d) {
    int ct = 0;

    for (int i = 0; i < d; i++) {
        int j = i;

        while (j + 1 < d && v[j + 1] >= v[j]) {
            j++;
        }
        ct++;
        i = j;
    }

    cout << "nr de secvente maximale crescatoare este " << ct << endl;
}

void solutie304() {
    int v[100] = { 12, 15, 19, 10, 14, 8, 9, 11, 20 };
    int d = 9;

    secventeMaximaleCrescatoare(v, d);
}
//

//12
//516
//Se dă un vector format din n elemente, numere naturale. 
//Calculați suma elementelor din secvența determinată de primul și ultimul element impar.
void secventaPrimulUltimulNrImp(int v[], int d) {
    int x = -1;
    int y = -1;

    for (int i = 0;i < d;i++) {
        if (v[i] % 2 != 0) {
            if (x == -1) {
                x = i;
            }
            y = i;
        }

    }


    if (x != -1) {
        int s = 0;
        for (int i = x;i <= y;i++) {
            s = s + v[i];
        }
        cout << s << endl;
    }
    else {
        cout << "Sirul de numere nu indeplineste cerinta" << endl;
    }
}

void solutie516() {
    int v[100] = { 12,10,15,6,7,10,19,14 };
    int d = 8;
    secventaPrimulUltimulNrImp(v, d);
}
//

//13
//862
//Se dă un vector cu n elemente, numere naturale și două numere t și k.
// Să se determine câte secvențe din șir au lungimea k și sunt formate din valori mai mici sau egale cu t.
void secventeLungimeK(int v[], int n, int t, int k) {
    int ct = 0;

    for (int i = 0; i <= n - k; i++) {
        bool vf = true;

        for (int j = 0; j < k; j++) {
            if (v[i + j] > t) {
                vf = false;
                break;
            }
        }

        if (vf) {
            ct++;
        }
    }

    cout << "nr de secvente este " << ct << endl;
}

void solutie862() {
    int v[100] = { 1, 4, 3, 5, 7, 3, 4, 2 };
    int n = 8;
    int t = 5;
    int k = 3;
    secventeLungimeK(v, n, t, k);
}
//

//14
//981
//Într-un şir trebuie determinată lungimea maximă a unei secvenţe de numere care în scrierea binară au numai cifra 1.
bool nr1InBaza2(int n) {
    int ct = 0;
    int total = 0;

    while (n != 0) {
        total++;
        if (n % 2 == 1) {
            ct++;
        }
        n = n / 2;
    }

    if (ct == total) {
        return true;
    }
    return false;
}

void solutie981() {
    int v[100] = { 4, 6, 7, 15, 88 };
    int d = 5;

    int dmax = 0;

    for (int i = 0; i < d; i++) {
        if (nr1InBaza2(v[i])) {
            int j = i;

            while (j + 1 < d && nr1InBaza2(v[j + 1])) {
                j++;
            }

            int l = j - i + 1;
            if (l > dmax) {
                dmax = l;
            }

            i = j;
        }
    }

    cout << "lungimea maxima a secventei in scriere binara este " << dmax << endl;
}
//

//15
//524
//Se dă un vector cu n elemente, numere naturale. 
// Determinați cea mai lungă secvență de elemente din vector care începe și se termină cu aceeași valoare. 
// Dacă în vector există mai multe secvențe corecte de lungime maximă se va determina cea mai din stânga.
void secvEgale1(int v[], int d) {
    int smax = 0;
    int dmax = -1;

    for (int i = 0; i < d; i++) {
        
        for (int j = i; j < d; j++) {
          
            if (v[i] == v[j]) {
               
                if ((j - i) > (dmax - smax)) { 
                    smax = i;
                    dmax = j;
                }

            }

        }

    }

    if (dmax != -1) {
        cout << smax + 1 << dmax + 1 << endl;
    }
    else {
        cout << "sirul nu indeplineste conditiile cerintei" << endl;
    }
}

void solutie524() {
    int v[100] = { 6, 6, 8, 3, 6, 6, 3, 8, 4, 3, 3, 4 };
    int d = 12;

    secvEgale1(v, d);
}
//

//16
//4148
//Se dau n numere naturale, reprezentând elementele unui vector. Determinați lungimea maximă a unei 
// secvențe de elemente divizibile cu 10, precum și numărul de secvențe de lungime maximă cu elemente 
// divizibile cu 10.
void secv10(int v[], int n) {
    int lmax = 0;

    for (int i = 0; i < n; i++) {
        if (v[i] % 10 == 0) {
            int j = i;

            while (j + 1 < n && v[j + 1] % 10 == 0) {
                j++;
            }

            int lungime = j - i + 1;
            if (lungime > lmax) {
                lmax = lungime;
            }

            i = j;
        }
    }

    int ct = 0;


    cout << "Lungimea max = " << lmax << endl;
    cout << "nr de secvente de lungime maxima = " << ct << endl;
}

void solutie4148() {
    int v[100] = { 12, 20, 30, 7, 50, 60, 13, 90 };
    int n = 8;

    secv10(v, n);
}
//

//17
//2921
//Se dă un șir cu n elemente numere întregi, numerotate de la 1 la n și m perechi de indici i j. 
// Pentru fiecare pereche de indici se calculează suma elementelor din secvență determinată de cei doi indici. 
// Afișați suma maximă obținută.
void solutie2921() {
    int v[100] = { 0, 2, -3, 5, 4, -1, 6 };
    int d = 6;
    int m = 3;


    int sp[100] = { 0 };
    for (int i = 1; i <= d; i++) {
        sp[i] = sp[i - 1] + v[i];
    }


    int smax = -2000000000;

    for (int k = 0; k < m; k++) {

      
    }

    cout << "Suma maxima obtinuta din perechi este: " << smax << endl;
}
//

//18
//283
//Se dă un şir cu n elemente, numere naturale.
//Determinaţi cea mai lungă secvenţă de elemente din şir cu proprietatea că 
//oricare două valori consecutive în secvenţă au parităţi diferite.
void ceaMaiLungaSecventaParitatiDiferite(int v[], int d) {
    int smax = 0;
    int dmax = -1;

    for (int i = 0; i < d; i++) {
        int j = i;

        while (j + 1 < d && (v[j] % 2 != v[j + 1] % 2)) {
            j++;
        }

        if (j - i >= dmax - smax) {
            smax = i;
            dmax = j;
        }

        i = j;

    }

    if (dmax != -1) {
        cout << smax + 1 << " " << dmax + 1 << endl;
    }
    else {
        cout << "nu exista secvente care respecta cerinta" << endl;
    }
}

void solutie283() {
    int v[100] = { 2, 4, 3, 6, 7, 5, 2, 5, 8, 10 };
    int d = 10;

    ceaMaiLungaSecventaParitatiDiferite(v, d);
}
//

//19
//4457
//Se dă un şir cu n elemente, numere naturale.
//Determinaţi cea mai lungă secvenţă de elemente din şir cu proprietatea că oricare
//două valori consecutive în secvenţă au parităţi diferite.
void secventaParitatiDiferite(int v[], int d) {
    int smax = 0;
    int dmax = -1;

    for (int i = 0; i < d; i++) {
        int j = i;

        while (j + 1 < d && (v[j] % 2 != v[j + 1] % 2)) {
            j++;
        }

        if ((j - i) >= (dmax - smax)) {
            smax = i;
            dmax = j;
        }

        i = j;
    }

    if (dmax != -1) {
        cout << smax + 1 << " " << dmax + 1 << endl;
    }
    else {
        cout << "nu sunt secvente care indeplinesc conditia" << endl;
    }
}

void solutie4457() {
    int v[100] = { 2, 4, 3, 6, 7, 5, 2, 5, 8, 10 };
    int d = 10;

    secventaParitatiDiferite(v, d);
}
//

//20
//297
//Se dă un şir cu n elemente, numere întregi. Determinaţi secvenţa de elemente cu suma maximă.
void determinaSecvSumMax(int v[], int d) {
    int sumaMax = v[0];
    int suma = v[0];
    int smax = 0;
    int dmax = 0;

    for (int i = 1; i < d; i++) {
        if (suma < 0) {
            suma= v[i];
        }
        else {
            suma = suma + v[i];
        }

        if (suma > sumaMax) {
            sumaMax = suma;
            dmax = i;
        }
    }

}

void solutie297() {
    int v[10] = { -4, 1, - 5, 1, 4, - 2, 2, 3, - 4, 4, };
    int d = 9;

    determinaSecvSumMax(v, d);
}