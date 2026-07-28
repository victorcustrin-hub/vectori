# Code Review — victor-vectori · runda 3: `exercitiiRecapitulative.h`

Review pentru fișa recapitulativă rezolvată integral (33 de soluții, module 1–5 + provocări). Codul NU a fost modificat — totul e doar aici.

> **Progres față de runda trecută.** Ambele critice vechi sunt rezolvate corect:
> `progresieAritmetica` are acum `while (n > 0)` (`realizareaUnuiNouVector.h:95`) și `cmmdc` e Euclid cu rest în `tema2.h:681` și `corectareTema2.h:249`. În plus, `cmmdc` din fișierul nou (`exercitiiRecapitulative.h:436`) e scris direct corect. Bravo — exact varianta discutată.
>
> **Scor pe fișă:** 27 din 33 corecte la prima strigare, inclusiv aproape toate provocările (P1–P4 corecte). Criticele de mai jos sunt concentrate în 5 soluții.

---

## 🔴 Critice

### B1 — `solutie6` (1.6, platou): while-ul interior nu se oprește la marginea vectorului
- `exercitiiRecapitulative.h:154` — `while (v[ct] == v[ct + 1])` fără nicio limită pe `ct`
- agravat de datele de test: `exercitiiRecapitulative.h:144-145` — 8 valori în acolade, dar `d = 6`

Bucla interioară compară `v[ct]` cu `v[ct+1]` până când valorile diferă — dar nimic nu o oprește la `d`. Cu `{2,5,5,5,1,1,1,1}` și `d=6`, vectorul *logic* e `{2,5,5,5,1,1}`, însă while-ul merge mai departe peste `v[6]` și `v[7]` (care există în acolade, dar sunt în afara lui `d`):

```
i=4: v[4]==v[5] (1==1) → ct=4
     v[4]==v[5] → lungime=2, ct=5
     v[5]==v[6] (1==1, dar v[6] e DINCOLO de d!) → lungime=3, ct=6
     v[6]==v[7] (1==1) → lungime=4, ct=7
     v[7]==v[8] (1==0) → stop
→ afișează: valoare 1, lungime 4   (corect era: valoare 5, lungime 3)
```

**Ce înveți:** `d` e granița lumii tale, nu conținutul acoladelor. Orice buclă care avansează un index trebuie să aibă condiția de graniță *în ea*: `while (ct < d - 1 && v[ct] == v[ct + 1])`. Ordinea contează — testul de graniță stă PRIMUL, ca `v[ct+1]` să nu fie citit când `ct+1 == d`. Propriul tău tabel de urmărire (liniile 136–142) se oprea la `ct=5` — tabelul era corect, codul nu-l respectă.

### B2 — `solutie19` (4.2): sortarea „doar a primelor" mută și ne-primele
- `exercitiiRecapitulative.h:547` — `if (prim(v[i]) && v[i] > v[i + 1])` + swap cu vecinul

E chiar una din întrebările tale — pe bună dreptate. Condiția testează dacă `v[i]` e prim, dar swap-ul se face cu `v[i+1]` *oricine ar fi el* — deci un prim „împinge" ne-primele din drum și toată lumea se mută de pe pozițiile ei. Pe `{29,12,7,113,4}`:

```
pasul 1: 29>12 swap → {12,29,7,113,4} → 29>7 swap → {12,7,29,113,4} → 113>4 swap → {12,7,29,4,113}
pasul 2: 29>4 swap → {12,7,4,29,113}
pasul 3: 7>4 swap  → {12,4,7,29,113}
→ afișează: 12 4 7 29 113   (corect era: 7 12 29 113 4 — 12 și 4 nu aveau voie să se miște!)
```

**Ce înveți:** „sortează subșirul păstrând restul pe loc" nu se poate face swapuind vecini din vectorul mare — vecinul unui prim nu e următorul prim, e doar următorul element. Mecanismul corect are 3 pași: **extrage** (copiază primele într-un vector `aux` și pozițiile lor într-un `poz`), **sortează** `aux` cu bubble sort-ul normal, **pune înapoi** (`v[poz[k]] = aux[k]`). Restul elementelor nici nu sunt atinse. Vezi și răspunsul la întrebările tale, mai jos — 4.6 e același tipar de două ori.

