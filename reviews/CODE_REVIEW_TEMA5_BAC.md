# Code Review — victor-vectori · `tema5.h` + `exercitiiBac.h`

Review pe `0b04d60` → `3a5377e` (commit-urile `finish code review critical`, `tema5`, `finish bac 2026 var4 sub1`, `finish sub 2`, `sub3 ex2`, `finish sub3 ex2`). Fișiere: `vectori/tema5.h` (752 linii, nou), `vectori/exercitiiBac.h` (166 linii, nou), plus modificările din `vectori/secvente.h`.

Codul NU a fost modificat — totul e doar aici. Toate constatările sunt **verificate prin compilare și rulare** (clang++ `-std=c++17 -Wall`, plus AddressSanitizer), nu doar prin citire.

> **Verdictul pe scurt.** Din cele 20 de probleme din `tema5.h`, **14 dau răspunsul corect** pe datele din cod: 519, 520, 578, 854, 523, 298, 181, 300, 304, 516, 862, 981, 283, 4457. Sunt rezolvări curate, cu garda `j + 1 < d &&` pusă în ordinea corectă peste tot — deci lucrul ăla din review-urile trecute a intrat în reflex.
>
> Și ai închis corect ce ți-am semnalat data trecută în `secvente.h`: `% 2 == 1` → `% 2 != 0` în ambele locuri, plus santinela tratată la #518.
>
> Și subiectul III l-ai închis singur în `3a5377e`, corect — vezi **B4**, e singura constatare din review-ul ăsta care era deja rezolvată când l-am scris.
>
> Ce a rămas se împarte în trei:
> 1. **Un bug real de logică** la subiectul II d) — o condiție de `do...while` inversată, care dă răspuns greșit la bac.
> 2. **Patru funcții comise pe jumătate** (522, 4148, 2921, 297) — nu sunt „neterminate și tăcute", ci **afișează un rezultat care arată ca un răspuns**. Asta e mai periculos decât să nu afișeze nimic.
> 3. **Firul roșu, a treia oară: repari linia, nu regula.** Ai reparat `% 2 == 1` în `secvente.h`, dar ai copiat aceeași funcție în `tema5.h:493` cu bug-ul vechi în ea. Ai tratat santinela la #518, dar la #166 din `tema5.h` ai reintrodus-o. Vezi M2.

---

## 🔴 Critice

### B1 — `do...while` cu condiția inversată (subiectul II, punctul d)

`exercitiiBac.h:108-112`

```cpp
do {
    p = 1;
    n = n / d;
} while (n % d != 0);
```

Cerința era: înlocuiește `cât timp n % d == 0 execută ...` cu o structură cu **test final**. Transformarea corectă păstrează condiția, nu o neagă:

| structură | continuă cât timp... |
|---|---|
| `while (n % d == 0) { ... }` | `n % d == 0` |
| `do { ... } while (n % d == 0);` | `n % d == 0` |
| ce ai scris: `do { ... } while (n % d != 0);` | `n % d != 0` ← **opusul** |

Rezultatul: bucla iese după **o singură** împărțire, în loc să scoată tot factorul.

**Verificat prin rulare** — aceeași intrare, cele două funcții:

```
c) n=8    -> 1     (corect)
d) n=8    -> 2     (gresit)
c) n=12   -> 2     (corect)
d) n=12   -> 2
c) n=2600 -> 3     (corect)
d) n=2600 -> 3
```

Pe `n = 2600` iese 3 din noroc, de-aia n-ai prins-o. Pe `n = 8` (`2³`) se vede: `8 % 2 == 0` → intri, `p = 1`, `n = 4`; testul final `4 % 2 != 0` e **fals** → ieși cu `n = 4` neîmpărțit. Apoi `d = 3`, `9 <= 4` fals, buclă exterioară gata. `n = 4 != 1` → `nr = 1 + 1 = 2`. Ai numărat factorul 2 de două ori.

**Ce înveți.** `while` și `do...while` diferă prin *când* se testează, nu prin *ce* se testează. Când transformi una în alta, condiția rămâne literalmente aceeași; singura schimbare e că trebuie să garantezi prima intrare — și tu ai făcut asta corect, cu `if (n % d == 0)` în față. Erai la un caracter distanță de răspunsul complet.

---

