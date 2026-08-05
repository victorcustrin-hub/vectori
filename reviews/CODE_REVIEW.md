# Code Review — victor-vectori · runda 5: modulul `frecventa.h`

Review pe commit-urile `frecventa` → `finish ex2`, adică fișa de probleme din `cerinte/frecventa.jpeg` (1a–1e, 2a–2g). Codul NU a fost modificat — totul e doar aici. Constatările marcate „verificat prin rulare" au fost compilate și executate separat, cu detector de acces în afara vectorului (AddressSanitizer).

> **Verdictul pe scurt.** Din 12 subpuncte rezolvate, **logica e corectă la toate 12**. Nu e o formulă de politețe: ai citit cerințele exact. La 2g ai pornit bucla de la `i = 1`, deci ai eliminat cifra 0 fiindcă *așa cerea enunțul* — nu din întâmplare. La 2e ai adunat `fMax - f[i]` **doar peste cifrele prezente**, care e singura citire corectă a cerinței. La 2d ai plafonat corect cu `ct > 2 → ct = 2`. La 1a ai folosit „minimul diferit de zero" ca să sari peste numerele care nu apar deloc — exact ideea centrală a vectorului de frecvență.
>
> Problemele care au rămas nu sunt de logică, ci de **limite**: unde se termină vectorul, cât de mare poate fi o valoare, ce scrie în mesaj față de ce se afișează de fapt.

---

## 🔴 Critice

### B1 — `pozElemMinVec`: „infinitul" tău e 100, iar frecvențele pot trece de 100
- `frecventa.h:43` — `int minim = 100;`
- Apelat la `:80` și `:114`, iar rezultatul e folosit ca index la `:83`

Ca să găsești un minim, pornești de la o valoare „mai mare decât orice"— aici, `100`. Dar funcția e chemată pe **vectorul de frecvențe**, nu pe vectorul de date. Iar enunțul spune „vector de maxim 2000 de numere": dacă o valoare apare de 150 de ori, `f[...]` este `150`, iar condiția `150 < 100` e falsă. Elementul nu e văzut niciodată.

Când *toate* frecvențele sunt ≥ 100, `poz` rămâne `-1` și se întoarce așa. Apelantul nu verifică:

```cpp
int min = pozElemMinVec(f, 100);          // :80  → -1
cout << ... << f[min] << ...              // :83  → f[-1], în afara vectorului
```

Verificat prin rulare — vector cu 150 de „5" și 200 de „7":

```
poz returnat = -1   (asteptat: 5)
apelantul ar face f[-1] -> citire in afara vectorului
```

`f[-1]` nu dă eroare la compilare și de multe ori nici la rulare: citește pur și simplu cei 4 octeți dinaintea vectorului și afișează ce găsește acolo. De asta e categoria cea mai periculoasă de bug — nu se plânge nimeni, doar numărul e greșit.

**Ce înveți:** un „infinit" ales cu ochiul e o presupunere ascunsă despre datele tale. Două variante corecte, ambele fără constantă magică:

```cpp
int minim = -1;                            // „încă n-am găsit nimic"
for (int i = 0; i < d; i++)
    if (v[i] != 0 && (poz == -1 || v[i] < minim)) { minim = v[i]; poz = i; }
```

sau, dacă vrei să păstrezi forma actuală, `#include <climits>` și `int minim = INT_MAX;` — adică cel mai mare `int` care există, nu unul pe care îl speri suficient de mare.

Același raționament se aplică și la `pozElemMaxVec:57` (`int maxim = -1;`): acolo *merge*, pentru că o frecvență nu e niciodată negativă. Merge din noroc, nu din construcție — dacă mâine dai funcția pe un vector cu numere negative, se rupe la fel.

---

### B2 — `frecventaNumarVector`: vectorul are 100 de căsuțe, dar valorile ajung la 100
- `frecventa.h:25` — `int f[100]{};`
- `frecventa.h:28` — `f[v[i]]++;`

Enunțul 1 spune „valori intre 1-100". `int f[100]` are indicii `0…99`. Când `v[i]` este `100`, `f[100]++` scrie **imediat după** vectorul tău, peste altceva de pe stivă.

Verificat prin rulare, cu AddressSanitizer pe `v = {99, 99, 42, 100, 13}`:

