#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//BAC 2026, VARIANTA 4



//SUBIECTUL I

//1. Indicați expresia C/C++ a cărei valoare este egală cu 26.
// d) 2026%100

//2.Tabloul unidimensional A=(3,9,11,12,17) se interclasează cu tabloul unidimensional B, în ordine
//crescătoare, elementele fiind parcurse de la stânga la dreapta.Știind că elementul cu valoarea 9 din tabloul
//A se compară cu 4 elemente ale tabloului B pe parcursul aplicării metodei, indicați o succesiune de valori
//care pot fi elementele tabloului B, în ordinea în care apar în acesta.
// b)(4,5,6,10,13) -> 9 se compara de 4 ori, cu 4,5,6 si 10

//3. Indicați valoarea expresiei C/C++ alăturate. ceil(20.26)
// a) 21

//4. În secvența C/C++ alăturată toate variabilele sunt întregi. Indicați atribuirile
//care pot înlocui punctele de suspensie astfel încât, în urma executării
//secvenței obținute, variabila r să memoreze valoarea 2^26.
// d) n=n*n; e=e/2


//5.  O agenție de turism pune la dispoziție pachete de vacanță cu câte două destinații, în ordinea următoare: una
//la munte și una pe litoral.Destinațiile sunt din mulțimile{ Bușteni - notat cu 1, Păltiniș - notat cu 2,
//Predeal - notat cu 3 }, pentru munte și{ Venus - notat cu 1, Neptun - notat cu 2, Olimp - notat cu 3 } pentru
//litoral.Două pachete diferă prin cel puțin o destinație de un anumit tip.În secvența C / C++ de mai jos toate
//variabilele sunt de tip întreg, iar în urma executării ei se obțin toate pachetele de tipul precizat, afișându - se pe
//ecran notațiile corespunzătoare destinațiilor alese.Primele cinci pachete obținute sunt, în această ordine,
//(Bușteni, Venus), (Bușteni, Neptun), (Bușteni, Olimp), (Păltiniș, Venus), (Păltiniș, Neptun).
//Indicați pachetul corespunzător soluției obținute imediat înainte de (Predeal, Venus).

//for (i = 1;i <= 3;i++)
//(j = 1;j <= 3;j++)
//cout << i << " " << j << endl;

//c. (Păltiniș, Olimp) 



//SUBIECTUL II

// 1. Algoritmul alăturat este reprezentat în pseudocod. 


//a) Scrieţi valoarea afișată în urma executării algoritmului dacă se citeşte
//numărul 2600.
  
//    d*d<=n       n%d==0        n      nr       d
//   4<2600 da   2600%2==0 da   1300    -
//       -       1300%2==0 da   650     -
//       -       650%2==0 da    325     -
//       -       325%2==0 nu           0+1=1     3
//   9<=325 da   325%3==0 nu           1+0=0     4            
//  16<=325 da   325%4==0 nu           1+0=0     5
//  25<=325 da   325%5==0 da    65 
//               65%5==0 da     13 
//               13%5==0 nu     13     1+1=2
//n!=0 => nr= 2+1=3

//  ==> se va afisa 3.

//b)Scrieţi două numere din intervalul [10,99] care pot fi citite, astfel încât,
//pentru fiecare dintre acestea, în urma executării algoritmului să se
//afişeze 1.
// 11,17 (numere prime)

//c)Scrieţi programul C/C++ corespunzător algoritmului dat. 
void sub2ex1c() {
	int n, p;
	int nr = 0;
	int d = 2;
	cin >> n;

	while (d * d <= n) {
		p = 0;
		while (n % d == 0) {
			p = 1;
			n = n / d;
		}
		nr = nr + p;
		d = d + 1;
	}

	if (n != 1) {
		nr = nr + 1;
	}
	cout << nr;
}

//d)Scrieţi în pseudocod un algoritm, echivalent cu cel dat, înlocuind a doua
//structură cât timp...execută cu o structură repetitivă cu test final.
void sub2ex1d() {
	int n, p;
	int nr = 0;
	int d = 2;
	cin >> n;

	while (d * d <= n) {
		p = 0;
		if (n % d == 0) {
			do {
				p = 1;
				n = n / d;
			} while (n % d != 0);
		}
		nr = nr + p;
		d = d + 1;
	}

	if (n != 1) {
		nr++;
	}
	cout << nr;
}



//SUBIECTUL III

//2. Scrieți un program C/C++ care citește de la tastatură un număr natural, n (n∈[2,50]), și un șir de n numere
//naturale din intervalul[0, 102], elemente ale unui tablou unidimensional.Programul transformă tabloul în
//memorie, interschimbând elementul său de valoare minimă cu primul element al tabloului, dacă acest minim
//este par, sau cu ultimul element al tabloului, dacă acest minim este impar.Dacă în tablou sunt mai multe
//elemente de valoare minimă, se alege doar unul dintre acestea.Tabloul obținut este afișat pe ecran, cu
//elementele separate prin câte un spațiu.
//Exemplu: dacă n = 6, pentru tabloul(8, 6, 2, 2, 7, 4) se poate obține tabloul(2, 6, 8, 2, 7, 4)
//iar pentru tabloul(8, 6, 1, 2, 7, 4) se obține tabloul(8, 6, 4, 2, 7, 1)

void sub3ex2() {
	int n = 6;
	int v[51] = {2,5,1,6,4,9};
	int min = v[0];
    int stanga = v[0];
	int dreapta = v[n-1];
	cout << dreapta;
	
	
	for (int i = 0;i < n;i++) {
		if (v[i] < min) {
			min = v[i];
		}
	}

}