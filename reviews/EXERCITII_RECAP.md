---
title: "Vectori --- Fișă recapitulativă"
subtitle: "Victor · toate temele parcurse, exersate din nou"
date: "22 iulie 2026"
---

# Cum folosești fișa

Fișa strânge, pe module, tot ce ai lucrat în `vectori/` --- de la parcurgere simplă până la ștergere/inserare cu redimensionare. Fiecare exercițiu are un **exemplu** (vectorul de intrare și rezultatul așteptat), ca să știi exact ce trebuie să iasă. Nu sunt indicii: scrii singur funcțiile-cărămidă și le combini.

Reguli de joc, aceleași ca la clasă:

- Fiecare cerință se rezolvă cu funcții mici, refolosibile (`prim`, `sumaCifrelor`, `oglindit`, `cmmdc`...), nu cu tot codul în `main`.
- Vectorul are capacitate fixă (`int v[100]`), iar dimensiunea reală o ții separat în `d`.
- Când o funcție schimbă lungimea vectorului (ștergere/inserare), `dim` se transmite **prin referință** (`int& dim`).
- Termenii tehnici, mesajele și numele funcțiilor rămân în engleză; explicațiile, în română.

Modulele sunt în ordinea în care le-ai făcut. Ultima secțiune, *Provocări*, combină mai multe teme --- acolo se vede dacă piesele chiar se leagă.

**Legenda dificultății:** [C] cald · [M] mediu · [P] provocare

---

# Modulul 1 --- Parcurgere, numărare, filtrare

Reiei parcurgerea de bază: numeri, filtrezi, construiești un vector nou din elementele care trec un test.

**1.1** `[C]` Se dă un vector de numere întregi. Să se afișeze câte elemente sunt strict mai mari decât media aritmetică a vectorului.

> *Exemplu:* `v = {4, 10, 2, 8, 6}` → media este `6`, elemente strict mai mari: `10, 8` → răspuns `2`.

**1.2** `[C]` Să se construiască un vector nou care conține doar elementele de pe poziții pare (index 0, 2, 4...) din vectorul dat, apoi să se afișeze.

> *Exemplu:* `v = {7, 4, 9, 6, 2, 5}` → `7 9 2`.

