# Code Review — victor-vectori · `tema6.h` + fix-urile la review-ul anterior

Review pe `826f748` → `ebd8da1` (commit-urile `finish tema 6 ex1->ex4`, `finish t6`). Fișiere: `vectori/tema6.h` (359 linii, nou), plus modificările din `vectori/tema5.h` și `vectori/exercitiiBac.h` ca răspuns la review-ul precedent.

Codul NU a fost modificat — totul e doar aici. Toate constatările sunt **verificate prin compilare și rulare** (clang++ `-std=c++17 -Wall -Wextra`, cu AddressSanitizer și UndefinedBehaviorSanitizer), nu doar prin citire.

> **Verdictul pe scurt — și e cel mai bun de până acum.**
>
> **`tema6.h`: toate cele 8 probleme dau răspunsul corect pe datele din cod.** Nu 14 din 20, nu „corect din noroc" — 8 din 8, verificate prin rulare, cu zero erori de sanitizer. Fișierul se compilează cu `-Wall -Wextra` fără **niciun** warning. Asta nu ți s-a mai întâmplat.
>
> Și mai important: **ai început să tratezi cazul „n-am găsit nimic"** — `if (dmax != -1)` apare la 4 din cele 5 funcții de secvențe, cu mesaj explicit pe ramura `else`. Exact santinela pe care ți-am semnalat-o de două ori. De data asta ai aplicat-o **preventiv**, nu ca reparație.
>
> Ce a rămas — și tiparul e nou, mai fin decât înainte:
>
> 1. **Două bug-uri reale în `tema6.h`**, ambele pe *domeniul de valori*, nu pe algoritm: negativele la paritate (B1) și zeroul la dublete (B2). Algoritmii sunt corecți; presupunerea despre ce intră în vector e greșită.
> 2. **B1 din review-ul trecut e închis corect** (`do...while`), dar **#522 și #4148 le-ai rescris și au ieșit tot greșite**, iar la #522 ai introdus un **buffer overflow real** — cu garda pusă invers, exact regula pe care o aplicai corect în celelalte 20 de funcții. Vezi B3 și B4.
> 3. **#297 nu l-ai atins deloc** — încă nu afișează nimic.
>
> Firul roșu de anul ăsta se schimbă: nu mai e „repari linia, nu regula". Acum e **„rescrii funcția de la zero în loc s-o repari"** — și la rescriere pierzi garda pe care o aveai deja corectă. Vezi secțiunea *Ce s-a schimbat în tipar*, la final.

---

# Partea I — `tema6.h` (lucrul nou)

## 🔴 Critice

### B1 — Paritatea comparată prin `%` se rupe pe numere negative (#8)

`tema6.h:328`

```cpp
while (j + 1 < d && (v[j] % 2 != v[j + 1] % 2)) {
```

În C++, `%` păstrează semnul deîmpărțitului: `-3 % 2` dă **`-1`**, nu `1`. Deci pentru două numere **amândouă impare**, unul negativ și unul pozitiv, comparația devine `-1 != 1` → **adevărat** → codul le declară „de parități diferite".

**Verificat prin rulare**, pe `v = {-3, 5, -7, 9}` — toate patru sunt impare, deci cea mai lungă secvență de parități alternante are lungimea **1**:

```
secventa = -3 5 -7 9 lungime: 4
```

Codul găsește o secvență alternantă de lungime 4 într-un vector în care nu există niciuna.

**Ce înveți — și de ce e a treia oară.** Ți-am semnalat `% 2 == 1` pe negative în review-ul de la `secvente.h`. Acolo l-ai reparat. Aici apare **în altă formă**: nu mai compari cu `1`, compari două resturi între ele — și tot pe `%` cade. Regula nu e „nu scrie `% 2 == 1`", regula e **`%` nu îți dă paritatea unui întreg cu semn, îți dă restul**. Forma care ține la orice semn:

```cpp
v[j] % 2 != 0   // "e impar", pentru orice int
```

și pentru „au parități diferite", compari cele două *predicate booleene*, nu cele două resturi:

```cpp
(v[j] % 2 != 0) != (v[j + 1] % 2 != 0)
```

Dacă enunțul garantează numere naturale, codul tău merge — dar atunci scrie asta în comentariu, ca să fie o decizie, nu un accident.

---

### B2 — Bucla de căutare a dubletului începe de la 1 și pierde valoarea 0 (#3)

`tema6.h:95`

```cpp
for (int i = 1; i <= 100; i++) {
    if (f[i] >= 2) { vf = i; break; }
}
```

Vectorul de frecvențe e `int f[101]`, indexat `0..100`, iar la numărare (`tema6.h:90`) folosești corect `f[v[i]]++` — deci `f[0]` **se completează**. Dar la căutare pornești de la `i = 1`, așa că `f[0]` nu e citit niciodată.