### B3 — `solutie20` (4.3): `d = 4` dar doar 3 elemente în acolade → un `0` fantomă intră în sortare
- `exercitiiRecapitulative.h:591-592` — `int v[100] = { 89,22,51 }; int d = 4;`
- același tipar, azi fără efect: `exercitiiRecapitulative.h:273-274` — `solutie9` are 3 elemente și `d = 4`

În C++, `int v[100] = {89,22,51}` umple restul cu `0`. Cu `d=4`, al patrulea element „văzut" e `v[3] = 0`, cu suma cifrelor `0` — cea mai mică — deci sortarea îl aduce primul:

```
→ afișează: 0 22 51 89   (corect era: 22 51 89)
```

La `solutie9` același dezacord scapă nepedepsit doar pentru că `0` nu are cifre de parcurs (`while (n != 0)` nu intră deloc), deci nu influențează min/max. **Ce înveți:** `d` și acoladele sunt aceeași informație scrisă de două ori — la fiecare modificare a datelor de test, numeri elementele și corectezi `d`. B1 și B3 sunt, de fapt, aceeași greșeală în două direcții: acolo acoladele aveau mai mult decât `d`, aici `d` are mai mult decât acoladele.

### B4 — `solutie33` (P5, munte pe pătrat perfect): ambele intervale de sortare sunt greșite cu 1
- `exercitiiRecapitulative.h:958` — `sortatCrescatorInterval(v, 0, i)` include chiar pătratul perfect în prefix
- `exercitiiRecapitulative.h:959` — `sortatDescrescatorInterval(v, i + 1, d)` — `finish = d` atinge `v[d]`, dincolo de vector

Funcțiile tale de interval sortează `[start, finish]` *inclusiv* (bucla `i < finish` compară `v[i]` cu `v[i+1]`, deci atinge `v[finish]`). De aici două probleme:

1. Prefixul sortat e `[0..i]`, cu tot cu pătratul perfect. Pe datele tale (`16` e maximul prefixului) iese bine **din noroc**; pe `{20,3,16,2,9,1}` sortarea `[0..2]` dă `{3,16,20}` — pătratul alunecă de pe vârf și muntele e stricat (`3 16 20 9 2 1` în loc de `3 20 16 9 2 1`).
2. Sufixul `[i+1..d]` atinge `v[d]` = element fantomă `0`. Azi `0` e mai mic decât toate și rămâne ultimul — invizibil. Cu un element negativ în sufix (`{7,3,16,2,-9,1}`), `0`-ul fantomă ar fi sortat *înăuntru* și `-9` împins afară din vector.

**Ce înveți:** exact capcana notată în fișă la Modulul 4 — `finish` trebuie să fie *ultimul index valid*, nu dincolo de el. Apelurile corecte: `sortatCrescatorInterval(v, 0, i - 1)` și `sortatDescrescatorInterval(v, i + 1, d - 1)`. Comparație utilă: în `solutie21` (4.4) ai apelat cu `d - 1` și e corect — aceeași mână a scris ambele, diferența e doar atenția la contractul funcției.

---

## 🟡 Importante

### M1 — `descompunereFactoriPrimi`: un element prim se afișează `7=1`
- `exercitiiRecapitulative.h:383-399` — bucla merge `k <= aux/2`, apoi tipărește mereu `*1`

Pentru un `n` prim (de ex. `7`, care nu e pătrat perfect, deci intră la afișare), niciun `k ≤ n/2` nu îl divide → se tipărește doar `7=1`, fără factorul `7^1`. Datele tale `{12,16,18}` nu ating cazul, dar prima temă cu un prim în vector îl atinge. Fix de mecanism: după buclă, dacă `n > 1`, ce a rămas în `n` e un factor prim → tipărește `n^1`. Bonus de format: fișa cere `12=2^2*3^1`, codul scoate `12=2^2*3^1*1` — coada `*1` există doar ca să închidă `*`-ul; dacă tratezi restul `n > 1`, dispare natural.

### M2 — `solutie16` (3.3): oglinditul e verificat într-o singură direcție
- `exercitiiRecapitulative.h:466` — `if (v[i] == oglindit(v[j]))`

Pare simetric, dar nu e — din cauza zerourilor finale. Perechea `(120, 21)`: `oglindit(120) = 21`, deci „un element este oglinditul celuilalt" e adevărat; codul însă verifică doar `120 == oglindit(21)`, adică `120 == 12` → fals, perechea e ratată. Condiția completă: `v[i] == oglindit(v[j]) || v[j] == oglindit(v[i])`.

