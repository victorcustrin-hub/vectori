# Code Review — victor-vectori · runda 4: verificarea corecturilor

Reverificare, linie cu linie, a corecturilor din commit-urile `finish 4.2` → `finish code review`. Codul NU a fost modificat — totul e doar aici.

> **Progres față de runda 3.** Din 4 critice + 2 importante: **5 rezolvate corect, 1 rezolvată doar pe jumătate.** Punctul culminant: 4.2 și 4.6 nu le-ai rezolvat cu extrage/sortează/pune-înapoi, ci cu **sortare prin selecție direct peste pozițiile primelor/parelor** — comparația „sare peste gaură" exact cum trebuia, ne-primele nu sunt nici citite la swap. Am rulat trace-urile pe hârtie: ambele corecte. E o soluție mai elegantă decât cea propusă în review.

## ✅ Confirmate rezolvate

| Runda 3 | Fix-ul tău | Verdict |
|---|---|---|
| B2 — 4.2 muta ne-primele | `sortarePrinSelectieNrPrime`: `i` prim + `j` prim, swap la distanță | ✓ `{7,12,29,113,4}` — corect |
| B3 — `d=4` cu 3 elemente la 4.3 | `d = 3` | ✓ `22 51 89` |
| B4 — intervale greșite cu 1 la P5 | `(v, 0, i-1)` și `(v, i+1, d-1)` | ✓ inclusiv cazul `i=0` (interval gol, bucla nu intră) |
| M1 — `7=1` la descompunere | rest `n > 1` tipărit ca `n^1`, `*` doar când mai urmează ceva | ✓ `7=7^1`, `12=2^2*3^1` — și formatul cerut de fișă |
| M2 — oglindit unidirecțional | `\|\| v[j] == oglindit(v[i])` | ✓ prinde `(120, 21)` |
| 4.6 — neatacat | două selecții: pare crescător, impare descrescător | ✓ `{5,4,3,2,1,6}` → `5 2 3 4 1 6` |
| C1/C2/C3 | `;;` scoase, `stergereElement` cu `i < d-1`, `ct` mort eliminat | ✓ toate |

---

## 🔴 Critice

### B1 (rămas din runda 3) — `solutie6`: ai reparat datele, dar nu cauza
- `exercitiiRecapitulative.h:152` — `while (v[ct] == v[ct + 1])` tot fără graniță pe `ct`

`d = 8` face ca demo-ul curent să afișeze corect `valoare 1, lungime 4` — dar se oprește doar pentru că `v[8]` (fantoma) e `0` și `0 ≠ 1`. Bucla tot nu știe unde se termină vectorul; a avut noroc cu valoarea de dincolo de el. Contra-exemplu: orice vector care se **termină cu un platou de zerouri**:

```
v = {2, 0, 0}, d = 3
i=1: v[1]==v[2] → ct=1
     while: v[1]==v[2] (0==0) → ct=2
            v[2]==v[3] (0==0, fantomă!) → ct=3
            ... 0==0 până la ct=99
            v[99]==v[100] → citire ÎN AFARA array-ului → comportament nedefinit
→ lungime ~100 în loc de 2, posibil crash
```

**Ce înveți:** un fix de date face *testul* să treacă; un fix de cauză face *funcția* corectă pentru orice date. Regula rămâne cea din runda 3: granița stă în buclă, pe prima poziție —

```cpp
while (ct < d - 1 && v[ct] == v[ct + 1])
```

`&&` evaluează stânga întâi și se oprește dacă e falsă (short-circuit), deci `v[ct+1]` nu mai e citit niciodată când `ct + 1 == d`.

---

## 🟡 Importante

### M1 — `solutie9` a scăpat cu `d = 4` la 3 elemente
- `exercitiiRecapitulative.h:272-273` — ai scos `;;`-ul, dar dezacordul `d`/acolade a rămas

Azi e invizibil: fantoma `v[3] = 0` nu are cifre (`while (n != 0)` nu intră), deci min/max nu se schimbă. Dar e fix familia lui B3, pe care ai reparat-o la 4.3 — repar-o și aici, pentru consecvență: `d = 3`.

### M2 — funcții duplicate între headere (reportat, nerezolvat)
`prim`, `afisare`, `oglindit`, `cmmdc` etc. trăiesc în 7 fișiere. Merge cât timp `vectori.cpp` include unul singur; la două → `function redefinition`. Rămâne pe lista de refactor: un `utile.h` comun. Nu e blocant pentru fișă, dar e prima temă a următorului modul de „igienă de proiect".

---

## 🟢 Cleanups

- **C1 — `medieAritmetica` întoarce tot `int`** (`exercitiiRecapitulative.h:9`): ai mutat garda `d == 0` prima (bine) și ai făcut `medie` un `double` în `solutie1` — dar funcția întoarce `int`, deci trunchierea se întâmplă *la return*, înainte ca `double`-ul tău să o poată salva. Pentru „strict mai mare" rezultatul e același; mecanic însă, fixul e la tipul de retur: `double medieAritmetica(...)`.
- **C2 — `patratPerfect` pe float** (`:378`, reportat): `sqrt(n) == (int)sqrt(n)` — varianta robustă `rad * rad == n` o ai în `tema4.h:167`.

---

## Before / After — ce a rămas

| # | Before (actual) | After (corect) |
|---|---|---|
| B1 | `while (v[ct] == v[ct + 1])` | `while (ct < d - 1 && v[ct] == v[ct + 1])` |
| M1 | `solutie9`: 3 elemente, `int d = 4;` | `int d = 3;` |
| C1 | `int medieAritmetica(int v[], int d)` | `double medieAritmetica(int v[], int d)` |

---

## Q&A — verifică-ți înțelegerea

1. La `solutie6` cu `d = 8` rezultatul e corect. Explică de ce se oprește while-ul la `ct = 7` — și de ce asta e *noroc*, nu corectitudine. Pe ce fel de vector ar lua-o razna?
2. În `sortarePrinSelectieNrPrime`, după un swap, `v[i]` s-a schimbat. De ce e garantat că `v[i]` e în continuare prim, astfel încât bucla `j` poate continua fără să re-verifice `prim(v[i])`?
3. `double medie = medieAritmetica(v, d);` — variabila e `double`, dar valoarea primită e deja trunchiată. Unde anume pe traseul `suma/d → return → atribuire` se pierde partea zecimală?