**Verificat prin rulare**, pe `v = {0, 5, 0, 7}` — zeroul apare de două ori:

```
Nu exista dublete
```

**Ce înveți.** Bug-ul e de o singură cifră, dar cauza e că ai două bucle peste același domeniu și ele nu pornesc din același loc: una din `0`, cealaltă din `1`. Când folosești un vector de frecvențe, **scrie limitele o singură dată** și refolosește-le, nu le rescrie la fiecare buclă:

```cpp
const int VMAX = 100;
int f[VMAX + 1] = { 0 };
for (int i = 0; i <= VMAX; i++) { ... }   // aceleasi limite, peste tot
```

Reflexul de verificat: *„domeniul din care citesc e același cu domeniul în care am scris?"*

---

## 🟡 Importante

### M1 — `>=` la unele funcții, `>` la altele: reții când prima, când ultima secvență

Cinci funcții din `tema6.h` caută „cea mai lungă secvență". Comparația de la înlocuirea maximului nu e aceeași:

| problemă | linie | comparație | ce reține la egalitate |
|---|---|---|---|
| #1 crescătoare | `tema6.h:22` | `if (j - i >= dmax - smax)` | **ultima** |
| #4 sumă cifre egală | `tema6.h:146` | `if (j - i >= dmax - smax)` | **ultima** |
| #6 pare | `tema6.h:244` | `if (j - i > dmax - smax)` | **prima** |
| #7 distincte | `tema6.h:289` | `if (d - i > dmax - smax)` | **prima** |
| #8 parități alternante | `tema6.h:332` | `if (j - i > dmax - smax)` | **prima** |

**Verificat prin rulare**, pe vectori construiți special cu două secvențe de lungime egală:

```
#1 v={5,9,1,7}          -> secventa = 1 7        (a retinut ULTIMA)
#4 v={11,20,7,13,31}    -> secventa: 13 31       (a retinut ULTIMA)
#6 v={2,4,9,6,8}        -> incepe pe pozitia 0   (a retinut PRIMA)
#8 v={4,7,4,4,9,2}      -> secventa = 4 7 4      (a retinut PRIMA)
```

Ambele variante sunt corecte ca lungime. Dar enunțurile de tipul ăsta cer aproape întotdeauna **prima** secvență, iar la corectare asta se punctează.

**Ce înveți.** La review-ul de la `secvente.h` te-am lăudat fix pentru asta: la #523 ai folosit `>=` și la #518 `>`, pentru că unul cerea „cea mai din dreapta" și celălalt „cea mai din stânga" — un caracter, ales conștient, în două sensuri opuse. Aici ai amestecat cele două variante **în același fișier**, fără ca vreun enunț să ceară asta. Nu e greșeală de C++, e o alegere care nu s-a făcut. Alege `>` peste tot (= prima), și pune `>=` doar unde enunțul cere explicit ultima.

---

### M2 — `int d = j - 1;` ascunde parametrul `d` al funcției (#7)

`tema6.h:287`

```cpp
void ceaMaiLungaSecventaElementeDistincte(int v[], int d) {   // <- d = dimensiunea
    for (int i = 0; i < d; i++) {
        ...
        while (j < d && f[v[j]] == 0) { ... }   // aici d = dimensiunea, corect
        int d = j - 1;                          // <- ALT d, ultimul indice
        if (d - i > dmax - smax) { ... }        // aici d = j - 1
    }
```

Ai două variabile diferite cu același nume în aceeași funcție: parametrul (dimensiunea vectorului) și una locală (ultimul indice al secvenței). Se numește **shadowing**.

**Funcționează** — și am verificat că răspunsul e corect — dar doar pentru că declarația de la `:287` vine *după* buclele care folosesc `d`-ul cel bun. Compilatorul rezolvă numele în ordinea în care le vede. Dacă mai târziu muți `int d = j - 1;` cu trei linii mai sus, sau adaugi un `while (j < d)` sub ea, `d` devine tăcut altceva și bucla ori nu mai pornește, ori nu se mai oprește. Nu ai niciun warning care să te avertizeze.

**Ce înveți.** Numele unei variabile e documentație. `d` înseamnă „dimensiune" în tot proiectul tău — în toate cele 6 fișiere. Când ai nevoie de ultimul indice, numește-l `ultim` sau `sfarsit`. Regula generală: **într-o funcție, un nume = un lucru**. Alternativ, aici nici nu-ți trebuie variabila: `if (j - 1 - i > dmax - smax)`.

---

### M3 — Poziția afișată e 0-indexată, spre deosebire de restul proiectului (#6)