```
ERROR: AddressSanitizer: stack-buffer-overflow
This frame has 1 object(s):
  [32, 432) 'f' <== Memory access at offset 432 overflows this variable
```

`f` ocupă 400 de octeți (100 × 4); offset-ul 432 este exact `f[100]`.

Interesant e că în `solutie1a:73` ai declarat `int f[101]{}` — deci **ai știut** că îți trebuie și căsuța 100. În `frecventaNumarVector` s-a pierdut.

**Ce înveți:** dimensiunea unui vector de frecvență nu e „un număr rotund", ci *cea mai mare valoare posibilă + 1*. Pentru valori `1…100` → `f[101]`. Pentru cifre `0…9` → `f[10]`, cum ai și făcut peste tot la problema 2.

---

### B3 — `frecventaNumarVector`: bucla de afișare nu ajunge niciodată la 99
- `frecventa.h:31` — `for (int i = 10; i < 99; i++)`

`i < 99` oprește bucla la `i = 98`. Numărul 99 e numărat corect în `f[99]`, dar nu e afișat niciodată. Din aceeași rulare:

```
in vector apare 13 de 1 ori
in vector apare 42 de 1 ori
^ lipsesc 99 (de 2 ori) si 100 (de 1 ora)
```

Corect: `for (int i = 10; i <= 99; i++)` — sau, dacă extinzi și la valoarea 100 (B2), `i <= 100`.

**Ce înveți:** `<` și `<=` nu sunt interschimbabile după gust. Regula pe care o poți aplica mecanic, fără să te gândești: cu `<` scrii **limita+1** (`i < 100`), cu `<=` scrii **ultima valoare validă** (`i <= 99`). Aici ai amestecat cele două: ai scris ultima valoare validă, dar cu operatorul celeilalte forme.

---

## 🟡 Importante

### M1 — mesajele spun altceva decât valoarea afișată
- `frecventa.h:82-83` — `"Maximul din vector este " << maxi`
- `frecventa.h:116-117` — `"Frecventa minima = " << minim`

Aici **calculul e corect, textul minte.** Sunt două cazuri distincte, opuse:

La 1a (`:82`), cerința e „numarul ce are frecventa cea mai mica si cea mai mare". Afișezi `maxi`, care e numărul cel mai frecvent — corect. Dar pe `v = {5,5,5,2,2,7,8,9}` se tipărește:

```
Maximul din vector este 5 si apare de 3 ori
```

Maximul vectorului e 9, nu 5. Cine citește ecranul primește o afirmație falsă despre un calcul corect.

La 1b (`:116`), cerința e „cifra ce are frecventa cea mai mica". Afișezi `minim`, care e cifra — iar corect. Dar textul zice „Frecventa minima = 4", când 4 e *cifra*, nu frecvența ei.

Formulări care spun ce e:

```cpp
cout << "Numarul cel mai frecvent este " << maxi << " si apare de " << f[maxi] << " ori" << endl;
cout << "Cifra cu frecventa minima este " << minim << " (apare de " << f[minim] << " ori)" << endl;
```

**Ce înveți:** la problemele de frecvență lucrezi tot timpul cu două lucruri ușor de confundat — **indicele** (`i` = numărul sau cifra) și **conținutul** (`f[i]` = de câte ori apare). Când mesajul nu spune explicit care din ele e, nu ai cum să prinzi confuzia la citire. Aici ai avut-o corect în cap și greșit pe ecran; data viitoare poate fi invers, și atunci mesajul te salvează.

### M2 — `solutie1a` scanează 0…99 dintr-un vector de 101
- `frecventa.h:79-80` — `pozElemMaxVec(f, 100)` și `pozElemMinVec(f, 100)`

Ai dimensionat `f[101]` (corect, B2), dar treci `d = 100`, deci buclele merg `i < 100` → se opresc la 99. Dacă în vector apare valoarea 100, e numărată și apoi ignorată. Corect: `pozElemMaxVec(f, 101)`.

Aceeași familie ca B3 — de fiecare dată când un vector de frecvență are `N+1` căsuțe, tot ce îl parcurge trebuie să meargă până la `N` inclusiv.