### B2 — `if (v, i, j, k)` este mereu adevărat (#522)

`tema5.h:98`

```cpp
if (v, i, j, k) {   //???
```

Ăsta nu e un apel de funcție — e **operatorul virgulă**. C++ evaluează `v`, apoi `i`, apoi `j`, le aruncă pe toate, și păstrează ultima valoare: `k`. Cum `k = 3`, condiția e `if (3)` → mereu adevărat. Funcția afișează **„DA" pentru orice vector**.

Compilatorul îți spune asta, de trei ori:

```
tema5.h:98:17: warning: left operand of comma operator has no effect [-Wunused-value]
tema5.h:98:20: warning: left operand of comma operator has no effect [-Wunused-value]
tema5.h:98:23: warning: left operand of comma operator has no effect [-Wunused-value]
```

**Verificat prin rulare** pe `v = {1,2,3,4,5,6,7,8}`, `k = 3` — vector în care nu există două secvențe identice de lungime 3:

```
--- 522 (asteptat NU) ---
DA
```

Pe datele tale din `solutie522` iese „DA" — dar corect din întâmplare, nu din calcul.

**Ce înveți.** `//???` din cod arată că știai că lipsește ceva. Când ești în punctul ăsta, scrie o funcție goală cu nume — `bool secventeEgale(int v[], int i, int j, int k)` — și las-o să returneze `false`. Programul dă atunci un răspuns *conservator și verificabil*, nu unul optimist. Un „NU" greșit se prinde; un „DA" mereu adevărat trece nedetectat prin toate testele care se întâmplă să aibă răspunsul „DA".

---

### B3 — Trei funcții afișează un rezultat pe care nu l-au calculat

Același tipar în trei locuri: variabila de rezultat e declarată, inițializată, **niciodată actualizată**, și apoi afișată ca și cum ar fi un răspuns.