`tema6.h:257`

```cpp
cout << "cea mai lunga are lungimea " << lungimeMax << " si incepe pe pozitia " << smax << endl;
```

**Verificat prin rulare** pe `v = {3,8,4,6,7,2,5,10,12,14,16,9}`:

```
cea mai lunga are lungimea 4 si incepe pe pozitia 7
```

Secvența `10 12 14 16` începe la indicele 7, adică pe **poziția 8** dacă numeri de la 1. În `tema5.h` ai `smax + 1` peste tot (`:572`, `:737`), pentru că pbinfo numerotează de la 1. Aici afișezi indicele brut.

Care e corect depinde de enunț — și enunțul lipsește (vezi M6). Dar în aceeași temă nu poți avea două convenții.

---

### M4 — #1 e singura funcție de secvențe fără santinelă

`tema6.h:29-35`

La #4 (`:155`), #6 (`:255`), #7 (`:296`) și #8 (`:341`) ai pus `if (dmax != -1)` cu mesaj explicit pe `else` — corect, e exact ce ți-am cerut. La #1 nu:

```cpp
cout << "secventa = ";
for (int k = smax; k <= dmax; k++) { ... }   // nu ruleaza daca dmax == -1
cout << "Lungime = " << ct;                  // afiseaza 0
```

Pe un vector cu cel puțin un element nu se vede niciodată, pentru că orice element singur e o secvență strict crescătoare validă — deci `dmax` se setează mereu. Dar e singurul loc din fișier unde regula ta nu se aplică. Aliniază-l: patru din cinci au forma bună, a cincea trebuie s-o aibă și ea.

---

### M5 — La #5, „nu există cifre comune" și „singura cifră comună e 0" afișează amândouă `0`

`tema6.h:204` și `:209-214`

```cpp
nr = nr * 10 + c;         // pentru c = 0:  nr = 0 * 10 + 0 = 0
...
if (cifComune) { cout << "numarul format = " << nr << endl; }
else           { cout << "0" << endl; }
```

**Verificat prin rulare**, pe `v = {101, 203, 50}` — singura cifră prezentă în toate trei este `0`:

```
numarul format = 0
```

Care e și ce ar afișa dacă n-ar exista nicio cifră comună. Cele două situații sunt diferite și nu se pot deosebi din output.

În plus, cifra `0` la început se pierde din construcție: dacă cifrele comune sunt `0` și `5`, `nr` devine `0 * 10 + 0 = 0`, apoi `0 * 10 + 5 = 5` — afișezi `5`, nu `05`. E o limitare reală a reprezentării ca `int`; dacă enunțul cere cifrele în ordine, construiește un `string` sau afișează-le direct în bucla de la `:202`, fără să le mai împachetezi într-un număr.

**Ce înveți.** Mesajul de pe ramura `else` trebuie să spună *ce s-a întâmplat*, nu să afișeze o valoare care poate apărea și pe ramura cealaltă. `cout << "nu exista cifre comune" << endl;` — o secundă de scris, și cele două cazuri nu se mai confundă niciodată.

---

### M6 — `tema6.h` nu are enunțurile problemelor în comentarii

`tema6.h:9`, `:46`, `:85`, `:119`, `:174`, `:227`, `:272`, `:320` — toate opt sunt doar `//1`, `//2`, `//3`…

În `tema2.h` … `tema5.h` ai pus de fiecare dată enunțul complet deasupra funcției:

```cpp
//166
//Să se determine cea mai lungă secvență de elemente pare dintr-un vector.
```

Aici nu. Consecința practică e imediată: **la M3 nu pot să-ți spun dacă poziția trebuie afișată de la 0 sau de la 1, pentru că nu știu ce cere problema.** Peste trei luni, când recapitulezi pentru bac, nici tu n-o să știi ce cerea #5 — o să trebuiască să deduci enunțul din propriul cod, ceea ce e exact pe dos.

Ai făcut, în schimb, un lucru bun pe care nu-l aveai înainte: **tabelul de urmărire** de la `tema5.h:95-100`. Ține-l — dar pune și enunțul deasupra lui.

---

### M7 — `f[101]` presupune elemente în `0..100`, fără nicio verificare

