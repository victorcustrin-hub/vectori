#pragma once
#include <iostream>
#include <cmath>
using namespace std;


void ceaMaiLungaSevcentaDeNumerePare(int v[], int dim) {
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

    for (int i = smax;i <=dmax;i++) {
        cout << v[i] << " ";
    }
}