| loc | variabila | ce afișează | ce ar trebui |
|---|---|---|---|
| `tema5.h:599-603` (#4148) | `int ct = 0;` | `nr de secvente de lungime maxima = 0` | `2` |
| `tema5.h:631-638` (#2921) | `int smax = -2000000000;` | `Suma maxima ... este: -2000000000` | suma maximă pe perechi |
| `tema5.h:726-746` (#297) | `smax`, `dmax` | **nimic** — funcția n-are niciun `cout` | secvența cu suma 8 |

**Verificat prin rulare:**

```
--- 4148 solutie4148 (asteptat lmax=2, nr=2) ---
Lungimea max = 2
nr de secvente de lungime maxima = 0
--- 2921 solutie2921 ---
Suma maxima obtinuta din perechi este: -2000000000
--- 297 solutie297 (asteptat suma max = 8) ---
[sfarsit 297]          <-- nimic intre marcaje
```

La #2921 bucla e literalmente goală:

```cpp
for (int k = 0; k < m; k++) {

  
}
```

La #297 compilatorul te avertizează direct:

```
tema5.h:729:9: warning: unused variable 'smax'
tema5.h:730:9: warning: variable 'dmax' set but not used
```

Partea de Kadane e scrisă corect (`if (suma < 0) suma = v[i];`) — îți lipsește doar `smax` actualizat la reset și un `cout` la final.

**Ce înveți.** „Neterminat" și „greșit" nu costă la fel. O funcție care nu compilează te oprește. O funcție care afișează `0` sau `-2000000000` **arată ca un program care merge** — și o vei descoperi abia la teză. Regulă practică: cât timp o funcție e pe jumătate, pune `cout << "TODO" << endl;` în loc de rezultat. Costă o linie și îți garantează că nu confunzi „n-am scris încă" cu „am scris greșit".

---

### B4 — ✅ REZOLVAT în `3a5377e` — `sub3ex2()`, indice în loc de valoare

`exercitiiBac.h:136-166`

În `dfc94a6` funcția era blocată exact aici:

```cpp
int min = v[0];
int stanga = v[0];       // valoare, nu pozitie
int dreapta = v[n-1];    // valoare, nu pozitie
cout << dreapta;         // ramasita de debug -> programul afisa doar "9"

for (int i = 0; i < n; i++)
    if (v[i] < min) min = v[i];   // retineai VALOAREA minimului
// interschimbarea si afisarea lipseau
```

În `3a5377e` ai adăugat `poz`, ai făcut `stanga`/`dreapta` **indici** în loc de valori, ai scos `cout`-ul de debug și ai pus interschimbarea pe ramuri + afișarea. **E corect.**

**Verificat prin rulare**, pe ambele exemple din enunț plus cinci cazuri-limită:

```
ex.2 din enunt  -> 8 6 4 2 7 1     asteptat: 8 6 4 2 7 1   ✅
ex.1 din enunt  -> 2 6 8 2 7 4     asteptat: 2 6 8 2 7 4   ✅
min impar la 0  -> 7 9 5 3         asteptat: 7 9 5 3       ✅
min par la 0    -> 4 9 5 7         asteptat: 4 9 5 7       ✅
min par la n-1  -> 2 5 7 9         asteptat: 2 5 7 9       ✅
min = 0 (par)   -> 0 5 7 3         asteptat: 0 5 7 3       ✅
n=2, egale      -> 5 5             asteptat: 5 5           ✅
```

Trei detalii pe care le-ai luat corect fără să ți le ceară nimeni:

- **`<` strict** în `if (v[i] < min)` → când minimul apare de mai multe ori, îl reții pe **primul**. Enunțul spune „se alege doar unul dintre acestea", deci merge oricare — dar tu ai ales conștient, nu la întâmplare.
- **Interschimbarea cu tine însuți nu strică nimic** — dacă `poz == stanga`, cele trei linii cu `aux` lasă vectorul neatins. Verificat pe `{4,9,5,7}`.
- **`min = 0`** cade pe ramura „par", corect (`0 % 2 == 0`).

**Ce înveți — și de ce merită reținut dincolo de problema asta.** Blocajul din `dfc94a6` nu era de sintaxă, era de *alegere a informației*: reținuseși valoarea minimului, iar din valoare nu se poate face interschimbarea. Indicele e informația mai bogată — valoarea o obții oricând din el (`v[poz]`), invers nu, ar trebui să cauți din nou prin vector și, dacă minimul apare de două ori, n-ai ști pe care l-ai găsit. Regula ține la toate problemele de tipul „găsește X și fă ceva cu el": **caută poziția, nu valoarea.**

Rămâne deschis doar M6 de mai jos (citirea de la tastatură).

---

## 🟡 Importante

### M1 — `tema5.h` și `secvente.h` nu pot fi incluse în același program

Patru funcții sunt definite identic în ambele fișiere:

| funcție | `secvente.h` | `tema5.h` |
|---|---|---|
| `nr1InBaza2` | `:156` | `:487` |
| `solutie516` | `:76` | `:443` |
| `solutie523` | `:145` | `:217` |
| `solutie981` | `:194` | `:505` |

**Verificat prin compilare** — un `.cpp` care le include pe amândouă nu trece:

```
tema5.h:217:6: error: redefinition of 'solutie523'
tema5.h:443:6: error: redefinition of 'solutie516'
tema5.h:487:6: error: redefinition of 'nr1InBaza2'
tema5.h:505:6: error: redefinition of 'solutie981'
```

Acum nu se vede, pentru că `vectori.cpp` include un singur header. Dar în momentul în care vrei să rulezi și secvențe, și tema 5, din același `main()`, proiectul nu mai compilează.

`#pragma once` **nu** te apără aici — el previne includerea aceluiași fișier de două ori, nu două fișiere diferite care declară același nume. Cea mai simplă ieșire: numele funcțiilor de test să spună de unde vin (`tema5_solutie523`), sau ține fiecare problemă într-un singur fișier.

### M2 — Regula reparată în `secvente.h`, dar nu și în copia din `tema5.h`

Ăsta e firul roșu al ultimelor trei review-uri, de-aia îl scot separat.

**(a) `% 2 == 1`.** În `secvente.h` l-ai schimbat corect în `% 2 != 0`, în ambele locuri (`:24`, `:27`, `:57`). Dar `nr1InBaza2` din `tema5.h:493` e copia veche, cu bug-ul în ea:

```cpp
// secvente.h:162  (reparat)
if (n % 2 != 0) { ct++; }

// tema5.h:493     (copia veche)
if (n % 2 == 1) { ct++; }
```

Aici `n` e natural, deci nu mușcă — dar linia a supraviețuit pentru că ai reparat *apariția semnalată*, nu *regula*.

**(b) Santinela „n-am găsit nimic".** La #518 ai tratat-o corect (`secvente.h:105-108`). La #166 din `tema5.h:277-298` ai reintrodus exact problema veche:

```cpp
int smax = 0;
int dmax = -1;
// ... daca niciun element nu e par, nimic nu le modifica
smax++;  // -> 1
dmax++;  // -> 0
cout << smax << " " << dmax << endl;
```

**Verificat prin rulare** pe `v = {1,3,5,7}` — vector fără niciun element par:

```
--- 166 pe vector fara elemente pare ---
1 0
```

Afișează perechea de indici `1 0`, adică o secvență care începe după ce s-a terminat. `#181` (`:311`) are aceeași inițializare, dar acolo nu se vede, pentru că orice element singur e o secvență crescătoare validă — deci `dmax` se setează mereu.

**Ce înveți.** Când repari ceva, întreabă-te de fiecare dată: *„unde mai am scris asta?"*. `Ctrl+Shift+F` în Visual Studio, caută `% 2 == 1` peste tot în proiect. O regulă învățată se aplică la toate aparițiile, altfel n-ai învățat regula, ai reparat o linie.

### M3 — Lipsește separatorul la afișare (#524)

`tema5.h:559`

```cpp
cout << smax + 1 << dmax + 1 << endl;
```

**Verificat prin rulare:**

```
--- 524 solutie524 (asteptat: 4 11) ---
411
```

Algoritmul e corect — pe `{6,6,8,3,6,6,3,8,4,3,3,4}` găsește într-adevăr secvența de la poziția 4 la 11 (`3 ... 3`). Doar că `411` nu se poate citi. La restul funcțiilor din fișier ai pus `<< " " <<`; aici a scăpat.

### M4 — `d` nu corespunde numărului de elemente din vector

| loc | vector | elemente | `d` declarat |
|---|---|---|---|
| `tema5.h:379-380` (#300) | `{12,10,15,7,17,13,19,14}` | 8 | `9` |
| `tema5.h:749-750` (#297) | `{-4,1,-5,1,4,-2,2,3,-4,4}` | 10 | `9` |

La #300 citești `v[8]`, care e `0` (restul lui `int v[100]` e zero-inițializat) — răspunsul iese corect din noroc. La #297 ignori ultimul element. Niciunul nu e crash, dar amândouă înseamnă că testul tău nu testează ce crezi tu că testează.

### M5 — Limitele buclelor de la #522 ies din vector

`tema5.h:96-97`

```cpp
for (int i = 0; i <= n; i++) {
    for (int j = i + 1; j <= n - k; j++) {
```

`i <= n` merge până la `v[n]`, adică un pas peste ultimul element (indicii valizi sunt `0 .. n-1`). Acum nu crapă doar pentru că B2 face ca `v` să nu fie nici măcar citit. În clipa în care pui comparația reală, ai citire în afara vectorului. Corect: `i <= n - k` la ambele (o secvență de lungime `k` care începe la `i` are nevoie de `i + k <= n`).

### M6 — Subiectul III cere citire de la tastatură

`exercitiiBac.h:137-138`

```cpp
int n = 6;
int v[51] = {2,5,1,6,4,9};
```

Enunțul spune explicit: *„citește de la tastatură un număr natural n (n ∈ [2,50]), și un șir de n numere naturale"*. La corectare, citirea datelor e punctată separat. Pentru testat în Visual Studio e în regulă să ai valori fixe, dar versiunea pe care o predai trebuie să aibă `cin >> n;` și bucla de citire. Restul fișierului e OK din punctul ăsta de vedere — la subiectul II ai `cin >> n;` corect.

---

## 🟢 Cleanups

- **C1** — `tema5.h:647-673` (#283) și `tema5.h:688-713` (#4457) sunt aceeași funcție, linie cu linie, sub două nume. Și enunțul din comentariul de la `:685-687` e copiat de la 283 — pbinfo 4457 cere altceva. Verificat: ambele afișează `6 9`.
- **C2** — `secvente.h:174` — `int lungime = 0;` declarat în funcție și umbrit imediat de `int lungime = j - i + 1;` de la `:184`. Compilatorul îl semnalează: `warning: unused variable 'lungime'`. Cel exterior se poate șterge.
- **C3** — ✅ rezolvat în `3a5377e` odată cu B4 (`stanga` nefolosit + `cout << dreapta;` de debug — ambele au dispărut). Rămâne doar: fișierul **nu se termină cu linie nouă** (`\ No newline at end of file`); pune Enter după ultima acoladă, altfel diff-urile viitoare arată ultima linie ca modificată degeaba.
- **C4** — `tema5.h:487-503` — `nr1InBaza2(0)` returnează `true`, pentru că `ct == total` devine `0 == 0`. Zero în binar e `0`, n-are nicio cifră de 1. Se rezolvă cu `if (n <= 0) return false;` la început.
- **C5** — Trace-ul de la subiectul II a): `exercitiiBac.h:60` și `:61` scriu `1+0=0` (ar fi `1`), iar `:65` zice `n!=0` deși codul tău are corect `n != 1`. Rezultatul final (3) e bun, dar la bac tabelul de urmărire se citește de către corector — aritmetica din el trebuie să fie curată.
- **C6** — `tema5.h:12-13` — `bool vf` și `int mem` țin aceeași informație. `mem` inițializat cu `-1` e suficient: `if (mem != -1)` la final, ca la `secvente.h:64`, unde ai făcut deja asta corect.

---

## Before / After (doar pentru cele critice — NU aplicat în cod)

### B1 — `exercitiiBac.h:108-112`

| acum | corect |
|---|---|
| <pre>if (n % d == 0) {<br>    do {<br>        p = 1;<br>        n = n / d;<br>    } while (n % d != 0);<br>}</pre> | <pre>if (n % d == 0) {<br>    do {<br>        p = 1;<br>        n = n / d;<br>    } while (n % d == 0);<br>}</pre> |

### B2 — `tema5.h:93-106`

| acum | corect |
|---|---|
| <pre>for (int i = 0; i <= n; i++) {<br>    for (int j = i+1; j <= n-k; j++) {<br>        if (v, i, j, k) {   //???<br>            vf = true;<br>            break;<br>        }<br>    }<br>    ...<br>}</pre> | <pre>bool egale(int v[], int i, int j, int k) {<br>    for (int t = 0; t < k; t++) {<br>        if (v[i+t] != v[j+t]) return false;<br>    }<br>    return true;<br>}<br><br>for (int i = 0; i <= n-k; i++)<br>    for (int j = i+1; j <= n-k; j++)<br>        if (egale(v, i, j, k)) { vf = true; break; }</pre> |

### B3 — `tema5.h:579-604` (#4148, numărătoarea lipsă)

| acum | corect |
|---|---|
| <pre>// o singura trecere, doar lmax<br>int ct = 0;<br><br>cout << "Lungimea max = " << lmax;<br>cout << "nr de secvente ... = " << ct;</pre> | <pre>// a doua trecere, identica, dar numara<br>int ct = 0;<br>for (int i = 0; i &lt; n; i++) {<br>    if (v[i] % 10 == 0) {<br>        int j = i;<br>        while (j+1 &lt; n && v[j+1] % 10 == 0) j++;<br>        if (j - i + 1 == lmax) ct++;<br>        i = j;<br>    }<br>}</pre> |

### B3 — `tema5.h:726-746` (#297, Kadane fără start și fără afișare)

| acum | corect |
|---|---|
| <pre>int smax = 0, dmax = 0;<br>for (int i = 1; i &lt; d; i++) {<br>    if (suma &lt; 0) suma = v[i];<br>    else suma = suma + v[i];<br>    if (suma &gt; sumaMax) {<br>        sumaMax = suma;<br>        dmax = i;<br>    }<br>}<br>// nicio afisare</pre> | <pre>int start = 0, smax = 0, dmax = 0;<br>for (int i = 1; i &lt; d; i++) {<br>    if (suma &lt; 0) { suma = v[i]; start = i; }<br>    else suma = suma + v[i];<br>    if (suma &gt; sumaMax) {<br>        sumaMax = suma;<br>        smax = start;<br>        dmax = i;<br>    }<br>}<br>cout &lt;&lt; sumaMax &lt;&lt; ": " &lt;&lt; smax+1 &lt;&lt; " " &lt;&lt; dmax+1;</pre> |

### B4 — `exercitiiBac.h:136-166` — ✅ închis de tine în `3a5377e`

| `dfc94a6` (blocat) | `3a5377e` (ce ai scris — corect) |
|---|---|
| <pre>int min = v[0];<br>int stanga = v[0];<br>int dreapta = v[n-1];<br>cout &lt;&lt; dreapta;<br><br>for (int i = 0; i &lt; n; i++)<br>    if (v[i] &lt; min) min = v[i];<br>// interschimbarea lipseste</pre> | <pre>int min = v[0], poz = 0;<br>int stanga = 0, dreapta = n-1;<br><br>for (int i = 0; i &lt; n; i++)<br>    if (v[i] &lt; min) { min = v[i]; poz = i; }<br><br>if (min % 2 == 0) { /* swap poz &lt;-&gt; stanga */ }<br>else               { /* swap poz &lt;-&gt; dreapta */ }<br><br>for (int i = 0; i &lt; n; i++)<br>    cout &lt;&lt; v[i] &lt;&lt; " ";</pre> |

### M2(b) — `tema5.h:295-297` (santinela)

| acum | corect |
|---|---|
| <pre>smax++;<br>dmax++;<br>cout &lt;&lt; smax &lt;&lt; " " &lt;&lt; dmax &lt;&lt; endl;</pre> | <pre>if (dmax == -1) {<br>    cout &lt;&lt; "Nu exista elemente pare in vector" &lt;&lt; endl;<br>    return;<br>}<br>cout &lt;&lt; smax+1 &lt;&lt; " " &lt;&lt; dmax+1 &lt;&lt; endl;</pre> |

---

## Q&A — verifică-ți înțelegerea

**1.** În `if (v, i, j, k)`, ce valoare are de fapt condiția și de ce? Ce s-ar fi întâmplat dacă scriai variabilele în altă ordine, `if (k, j, i, v)`?

**2.** La #166 rezultatul greșit e `1 0`. Explică de unde vine fiecare cifră, pornind de la `smax = 0` și `dmax = -1`. De ce aceeași inițializare **nu** produce niciodată rezultatul ăsta la #181?

**3.** La subiectul III ai scris `if (v[i] < min)`. Pe vectorul `(8, 6, 2, 7, 2, 4)` minimul apare de două ori. Ce afișează programul tău, și ce ar fi afișat dacă puneai `<=` în loc de `<`? Sunt ambele răspunsuri acceptate de enunț — dar spune-mi care poziție reține fiecare variantă și de ce.

---

## Ce a mers — pe bune

Nu sunt umpluturi; astea sunt verificate prin rulare:

- **Garda `j + 1 < d &&` e corectă în toate cele 20 de probleme.** Întâi întrebi dacă ai voie să citești, apoi citești. Zero citiri în afara vectorului confirmate cu AddressSanitizer.
- **#854** (secvențe disjuncte cu cel mult `k` impare) — soluția greedy cu `nrImp = 1` la reset e exact cea corectă, inclusiv garda `if (n == 0)`. E cea mai grea problemă din fișier.
- **#578** — formula `l * (l + 1) / 2` pentru numărul de subsecvențe dintr-un bloc de lungime `l`. Ai văzut structura combinatorială în loc să numeri cu trei bucle.
- **#523 vs #518** — `>=` unde vrei „cea mai din dreapta", `>` unde vrei „cea mai din stânga". Ai luat corect ambele sensuri, a doua oară la rând.
- **#300** — fereastră glisantă cu doi indici, nu două bucle imbricate. Ai trecut de la `O(n²)` la `O(n)` fără să ți se ceară.
- **Subiectul II c)** — traducerea din pseudocod în C++ e impecabilă, inclusiv `if (n != 1)` de la final, care e partea pe care cei mai mulți o ratează.
- **Subiectul III (`3a5377e`)** — l-ai dus singur la capăt, corect pe ambele exemple din enunț și pe cinci cazuri-limită pe care le-am aruncat eu în el. Vezi B4.

Următorul pas: **rulează fiecare funcție înainte de commit.** Trei din cele patru probleme critice rămase s-ar fi văzut într-o singură rulare a lui `main()` cu toate `solutieXXX()` apelate pe rând — `0`, `-2000000000` și nimic afișat sar în ochi imediat. Exact ce ai făcut, de altfel, la subiectul III: acolo ai rulat, ai văzut că iese „9", și l-ai terminat.