`tema6.h:87` (#3) și `tema6.h:278` (#7)

```cpp
int f[101] = { 0 };
...
f[v[i]]++;      // :90
f[v[j]] = 1;    // :283
```

Dacă vectorul conține un element negativ sau mai mare ca 100, scrii în afara lui `f` — memorie care nu-ți aparține. Pe datele tale nu se întâmplă, și AddressSanitizer confirmă că **acum** nu se iese nicăieri. Dar e o presupunere nescrisă.

Vectorul de frecvențe e unealta corectă aici (transformă o căutare `O(n²)` într-una `O(n)`) — doar că vine cu o condiție: **valorile trebuie să încapă în indici**. Scrie condiția, măcar ca `const int VMAX = 100;` plus un comentariu cu domeniul din enunț.

---

## 🟢 Cleanups (`tema6.h`)

- **C1** — `tema6.h:344-346` (#8): lipsește `endl` după bucla de afișare, așa că lungimea se lipește de secvență. Verificat: `secventa = 6 3 8 5 12 7 lungime: 6`. La #4 (`:161`) și #7 (`:304`) ai pus `cout << endl;` corect.
- **C2** — `tema6.h:35` (#1): `cout << "Lungime = " << ct;` — fără `endl` la final, deci următorul afișaj continuă pe aceeași linie.
- **C3** — `tema6.h:13,32,35` (#1): `ct` numără elementele *în bucla de afișare*. Lungimea o știi deja: `dmax - smax + 1`, formula pe care o folosești la #4 (`:162`), #6 (`:256`), #7 (`:305`) și #8 (`:346`). Variabila și incrementul se pot șterge.
- **C4** — `tema6.h:47-73` (#2) și `tema6.h:175-197` (#5) conțin același bloc, literă cu literă: `int f[10] = {0}`, tratarea lui `aux == 0`, bucla de extras cifre. Scrie-l o dată ca `void cifreleLui(int n, int f[])` și cheamă-l din amândouă.
- **C5** — `tema6.h:6`: `//5,7` — o notiță rămasă din lucru. Șterge-o sau explic-o.

---

# Partea a II-a — ce s-a întâmplat cu review-ul anterior

## ✅ Închis corect

### B1 (review anterior) — `do...while` la subiectul II d)

`exercitiiBac.h:111` — `while (n % d != 0);` → `while (n % d == 0);`

**Verificat prin rulare**, aceeași intrare pe c) și d):

```
c) n=8    -> 1     d) n=8    -> 1     ✅
c) n=12   -> 2     d) n=12   -> 2     ✅
c) n=2600 -> 3     d) n=2600 -> 3     ✅
```

Un caracter, și subiectul II e complet. Aici ai făcut exact ce trebuia: **ai reparat linia semnalată, fără să rescrii funcția**. Ține minte contrastul ăsta când citești B3 și B4 de mai jos.

### #2921 — funcția goală a devenit funcție care calculează

`tema5.h:635-670`. Bucla `for (int k = 0; k < m; k++) { }` era literalmente goală și afișa `-2000000000`. Acum citește `m` perechi de indici, le convertește din numerotarea de la 1, tratează și cazul `i > j` prin interschimbare, și ține maximul.

**Verificat prin rulare** pe `v = {7, 9, -6, 1, -8}` cu perechile `(1,2)`, `(3,5)`, `(1,5)`:

```
Suma din secventa i->j este 16
Suma din secventa i->j este -13
Suma din secventa i->j este 3
Suma maxima obtinuta din perechi este: 16
```

Corect. Vezi totuși M8 mai jos — ai șters ideea bună odată cu bucla goală.

---

## 🔴 Rămase deschise sau reintroduse

### B3 — #522 rescris: nu mai răspunde la întrebarea din enunț

`tema5.h:101-123`

Enunțul, chiar din comentariul tău de la `:95`: *„Să se stabilească dacă în vector există două secvențe de lungime k **identice**."* Adică două ferestre de lungime `k` care, element cu element, conțin aceleași valori — cum era chiar vectorul tău de test de dinainte, `{1,2,3,4,2,3,4,5}` cu `k = 3`, unde `(2,3,4)` apare de două ori.

Codul nou numără cu totul altceva: **grupuri de elemente egale între ele** (`v[i] == v[j]`) de lungime exact `k`, și răspunde „DA" dacă găsește două astfel de grupuri — **fără să compare vreodată grupurile între ele**.

**Verificat prin rulare**, patru vectori:

```
v={7,7,7,7,1,5,5,5} k=3 -> NU   (asteptat DA: (7,7,7) apare la poz 0 SI la poz 1)
v={1,2,3,1,2,3}     k=3 -> NU   (asteptat DA: (1,2,3) de doua ori)
v={3,3,3,5,6,6,6}   k=3 -> DA   (asteptat NU: (3,3,3) si (6,6,6) nu sunt identice)
v={4,4,4,9,4,4,4}   k=3 -> DA   (asteptat DA)                                  ✅
```

Trei din patru greșite, și greșite **în ambele sensuri** — și „DA" fals, și „NU" fals. Pe datele tale din `solutie522` iese „DA", dar răspunsul corect acolo este **NU**: `(3,3,3)` și `(6,6,6)` sunt două secvențe de lungime 3, dar nu sunt identice **între ele**.

Două defecte separate, ambele vizibile în tabelul de mai sus:

1. **Nu compari niciodată două secvențe.** `nrSec >= 2` întreabă „am găsit două grupuri?", nu „am găsit două grupuri **la fel**?". De aici linia 3.
2. **`if (ct == k)` în loc de `ct >= k`.** Un grup de 4 elemente egale conține două ferestre de lungime 3, ambele identice — deci răspunsul e „DA" chiar și fără să ieși din grup. Cu `==`, grupul de 4 nu se numără deloc. De aici linia 1.

**Ce înveți.** Ai avut o funcție cu un `//???` în ea — semn că știai ce lipsește: *comparația a două secvențe*. La rescriere ai construit un algoritm nou care evită complet comparația aia. E cel mai frecvent mod de a te bloca: în loc să scrii bucata grea (o buclă de `k` pași care compară `v[i+t]` cu `v[j+t]`), construiești în jurul ei ceva ce știi deja să scrii — numărat de grupuri egale. Rezultatul rulează, dar răspunde la altă întrebare.

Când te blochezi la o bucată, **izoleaz-o într-o funcție cu nume și rezolv-o singură**, pe hârtie, pe doi indici concreți. `bool egale(int v[], int i, int j, int k)` are patru linii.

---

### B4 — 🔴 REGRESIE: garda pusă invers la #522 → citire în afara vectorului

`tema5.h:110`

```cpp
while (v[i] == v[j] && j < d) {
```

Întâi citești `v[j]`, **apoi** întrebi dacă `j` e valid. Când grupul de elemente egale ajunge până la ultimul element, `j` ajunge la `d` și `v[d]` se citește oricum.

**Verificat cu AddressSanitizer**, pe un vector dimensionat exact (`int v[6]`, nu `int v[100]`):

```
==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x00016baee9d8
READ of size 4 at 0x00016baee9d8 thread T0
    #0 secventeIdentice(int*, int, int) tema5.h:110
This frame has 2 object(s):
    [32, 56) 'v' (line 7) <== Memory access at offset 56 overflows this variable
```

În Visual Studio nu vezi nimic, pentru că declari `int v[100]` și restul e zero — citești un `0` care nu-ți aparține și mergi mai departe. Dar e o citire în afara vectorului, iar la pbinfo, unde vectorul e dimensionat exact, e sursă clasică de „Wrong answer" sau crash.

Corect, ordinea inversată:

```cpp
while (j < d && v[i] == v[j]) {
```

**Ce înveți — și de asta e cea mai importantă constatare din review.** Garda asta o ai **corectă în toate celelalte funcții din proiect**: `tema5.h:600`, `tema6.h:18`, `:142`, `:237`, `:282`, `:328` — peste 25 de locuri, toate cu `j + 1 < d &&` pus primul. Te-am lăudat pentru ea în trei review-uri la rând. Singurul loc unde apare inversată e **singura funcție pe care ai rescris-o de la zero**.

Asta îți spune ceva concret despre cum lucrezi: **regula e în reflex când continui, și cade când repornești.** Când scrii cod nou de la zero, mintea e ocupată cu algoritmul și rulează pe pilot automat pe restul. Contramăsura nu e „ai grijă mai mult" — e mecanică: **după ce scrii o buclă `while` care indexează un vector, citește-o o dată doar pentru gardă**, înainte să rulezi. Trei secunde, o singură întrebare: *„am voie să citesc, înainte să citesc?"*

---

### B5 — #4148: `ct` nu se resetează când apare un maxim nou

`tema5.h:605-611`

```cpp
if (lungime > lmax) {
    lmax = lungime;
    ct++;          // <- ar trebui ct = 1
}
else if (lungime == lmax) {
    ct++;
}
```

Când găsești o secvență **mai lungă** decât maximul de până acum, toate secvențele numărate înainte devin irelevante — nu mai sunt de lungime maximă. Numărătoarea trebuie să repornească de la 1, nu să continue.

**Verificat prin rulare:**

```
--- pe datele tale v={12,20,30,40,7,50,60,13,90,100} ---
Lungimea max = 3
nr de secvente de lungime maxima = 1          ✅ corect

--- cu maximul la FINAL: v={10,7,20,30,40} ---
Lungimea max = 3
nr de secvente de lungime maxima = 2          ❌ corect ar fi 1
```

Pe `{10, 7, 20, 30, 40}`: prima secvență `(10)` are lungimea 1 → `lmax = 1`, `ct = 1`. Apoi `(20,30,40)` are lungimea 3 → `3 > 1`, deci `lmax = 3` și `ct++` → **`ct = 2`**. Dar secvențe de lungime 3 există **una singură**; pe cea de lungime 1 tocmai ai declasat-o.

Pe datele tale nu se vede, pentru că **secvența cea mai lungă e prima din vector** — după ea nu mai apare niciun maxim nou, deci resetarea n-ar avea ce să reseteze.

**Ce înveți.** E același tipar ca la „14 din 20 corecte, dar unele din noroc" din review-ul trecut: datele de test alese confirmă codul în loc să-l pună la încercare. Când scrii un „maxim + câte de maxim", **testul obligatoriu e cel cu maximul la sfârșit** — el e singurul care execută resetarea. Regulă de reținut, valabilă la orice problemă de tipul ăsta:

```cpp
if (lungime > lmax) { lmax = lungime; ct = 1; }   // maxim nou -> repornesc numaratoarea
else if (lungime == lmax) { ct++; }               // inca unul la fel -> adaug
```

---

### B6 — #297 nu a fost atins: încă nu afișează nimic

`tema5.h:755-775`

Neschimbat față de review-ul trecut. `smax` e declarat la `:758` și nu e actualizat nicăieri, `dmax` e setat la `:771` dar nu e citit niciodată, iar funcția **nu are niciun `cout`**.

**Verificat prin rulare:**

```
=== #297 (Kadane) ===
[sfarsit 297]          <-- nimic intre marcaje
```

Compilatorul îți spune direct:

```
tema5.h:758:9: warning: unused variable 'smax'
tema5.h:759:9: warning: variable 'dmax' set but not used
```

Partea grea — algoritmul lui Kadane, `if (suma < 0) suma = v[i];` — e scrisă corect. Îți lipsesc trei linii: o variabilă `start` care reține unde a repornit suma, `smax = start` la actualizarea maximului, și un `cout` la final. Ai before/after-ul complet în `CODE_REVIEW_TEMA5_BAC.md`, la secțiunea B3.

---

## 🟡 Importante — rămase din review-ul anterior, netratate

### M8 — La #2921 ai șters sumele parțiale, care erau ideea corectă

`tema5.h:635-670`

Aveai construit vectorul de sume parțiale:

```cpp
int sp[100] = { 0 };
for (int i = 1; i <= d; i++) { sp[i] = sp[i - 1] + v[i]; }
```

L-ai șters odată cu bucla goală, și acum aduni la fiecare interogare, cu o buclă:

```cpp
for (int j = stanga; j <= dreapta; j++) { suma += v[j]; }
```

Răspunsul e corect — dar ai trecut de la `O(m + n)` la `O(m · n)`. Pentru pbinfo 2921, unde `n` și `m` merg la sute de mii, asta e diferența dintre „Accepted" și „Time limit exceeded". **Sumele parțiale sunt tot subiectul problemei ăsteia** — cu `sp` construit, fiecare interogare e o scădere:

```cpp
suma = sp[dreapta + 1] - sp[stanga];
```

**Ce înveți.** Când o funcție e pe jumătate, partea scrisă nu e automat partea de aruncat. Aici aveai ideea grea deja pe hârtie și îți lipsea doar bucla de interogări — ai șters-o pe cea bună și ai rescris-o pe cea ușoară. Înainte să ștergi, întreabă-te: *„ce am aici e greșit, sau doar neterminat?"*

### M9 — Neschimbate din review-ul precedent

Le reiau pe scurt, cu linia actualizată — toate sunt încă deschise:

| # | ce | unde acum | stare |
|---|---|---|---|
| M1 | `tema5.h` și `secvente.h` nu pot fi incluse în același program: `nr1InBaza2` (`secvente.h:156` / `tema5.h:500`), `solutie516` (`:76` / `:456`), `solutie523` (`:145` / `:230`), `solutie981` (`:194` / `:518`) | — | deschis |
| M2a | `% 2 == 1` supraviețuiește în copiile nesemnalate: `tema5.h:506`, `MunteVale.h:145`, `realizareaUnuiNouVector.h:644` | — | deschis |
| M2b | #166: santinela netratată — `smax++; dmax++;` fără `if (dmax == -1)` | `tema5.h:308-310` | deschis |
| M3 | #524: lipsește separatorul, afișează `411` în loc de `4 11` | `tema5.h:572` | deschis |
| M4 | `d` nu corespunde numărului de elemente (#300, #297) | `tema5.h:392`, `:778` | deschis |
| M6 | Subiectul III cere citire de la tastatură, nu vector fix | `exercitiiBac.h:137-138` | deschis |

M2a merită subliniat încă o dată, pentru că e exact contra-exemplul lui B4: acolo ai pierdut o regulă la rescriere, aici o regulă reparată o dată **n-a fost căutată** în restul proiectului. `Ctrl+Shift+F` pe `% 2 == 1`, în tot proiectul, îți dă cele trei locuri în două secunde.

---

# Before / After (doar criticele — NU aplicat în cod)

### B1 — `tema6.h:328` (paritate pe negative)

| acum | corect |
|---|---|
| <pre>while (j + 1 &lt; d &&<br>       (v[j] % 2 != v[j+1] % 2)) {<br>    j++;<br>}</pre> | <pre>while (j + 1 &lt; d &&<br>       ((v[j] % 2 != 0) != (v[j+1] % 2 != 0))) {<br>    j++;<br>}</pre> |

### B2 — `tema6.h:95` (zeroul pierdut)

| acum | corect |
|---|---|
| <pre>for (int i = 1; i &lt;= 100; i++) {<br>    if (f[i] &gt;= 2) { vf = i; break; }<br>}</pre> | <pre>for (int i = 0; i &lt;= 100; i++) {<br>    if (f[i] &gt;= 2) { vf = i; break; }<br>}</pre> |

### B3 + B4 — `tema5.h:101-123` (#522: comparația care lipsește + garda inversată)

| acum | corect |
|---|---|
| <pre>bool secventeIdentice(int v[], int d, int k) {<br>  int nrSec = 0;<br>  for (int i = 0; i &lt; d-1; i++) {<br>    if (v[i] == v[i+1]) {<br>      int j = i+1, ct = 1;<br>      while (v[i] == v[j] && j &lt; d) {<br>        ct++; j++;<br>      }<br>      if (ct == k) nrSec++;<br>      i = j - 1;<br>    }<br>  }<br>  return nrSec &gt;= 2;<br>}</pre> | <pre>bool egale(int v[], int i, int j, int k) {<br>  for (int t = 0; t &lt; k; t++)<br>    if (v[i+t] != v[j+t]) return false;<br>  return true;<br>}<br><br>bool secventeIdentice(int v[], int d, int k) {<br>  for (int i = 0; i + k &lt;= d; i++)<br>    for (int j = i+1; j + k &lt;= d; j++)<br>      if (egale(v, i, j, k)) return true;<br>  return false;<br>}</pre> |

Observă ce dispare în varianta din dreapta: `nrSec`, `ct`, `i = j - 1` și garda cu totul. Nu mai ai nevoie de gardă în `egale`, pentru că limitele buclelor (`i + k <= d`) garantează deja că `v[i+t]` și `v[j+t]` sunt în vector. **Cea mai sigură gardă e cea de care nu mai ai nevoie.**

### B5 — `tema5.h:605-611` (#4148: resetarea numărătorii)

| acum | corect |
|---|---|
| <pre>if (lungime &gt; lmax) {<br>    lmax = lungime;<br>    ct++;<br>}<br>else if (lungime == lmax) {<br>    ct++;<br>}</pre> | <pre>if (lungime &gt; lmax) {<br>    lmax = lungime;<br>    ct = 1;<br>}<br>else if (lungime == lmax) {<br>    ct++;<br>}</pre> |

---

# Ce s-a schimbat în tipar

Merită spus explicit, pentru că e o veste bună îngropată sub 🔴-uri.

**Tiparul vechi era „repari linia, nu regula".** L-am scris în trei review-uri la rând: reparai apariția semnalată și lăsai celelalte apariții ale aceleiași greșeli neatinse. Tiparul ăla **s-a redus, dar n-a dispărut** — M2a e ultima lui urmă (`% 2 == 1` încă în trei fișiere), și e o urmă mecanică, ușor de închis cu un `Ctrl+Shift+F`.

**Tiparul nou e altul: la rescriere pierzi ce aveai corect.** Se vede în trei locuri, toate în această rundă:

| ai atins | cum | rezultat |
|---|---|---|
| `exercitiiBac.h` sub2 d) | **ai reparat linia** (un caracter) | ✅ corect |
| #522 | **ai rescris funcția** de la zero | ❌ alt algoritm + gardă inversată (B3, B4) |
| #4148 | ai adăugat peste ce era | ❌ resetare lipsă (B5) |
| #2921 | **ai rescris funcția** de la zero | ✅ corect, dar ai șters sumele parțiale (M8) |

Singurul lucru pe care l-ai **reparat** a ieșit perfect. Din cele două pe care le-ai **rescris**, unul e greșit și celălalt e mai slab decât ce aveai.

Asta nu înseamnă „nu mai rescrie". Înseamnă că, atunci când rescrii, **pierzi reflexele** — garda, sumele parțiale — pentru că atenția e la algoritm. Contramăsura, în ordinea asta:

1. **Înainte de a șterge**, întreabă-te: *ce am aici e greșit, sau doar neterminat?* (M8 s-ar fi evitat)
2. **După ce scrii o buclă nouă cu indici**, recitește-o o dată **doar pentru gardă**. (B4 s-ar fi evitat)
3. **Testul obligatoriu** la orice „maxim + de câte ori": pune maximul la **sfârșitul** vectorului. (B5 s-ar fi evitat)

Și, contra-argumentul cel mai puternic că merge: `tema6.h` — 359 de linii scrise de la zero, 8 din 8 corecte, zero warning-uri, santinela pusă preventiv la 4 din 5 funcții. Când scrii ceva nou **de la început**, în ritmul tău, iese curat. Problemele apar când te întorci peste cod vechi în grabă.

---

# Q&A — verifică-ți înțelegerea

**1.** În C++, `-3 % 2` dă `-1`. Pornind de la asta, explică de ce funcția de la #8 spune că `-3` și `5` au parități diferite, deși amândouă sunt impare. Apoi: de ce **aceeași** problemă **nu** apare la #6 (`v[i] % 2 == 0`), deși și acolo folosești `%` pe numere care ar putea fi negative?

**2.** La #4148, pe vectorul `{10, 7, 20, 30, 40}` codul tău afișează `nr de secvente de lungime maxima = 2`, iar pe `{12,20,30,40,7,50,60,13,90,100}` afișează `1`, corect. Urmărește `lmax` și `ct` pas cu pas pe **primul** vector și spune exact la ce secvență se strică numărătoarea. Apoi: construiește tu un vector pe care codul afișează `3` în loc de `1`.

**3.** La #522, garda scrisă `while (v[i] == v[j] && j < d)` citește în afara vectorului, dar în Visual Studio programul pare că merge. Explică de ce nu se vede — ce e la `v[d]` în `int v[100] = {1,3,3,3,5,2,6,6,6,4,2}`? Și de ce varianta corectă din tabelul Before/After (`egale` cu `i + k <= d`) **nu are nevoie de nicio gardă** înăuntru?

---

# Ce a mers — pe bune

Verificate prin rulare, nu umplutură:

- **`tema6.h`: 8 din 8 corecte pe datele din cod.** Cea mai bună rundă de până acum, la distanță. Compilare cu `-Wall -Wextra`: **zero warning-uri** — singurul fișier din proiect care reușește asta.
- **Zero erori de sanitizer în tot `tema6.h`** — nicio citire în afara vectorului, niciun comportament nedefinit, pe toate cele 8 probleme plus 8 cazuri-limită construite special.
- **Santinela aplicată preventiv.** `if (dmax != -1)` cu mesaj explicit la #4, #6, #7, #8 — patru din cinci funcții de secvențe, scrisă din prima, nu ca reparație. Asta e diferența dintre „am corectat ce mi-a zis" și „am înțeles regula".
- **#7 (secvență de elemente distincte)** e cea mai grea problemă din temă și ai luat-o corect, inclusiv partea contraintuitivă: aici **nu** ai voie să faci `i = j`, cum faci la toate celelalte, pentru că fereastra următoare poate începe înăuntrul celei curente. E singura funcție din fișier fără salt — și e exact unde trebuia să lipsească.
- **#5 (cifre comune tuturor numerelor)** — `ct[c] == d` ca test de „apare peste tot" e soluția elegantă. Alternativa la care ajung majoritatea e o intersecție refăcută la fiecare pas; tu ai numărat o dată și ai comparat cu `d`.
- **#2 și #5 tratează corect `aux == 0`** înainte de bucla de extras cifre — cazul pe care îl uită aproape toată lumea, pentru că `while (aux != 0)` nu se execută deloc pentru zero.
- **Tabelul de urmărire de la `tema5.h:95-100`** — ți-ai desenat singur execuția pe hârtie, cu coloane pe variabile, fără să ți-o ceară nimeni. E fix instrumentul care ți-ar fi arătat B5 (`ct` nesetat pe resetare) într-un minut. Folosește-l și când **verifici**, nu doar când scrii.
- **`exercitiiBac.h` sub2 d)** — reparat cu un singur caracter, exact linia semnalată, fără efecte laterale. Vezi secțiunea *Ce s-a schimbat în tipar*: e singura modificare din rundă care a ieșit perfect.

**Următorul pas, în ordinea asta:** B4 (garda — 10 secunde), B5 (`ct = 1` — 10 secunde), B2 (`i = 0` — 10 secunde), B1 (paritatea — o linie), apoi B6 (#297, trei linii, ai before/after-ul gata), și la final B3 (#522, singurul care cere gândit de la capăt). Cinci din șase sunt sub un minut fiecare.
