# Code Review — victor-vectori (toate headerele)

Review pe cele 7 headere din `vectori/`: `exercitiiVectori.h`, `tema2.h`, `realizareaUnuiNouVector.h`, `MunteVale.h`, `dublete.h`, `corectareTema2.h`, `tema3.h`, plus `sortareaVectorilor.h` și `vectori.cpp`. Codul NU a fost modificat — toate observațiile sunt doar aici.

---

## 🔴 Critice (bug-uri reale)

### B1 — `cmmmc` returnează mereu `a`, nu cmmmc-ul (operatorul virgulă)
- `corectareTema2.h:249` — `return a * b / (a, b);`
- `tema2.h:655` — `return (a * b) / (a, b);`

În C++, `(a, b)` NU este „cmmdc de a și b" ca în notația matematică `[a,b] = a·b/(a,b)`. Este **operatorul virgulă**: evaluează `a`, îl aruncă, și întoarce `b`. Deci expresia devine `a * b / b`, adică `a`. `solutie3f` din `corectareTema2.h:257` afișează deci `v[7]` (56), nu cmmmc(56, 196).

**Ce înveți:** notația matematică nu se traduce direct în cod. Compilatorul a acceptat expresia pentru că e sintactic validă — dar cu alt sens. Aici trebuia un apel real: `cmmdc(a, b)`.

### B2 — comparația înlănțuită de parități nu face ce pare
- `corectareTema2.h:110` — `v[i] % 2 == v[i - 1] % 2 == v[i + 1] % 2`

C++ evaluează stânga→dreapta: întâi `v[i]%2 == v[i-1]%2`, care dă `true`/`false` (adică `1`/`0`), apoi compară acest `0`/`1` cu `v[i+1]%2`. Deci pentru trei numere pare: `(0==0)` → `1`, apoi `1 == 0` → `false`. Exact cazul pe care voiai să-l prinzi pică testul.

Corect: `v[i] % 2 == v[i-1] % 2 && v[i-1] % 2 == v[i+1] % 2`.

### B3 — acces în afara vectorului: `v[i-1]` la `i == 0`
- `corectareTema2.h:109` — `if (v[i + 1] != 0 && v[i - 1] >= 1)`

La prima iterație `i = 0`, deci `v[i-1]` este `v[-1]` — citire înainte de începutul vectorului, comportament nedefinit (poate merge azi, poate crăpa mâine). Condiția de graniță trebuie pusă pe **index**, nu pe valoare: `if (i > 0 && i < d - 1)`.

**Ce înveți:** `v[i+1] != 0` verifică *valoarea* vecinului, nu *existența* lui. Existența unui vecin o decide indexul, valoarea nu-ți spune nimic despre graniță.

### B4 — `cmmdc` prin scăderi intră în buclă infinită pentru 0
- `realizareaUnuiNouVector.h:59-70` — `while (a != b) { ... a = a - b ... }`
- declanșat real în `solutie3a` (`realizareaUnuiNouVector.h:533-544`): vectorul conține `0`, `minim(v,d)` întoarce `0`, iar `cmmdc(0, 45)` nu se termină niciodată (`b = 45 - 0 = 45`, la infinit).

Varianta cu scăderi cere `a > 0 && b > 0`. Ai deja varianta corectă (Euclid cu rest) în `dublete.h:18-26` — aceea se oprește natural când `b == 0`. Ai marcat singur `//incorect` la `realizareaUnuiNouVector.h:503` — diagnosticul complet e acesta.

### B5 — `solutie1a` din dublete: dimensiune falsă + dublet cu element inexistent
- `dublete.h:29-34` — `int v[100] = { 5 };` dar `d = 5`, iar bucla `i < d` folosește `v[i+1]`.

Două probleme suprapuse: (1) vectorul are un singur element cu sens, dar `d = 5` spune că are cinci — pozițiile 1–4 sunt `0` (agregatele se completează cu zero); (2) la `i = 4` se citește `v[5]`, un element care nu face parte din date. Pentru dublete (perechi alăturate), bucla corectă e `i < d - 1`.

### B6 — același off-by-one la dublete în `solutie2b`
- `realizareaUnuiNouVector.h:364-365` — `for (i = 0; i < d; i++)` cu `nrCifre(v[i+1])`.

La `i = d-1` se compară cu `v[d]`, care e în afara datelor (aici `0`, deci `nrCifre(0) = 0` — rezultat fals silențios, nu crash, ceea ce e mai periculos). Corect: `i < d - 1`.

