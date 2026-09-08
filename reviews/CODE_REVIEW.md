# Code Review — victor-vectori

Un singur fișier, runda cea mai nouă sus. Rundele vechi rămân dedesubt.

## Runde anterioare — index

| rundă | subiect | fișier | stare |
|---|---|---|---|
| 8 | fix-uri `tema6.h` + `cautareBinara.h` | *(aici, mai jos)* | 2 ✅ închise · 6 🔴 deschise |
| 7 | `cautareBinara.h` | *(mai jos)* | 🔴 B1 + B2 **deschise** |
| 6 | `tema6.h` + fix-uri tema5/bac | `CODE_REVIEW_TEMA6.md` | ✅ B1, B2 închise · 🔴 B3–B6 deschise · 🟡 M2a deschis |
| 5 | tema5 + bac 2026 | `CODE_REVIEW_TEMA5_BAC.md` | preluate în runda 6 |
| 4 | `secvente.h` | `CODE_REVIEW_SECVENTE.md` | ✅ închis |
| 1–3 | vectori (fix-uri runde 4+5) | *(mai jos, sub runda 7)* | ✅ închise |

---

# Runda 8 — 2026-09-08 — sha `e3502f0`

Commit `e3502f0 finish code review critical`. Fișiere atinse: `tema6.h`, `cautareBinara.h`, `vectori.cpp`.

Codul NU a fost modificat — totul e doar aici. Verificat prin compilare și rulare (`g++ -std=c++17 -Wall -Wextra`, AddressSanitizer + UndefinedBehaviorSanitizer).

> **Verdictul pe scurt.**
>
> **Cele două 🔴 pe care le-ai atacat sunt închise corect, amândouă.** B1 (paritate pe negative) și B2 (zeroul la dublete) din runda 6 — verificate prin rulare, cu date noi *și* cu datele vechi, ca să văd că n-ai stricat nimic. Zero regresii, zero erori de sanitizer.
>
> Și ceva ce nu s-a mai întâmplat: **ți-ai schimbat datele de test ca să lovească exact bug-ul.** `{42,17,8,42,17,91,17}` → `{0,5,0,7}`. `{4,6,3,8,5,12,7,9,2}` → `{-3,5,-7,9}`. În fișa ta scrie de patru runde „datele lui de test camuflează bug-urile". Runda asta e prima în care datele **demonstrează** fix-ul. E cea mai importantă linie din review.
>
> Ce n-a mers:
>
> 1. **Cele două 🔴 din runda 7 sunt neatinse** — `sup = dim` (B1) și sortarea neapelată (B2). Ai umblat prin `cautareBinara.h`, ai completat tabelul, ai șters comentariile goale, ai schimbat datele — și ai trecut pe lângă exact cele două linii care erau constatările.
> 2. **`vectori.cpp` nu mai cheamă `verificare()`.** Acum include `tema6.h` și cheamă `solutie3()`. Căutarea binară nu mai e nici măcar compilată — cele două bug-uri nu se mai pot vedea la rulare, indiferent cât ai rula.
> 3. **B1 e reparat într-un loc din trei.** Aceeași funcție, literă cu literă, mai există la `tema5.h:683` și `tema5.h:724`, cu `%` neprotejat. Vezi M1 — e „repară linia, nu regula", exact tiparul pe care îl închideai.
> 4. **B3, B4, B5, B6 din runda 6** (toate în `tema5.h`) — tot neatinse. Sunt deschise de trei runde.

---

## Starea constatărilor deschise

| # | rundă | unde | starea |
|---|---|---|---|
| B1 | 6 | `tema6.h:329` paritate pe negative | ✅ **ÎNCHIS** — `abs(v[j] % 2)`, corect, verificat pe 3 seturi |
| B2 | 6 | `tema6.h:96` zeroul pierdut | ✅ **ÎNCHIS** — `i = 0` + `const int valoareMax` |
| B3 | 6 | `tema5.h:101` #522, alt algoritm | 🔴 neatins |
| B4 | 6 | `tema5.h:110` #522, garda inversată | 🔴 neatins |
| B5 | 6 | `tema5.h:606` #4148, `ct++` în loc de `ct = 1` | 🔴 neatins |
| B6 | 6 | `tema5.h:755` #297 fără `cout` | 🔴 neatins |
| B1 | 7 | `cautareBinara.h:40` `sup = dim` | 🔴 neatins — OOB reconfirmat pe datele NOI |
| B2 | 7 | `cautareBinara.h:58` sortarea neapelată | 🔴 neatins |
| C4 | 7 | tabelul de urmărire abandonat | ✅ **completat** — dar pe cazul care merge, vezi M3 |
| C5 | 7 | comentarii goale `:9-12` | ✅ șterse |

---

# ✅ Ce ai închis — și de ce contează

## B1 (runda 6) — paritatea pe negative

`tema6.h:329` — `abs(v[j] % 2) != abs(v[j + 1] % 2)`

Corect. Rulat:

```
v={-3,5,-7,9}   (toate impare)      -> secventa = -3        lungime = 1     ✅
v={-3,4,-7,8,-9} (alterneaza)       -> secventa = -3 4 -7 8 -9  lungime = 5 ✅
v={4,6,3,8,5,12,7,9,2} (testul vechi) -> secventa = 6 3 8 5 12 7  lungime = 6 ✅
```

Al treilea e important: **datele vechi dau același răspuns ca înainte.** Ăsta e testul pe care nu-l făceai — de două ori un „fix" ți-a rupt cod care mergea.

`abs(x % 2)` funcționează pentru că `%` în C++ păstrează semnul deîmpărțitului: `-3 % 2` dă `-1`, nu `1`. `abs` îl aduce la `1` și atunci `0` = par / `1` = impar, indiferent de semn.

Varianta care se transferă mai bine — de reținut, nu de schimbat acum — e să compari **răspunsuri de tip da/nu**, nu resturi: `(v[j] % 2 != 0) != (v[j+1] % 2 != 0)`. `v[j] % 2 != 0` e deja „e impar?", iar la întrebări de tip da/nu semnul nu mai are cum să intre în discuție. E aceeași idee ca la M2a (`n % 2 == 1` → `n % 2 != 0`): **întreabă „e impar?", nu „restul e 1?"**.

## B2 (runda 6) — zeroul pierdut la dublete

`tema6.h:87-96`

```
v={0,5,0,7}                  -> cel mai mic numar repetat = 0, apare de 2 ori   ✅
v={42,17,8,42,17,91,17}      -> cel mai mic numar repetat = 17, apare de 3 ori  ✅
v={1,2,3}                    -> Nu exista dublete                                ✅
```