### M3 — restanță din runda 4: funcții duplicate în 9 headere
`afisare` există acum în **9** fișiere din `vectori/`, inclusiv noul `frecventa.h:323`. La fel `prim`, `oglindit`, `cmmdc`. Merge atâta timp cât `vectori.cpp` include un singur header; la două include-uri simultane primești `error C2084: function already has a body`.

Rămâne tema de „igienă de proiect": un `utile.h` cu funcțiile-cărămidă, incluse de restul. Nu blochează fișa.

### M4 — restanțe runda 4, neatinse
Commit-urile noi ating doar `frecventa.h` și `vectori.cpp`, deci din runda 4 au rămas deschise:

| # | Loc | Ce e |
|---|---|---|
| B1 (r4) | `exercitiiRecapitulative.h:153` | `while (v[ct] == v[ct+1])` fără graniță `ct < d-1` |
| M1 (r4) | `exercitiiRecapitulative.h:273` | `solutie9`: `int d = 4;` la 3 elemente |
| C1 (r4) | `exercitiiRecapitulative.h:8` | `int medieAritmetica(...)` — trebuie `double` la **retur** |
| C2 (r4) | `exercitiiRecapitulative.h:379` | `sqrt(n) == (int)sqrt(n)` — varianta robustă e `rad*rad == n` |

B1 din runda 4 e exact aceeași lecție ca B1 și B2 de aici: **unde se termină vectorul**. Trei bug-uri, o singură cauză.

---

## 🟢 Cleanups

- **C1** — `frecventa.h:259`: `int aux = n;` nefolosit în `solutie2c` (`frecventaCif(n, f)` primește `n`, nu `aux`). Variabilă moartă.
- **C2** — `frecventa.h:131`: `//todo:` rămas deasupra unui cod care e gata.
- **C3** — `frecventa.h:8` vs `:219`: `frecventaCifraNumar` e `frecventaCif` + afișare. Odată ce ai `frecventaCif(n, f)`, prima poate fi doar `frecventaCif(numar, f)` urmat de bucla de afișare — n-o rescrii.
- **C4** — `frecventa.h:334`: `int nou[100];` neinițializat. Aici e inofensiv (afișezi doar primele `ct`), dar `int nou[100]{};` te costă două caractere și elimină clasa de bug.
- **C5** — `frecventaCif:219` nu tratează `n == 0`: `while (n != 0)` nu intră deloc, deci cifra 0 nu e numărată. La 1d ai pus explicit `if (nou == 0) f[0] = 1;` — deci ai văzut cazul acolo, dar nu l-ai dus în funcția comună.

---

## Before / After — criticele

| # | Before (actual) | After (corect) |
|---|---|---|
| B1 | `int minim = 100;` (`:43`) | `int minim = INT_MAX;` + `#include <climits>` — sau santinelă pe `poz == -1` |
| B2 | `int f[100]{};` (`:25`) | `int f[101]{};` — valorile merg până la 100 inclusiv |
| B3 | `for (int i = 10; i < 99; i++)` (`:31`) | `for (int i = 10; i <= 100; i++)` |
| M1 | `"Maximul din vector este " << maxi` (`:82`) | `"Numarul cel mai frecvent este " << maxi` |
| M2 | `pozElemMaxVec(f, 100)` (`:79-80`) | `pozElemMaxVec(f, 101)` |

---

## Q&A — verifică-ți înțelegerea

1. La `solutie1a` cu vectorul din cod, rezultatul afișat e corect. Explică de ce `int minim = 100` **nu** strică nimic pe acest vector, dar ar strica pe un vector de 300 de elemente în care toate valorile se repetă mult. Care e cel mai mic vector de test la care ai vedea `-1` pe ecran?

2. `int f[100]` și `int f[101]` diferă printr-o singură căsuță, dar B2 e un bug de memorie, iar M2 doar un număr lipsă. Explică de ce **scrierea** `f[100]++` e mai gravă decât **necitirea** lui `f[100]` — ce se poate strica în primul caz și nu în al doilea?

3. La 1b afișezi cifra, la 1a afișezi numărul, iar în ambele cazuri valoarea vine dintr-un `poz...` care întoarce un **index**. De ce la 1a mai ai nevoie și de `f[maxi]`, iar la 1b nu ai nevoie de `f[minim]`? Ce întreabă fiecare cerință, de fapt?
