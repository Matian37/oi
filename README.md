![Progres OI](checklista/oi_progress.svg)

# Moje rozwiązania do zadań z Olimpiady Informatycznej

## Struktura repozytorium:

Zawartości katalogów `skrypty`, oraz `materialy` łatwo się domyślić, zachęcam do zapoznania się z nią.
W katalogu `rozwiazania` znajdziesz wszystkie rozwiązania zadań z OI, które zaimplementowałem.
Katalog `rozwiazania/<edycja_oi>/<etap_oi>/[dzień_etapu]/<skrót zadania>` zawiera pliki dotyczące danego zadania z OI.
- `<skrót zadania>.cpp` - moje rozwiązanie zadania, które otrzymuje 100 pkt na testach na sio2/szkopule, 
        dodatkowo z dopiskiem `_alt` bądź `_oi` pojawiają się czasem rozwiązania alternatywne oraz wprost z omówienia zadania,
        w przypadkach gdy rozwiązałem zadanie na 100 punktów na kilka różnych sposobów.
- `<skrót zadania><liczba punktów>.cpp` - Rozwiązania, które dostają mniej niż 100 punktów, takie jak bruty, bądź rozwiązania podgrup.
I dosyć często również pliki: 
- `<skrót zadania>g.cpp` - moja generatorka do zadania, której używałem testując rozwiązanie.
- `<skrót zadania>chk.cpp` - moja czekerka w przypadku zadań, w których istnieje więcej niż jedno poprawne rozwiązanie inne niż generowane przez bruta.
- Katalog `virtual_contest/`, zawierający moje skrypty, generatorki, czekerki i różne podejścia do zadania w przypadku, gdy symulowałem ograniczenia czasu i widoczności werdyktów występujące na olimpiadzie, tzn. w przypadku etapów I i II olimpiady, nie mogłem poznać liczby punktów, które dostanie moje zadanie na sprawdzarce szkopuł. Testowałem rozwiązanie lokalnie, i wysyłałem dopiero po przetestowaniu. Rozwiązania zadań z III etapu mogłem wysłać do 10 rozwiązań na szkopuła poznając ich wynik.