**1.3** `[M]` Să se afișeze elementele care sunt strict mai mari decât **ambii** vecini (element „vârf"). Primul și ultimul element nu se verifică --- nu au doi vecini.

> *Exemplu:* `v = {3, 8, 5, 9, 4}` → `8 9`.

**1.4** `[M]` Se dă un vector. Să se construiască un vector nou care conține, pentru fiecare element, numărul de divizori proprii ai lui (divizori fără `1` și fără numărul însuși).

> *Exemplu:* `v = {6, 7, 12}` → `6`→(2,3)=2, `7`→0, `12`→(2,3,4,6)=4 → `2 0 4`.

**1.5** `[M]` Să se înlocuiască fiecare element care este multiplu al **primului** element cu `0`, apoi să se afișeze vectorul. Atenție la cazul în care primul element este `0`.

> *Exemplu:* `v = {3, 9, 4, 12, 5}` → `0 0 4 0 5`.

**1.6** `[P]` Se dă un vector. Să se afișeze cel mai lung „platou" --- cea mai lungă secvență de elemente egale și alăturate --- prin lungimea lui și valoarea repetată.

> *Exemplu:* `v = {2, 5, 5, 5, 1, 1}` → `valoare 5, lungime 3`.

---

# Modulul 2 --- Funcții pe cifre, aplicate pe vector

Aici ai construit cel mai mult: funcții care lucrează pe cifrele unui număr, apoi le aplici pe fiecare element. Refolosește funcțiile-cărămidă.

**2.1** `[C]` Să se construiască un vector nou cu suma cifrelor fiecărui element, apoi să se afișeze.

> *Exemplu:* `v = {213, 45, 1000}` → `6 9 1`.

**2.2** `[C]` Să se afișeze elementele care sunt palindrom (se citesc la fel de la stânga și de la dreapta).

> *Exemplu:* `v = {121, 45, 707, 89}` → `121 707`.

**2.3** `[M]` Să se afișeze, pentru tot vectorul, cea mai mică și cea mai mare **cifră** care apare în oricare dintre elemente.

> *Exemplu:* `v = {45, 634, 23}` → `cifra minima 2, cifra maxima 6`.

**2.4** `[M]` Se dă un vector. Să se afișeze elementele a căror **cifră de control** (rădăcina digitală: suma repetată a cifrelor până rămâne o singură cifră) este un număr par.

> *Exemplu:* `v = {542, 741, 999}` → `cifControl(542)=2` par → `542`; `741`→3 impar; `999`→9 impar → răspuns `542`.

**2.5** `[M]` Să se construiască un vector nou care conține oglinditul fiecărui element care are prima cifră egală cu ultima cifră. Elementele care nu respectă condiția se copiază neschimbate.

> *Exemplu:* `v = {12, 343, 90}` → `343` are prima=ultima → oglindit; `12` și `90` rămân → `12 343 90`.

**2.6** `[P]` Un număr este **superprim** dacă el și toate numerele obținute ștergând cifre de la coadă (`1234 → 123 → 12 → 1`) sunt prime. Să se afișeze pe ce **poziții** (index de la 1) se află elementele superprime.

> *Exemplu:* `v = {12, 239, 45, 23, 7}` → `239`(239,23,2) poz 2, `23`(23,2) poz 4, `7` poz 5 → `2 4 5`.

**2.7** `[P]` Să se afișeze descompunerea în factori primi a fiecărui element care **nu** este pătrat perfect. Formatul: `12=2^2*3^1`.

> *Exemplu:* `v = {12, 16, 18}` → `12=2^2*3^1` și `18=2^1*3^2` (`16` e pătrat perfect, se sare).

---

# Modulul 3 --- Dublete (perechi de elemente)

Un *dublet* = pereche de elemente. La perechi **alăturate** bucla merge `i < d - 1` și folosești `v[i]` cu `v[i+1]`. La **toate** perechile ai două bucle: `j` pornește de la `i + 1`.

**3.1** `[C]` (perechi alăturate) Să se afișeze toate dubletele alăturate în care ambele elemente au același număr de cifre.

> *Exemplu:* `v = {45, 12, 7, 103, 564}` → `45 12`.

**3.2** `[M]` (perechi alăturate) Să se numere câte dublete alăturate sunt **prime între ele** (cmmdc egal cu 1).

> *Exemplu:* `v = {12, 25, 10, 21}` → `(12,25)` da, `(25,10)` nu, `(10,21)` da → `2`.

**3.3** `[M]` (toate perechile) Să se afișeze toate perechile `(v[i], v[j])` cu `i < j` în care un element este oglinditul celuilalt.

> *Exemplu:* `v = {213, 312, 45, 54}` → `213 312` și `45 54`.

**3.4** `[P]` (toate perechile) Să se afișeze perechea `(i, j)` cu cea mai mare sumă `v[i] + v[j]`, unde ambele elemente sunt numere prime. Dacă nu există două prime, se afișează un mesaj.

> *Exemplu:* `v = {4, 7, 10, 13, 6}` → `7 + 13 = 20`.

---

# Modulul 4 --- Sortări

Ai lucrat bubble sort, sortare prin selecție, sortare după un **criteriu** (nr. divizori, sumă cifre, prima cifră) și sortări **parțiale** pe interval. Reține: la sortarea parțială pe `[start, finish]` bucla interioară merge `i < finish` și accesează `v[i+1]` --- deci `finish` trebuie să fie ultimul index valid, nu dincolo de el.

**4.1** `[C]` Să se sorteze crescător vectorul folosind bubble sort și să se afișeze.

> *Exemplu:* `v = {32, 56, 19, 42}` → `19 32 42 56`.

**4.2** `[M]` Să se sorteze crescător **doar** subșirul elementelor prime, lăsând restul elementelor pe pozițiile lor.

> *Exemplu:* `v = {29, 12, 7, 113, 4}` → primele (`29, 7, 113`) sortate pe pozițiile lor → `7 12 29 113 4`.

**4.3** `[M]` Să se sorteze crescător elementele după **suma cifrelor**. La sumă egală, se păstrează ordinea inițială (sortare stabilă).

> *Exemplu:* `v = {89, 22, 51}` → sume `17, 4, 6` → `22 51 89`.

**4.4** `[M]` (munte) Să se sorteze vectorul „în formă de munte": crescător până la poziția elementului maxim, descrescător după ea.

> *Exemplu:* `v = {3, 9, 5, 2, 8, 1}` → maxim `9` pe poziția 1 → `3 9 8 5 2 1`.

**4.5** `[P]` (indici paraleli) Se dau înălțimile unor persoane într-un vector. Să se afișeze pozițiile inițiale (de la 1) în ordinea crescătoare a înălțimii --- fără să pierzi corespondența, deci sortezi în paralel un al doilea vector cu indici.

> *Exemplu:* `v = {8, 20, 16, 14}` → sortat `8, 14, 16, 20` cu pozițiile inițiale → `1 4 3 2`.

**4.6** `[P]` (pare/impare) Să se sorteze crescător subșirul elementelor pare și descrescător subșirul elementelor impare, fiecare rămânând pe pozițiile ocupate inițial de paritatea respectivă.

> *Exemplu:* `v = {5, 4, 3, 2, 1, 6}` → pare crescător `2, 4, 6`, impare descrescător `5, 3, 1` → `5 2 3 4 1 6`.

---

# Modulul 5 --- Ștergere și inserare

Aici dimensiunea se schimbă, deci `dim` merge **prin referință**. Când ștergi într-o buclă și dai `i--`, ai grijă să nu sari elemente. Când inserezi, decide dacă avansezi peste elementul nou (`i++`) ca să nu-l reprocesezi.

**5.1** `[C]` Să se șteargă din vector toate elementele egale cu `0`, apoi să se afișeze.

> *Exemplu:* `v = {9, 0, 0, 5, 0}` → `9 5`.

**5.2** `[M]` Să se șteargă toate elementele care se află în intervalul `[a, b]` (inclusiv). Dacă `a > b`, se interschimbă înainte.

> *Exemplu:* `v = {5, 11, 23, 4, 7}`, `a=3, b=7` → se șterg `5, 4, 7` → `11 23`.

**5.3** `[M]` După fiecare element negativ să se insereze cubul lui, apoi să se afișeze.

> *Exemplu:* `v = {4, -2, 5}` → `4 -2 -8 5`.

**5.4** `[M]` Să se șteargă al **3-lea** element prim din vector (dacă există). Numeri primele, iar la al treilea îl ștergi.

> *Exemplu:* `v = {4, 7, 10, 13, 8, 5}` → primele: `7`(1), `13`(2), `5`(3) → se șterge `5` → `4 7 10 13 8`.

**5.5** `[P]` Pentru fiecare element care are prima cifră egală cu ultima cifră, să se insereze prima cifră **înaintea** lui și ultima cifră **după** el.

> *Exemplu:* `v = {45, 121, 7}` → `121` are prima=ultima=1 → `45 1 121 1 7`.

---

# Provocări --- combină mai multe teme

Fiecare provocare cere cel puțin două module diferite. Sparge-le în funcții mici; dacă o funcție e greu de numit, probabil face prea multe.

**P1** `[P]` **Filtrare + sortare.** Din vector, construiește un vector nou doar cu elementele palindrom, sortează-l descrescător după suma cifrelor și afișează-l.

> *Exemplu:* `v = {121, 45, 707, 33, 89}` → palindroame `121, 707, 33` → sume `4, 14, 6` → descrescător `707 33 121`.

**P2** `[P]` **Cifre + dublete.** Afișează toate dubletele alăturate `(v[i], v[i+1])` în care alipirea celor două numere (`12` și `34` → `1234`) este un număr prim.

> *Exemplu:* `v = {1, 3, 20, 7}` → `1|3 = 13` prim → `1 3`; `3|20 = 320` nu; `20|7 = 207` nu → răspuns `1 3`.

**P3** `[P]` **cmmdc corect, fără operator-virgulă.** Calculează cmmmc-ul tuturor elementelor pare din vector. Folosește relația `cmmmc(a,b) = a / cmmdc(a,b) * b` și un `cmmdc` scris cu **apel de funcție real**, nu cu vreo expresie de tip `(a, b)`.

> *Exemplu:* `v = {4, 5, 6, 8, 12}` → pare `4, 6, 8, 12` → `cmmmc = 24`.

**P4** `[P]` **Ștergere + condiție pe cifre.** Șterge din vector toate elementele care au cel puțin o cifră de `0`, apoi inserează la începutul vectorului numărul de elemente rămase.

> *Exemplu:* `v = {12, 40, 305, 7, 88}` → se șterg `40, 305` → rămân `12, 7, 88` → `3 12 7 88`.

**P5** `[P]` **Munte pe criteriu.** Găsește poziția primului element care este pătrat perfect. Sortează crescător tot ce e înaintea lui și descrescător tot ce e după el (vârful pe pătratul perfect). Dacă nu există pătrat perfect, afișează un mesaj.

> *Exemplu:* `v = {7, 3, 16, 2, 9, 1}` → primul pătrat perfect `16` pe poziția 2 → `3 7 16 9 2 1`.

\vspace{1em}

*Sfat de final:* fiecare cerință are cel puțin o capcană pe care ai întâlnit-o deja --- graniță la `v[i-1]` când `i` e 0, buclă `i < d - 1` la dublete, `dim` prin referință, `cmmdc` care nu trebuie să intre în buclă infinită pe `0`. Dacă rezultatul nu iese, verifică întâi granițele și cazurile speciale: vector gol, un singur element, zerouri.