Ai făcut mai mult decât ceream: `const int valoareMax = 100` folosit **și** la declarația lui `f`, **și** la limita buclei. Înainte aveai `101` scris o dată și `100` scris altundeva — două numere care trebuiau să rămână în pas, fără nimic care să le lege. Acum e o singură sursă. Dacă mâine valorile urcă la 1000, schimbi o linie, nu două care se pot desincroniza.

---

# 🔴 Critice (neatinse din runda 7)

## B1 — `sup = dim` — reconfirmat pe datele tale NOI

`vectori/cautareBinara.h:40`

Ai schimbat vectorul de test, dar bug-ul e în funcție, nu în date. Cu dimensiunea reală (`int v[7]`, fiindcă ai 7 elemente):

```
int v[7] = { 5,10,14,16,19,21,26 };
cautareaBinara(v, 7, 30);

==49479==ERROR: AddressSanitizer: stack-buffer-overflow
READ of size 4
    #0 cautareaBinara(int*, int, int) cautareBinara.h:44
    'v' (line 4) <== Memory access at offset 60 overflows this variable
```

Și răspunsul greșit fără crash, cu negative:

```
int a[100] = { -9,-4,-1 };
cautareaBinara(a, 3, 0) = 3        // dim = 3, pozitiile valide sunt 0, 1, 2
```

**DE CE (a doua oară, altfel).** `dim` răspunde la întrebarea *„câte elemente sunt?"*. `sup` răspunde la *„care e ultimul indice?"*. Sunt două întrebări diferite și au răspunsuri diferite: 7 elemente înseamnă ultimul indice 6. Scriind `sup = dim` amesteci un **număr de bucăți** cu o **poziție**.

Bucla se sprijină pe promisiunea *„orice indice între `inf` și `sup` e citibil"*. Promisiunea aia e ruptă din prima linie: `v[7]` nu e al tău. Când cheia e mai mare decât toate elementele, `inf` urcă exact până la `dim` și `mij = (dim + dim) / 2 = dim` — atunci se citește.

E aceeași familie cu B4 din runda 6 (`while (v[i] == v[j] && j < d)`, unde citești `v[j]` *înainte* să verifici că `j` e valid). În ambele cazuri codul întreabă întâi și verifică pe urmă. **FIX:** `int sup = dim - 1;`

## B2 — sortarea tot nu e apelată

`vectori/cautareBinara.h:58-62` (`sortareaPrinSelectie` definită la `:9`, apelată: nicăieri)

Ai schimbat datele din `{2,9,13,16,18,21,33,49}` în `{5,10,14,16,19,21,26}`. Le-ai scris tot **sortate de mână**. Deci demo-ul spune exact ce spunea și înainte: nimic despre sortare.

```
int c[100] = { 26,5,21,10,19,14,16 };   // aceleasi 7 valori, amestecate
cautareaBinara(c, 7, 26) = -1            // 26 e pe pozitia 0, in vector
```

**DE CE (partea pe care n-am spus-o runda trecută).** Sortarea nu e „încă un pas". Ea e **contractul** funcției: `cautareaBinara` are voie să arunce jumătate de vector fără s-o citească *pentru că* i s-a promis ceva despre ordine. Cine cheamă funcția e cel care trebuie să onoreze promisiunea. `verificare()` o cheamă fără s-o onoreze — și scapă doar fiindcă tu, ca om, ai scris datele deja în ordine.

Un test care nu poate să pice nu e test. Vectorul sortat de mână face ca apelul la sortare să fie invizibil: îl pui, îl scoți, ieșirea e aceeași. Ca să însemne ceva, **datele trebuie să fie nesortate**.

**FIX:** `sortareaPrinSelectie(v, d);` înainte de apel, **și** date amestecate în `verificare()`.

---

# 🟡 Importante

## M1 — B1 e reparat într-un loc din trei

`tema5.h:683` și `tema5.h:724` — ambele conțin, literă cu literă:

```cpp
while (j + 1 < d && (v[j] % 2 != v[j + 1] % 2)) {
```

