# Code Review — victor-vectori · modulul `secvente.h`

Review pe `d0e5a8f` → `a50991f` (commit-urile `secvente`, `finish frecvanta nr pare`, `finish pbinfo516`, `finish pbinfo 518+solutii`, `finish 523`). Fișier: `vectori/secvente.h`, patru funcții. Codul NU a fost modificat — totul e doar aici. Toate constatările sunt verificate prin compilare și rulare, cu AddressSanitizer.

> **Verdictul pe scurt.** Modulul ăsta e cel mai curat lucru pe care l-ai scris până acum. Toate cele patru funcții dau răspunsul corect pe datele din cod, iar trei lucruri arată că review-urile anterioare au prins:
>
> - **Garda e pusă în ordinea corectă peste tot**: `while (j + 1 < dim && v[j + 1] % 2 == 1)`. Întâi întrebi dacă ai voie, apoi citești. Exact ce lipsea la `solutie6` din `exercitiiRecapitulative.h`.
> - **Ai redenumit funcția**: era `ceaMaiLungaSevcentaDeNumerePare` peste un cod care caută impare. Acum numele și codul spun același lucru.
> - **La #523 ai folosit `>=` acolo unde la #518 ai folosit `>`** — și e exact diferența dintre „cea mai din stânga" și „cea mai din dreapta". Detaliu de un caracter, luat corect de două ori la rând, în două sensuri opuse. Vezi secțiunea de la final.
>
> Ce a mai rămas se împarte în două: o problemă reală de matematică pe care n-ai de unde s-o știi (`%` cu numere negative în C++), și o inconsecvență între funcții — fiecare tratează altfel cazul „n-am găsit nimic", iar doar una îl tratează corect.

---

## 🔴 Critice

### B1 — `% 2 == 1` nu recunoaște numerele impare negative

- `secvente.h:24` — `if (v[i] % 2 == 1)` în `ceaMaiLungaSecventaDeNumereImpare`
- `secvente.h:27` — `while (j + 1 < dim && v[j + 1] % 2 == 1)`
- `secvente.h:57` — `if (v[i] % 2 == 1)` în `secventaPrimulSiUltimulNumarImpar`

În C++, restul împărțirii **păstrează semnul deîmpărțitului**. Adică `-3 % 2` este `-1`, nu `1`. Testul `v[i] % 2 == 1` e fals pentru orice impar negativ, deci funcția îl tratează ca pe un număr par.

Verificat prin rulare, pe `v = {-3, -5, -7, 4}` — un vector care începe cu o secvență de trei impare:

```
[1] impare negative:  <-- nu afiseaza nimic
[2] impare negative:  Nu exista elemente impare in vector
```

Ambele funcții spun că nu există impare într-un vector format aproape numai din impare.

Enunțurile tale zic „numere naturale", deci pe pbinfo trece. Dar prima funcție e scrisă cu `int v[]`, care acceptă negative — iar în clasă o să primești vectori cu numere întregi.

**Ce înveți.** `%` în C++ nu e „restul de la școală". Definiția din matematică dă mereu un rest între 0 și 1 pentru împărțirea la 2; C++ garantează doar că `(a / b) * b + a % b == a`, ceea ce pentru negative iese cu semnul lui `a`. Concret:

| n | `n % 2` | `n % 2 == 1` | `n % 2 != 0` |
|---|---|---|---|
| 7 | `1` | ✅ adevărat | ✅ adevărat |
| −7 | `−1` | ❌ **fals** | ✅ adevărat |
| 4 | `0` | ❌ fals | ❌ fals |
| −4 | `0` | ❌ fals | ❌ fals |

Regula pe care o poți aplica mecanic: **pentru „e impar?" scrie `n % 2 != 0`, nu `n % 2 == 1`.** Testul de paritate e de fapt „restul nu e zero", iar zero e singura valoare care n-are semn. Pentru „e par?", `n % 2 == 0` e deja corect și pentru negative — de asta doar jumătate din teste au problema asta.

---

