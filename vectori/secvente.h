#pragma once
#include <iostream>
#include <cmath>
using namespace std;



// int v[100] = { 2,4,5,7,11,19,24,21,31,41,19 },  d=12

//  i<dim      v[i]%2==1     j    j+i<dim && v[j+1]%2==1      j   i
//  0<12 da      2 nu        -           -                    -   1
//  1<12 da      4 nu        -           -                    -   2
//  2<12 da      5 da        2       3<12 da, 7=impar         3   -  
//   -             -         -       4<12 da, 11=impar        4   -
//   -             -         -       5<12 da, 19=impar        5   -
//   -             -         -       6<12 da, 20=impar                    

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