### B7 — sortezi `aux`, dar afișezi `v`
- `sortareaVectorilor.h:108-109` — `sortatPrinBubbleSort(aux, ct); afisare(v, d);`

Toată munca de filtrare + sortare a numerelor prime se face în `aux`, apoi se afișează vectorul original neatins. Corect: `afisare(aux, ct)`.

### B8 — `d = 8` pe un vector cu 6 elemente
- `tema3.h:635-636` — `int v[100] = { 8, 9, 9, 4, 5, 7 }; int d = 8;`

Pozițiile 6 și 7 sunt `0` și intră în sortare ca elemente reale — output-ul conține două zerouri care nu există în date. Dimensiunea declarată trebuie să corespundă exact cu numărul de valori din inițializare.

---

## 🟡 Importante (design / pattern)

### M1 — funcții definite duplicat în headere: bombă de compilare
`prim` apare în 6 fișiere (`exercitiiVectori.h:70`, `tema2.h:8`, `realizareaUnuiNouVector.h:186`, `dublete.h:6`, `corectareTema2.h:9`, `sortareaVectorilor.h:84`), `afisare` în 5, `cmmdc`, `palindrom`, `baza2`, `cifControl`, `par`, `div3`, `solutie1a` etc. la fel.

Azi merge pentru că `vectori.cpp:2` include un singur header. În momentul în care incluzi două (de exemplu `dublete.h` + `tema2.h`), compilatorul dă „function redefinition" — `#pragma once` NU te apără, el previne doar dubla includere a *aceluiași* fișier, nu ciocnirea de nume *între* fișiere.

**Ce înveți:** headerul e pentru *declarații*, definițiile stau în `.cpp`. La nivelul actual, o soluție pragmatică: un singur `utile.h` cu funcțiile comune (`prim`, `afisare`, `cmmdc`, `palindrom`) și headerele de teme doar îl includ.

### M2 — `solutie1` din MunteVale poate primi poziție `-1`
- `MunteVale.h:119-126` — `deterPozitie1Ex1` returnează `-1` dacă nu găsește al 4-lea element (`MunteVale.h:87,99`), iar apoi `sortatDescrescatorInterval(v, -1, d-1)` pornește bucla de la `i = -1` → `v[-1]`.

Cu datele actuale poziția e 4, deci nu se vede — dar nimic nu previne cazul. După apel: `if (poz == -1) return;`.

### M3 — `solutie2d`: 6 valori în inițializare, `d = 5`
- `realizareaUnuiNouVector.h:418-419` — `{ 4321,1234,5414,6531,6425,5246 }` cu `d = 5`.

Aici combinația `i < d` + `v[i+1]` acoperă accidental și al 6-lea element, deci „merge" — dar din motivul greșit. Aceeași disciplină ca la B8: `d` = numărul real de elemente, iar bucla de dublete `i < d - 1`.

### M4 — `baza2` acumulează în `int` deși promite `long long`
- `tema2.h:230-241` — `long long baza2(int n)` dar `int b2` și `int p`.

Pentru `n ≥ 1024` reprezentarea are 11+ cifre zecimale și depășește `int` (max ~2.1 miliarde) *înainte* de return — tipul de retur `long long` nu mai salvează nimic, trunchierea s-a produs deja. Variabilele de lucru trebuie să fie și ele `long long`.

### M5 — testul de impar cu `% 2 == 1` pică pe numere negative
- `exercitiiVectori.h:36` — `v[i] % 2 == 1`.

În C++, `-7 % 2` este `-1`, nu `1`, deci imparele negative nu sunt numărate. Idiomul robust: `v[i] % 2 != 0`.

### M6 — santinele magice în loc de primul element
- `realizareaUnuiNouVector.h:505` (`min = 9999`), `:520` (`max = -9999`), `:763`/`:776` (`±999999`).

Dacă toate elementele sunt peste 9999, minimul „găsit" e 9999 — un număr care nu există în vector. Pattern-ul corect: pornești cu `v[0]` și compari de la `i = 1`. Nu are cum să dea greș, indiferent de valori.

### M7 — `solutie3b` din tema2 e neterminată
- `tema2.h:529` — `int desc = 0;//descompunere factori primi?`

Corpul condiției e gol. Descompunerea există deja implementată în `corectareTema2.h:79` (`afisareDescompunereFactoriPrimi`) — de refolosit, nu de rescris.

---

## 🟢 Cleanups (stil)