### B2 — `secventaElementeNuleMaxima` afișează poziția `-1` când nu există zerouri

- `secvente.h:87-88` — `int smax = 0;` și `int dmax = -1;`
- `secvente.h:105` — `cout << smax << " " << dmax;`

Cele două variabile pornesc de la `0` și `-1` ca să dea diferența `-1`, adică „încă n-am găsit nimic" — trucul e bun, fiindcă orice secvență găsită are `j - i >= 0`, deci câștigă sigur prima comparație. Problema e că, dacă vectorul **nu are niciun zero**, `if`-ul nu se execută niciodată și valorile inițiale ajung direct pe ecran.

Verificat pe `v = {2, 4, 6, 8}`:

```
[3] fara zerouri:     0 -1
```

`-1` nu e o poziție. Cine citește ieșirea nu are cum să știe dacă înseamnă „nu există" sau dacă programul s-a stricat.

Compară cu funcția de deasupra, `secventaPrimulSiUltimulNumarImpar:64`, unde ai făcut exact ce trebuia:

```cpp
if (primul != -1) {
    ...
}
else {
    cout << "Nu exista elemente impare in vector" << endl;
}
```

Acolo ai verificat santinela înainte s-o folosești. Aici nu.

**Ce înveți.** O valoare-santinelă (`-1`, „încă nimic") e utilă doar dacă e **întrebată** înainte de a fi folosită ca rezultat. Altfel nu e o santinelă, e o valoare greșită cu care ai plecat la drum. Verificarea e o singură linie:

```cpp
if (dmax == -1) {
    cout << "Nu exista secvente de elemente nule" << endl;
    return;
}
cout << smax << " " << dmax << endl;
```

Ce anume afișezi în cazul ăsta depinde de enunțul de pe pbinfo — verifică-l, unele probleme cer `0`, altele un mesaj. Important e să nu iasă `-1` niciodată.

---

## 🟡 Importante

### M1 — patru funcții, trei convenții diferite pentru „n-am găsit nimic"

Asta e observația care le leagă pe toate. Ai scris funcțiile una după alta, și fiecare pornește altfel:

| Funcție | Inițializare | Verifică înainte de afișare? | Ce iese când nu găsește |
|---|---|---|---|
| `ceaMaiLungaSecventaDeNumereImpare:22` | `smax = 1, dmax = 0` | ❌ nu | **tăcere completă** |
| `secventaPrimulSiUltimulNumarImpar:53` | `primul = -1, ultimul = -1` | ✅ da (`:64`) | mesaj clar |
| `secventaElementeNuleMaxima:87` | `smax = 0, dmax = -1` | ❌ nu | `0 -1` (B2) |
| `secventaElementeEgale:120` | `smax = 1, dmax = 0` | — | nu se aplică (vezi mai jos) |

La prima funcție, `smax = 1, dmax = 0` face ca bucla de afișare `for (int i = smax; i <= dmax; i++)` să pornească de la 1 și să se oprească imediat, fiindcă `1 <= 0` e fals. Deci programul nu afișează *nimic* — nici măcar o linie goală. Verificat pe `v = {2, 4, 6, 8}`:

```
[1] fara impare:      <-- nu afiseaza nimic
```

A patra funcție, `secventaElementeEgale`, scapă de problemă — dar din structură, nu din grijă: acolo **fiecare element începe o secvență**, nu există `if` care să filtreze, deci bucla intră garantat pentru orice `d >= 1`. E singurul caz din cele patru unde n-ai ce rata.

Din patru funcții, una singură verifică explicit. Nu pentru că n-ai știut — ai demonstrat la funcția 2 că știi. Ci pentru că **ai reinventat convenția de fiecare dată**.

**Ce înveți.** Alege o singură convenție și ține-te de ea în tot fișierul. Recomandarea mea: `poz = -1` înseamnă „nu am găsit", și **orice** funcție care o folosește o verifică imediat înainte de a afișa. Când toate funcțiile dintr-un fișier tratează la fel cazul „gol", nu mai trebuie să-ți amintești care e care.

### M2 — trei dintre cele patru funcții sunt același algoritm scris de trei ori

- `secvente.h:20-40`, `secvente.h:86-106` și `secvente.h:119-137`

Structura e identică — bucla exterioară caută un început, cea interioară întinde secvența, `i = j` sare peste ce s-a consumat, iar `if (j - i > dmax - smax)` reține maximul. Singura diferență e condiția: `v[i] % 2 == 1`, `v[i] == 0`, `v[j + 1] == v[i]`.

Nu-ți cer să le unifici acum (ar avea nevoie de noțiuni pe care nu le-ai făcut încă). Dar merită să vezi tiparul: **ai un schelet care rezolvă toată familia „cea mai lungă secvență de elemente cu proprietatea P".** Exercițiile 1, 4, 6 și 8 din fișa `exercitii-secvente-frecvente.pdf` sunt exact acest schelet cu alte patru condiții. Dacă îl scrii o dată bine, le rezolvi pe toate.

### M3 — comparația amestecă poziții 0-based cu 1-based

- `secvente.h:97-99` (la `secventaElementeNuleMaxima`) și `:129-131` (la `secventaElementeEgale`)

```cpp
if (j - i > dmax - smax) {   // j, i sunt indici 0-based
    smax = i + 1;            // dar stochezi 1-based
    dmax = j + 1;
}
```

Compari o lungime calculată din indici 0-based (`j - i`) cu una calculată din valori 1-based (`dmax - smax`). **Rezultatul e corect** — și merită să înțelegi de ce: `(j+1) - (i+1)` este exact `j - i`, deci diferența nu se schimbă la trecerea la 1-based. Se anulează.

Merge, dar din noroc structural, nu din construcție. Dacă mâine adaugi `+1` doar la unul dintre ele, sau schimbi `smax` fără `dmax`, se rupe fără niciun avertisment. Varianta care nu are cum să te trădeze: ține `smax`/`dmax` ca indici 0-based peste tot și adaugă `+1` **doar la afișare**:

```cpp
cout << smax + 1 << " " << dmax + 1 << endl;
```

Un singur loc unde se face conversia = un singur loc unde poți greși.

---

## 🟢 Cleanups

- **C1** — `secvente.h:99`: `dmax = j + 1;;` — două punct-și-virgulă. A doua e o instrucțiune goală; compilatorul o acceptă tăcut.
- **C2** — `secvente.h:39` și `:105`: lipsește `endl` la final. La funcția 3 se vede: `3 5` rămâne lipit de ce urmează în consolă. La #523 (`:136`) l-ai pus — deci ai observat singur, doar că n-ai mers înapoi.
- **C3** — `secvente.h:17-18`: în tabelul-comentariu scrie că `j` ajunge la `10` și `i` la `10`, dar cu `dim = 10` indicele maxim e `9`. Tabelul e o idee foarte bună — dar dacă cifrele din el nu sunt corecte, data viitoare te încrezi în el și te induce în eroare. Refă ultimele două linii.
- **C4** — ✅ rezolvat: numele `ceaMaiLungaSevcentaDeNumerePare` (cod care caută impare, plus typo `Sevcenta`) e acum `ceaMaiLungaSecventaDeNumereImpare`. Și `solutie1/2/3` → `solutie/solutie516/solutie518/solutie523`, cu numărul problemei în comentariu — mult mai ușor de găsit.

---

## Before / After — criticele

| # | Before (actual) | After (corect) |
|---|---|---|
| B1 | `if (v[i] % 2 == 1)` (`:24`, `:27`, `:57`) | `if (v[i] % 2 != 0)` — singurul test de imparitate care ține și pe negative |
| B2 | `cout << smax << " " << dmax;` (`:105`) | `if (dmax == -1) { cout << "Nu exista secvente de elemente nule" << endl; return; }` înainte de afișare |
| M1 | `smax = 1, dmax = 0;` fără verificare (`:22`) | aceeași santinelă `-1` ca la funcția 2, plus `if` înainte de bucla de afișare |
| M3 | `smax = i + 1; dmax = j + 1;` (`:98-99`, `:130-131`) | `smax = i; dmax = j;` și `+1` doar în `cout` |

---

## #523 — problema unde ai luat singur decizia grea

`secventaElementeEgale:119` cere „cea mai lungă secvență de elemente egale, iar la egalitate **cea mai din dreapta**". La #518 cerința era, pe dos, „cea mai din stânga". Diferența dintre cele două programe e un singur caracter:

| Problemă | Cerință la egalitate | Condiția ta | Corect? |
|---|---|---|---|
| #518 `:97` | cea mai din **stânga** | `if (j - i > dmax - smax)` | ✅ |
| #523 `:129` | cea mai din **dreapta** | `if (j - i >= dmax - smax)` | ✅ |

Cu `>` strict, o secvență de aceeași lungime **nu** o înlocuiește pe cea reținută, deci rămâne prima găsită. Cu `>=`, o înlocuiește de fiecare dată, deci rămâne ultima. Verificat prin rulare pe `v = {5,5,1,1,1,1,2,2,2,2}`, unde există două secvențe de lungime maximă 4:

```
v = {5,5,1,1,1,1,2,2,2,2}  ->  7 10    (secventa de 2-uri: cea din dreapta, corect)
v = {7,7,7,4,4,9}          ->  1 3     (maxim unic, nu conteaza departajarea)
v = {1,2,3,4}              ->  4 4     (toate de lungime 1 -> ultimul, corect)
v = {9}                    ->  1 1
```

Singurul caz care iese ciudat e `d = 0` (afișează `1 0`), dar pbinfo garantează `n >= 1`, deci nu te atinge.

**Ce înveți.** `>` și `>=` nu diferă doar prin „încă o valoare" — într-o căutare de maxim, ele codifică **politica de departajare**. `>` păstrează primul câștigător, `>=` păstrează ultimul. Când un enunț zice „cea mai din stânga" sau „cea mai din dreapta", el îți spune de fapt care dintre cei doi operatori să-l scrii. Ai nimerit-o de două ori la rând, în sensuri opuse — asta nu mai e noroc.

---

## Ce a mai mers

1. **Garda înaintea accesului**, în toate patru funcțiile (`:27`, `:93`, `:125`). E fix lecția din runda 6, aplicată din prima în cod nou.
2. **`i = j`** după fiecare secvență — sari peste ce ai consumat, deci nu renumeri aceeași secvență de mai multe ori. La exercițiul 7 din fișa nouă (secvență fără elemente repetate) o să vezi singurul caz din familie unde `i = j` ar fi **greșit**; când ajungi acolo, întreabă-te de ce.
3. **Cazul „nu există" tratat explicit** la `secventaPrimulSiUltimulNumarImpar` — singura funcție care o face, și modelul de urmat pentru celelalte.

---

## Q&A — verifică-ți înțelegerea

1. La B1, `-3 % 2` dă `-1` în C++. Scrie pe hârtie ce dau `-7 % 2`, `-7 / 2` și verifică apoi că `(a / b) * b + a % b` chiar reconstituie pe `a` pentru `a = -7, b = 2`. De ce testul `n % 2 == 0` pentru „e par" nu are aceeași problemă ca `n % 2 == 1` pentru „e impar"?

2. La funcția 1 ai pus `smax = 1, dmax = 0`, iar la funcția 3 `smax = 0, dmax = -1`. Amândouă dau diferența `-1` și amândouă „funcționează" la comparație. Explică ce face fiecare pereche **diferit** în bucla finală de afișare — și de ce doar una dintre ele produce ieșirea `0 -1`.

3. La #523 ai scris `>=` ca să iei secvența cea mai din dreapta. Dacă enunțul ar fi cerut „cea mai din dreapta, dar dintre cele care încep pe poziție **impară**", ce ai schimba? Și, mai important: la #518 ai `>` — ce ieșire ai fi obținut pe `v = {0,1,0,0,0,3,0,0,0,2}` dacă puneai `>=` din greșeală?