Katalogi `checklista` oraz `.github` zawierają skrypty automatycznie generujące checklisty, nie należy ich modyfikować. 
Jeśli coś nie działa, daj mi znać przez [Issue](https://github.com/Kulezi/oi/issues) na GitHubie.

Przykładowo katalog `rozwiazania/xxv/etap3/dzien1/kom/` będzie zawierał moje rozwiązania do zadania 'Liczby kompletne' z III etapu XXV OI.
Rozwiązania konkretnego zadanie można łatwo znaleźć sprawdzając, z której edycji i etapu olimpiady jest na [Liście zadań OI](https://oi.edu.pl/l/oi_zadania/),
bądź przy pomocy polecenia `grep 'nazwa zadania' -R .` wywołanego z głównego katalogu repozytorium, np. `grep `Trójkąty` -R .`.

## Jak samemu skorzystać z checklisty:

Sforkuj [szablon](https://github.com/testowyuczen/oi) tego repozytorium [klikając tutaj](https://github.com/testowyuczen/oi/fork), i w zakładce Actions swojego repozytorium kliknij `I understand my workflows, go ahead and enable them` - bez tego checklista nie będzie się aktualizować automatycznie.

Po wbiciu jakiegoś zadania, np 'Rycerz:wq' z pierwszego dnia II etapu XXXI OI:
- Zapisz rozwiązanie. np. w pliku `rozwiazania/xxxi/etap2/dzien1/ryc/ryc.cpp`.
- Dodaj je do repozytorium wykonując `git add `rozwiazania/xxxi/etap2/dzien1/ryc/ryc.cpp`, (przy pomocy `git status` możesz zobaczyć co już dodałeś w tym commicie).
- Scommituj je np. w ten sposób: `git commit -m "Dodano rozwiązanie zadania 'Rycerz' z XXXI OI"` (jeśli zapomnieliśmy czegoś dodać wystarczy powtórzyć poprzedni krok i użyć `git commit --am`.
- Zaktualizuj repozytorium na GitHub o lokalne zmiany przy pomocy `git push`, ewentualnie `git push -f`.
- Checklista w `README.md` na GitHub zaktualizuje się automatycznie w ciągu kilku minut.
- `git pull` wciągnie aktualną wersję checklisty z GitHuba (bez tego będziesz potrzebował robić `git push -f` przy każdym pushu.

<!-- AUTO-CHECKLIST -->

> ⚠️ **UWAGA:** Sekcja poniżej jest generowana automatycznie.
> Nie modyfikuj README poniżej tego napisu.
> ✅ oznacza wykonane zadanie.
> 🤔 oznacza zadanie z mniej niż 100 punktów.


# Podsumowanie

## Rozwiązane zadania wg etapów

Etap I | Etap II | Etap III | Łącznie
:---: | :---: | :---: | :---:
0/150 (0%) | 3/157 (2%) | 0/200 (0%) | 3/507 (1%)

## Rozwiązane zadania wg edycji

Edycja | Wynik | Edycja | Wynik | Edycja | Wynik | Edycja | Wynik
:--- | ---: | :--- | ---: | :--- | ---: | :--- | ---:
I | 0/10 (0%) | XI | 0/16 (0%) | XXI | 0/17 (0%) | XXXI | 0/17 (0%)
II | 0/14 (0%) | XII | 0/17 (0%) | XXII | 0/17 (0%) | XXXII | 1/18 (6%)
III | 0/13 (0%) | XIII | 0/16 (0%) | XXIII | 1/17 (6%) |  | 
IV | 0/16 (0%) | XIV | 0/16 (0%) | XXIV | 0/16 (0%) |  | 
V | 0/16 (0%) | XV | 0/16 (0%) | XXV | 0/18 (0%) |  | 
VI | 0/15 (0%) | XVI | 0/16 (0%) | XXVI | 0/17 (0%) |  | 
VII | 0/15 (0%) | XVII | 0/17 (0%) | XXVII | 0/10 (0%) |  | 
VIII | 0/15 (0%) | XVIII | 0/17 (0%) | XXVIII | 0/17 (0%) |  | 
IX | 0/15 (0%) | XIX | 0/17 (0%) | XXIX | 1/17 (6%) |  | 
X | 0/16 (0%) | XX | 0/17 (0%) | XXX | 0/17 (0%) |  |


## Rozwiązane zadania z I etapu

Edycja | zad. 1 | zad. 2 | zad. 3 | zad. 4 | zad. 5 | zad. 6
:--- | ---: | ---: | ---: | ---: | ---: | ---:
I |   |   |   | — | — | —
II |   |   |   |   | — | —
III |   |   |   |   | — | —
IV |   |   |   |   | — | —
V |   |   |   |   | — | —
VI |   |   |   |   | — | —
VII |   |   |   |   | — | —
VIII |   |   |   |   | — | —
IX |   |   |   |   | — | —
X |   |   |   |   |   | —
XI |   |   |   |   |   | —
XII |   |   |   |   |   | —
XIII |   |   |   |   |   | —
XIV |   |   |   |   |   | —
XV |   |   |   |   |   | —
XVI |   |   |   |   |   | —
XVII |   |   |   |   |   | —
XVIII |   |   |   |   |   | —
XIX |   |   |   |   |   | —
XX |   |   |   |   |   | —
XXI |   |   |   |   |   | —
XXII |   |   |   |   |   | —
XXIII |   |   |   |   |   | —
XXIV |   |   |   |   |   | —
XXV |   |   |   |   |   | —
XXVI |   |   |   |   |   | —
XXVII |   |   |   |   |   | —
XXVIII |   |   |   |   |   | —
XXIX |   |   |   |   |   | —
XXX |   |   |   |   |   | —
XXXI |   |   |   |   |   | —
XXXII |   |   |   |   |   |


## Rozwiązane zadania z II etapu

Edycja | zad. próbne | Dzień 1 - zad. 1 | Dzień 1 - zad. 2 | Dzień 2 - zad. 1 | Dzień 2 - zad. 2
:--- | ---: | ---: | ---: | ---: | ---:
I |   |   | — |   | —
II |   |   |   |   |  
III |   |   | — |   |  
IV |   |   |   |   |  
V |   |   |   |   |  
VI |   |   |   |   |  
VII |   |   |   |   |  
VIII |   |   |   |   |  
IX |   |   |   |   |  
X |   |   |   |   |  
XI |   |   |   |   |  
XII |   |   |   |   |  
XIII |   |   |   |   |  
XIV |   |   |   |   |  
XV |   |   |   |   |  
XVI |   |   |   |   |  
XVII |   |   |   |   |  
XVIII |   |   |   |   |  
XIX |   |   |   |   |  
XX |   |   |   |   |  
XXI |   |   |   |   |  
XXII |   |   |   |   |  
XXIII |   | zaj ✅ |   |   |  
XXIV |   |   |   |   |  
XXV |   |   |   |   |  
XXVI |   |   |   |   |  
XXVII |   |   |   |   |  
XXVIII |   |   |   |   |  
XXIX |   | age ✅ |   |   |  
XXX |   |   |   |   |  
XXXI |   |   |   |   |  
XXXII | sss ✅ |   |   |   |


## Rozwiązane zadania z III etapu

Edycja | Dzień próbny, zad. 1 | Dzień próbny, zad. 2 | Dzień 1 - zad. 1 | Dzień 1 - zad. 2 | Dzień 1 - zad. 3 | Dzień 2 - zad. 1 | Dzień 2 - zad. 2 | Dzień 2 - zad. 3
:--- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---:
I |   | — |   |   | — |   | — | —
II |   | — |   |   | — |   |   | —
III |   | — |   |   | — |   |   | —
IV |   | — |   |   |   |   |   | —
V |   | — |   |   |   |   |   |  
VI |   | — |   |   | — |   |   |  
VII |   | — |   |   | — |   |   |  
VIII |   | — |   |   | — |   |   |  
IX |   | — |   |   | — |   |   |  
X |   | — |   |   | — |   |   |  
XI |   | — |   |   |   |   |   | —
XII |   | — |   |   |   |   |   |  
XIII |   | — |   |   | — |   |   |  
XIV |   | — |   |   | — |   |   |  
XV |   | — |   |   |   |   |   | —
XVI |   | — |   |   |   |   |   | —
XVII |   | — |   |   |   |   |   |  
XVIII |   | — |   |   |   |   |   |  
XIX |   | — |   |   |   |   |   |  
XX |   | — |   |   |   |   |   |  
XXI |   | — |   |   |   |   |   |  
XXII |   | — |   |   |   |   |   |  
XXIII |   | — |   |   |   |   |   |  
XXIV |   | — |   |   |   |   |   | —
XXV |   |   |   |   |   |   |   |  
XXVI |   | — |   |   |   |   |   |  
XXVII | — | — | — | — | — | — | — | —
XXVIII |   | — |   |   |   |   |   |  
XXIX |   |   |   |   |   |   |   |  
XXX |   | — |   |   |   |   |   |  
XXXI |   | — |   |   |   |   |   |
