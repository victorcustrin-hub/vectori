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