- **C1 — duplicare masivă:** bubble sort e rescris de ~8 ori în `tema3.h` (`sortatPrinBubbleSortDescrescator:8`, `sortatCrescatorPartial:182`, `BubbleSortCrescator:356`, `sortatCrescatorSuma:460`, `sortatCrescator:494`, `sortatCrescatorPrimaCifra:550`…). Diferă doar *criteriul de comparație* — semn că o singură funcție + criteriu ar fi de ajuns; până la funcții cu parametru-criteriu, măcar una crescător + una descrescător, refolosite.
- **C2 — `if (cond) return true; return false;`** → `return cond;` (`tema2.h:117-121`, `realizareaUnuiNouVector.h:141-144`, `corectareTema2.h:31-34` și în multe alte locuri).
- **C3 — bool cu 0/1:** `bool vf = 1` (`tema2.h:176`), `vf == 1` (`corectareTema2.h:51`), `while (sortat == false)`. Folosește `true`/`false` și `while (!sortat)`.
- **C4 — nume înșelătoare:** `bubbleSortPatratPerfectCrescator` (`tema3.h:282`) și `sortareaPrinSelectie` (`sortareaVectorilor.h:19`) sunt de fapt exchange sort (swap direct între i și j), nu bubble/selection; `primCifEgalultimCif` (`tema2.h:108`) — capitalizare inconsecventă.
- **C5 — cod mort:** `cmmmc` din `tema2.h:651` nu e apelat nicăieri; `baza2`/`ctCifre1` la finalul `MunteVale.h:132-155`; `int poz = i + 1` nefolosit (`tema2.h:641`, `corectareTema2.h:234`); `int aux` nefolosit în `ogl` (`realizareaUnuiNouVector.h:375`); `;;` dublu (`exercitiiVectori.h:49`).
- **C6 — `patratPerfect` cu comparație float:** `sqrt(n) == (int)sqrt(n)` (`tema3.h:278`, `corectareTema2.h:66`) e fragil pe valori mari. Mai sigur: `int r = (int)round(sqrt(n)); return r * r == n;` — ai deja varianta cu `radacina * radacina == n` în `tema2.h:514-521`, aceea e cea bună.
- **C7 — `min`/`max` ca nume de funcții proprii** (`realizareaUnuiNouVector.h:762,775`) intră în coliziune cu `std::min`/`std::max` sub `using namespace std` — merge acum, dar e o sursă clasică de erori criptice; `minim`/`maxim` erau nume mai sigure.

---

## Before / After — criticele

| # | Before (actual) | After (corect) |
|---|---|---|
| B1 | `return a * b / (a, b);` | `return a * b / cmmdc(a, b);` |
| B2 | `v[i] % 2 == v[i-1] % 2 == v[i+1] % 2` | `v[i] % 2 == v[i-1] % 2 && v[i-1] % 2 == v[i+1] % 2` |
| B3 | `if (v[i + 1] != 0 && v[i - 1] >= 1)` | `if (i > 0 && i < d - 1)` |
| B4 | `while (a != b) { if (a > b) a = a - b; if (b > a) b = b - a; }` | `while (b != 0) { int r = a % b; a = b; b = r; }` |
| B5 | `int v[100] = { 5 }; int d = 5;` + `for (i = 0; i < d; i++)` cu `v[i+1]` | `int v[100] = { 5, 8, 9, 14, 25 }; int d = 5;` + `for (i = 0; i < d - 1; i++)` |
| B6 | `for (int i = 0; i < d; i++)` cu `nrCifre(v[i + 1])` | `for (int i = 0; i < d - 1; i++)` |
| B7 | `sortatPrinBubbleSort(aux, ct); afisare(v, d);` | `sortatPrinBubbleSort(aux, ct); afisare(aux, ct);` |
| B8 | `int v[100] = { 8, 9, 9, 4, 5, 7 }; int d = 8;` | `int d = 6;` |

---

## Q&A — verifică-ți înțelegerea

1. Ce valoare are expresia `(a, b)` în C++ și de ce `a * b / (a, b)` compilează fără eroare, deși calculează greșit?
2. Pentru trei numere pare, ce valoare are `v[i]%2 == v[i-1]%2 == v[i+1]%2` pas cu pas? De ce rezultatul e `false` exact în cazul „toate au aceeași paritate"?
3. De ce cmmdc-ul prin scăderi repetate se blochează când unul dintre numere e 0, iar varianta cu `%` (Euclid) nu? Urmărește ambele pe hârtie cu (45, 0).
4. Dacă în `vectori.cpp` incluzi și `dublete.h` și `tema2.h`, ce eroare dă compilatorul și de ce `#pragma once` nu te ajută aici?
