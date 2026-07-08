#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//4 numere{32,56,19,42},d=4                    0   1   2   3   
//   i<d       j<d     v[i]>v[j]               32  56  19  42     j   i
// 0<4da       1<4 da  v[0]>v[1] f                                2
//             2<4 da  v[0]>v[2] d             19      32         3
//             3<4 DA  V[0]>V[3] f                                4
//             4<4 nu                                                 1
//   1<4 da    2<4 da  v[1]>v[2] d             19  32  56  42     3
//             3<4 da  v[1]>[3]  f                                4                        
//             4<4 nu                                                 2
//   2<4 da    3<4 da  v[2]>v[3] d             19  32  42  56     4 
//             4<4 nu                                                 3
//   3<4 da    4<4 nu                                                 4
//   4<4 nu                          
void sortareaPrinSelectie(int v[],int d) {

	for (int i = 0;i < d;i++) {
		for (int j = i + 1;j < d;j++) {
			if (v[i] > v[j]) {
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			 }
		}
	}

}


//4 nr{32,56,19,42},d=4                  0    1    2    3
//  sortat    i<d-1     v[i]>v[i+1]     32   56   19   42       sortat          i     sortat==false
//   true     0<3 da     32>56 nu                                true           1           nu
//            1<3 da     56>19 da       32   19   56   42        false          2           da
//            2<3 da     56>42 da       32   19   42   56        false          3           da
//            3<3 nu                                              true                      nu                        
//    true    0<3 da     32>19 da       19   32   42   56        false          1           da
//            1<3 da     32>42 nu                                true           2           nu
//            2<3 da     42>56 nu                                true           3           nu
//            3<3 nu                                             true                       nu
//    false

void sortatPrinBubbleSort(int v[], int d) {

	bool sortat = true;

	do{
		sortat = true;

		for (int i = 0;i < d-1;i++) {
			
				if (v[i] > v[i+1]) {
					int aux = v[i];
					v[i] = v[i+1];
					v[i+1] = aux;
					sortat = false;
				}
			
		}

	} while (sortat == false);
}


void afisare(int v[], int d) {
	 
	for (int i = 0;i < d;i++) {
		cout << v[i] << " ";
	}

}

void solutie509() {
	int v[100] = { 32,56,19,42};
	int d = 4;

	sortatPrinBubbleSort(v, d);
    afisare(v, d);
}

bool prim(int n) {
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

void solutie510() {
	int v[100] = { 29,12,7,113,53,32 };
	int d = 6;
	int aux[100];
	int ct = 0;
	for (int i = 0;i < d;i++) {
		if (prim(v[i])) {
			aux[ct] = v[i];
			ct++;
			
		}
	}
	sortatPrinBubbleSort(aux,ct);
	afisare(v, d);
}