### M3 — funcții duplicate între headere (reportat din runda 2, acum și mai apăsat)
`exercitiiRecapitulative.h` redefinește `prim`, `afisare`, `oglindit`, `palindrom`, `sumaCifrelor`, `cifControl`, `cmmdc`, `patratPerfect`, `stergereElement`, `inserareElement` — toate există deja în celelalte headere. Merge doar cât timp `vectori.cpp` include un singur header; la două, `function redefinition`. Rămâne valabilă soluția: un `utile.h` cu cărămizile comune.

---

## 🟢 Cleanups

- **C1 — `;;` dublu:** `exercitiiRecapitulative.h:228` și `:274` (`int d = 4;;`).
- **C2 — `stergereElement` copiază un element de dincolo de `d`:** `exercitiiRecapitulative.h:710` — `for (i = poz; i < d; i++) v[i] = v[i+1]` citește `v[d]`. Azi inofensiv (capacitate 100), dar contractul corect e `i < d - 1`.
- **C3 — variabilă moartă:** `ct` în `solutie32` (`exercitiiRecapitulative.h:934,939`) e incrementat și nefolosit — numărul de rămase e chiar `d`.
- **C4 — `patratPerfect` pe float** (`exercitiiRecapitulative.h:380`): `sqrt(n) == (int)sqrt(n)` — reportat; varianta robustă `rad * rad == n` există deja în `tema4.h:167`.
- **C5 — `medieAritmetica`:** garda `d == 0` stă după buclă (`exercitiiRecapitulative.h:17`) — pune-o prima; iar media e trunchiată la `int` (`:21`) — pentru „strict mai mare" rezultatul iese identic (demonstrabil), dar la „mai mic decât media" trunchierea ar da alt răspuns. Păstrează media în `double`.
- **4.6 (`solutie23`) e neatacat** — doar afișare, marcat de tine la întrebări. Vezi mai jos.

---

## Before / After — criticele

| # | Before (actual) | After (corect) |
|---|---|---|
| B1 | `while (v[ct] == v[ct + 1])` | `while (ct < d - 1 && v[ct] == v[ct + 1])` |
| B2 | `if (prim(v[i]) && v[i] > v[i+1])` swap în vectorul mare | extrage primele în `aux` + pozițiile în `poz` → sortează `aux` → `v[poz[k]] = aux[k]` |
| B3 | `int v[100] = { 89,22,51 }; int d = 4;` | `int d = 3;` (sau al 4-lea element în acolade) |
| B4 | `sortatCrescatorInterval(v, 0, i);`<br>`sortatDescrescatorInterval(v, i + 1, d);` | `sortatCrescatorInterval(v, 0, i - 1);`<br>`sortatDescrescatorInterval(v, i + 1, d - 1);` |

---

## Întrebările tale — 4.2 și 4.6

Ai marcat exact soluțiile cu problema cea mai interesantă din fișă, deci întrebarea e bine pusă.

**4.2** — vezi B2. Ideea de reținut: nu poți sorta „printre" alte elemente cu swap de vecini, pentru că vecinul în vectorul mare nu e vecinul în subșir. Subșirul trebuie scos afară, sortat la el acasă, pus înapoi pe pozițiile memorate.

**4.6** — e *același* tipar, aplicat de două ori: o extragere pentru pare (sortate crescător), o extragere pentru impare (sortate descrescător), apoi fiecare listă se toarnă înapoi pe pozițiile de unde a fost scoasă. Ai deja toate cărămizile: bubble sort crescător, descrescător, și — după ce corectezi 4.2 — mecanismul extrage/pune-înapoi. Încearcă-l singur întâi pe 4.2, apoi 4.6 iese aproape de la sine.

---

## Q&A — verifică-ți înțelegerea

1. La `solutie6`, tabelul tău de urmărire (liniile 136–142) se oprește la `ct=5`, dar programul afișează `valoare 1, lungime 4`. Ce anume citește while-ul dincolo de `d` și de ce valorile alea există în memorie deși „nu fac parte" din vector?
2. Rulează pe hârtie prima trecere din `solutie19` pe `{29,12,7,113,4}`. Unde ajunge `12` după primele două swap-uri și ce regulă din enunț încalcă mutarea lui?
3. La `solutie33`, funcția `sortatDescrescatorInterval(v, i+1, d)` atinge `v[d]`. De ce pe datele tale rezultatul iese totuși corect, și ce s-ar întâmpla dacă vectorul ar conține un număr negativ după pătratul perfect?