Sunt **aceeași funcție**, copiată de trei ori: `ceaMaiLungaSecventaParitatiDiferite` (#283, `tema5.h:677`), `secventaParitatiDiferite` (#4457, `tema5.h:717`) și cea din `tema6.h:321`. Ai reparat-o pe a treia.

Corectitudinea: cerințele de la #283 și #4457 zic **„numere naturale"**, deci pe datele valide `%` nu se rupe acolo. Nu e bug pe cerință — de-aia e 🟡, nu 🔴. Dar:

Ăsta e tiparul care ți se repetă de patru runde: **repari apariția semnalată, nu regula.** Runda trecută am scris că tiparul „s-a redus, dar n-a dispărut". Aici e din nou, în forma lui cea mai curată: aceeași linie, în trei fișiere, una singură atinsă.

Contramăsura e mecanică, 20 de secunde: după fiecare fix, **`Ctrl+Shift+F` pe fragmentul pe care tocmai l-ai schimbat** (aici: `% 2 !=`). Dacă apare în alte locuri, decizi conștient dacă le atingi sau nu — dar decizi, nu ratezi.

Aceeași verificare mai scoate la iveală (aceeași familie, prioritate mică): `corectareTema2.h:112` și `tema2.h:552` compară `v[i] % 2 == v[i-1] % 2`, iar M2a e tot deschis — `n % 2 == 1` în `MunteVale.h:145`, `realizareaUnuiNouVector.h:644`, `tema5.h:506`.

## M2 — `vectori.cpp` a lăsat căutarea binară în urmă

`vectori/vectori.cpp:2,6` — acum `#include "tema6.h"` + `solutie3()`.

`cautareBinara.h` nu mai intră deloc în build. Cele două 🔴 de mai sus nu se mai pot manifesta la rulare — nu pentru că le-ai rezolvat, ci pentru că fișierul nu mai e compilat.

E o versiune nouă a tiparului tău: **nu doar scrii funcții pe care nu le conectezi — muți `main()` mai departe și lași bug-ul în urmă, în afara razei de acțiune.** Cât `main()` cheamă un singur `solutieXXX()`, tot ce nu e chemat e cod pe care nu-l mai verifică nimeni.

Sugestia (o singură linie de disciplină, nu refactor): ține în `main()` un apel la **fiecare** `verificare()` / `solutieXXX()` din fișierul la care lucrezi, comentează-le pe cele vechi doar când fișierul e închis, și rulează o dată tot blocul înainte de commit.

## M3 — tabelul de urmărire, completat pe cazul care merge

`cautareBinara.h:29-32`

Ai completat tabelul de la C4 (runda 7) — bine, și e vizibil corect: `inf` urcă la 5, `mij` ajunge la 5, `21 == 21`, gata în 3 pași.

Dar l-ai completat pe **`key = 21`, cheia care se găsește**. Întrebarea 1 din Q&A-ul rundei 7 cerea explicit `key = 100` — cheia mai mare decât toate. Pe aceea, tabelul ar fi arătat `inf` urcând la 8 și `mij` ajungând la 8, adică B1, desenat de mâna ta, fără compilator.

Regula generală, și e utilă mult dincolo de aici: **un tabel de urmărire pe cazul care merge nu-ți spune nimic.** Instrumentul ăsta e bun exact pe cazurile-limită — cheia lipsă, cheia mai mare decât toate, vectorul gol, un singur element.

## M4 — `f[v[i]]++` nu are gardă

`tema6.h:91`

`const int valoareMax = 100` **documentează** presupunerea, dar n-o **impune**. Rulat:

```
v={250, 5, 250}  ->  "Nu exista dublete"       // 250 apare de doua ori
```

`f[250]` scrie în afara vectorului `f` (101 elemente); numărătoarea se pierde undeva în memorie și răspunsul iese fals, fără nicio eroare. Sanitizer-ul nu l-a prins aici — motiv în plus să nu te bazezi pe el.

O linie: `if (v[i] >= 0 && v[i] <= valoareMax) f[v[i]]++;` — sau, dacă cerința chiar garantează `0..100`, măcar știi conștient că te sprijini pe garanția aia.

---

# 🟢 Cleanups

**C1 — `#include <cmath>` în `cautareBinara.h:3`** — încă nefolosit acolo (`abs` îl folosești în `tema6.h`, care are propriul `#include`).

**C2 — comentariul contrazice codul.** `cautareBinara.h:36` zice `//int d = 8;`, iar `:60` are `int d = 7;`. Vectorul are 7 valori, deci codul are dreptate. Un comentariu care minte e mai rău decât niciun comentariu — șterge-l sau pune-l în pas.

**C3 — `int v[100]` cu `d = 7`** (`:59`). Al doilea review la rând: dimensionează vectorul de test la dimensiunea reală. E singurul motiv pentru care B1 nu-ți crapă în față.

---

# Before / After (în document, NU aplicat în cod)

### B1 (runda 7) — `cautareBinara.h:40`

| acum | corect |
|---|---|
| <pre>int inf = 0;<br>int sup = dim;</pre> | <pre>int inf = 0;<br>int sup = dim - 1;</pre> |

### B2 (runda 7) — `cautareBinara.h:58-62`

| acum | corect |
|---|---|
| <pre>void verificare() {<br>  int v[100] = { 5,10,14,16,19,21,26 };<br>  int d = 7;<br>  int key = 20;<br>  int poz = cautareaBinara(v, d, key);</pre> | <pre>void verificare() {<br>  int v[7] = { 26,5,21,10,19,14,16 };<br>  int d = 7;<br>  int key = 26;<br><br>  sortareaPrinSelectie(v, d);<br>  int poz = cautareaBinara(v, d, key);</pre> |

Trei schimbări, nu una: apelul la sortare, **datele amestecate** (altfel apelul nu se vede) și `int v[7]` în loc de `int v[100]` (altfel B1 rămâne ascuns).

### M1 — `tema5.h:683` și `tema5.h:724`

| acum | ca în `tema6.h` |
|---|---|
| <pre>while (j + 1 &lt; d &&<br>  (v[j] % 2 != v[j+1] % 2)) {</pre> | <pre>while (j + 1 &lt; d &&<br>  (abs(v[j] % 2) != abs(v[j+1] % 2))) {</pre> |

---

# Q&A — verifică-ți înțelegerea

**1.** Ai reparat paritatea în `tema6.h` și ai lăsat neatinse `tema5.h:683` și `tema5.h:724`, care conțin **exact aceeași linie**. Fără să deschizi fișierele: ce comandă din Visual Studio ți-ar fi arătat, în 10 secunde, că mai există două copii? Și de ce nu e suficient să-ți aduci aminte că „am mai scris funcția asta undeva"?

**2.** În `verificare()` ai schimbat datele din `{2,9,13,16,18,21,33,49}` în `{5,10,14,16,19,21,26}`. Amândouă sunt sortate. Dacă ai șterge complet corpul lui `sortareaPrinSelectie` (funcție goală, care nu face nimic), s-ar schimba **vreun** rezultat afișat de `main()`? Răspunde cu da/nu și explică — apoi spune ce fel de date de test ar face răspunsul să fie „da".

**3.** La B2 din runda 6 ai făcut fix ce trebuia: ai schimbat `i = 1` în `i = 0` **și** ai schimbat datele în `{0,5,0,7}` ca să lovești chiar cazul reparat. Aplică același raționament la B1 din runda 7: după ce pui `sup = dim - 1`, ce **cheie** și ce **dimensiune de vector** trebuie să alegi în `verificare()` ca să demonstrezi că modificarea chiar a rezolvat ceva? (Indiciu: pe `key = 20` din codul actual, și varianta greșită, și cea corectă afișează același lucru.)

---

# Ce a mers

- **2 din 2 constatări atacate, 2 închise corect** — și amândouă verificate de mine prin rulare, inclusiv pe datele vechi, ca să confirm că n-ai stricat nimic. Prima rundă fără nicio regresie.
- **Ți-ai ales datele de test ca să lovească bug-ul.** `{0,5,0,7}` pentru zeroul pierdut, `{-3,5,-7,9}` pentru negative. Asta e schimbarea reală din runda asta. „Datele lui de test camuflează bug-uri" era observația care ți se repeta de patru runde — aici ai făcut opusul, de două ori, conștient.
- **`const int valoareMax`** — ai mers dincolo de fix și ai legat cele două numere care trebuiau să rămână în pas. Nu ți-o ceruse nimeni.
- **Ai completat tabelul de urmărire** (C4 din runda 7) — instrumentul e bun, îl folosești; îi mai lipsește doar cazul-limită. Vezi M3.
- **Compilare curată cu `-Wall -Wextra`**, zero warning-uri, zero erori de sanitizer pe tot `tema6.h`.

**Următorul pas, în ordinea asta:**
1. `cautareBinara.h:40` → `dim - 1` (5 secunde)
2. `verificare()` → apel la sortare + date amestecate + `int v[7]` (1 minut)
3. `Ctrl+Shift+F` pe `% 2 !=` → repară `tema5.h:683` și `:724` (30 de secunde)
4. **Apoi lista veche din `tema5.h`, deschisă de trei runde:** B4 (garda), B5 (`ct = 1`), B6 (`cout` la #297), B3 (#522, singurul care cere gândit).

Primele trei sunt sub două minute puse cap la cap.

---

# Runda 7 — 2026-09-08 — sha `589651f`

Fișier nou: `vectori/cautareBinara.h` (68 linii) + `vectori/vectori.cpp` rescris. Commit-urile `3c1d221 sortare binara` → `589651f`.

Codul NU a fost modificat — totul e doar aici. Toate constatările sunt **verificate prin compilare și rulare** (`g++ -std=c++17 -Wall -Wextra`, plus AddressSanitizer și UndefinedBehaviorSanitizer), nu prin citire.

> **Verdictul pe scurt.**
>
> Poarta de compilare: ✅ **trece**, fără niciun warning cu `-Wall -Wextra`. Sortarea pe care ai scris-o e **corectă**, inclusiv pe negative și dublete (verificat: `{5,-3,5,0,-3,12,1}` → `-3 -3 0 1 5 5 12`). Căutarea binară dă răspunsul corect pe datele din `verificare()`.
>
> Dar sunt două probleme, și amândouă sunt **aceeași greșeală de metodă**, nu de C++:
>
> 1. **`sup = dim` în loc de `dim - 1`** (B1). Pe datele tale nu se vede. Pe un vector dimensionat exact, AddressSanitizer oprește programul cu `stack-buffer-overflow` la `cautareBinara.h:42`. Pe un vector cu negative, funcția îți întoarce **poziția 3 într-un vector de 3 elemente**.
> 2. **Ai scris sortarea și n-ai chemat-o niciodată** (B2). `verificare()` caută direct într-un vector care era **deja sortat când l-ai scris tu de mână**. Demo-ul „merge" fără să demonstreze nimic. Pe un vector nesortat, căutarea răspunde `-1` pentru un element care **există în vector**.
>
> Și partea grea: **niciunul dintre cele 6 🔴 din runda 6 nu e închis.** B1, B2, B3, B4, B5, B6 — toate neatinse, verificate în cod acum. Cinci dintre ele erau sub un minut fiecare. Ai deschis un subiect nou peste unul rămas deschis.

---

## Starea rundei 6 (verificată în cod pe `589651f`)

| # | unde | starea |
|---|---|---|
| B1 | `tema6.h:328` — paritate pe negative | 🔴 **NEATINS** — încă `v[j] % 2 != v[j+1] % 2` |
| B2 | `tema6.h:95` — zeroul pierdut la dublete | 🔴 **NEATINS** — încă `for (int i = 1; ...)` |
| B3 | `tema5.h:101` — #522, alt algoritm | 🔴 **NEATINS** |
| B4 | `tema5.h:110` — #522, garda inversată (buffer overflow) | 🔴 **NEATINS** — încă `while (v[i] == v[j] && j < d)` |
| B5 | `tema5.h:606` — #4148, `ct++` în loc de `ct = 1` | 🔴 **NEATINS** |
| B6 | `tema5.h:755` — #297 nu afișează nimic | 🔴 **NEATINS** — funcția tot n-are `cout` |
| M2a | `% 2 == 1` pe negative | 🟡 **NEATINS** — încă în `MunteVale.h:145`, `realizareaUnuiNouVector.h:644`, `tema5.h:506` |

Singura modificare din runda trecută: `tema6.h:346` — ai spart afișarea pe două rânduri (`endl` + `lungime = `). Cosmetic, corect, dar nu era pe listă.

---

# 🔴 Critice

## B1 — `sup = dim` citește în afara vectorului

`vectori/cautareBinara.h:38`

**CUM E ACUM.** Pe un vector dimensionat exact, programul **moare**:

```
int v[8] = { 2,9,13,16,18,21,33,49 };
cautareaBinara(v, 8, 100);

==43079==ERROR: AddressSanitizer: stack-buffer-overflow
READ of size 4 at 0x00016b80e9e0
    #0 cautareaBinara(int*, int, int) cautareBinara.h:42
    'v' (line 4) <== Memory access at offset 64 overflows this variable
```

Și pe un vector cu negative îți întoarce o poziție care nu există:

```
int a[100] = { -5,-3,-2 };
cautareaBinara(a, 3, 0)  ->  3        // dim = 3, deci pozițiile valide sunt 0,1,2
```

**DE CE.** `inf` și `sup` nu sunt „început și sfârșit" în sensul din vorbire — sunt **indici**, iar `dim` e un **număr de elemente**. Într-un vector cu 8 elemente indicii merg de la `0` la `7`. Punând `sup = 8` îi spui buclei că `v[8]` e un element de căutat, deși el e primul din afara vectorului.

Bucla poate ajunge chiar acolo: dacă cheia e mai mare decât toate elementele, `inf` urcă până la `dim`, iar `mij = (dim + dim) / 2 = dim`. La linia `:42` citești `v[dim]`.

Atunci de ce ție îți merge? Pentru că ai scris `int v[100]` cu doar 8 valori (`:57`). Restul de 92 de poziții sunt **zerouri puse automat de compilator** — memorie validă, care îți aparține. Citirea nu crapă, doar minte. Cu `int v[8]` — dimensiunea reală — sanitizer-ul o vede imediat. **Vectorul supradimensionat nu ți-a rezolvat bug-ul, ți l-a ascuns.** Vezi și C2.

**Cazul cu negative arată de ce contează chiar și cu `v[100]`:** cheia `0` e mai mare decât `-5, -3, -2`, `inf` urcă la 3, `v[3]` e unul dintre zerourile din coadă, `0 == 0` → funcția raportează „găsit pe poziția 3". Nu e o citire ilegală, e un **răspuns greșit**.

**Bonus, aceeași cauză:** cu `sup = dim`, pe un vector gol (`dim = 0`) ai `inf = 0 <= sup = 0` → intri în buclă și citești `v[0]` dintr-un vector care n-are niciun element. Cu `sup = dim - 1 = -1`, `0 <= -1` e fals și bucla nu pornește deloc. Aceeași literă rezolvă și cazul-limită, gratis.

**FIX:** `int sup = dim - 1;`

---

## B2 — Ai scris sortarea și n-ai chemat-o niciodată

`vectori/cautareBinara.h:56-67` (`sortareaPrinSelectie` definită la `:14`, apelată: nicăieri)

**CUM E ACUM.** Ai scris de două ori în fișier, cu mâna ta, că vectorul trebuie sortat:

```
:6   //Obs cautarea binara se face tot timpul pe un vector sortat
:28  //Obs ve sa fie sortat crescator primna oara
```

Și ai scris funcția care face exact asta. Dar `verificare()` sare peste ea:

```
int v[100] = { 2,9,13,16,18,21,33,49 };   // deja sortat, l-ai scris tu așa
int poz = cautareaBinara(v, d, key);       // sortarea nu apare aici
```

Programul afișează `elementul 21 a fost gasit pe pozitia 5`. Corect. Dar ar fi afișat același lucru și dacă `sortareaPrinSelectie` ar fi fost goală pe dinăuntru. Rulare cu **același** vector, doar amestecat:

```
int c[100] = { 49,2,33,9,21,13,16,18 };
fara sortare:  cautareaBinara(c, 8, 49) = -1      // 49 e pe pozitia 0, in vector!
cu sortare:    2 9 13 16 18 21 33 49  ->  49 gasit pe pozitia 7
```

**DE CE.** Căutarea binară nu „caută" — ea **elimină**. Din `v[mij] > key` trage concluzia *„atunci key nu poate fi în dreapta"* și aruncă jumătate de vector fără să se uite la ea. Concluzia aia e valabilă **numai** dacă vectorul e crescător; e singura informație pe care se sprijină algoritmul. Pe un vector nesortat, `v[mij] > key` nu-ți spune absolut nimic despre unde e `key`, iar tăietura aruncă exact jumătatea în care se afla — de-aia primești `-1` pentru un element care există.

Sortarea nu e „un pas în plus, dacă vrei". Ea e **precondiția** fără de care funcția n-are voie să fie chemată. Un demo care o omite nu testează căutarea binară, testează dacă ai avut noroc la scrierea datelor.

Și e exact tiparul semnalat în runda trecută, în altă formă: **funcție scrisă, neconectată, output plauzibil.** Atunci era #297 (calcula corect, nu afișa nimic). Acum e sortarea (corectă, neapelată). În ambele cazuri programul rulează fără eroare și tu n-ai cum să vezi că lipsește ceva — pentru că *lipsa* nu produce mesaj.

**FIX:** `sortareaPrinSelectie(v, d);` înainte de `cautareaBinara(v, d, key)`, și **verifică pe un vector nesortat** — altfel apelul nu demonstrează nimic nici el.

---

# 🟡 Importante

**M1 — `sortareaPrinSelectie` nu e sortare prin selecție.** `cautareBinara.h:14-26`. Ce ai scris e **sortare prin interschimbare**: compari `v[i]` cu fiecare `v[j]` de după el și schimbi pe loc, de fiecare dată când găsești ceva mai mic. Rezultatul e corect (verificat pe negative și dublete), dar sortarea prin selecție face altceva: parcurge restul vectorului doar ca să **rețină indicele minimului** (`imin`), și face **o singură** interschimbare la sfârșitul pasului. Aceleași comparații, dar `n-1` schimbări în loc de până la ~`n²/4`. Merită scrisă și varianta cu `imin` alături — e diferența dintre „am sortat" și „știu ce algoritm am sortat cu".

**M2 — trei `if` unde cazurile se exclud.** `cautareBinara.h:42, 45, 48`. `v[mij]` e ori egal, ori mai mare, ori mai mic — a treia oară nu mai are ce afla. După `sup = mij - 1`, testul `if (v[mij] < key)` se evaluează degeaba (nu strică, `v[mij]` nu s-a schimbat). Scris cu `else if` / `else`, codul spune *„sunt exact trei cazuri"* — ceea ce e chiar ideea algoritmului.

**M3 — cu dublete, poziția returnată e arbitrară.** `cautareBinara.h:36`. Pe `{2,5,5,5,9}` cu `key = 5` primești poziția la care s-a nimerit `mij`, nu prima apariție. Nu e greșit față de cerință, dar e bine să știi că „prima apariție" cere o variantă separată (continui spre stânga în loc să te oprești la primul `==`).

**M4 — 6 🔴 din runda 6 sunt încă deschise.** Vezi tabelul de mai sus. Cinci sunt sub un minut fiecare, cu before/after gata scris în `reviews/CODE_REVIEW_TEMA6.md`.

---

# 🟢 Cleanups

**C1 — `#include <cmath>` (`:3`) nu e folosit.** Nicio funcție matematică în fișier.

**C2 — `int v[100]` cu `d = 8`** (`:57`). E cauza pentru care B1 nu s-a văzut: cele 92 de zerouri din coadă absorb citirea din afara vectorului. Declară `int v[8]` când ai 8 valori — vrei ca greșeala să crape, nu să tacă.

**C3 — `(inf + sup) / 2`** (`:41`). La dimensiunile tale e perfect în regulă. De știut pentru mai târziu: pe vectori foarte mari `inf + sup` poate depăși `int`, și varianta care nu depășește niciodată e `inf + (sup - inf) / 2`. Nu schimba acum, doar reține.

**C4 — tabelul de urmărire e început și abandonat.** `:34-35` — ai antetul cu 7 coloane și **un singur rând** completat (`0<8 da   4   18==21 false ...`), apoi liniuțe. În runda trecută ți-am lăudat exact instrumentul ăsta (`tema5.h:95-100`). Dacă îl duceai până la capăt aici, pe `key = 100`, vedeai singur cum `inf` urcă la 8 și `mij` ajunge la 8 — adică B1, fără compilator, fără sanitizer. Și comentariile goale de la `:9-12` pot dispărea.

**C5 — typo-uri în comentarii:** `:28` „ve sa fie sortat crescator primna oara" → „vectorul să fie sortat crescător prima oară". Comentariul e util, merită să fie și citibil.

---

# Before / After (în document, NU aplicat în cod)

### B1 — `cautareBinara.h:38`

| acum | corect |
|---|---|
| <pre>int inf = 0;<br>int sup = dim;</pre> | <pre>int inf = 0;<br>int sup = dim - 1;</pre> |

### B2 — `cautareBinara.h:56-61`

| acum | corect |
|---|---|
| <pre>void verificare() {<br>  int v[8] = { 2,9,13,16,18,21,33,49 };<br>  int d = 8;<br>  int key = 21;<br><br>  int poz = cautareaBinara(v, d, key);</pre> | <pre>void verificare() {<br>  int v[8] = { 49,2,33,9,21,13,16,18 };<br>  int d = 8;<br>  int key = 21;<br><br>  sortareaPrinSelectie(v, d);<br>  int poz = cautareaBinara(v, d, key);</pre> |

Observă că am schimbat **și datele**, nu doar apelul. Cu vectorul deja sortat, apelul la sortare rămâne o linie despre care nu poți spune dacă face ceva.

### M1 — `cautareBinara.h:14-26` (sortare prin selecție, cea adevărată)

| acum (interschimbare) | selecție |
|---|---|
| <pre>for (int i = 0; i &lt; d; i++)<br>  for (int j = i+1; j &lt; d; j++)<br>    if (v[i] &gt; v[j]) {<br>      int aux = v[i];<br>      v[i] = v[j];<br>      v[j] = aux;<br>    }</pre> | <pre>for (int i = 0; i &lt; d - 1; i++) {<br>  int imin = i;<br>  for (int j = i+1; j &lt; d; j++)<br>    if (v[j] &lt; v[imin])<br>      imin = j;<br>  if (imin != i) {<br>    int aux = v[i];<br>    v[i] = v[imin];<br>    v[imin] = aux;<br>  }<br>}</pre> |

---

# Q&A — verifică-ți înțelegerea

**1.** Pe `int v[100] = { 2,9,13,16,18,21,33,49 }` cu `d = 8`, caută `key = 100` și urmărește **pe hârtie**, în tabelul pe care l-ai început la `:34`, valorile `inf`, `sup`, `mij` până la ieșirea din buclă. La ce valoare ajunge `mij` la ultimul pas, și ce conține `v[mij]` acolo? Apoi: de ce **același** cod, cu `int v[8]` în loc de `int v[100]`, oprește programul cu eroare?

**2.** Ai schimbat `sup = dim` în `sup = dim - 1`. Explică, fără să rulezi, de ce modificarea asta rezolvă și cazul `dim = 0` (vector gol) — ce valoare are `sup`, și de ce nu se mai intră deloc în `while`.

**3.** Pe `{49,2,33,9,21,13,16,18}` (nesortat), `cautareaBinara(c, 8, 49)` întoarce `-1`, deși `49` e chiar pe poziția 0. Urmărește cei 3-4 pași și spune **exact la ce pas** algoritmul aruncă jumătatea în care se afla `49`. Legat de asta: care e singura afirmație pe care se sprijină linia `if (v[mij] > key) sup = mij - 1;`, și de ce ea devine falsă pe un vector nesortat?

---

# Ce a mers

Verificate prin rulare, nu umplutură:

- **Compilare curată cu `-Wall -Wextra`: zero warning-uri.** Al doilea fișier din proiect care reușește asta, după `tema6.h`.
- **Sortarea e corectă**, inclusiv pe cazurile care de obicei rup implementările de începător: negative și dublete simultan. `{5,-3,5,0,-3,12,1}` → `-3 -3 0 1 5 5 12`.
- **Structura căutării binare e corectă.** `mij` recalculat în buclă, `sup = mij - 1` / `inf = mij + 1` (nu `= mij`, greșeala clasică ce dă buclă infinită), `return -1` pe eșec. Scheletul e bun — bug-ul e într-o singură literă, nu în algoritm.
- **Ai scris invariantul înainte de cod** (`:6`). Ai știut de la început de ce depinde algoritmul. B2 nu e o problemă de înțelegere, e una de a nu fi dus firul până la capăt în `verificare()`.

**Următorul pas, în ordinea asta:** B1 (`- 1`, 5 secunde) → B2 (o linie + amestecă datele, 30 de secunde) → apoi **înapoi la runda 6**: B4, B5, B2, B1, B6, și la final B3. Nu deschide subiect nou până nu golești lista.

---
# Code Review — victor-vectori · runda 6: fix-urile din rundele 4+5

Review pe `232335c` → `98e9ad3` (commit-urile „code review 1st…4th push"). Codul NU a fost modificat — totul e doar aici. Toate constatările de mai jos au fost **verificate prin compilare și rulare**, cu AddressSanitizer pentru accesele în afara vectorului.

> **Verdictul pe scurt.** Ai atacat 8 puncte din review-ul anterior și ai rezolvat corect 4. Problema e ce s-a întâmplat la celelalte: **două „fix-uri" au stricat cod care mergea**. Cel de la `frecventaCif` rupe *toată* problema 2 (a–g, 7 subpuncte care înainte dădeau răspunsuri corecte). Cel de la `patratPerfect` transformă o funcție corectă într-una care spune că 11, 14, 17, 21, 22 și 27 sunt pătrate perfecte.
>
> Asta nu e o problemă de C++, ci de metodă: **ai pushat 4 commit-uri fără să rulezi nimic după modificare.** Cu problema 2 ruptă, `vectori.cpp` cheamă `solutie2g()` și tipărește `0` în loc de `123445` — un singur F5 ți-ar fi arătat-o în două secunde.

---

## 🔴 Critice

### B1 — `frecventaCif`: condiția inversată golește toată problema 2

- `frecventa.h:219` — `while (n <= 0) {`

Aveai `while (n != 0)`. Am semnalat la C5 că nu tratează cazul `n == 0`. Fix-ul aplicat schimbă condiția în `n <= 0`, ceea ce înseamnă **exact pe dos**: bucla intră doar pentru numere negative sau zero. Pentru orice `n` pozitiv — adică pentru toate apelurile din cod — corpul buclei **nu se execută niciodată**, iar `f[]` rămâne plin de zerouri.

`frecventaCif` e chemată din 2a, 2b, 2c, 2d, 2e, 2f și 2g. Rulare reală, codul de pe `98e9ad3`:

```
=== 2a ===  0 apare de 0 ori ... 9 apare de 0 ori     (asteptat: 2x2 3x1 4x1 5x1 7x1 8x1)
=== 2b ===  (nimic afisat)                            (asteptat: 3 apare de 4 ori, cu 1 peste k)
=== 2d ===  0                                          (asteptat: 75432211)
=== 2e ===  0                                          (asteptat: 5)
=== 2f ===  2 3 5 7                                    (asteptat: 5 7)
=== 2g ===  0                                          (asteptat: 123445)
```

Două lucruri de remarcat în tabelul ăsta:

**2c a rămas corect — din întâmplare.** Cerința e „cifrele impare care *nu* apar în `n = 24680`". Cu `f[]` gol, *nicio* cifră nu apare, deci se tipăresc toate impare: `13579`. Care e și răspunsul adevărat, fiindcă 24680 chiar n-are cifre impare. Dacă te uitai doar la 2c, ziceai că merge.

**2f e cazul periculos.** Tipărește `2 3 5 7` — patru numere aliniate frumos, arată a răspuns. Dar `n = 2341` chiar conține 2 și 3, deci răspunsul corect e `5 7`. Un bug care afișează *nimic* se vede; unul care afișează *ceva plauzibil* trece.

Și mai e o consecință: cu `n <= 0`, un apel `frecventaCif(0, f)` intră în buclă, face `n = 0 / 10 = 0`, iar condiția rămâne adevărată **la infinit**. Verificat — programul a trebuit omorât după 3 secunde (`EXIT=137`, adică SIGKILL):

```
apel cu n=0...
EXIT=137
```

**Ce înveți.** `!=` și `<=` nu sunt „variații pe aceeași temă", sunt întrebări diferite: `n != 0` întreabă *„mai am cifre de consumat?"*, `n <= 0` întreabă *„e numărul negativ sau nul?"*. Problema pe care ți-o semnalasem era alta: bucla `while` verifică **înainte** de prima execuție, deci pentru `n = 0` nu intră deloc și cifra 0 nu e numărată. Soluția pentru „vreau corpul măcar o dată" e `do…while`, care verifică **după**:

```cpp
void frecventaCif(int n, int f[]) {
    do {
        int cif = n % 10;
        f[cif]++;
        n = n / 10;
    } while (n != 0);
}
```

Pentru `n = 0`: intră o dată, `f[0]++`, `n` rămâne 0, condiția e falsă, iese. Pentru `n = 2534782`: identic cu ce aveai. Un singur cuvânt mutat rezolvă exact ce trebuia rezolvat, fără să atingă restul.

---

### B2 — `patratPerfect`: fix-ul spune că 11 e pătrat perfect

- `exercitiiRecapitulative.h:379` — `return sqrt(n) * sqrt(n) == n;`

Aveai `sqrt(n) == (int)sqrt(n)`. Ți-am scris „varianta robustă e `rad*rad == n`" — dar `rad` din propoziția aia era un **`int`**, nu `sqrt(n)`. Ridicând la pătrat un `double`, ai anulat exact partea care făcea verificarea sigură.

`sqrt(11)` este `3.3166247903554` — un `double`, deci o aproximare pe 53 de biți. Când înmulțești aproximarea cu ea însăși, rezultatul se rotunjește **înapoi la 11.0 exact**. Comparația e adevărată. Testat prin forță brută:

```
n=11 victor=1 corect=0
n=14 victor=1 corect=0
n=17 victor=1 corect=0
n=21 victor=1 corect=0
n=22 victor=1 corect=0
n=27 victor=1 corect=0
```

Peste 150 de milioane de valori testate divergează. Practic, funcția răspunde „da" pentru majoritatea numerelor.

De ce n-ai văzut-o: `solutie13:406` are `v = {12, 16, 18}`, iar 12 și 18 se nimeresc să fie printre numerele la care rotunjirea *nu* păcălește comparația. Ieșirea e corectă:

```
12=2^2*3^1
18=2^1*3^2
```

Datele de test au camuflat bug-ul. Pune `11` în vector și `solutie13` refuză să-l descompună.

Aceeași funcție e copiată în `tema2.h:514` și `tema4.h:166` — acolo a rămas varianta veche, deci acum ai **două comportamente diferite pentru același nume**, în același proiect.

**Ce înveți.** Regula, scurt: **nu compara `double`-uri cu `==`.** Un `double` e o aproximare; egalitatea între aproximări e o loterie. Ieși din virgulă mobilă cât mai devreme și pune întrebarea în numere întregi, unde `==` chiar înseamnă egal:

```cpp
bool patratPerfect(int n) {
    if (n < 0) return false;
    int rad = (int)sqrt((double)n);
    while (rad * rad > n) rad--;          // corectie de rotunjire in jos
    while ((rad + 1) * (rad + 1) <= n) rad++;   // ... si in sus
    return rad * rad == n;
}
```

`sqrt` e folosit doar ca *punct de plecare aproximativ*; cele două `while` îl aduc pe `rad` la valoarea exactă, iar decizia finală e o comparație între `int`-uri. Varianta ta veche, `sqrt(n) == (int)sqrt(n)`, era de fapt corectă pe intervalul din problemele tale — fix-ul a înrăutățit situația.

---

### B3 — `solutie6`: garda e pusă după accesul pe care trebuia să-l apere

- `exercitiiRecapitulative.h:153` — `while (v[ct] == v[ct + 1] && ct < d-1) {`

Ai adăugat garda cerută, dar în ordinea greșită. C++ evaluează `&&` **de la stânga la dreapta, cu oprire la primul fals**. Aici stânga e `v[ct] == v[ct + 1]` — adică citirea lui `v[ct+1]` se întâmplă **înainte** ca `ct < d-1` să fie măcar privit. Garda oprește *iterația următoare*, nu accesul curent.

Verificat cu AddressSanitizer, pe vectorul plin (`d = 100`, toate elementele egale):

```
ERROR: AddressSanitizer: stack-buffer-overflow
READ of size 4 at 0x00016ef1a9d0
  [32, 432) 'v' <== Memory access at offset 432 overflows this variable
```

Offset 432 = `v[100]`, adică prima căsuță de după vector. Pe datele tale (`d = 8` într-un vector de 100) citirea cade în zona neinițializată dar încă alocată, deci nu se vede nimic — de asta rulează „bine".

**Ce înveți.** Într-o condiție compusă, ordinea nu e cosmetică — e ordinea în care se execută lucrurile. Regula: **întâi întrebi dacă ai voie, apoi te uiți.**

```cpp
while (ct < d - 1 && v[ct] == v[ct + 1]) {
```

Acum, când `ct` ajunge la `d-1`, prima condiție e falsă, `&&` se oprește acolo și `v[ct+1]` nu mai e citit deloc. Se numește *short-circuit evaluation* și e singurul motiv pentru care forma asta e sigură. Ține minte tiparul — îl vei folosi la fel cu `if (i < n && v[i] == x)` și cu `if (p != nullptr && p->ceva)`.

---

### B4 — restanță: `pozElemMinVec` are încă „infinitul" 100

- `frecventa.h:43` — `int minim = 100;`
- Apelat la `:80`, rezultatul folosit ca index la `:83`

Nu a fost atins. Ba mai mult: acum îl chemi cu `d = 101` (corect, M2 rezolvat), deci funcția vede tot vectorul de frecvențe — dar tot nu poate vedea o frecvență ≥ 100.

Verificat pe un vector de 300 de elemente (enunțul spune „maxim 2000"), 150 de „5" și 150 de „7":

```
maxi=5 min=-1
nr cel mai frecvent 5 si apare de 150 ori
ERROR: AddressSanitizer: stack-buffer-overflow
  [8288, 8692) 'f' <== Memory access at offset 8284 underflows this variable
```

Prima linie iese corect. A doua încearcă `f[-1]` — citirea celor 4 octeți dinaintea vectorului. Fix-ul din runda 5 rămâne valabil: `#include <climits>` și `int minim = INT_MAX;`, sau santinelă pe `poz == -1` înainte de a folosi rezultatul ca index.

---

## 🟡 Importante

### M1 — `frecventaNumarVector`: vectorul numără până la 100, afișarea se oprește la 99

- `frecventa.h:25` — `int f[101]{};` ✅ (B2 din runda 5, rezolvat)
- `frecventa.h:31` — `for (int i = 10; i <= 99; i++)`

Ai rezolvat două treimi din problemă: `f[101]` elimină scrierea în afara vectorului (confirmat — ASan tace acum), iar `i <= 99` afișează în sfârșit numărul 99. A rămas capătul: valoarea 100 e numărată în `f[100]`, dar bucla nu ajunge la ea.

```
v = {99, 99, 42, 100, 13}  →  in vector apare 13 de 1 ori
                              in vector apare 42 de 1 ori
                              in vector apare 99 de 2 ori
                              ^ lipseste 100
```

`for (int i = 10; i <= 100; i++)`. Aceeași regulă ca înainte: tot ce parcurge un vector de frecvență de `N+1` căsuțe trebuie să meargă până la `N` **inclusiv**.

### M2 — la 1a mesajul zice „cifra", dar afișezi un număr

- `frecventa.h:83` — `"cifra cu frecventa minime este " << min`

Primul mesaj e reparat corect (`"nr cel mai frecvent"`). Al doilea a preluat formularea de la 1b — dar 1a lucrează pe **numere** din vector (`f[v[i]]++`), nu pe cifre. Pe datele din cod:

```
cifra cu frecventa minime este 7 si apare de 1 ori
```

7 e un număr din vector care se nimerește să aibă o singură cifră. Pune `42` în vector în locul lui și mesajul devine „cifra … este 42".

Corect: `"numarul cu frecventa minima este "`. (Și `minime` → `minima`.)

### M3 — restanță: funcții duplicate în 9 headere

`afisare`, `prim`, `oglindit`, `cmmdc`, `patratPerfect` există fiecare în mai multe fișiere din `vectori/`. B2 arată acum de ce contează dincolo de eroarea de compilare: ai reparat `patratPerfect` într-un fișier și au rămas două variante diferite ale aceleiași funcții în proiect. Un `utile.h` comun rezolvă și problema de „am reparat, dar nu peste tot".

---

## 🟢 Cleanups

- **C1** — `frecventa.h:117`: `"cifra cu recventa maxima"` — lipsește `f`-ul.
- **C2** — `frecventa.h:131`: `//todo:` încă acolo, deasupra unui cod terminat.
- **C3** — `frecventa.h:332`: `int nou[100];` neinițializat — `int nou[100]{};` costă două caractere.
- **C4** — `frecventa.h:8` vs `:218`: `frecventaCifraNumar` e tot o copie a lui `frecventaCif` + afișare.
- ✅ Rezolvate: `int aux` mort din `solutie2c`, `int d = 4` → `3` în `solutie9`, `int` → `double` la retur în `medieAritmetica` (verificat: `solutie1` dă 2, corect pentru media 43.4).

---

## Before / After — criticele

| # | Before (actual) | After (corect) |
|---|---|---|
| B1 | `while (n <= 0) {` (`frecventa.h:219`) | `do { … } while (n != 0);` — corpul rulează măcar o dată, deci și `n = 0` e tratat |
| B2 | `return sqrt(n) * sqrt(n) == n;` (`exercitiiRecapitulative.h:379`) | `int rad = (int)sqrt((double)n); … return rad * rad == n;` — decizia în `int`, nu în `double` |
| B3 | `while (v[ct] == v[ct+1] && ct < d-1)` (`exercitiiRecapitulative.h:153`) | `while (ct < d-1 && v[ct] == v[ct+1])` — garda înaintea accesului |
| B4 | `int minim = 100;` (`frecventa.h:43`) | `int minim = INT_MAX;` + `#include <climits>` |
| M1 | `for (int i = 10; i <= 99; i++)` (`frecventa.h:31`) | `for (int i = 10; i <= 100; i++)` |
| M2 | `"cifra cu frecventa minime este "` (`frecventa.h:83`) | `"numarul cu frecventa minima este "` |

---

## Regula rundei: rulează după fix, nu doar înainte

La David și la Ștefan a apărut aceeași lecție săptămâna asta, sub formă de „Build înainte de commit". La tine e varianta ei mai fină, fiindcă **codul tău compilează** — nu compilatorul e cel care te-ar fi salvat, ci rularea.

Ai schimbat `frecventaCif`, o funcție folosită de **7 subpuncte**. Regula, mecanic:

1. După ce modifici o funcție, întreabă-te **cine o cheamă** (în Visual Studio: click dreapta pe nume → *Find All References*).
2. Rulează măcar unul dintre apelanți, cu **F5**, și uită-te la ce iese.
3. Compară cu răspunsul pe care îl calculaseși de mână *înainte* de fix.

Pasul 3 e cel important. Când ai rulat 2c și ai văzut `13579`, ai fi zis „merge". Dar dacă ai avea scris pe hârtie că 2g trebuie să dea `123445` și pe ecran apare `0`, nu mai ai cum să ratezi. Un fix nu e gata când compilează — e gata când vezi cu ochii tăi vechiul răspuns corect ieșind din nou.

---

## Q&A — verifică-ți înțelegerea

1. La B1, `while (n != 0)` sărea peste cazul `n = 0`, iar `do…while (n != 0)` îl rezolvă. Explică, în cuvintele tale, **ce mută** `do` — nu ce face funcția, ci în ce moment se verifică condiția. Apoi: dacă ai fi vrut să păstrezi `while`, ce linie ai fi adăugat înainte de buclă ca să obții același rezultat?

2. La B3, ambele variante conțin exact aceleași două condiții, doar în ordine schimbată — totuși una citește în afara vectorului și cealaltă nu. Explică de ce ordinea contează la `&&`. Bonus: se schimbă ceva dacă ai `||` în loc de `&&`?

3. 2c și 2f au fost afectate identic de B1 (`f[]` gol), dar 2c a afișat răspunsul corect și 2f unul greșit. Explică ce anume din enunțul lui 2c a făcut ca bug-ul să fie invizibil acolo. Ce lecție tragi despre **cum îți alegi datele de test** — ce vector ai fi pus în 2c ca să prinzi bug-ul de la prima rulare?
