# Code Review — victor-vectori

Un singur fișier, runda cea mai nouă sus. Rundele vechi rămân dedesubt.

## Runde anterioare — index

| rundă | subiect | fișier | stare |
|---|---|---|---|
| 7 | `cautareBinara.h` | *(aici, mai jos)* | 2 🔴 deschise |
| 6 | `tema6.h` + fix-uri tema5/bac | `CODE_REVIEW_TEMA6.md` | 🔴 B1–B6 **toate deschise**, 🟡 M2a deschis |
| 5 | tema5 + bac 2026 | `CODE_REVIEW_TEMA5_BAC.md` | preluate în runda 6 |
| 4 | `secvente.h` | `CODE_REVIEW_SECVENTE.md` | ✅ închis |
| 1–3 | vectori (fix-uri runde 4+5) | *(mai jos, sub runda 7)* | ✅ închise |

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
