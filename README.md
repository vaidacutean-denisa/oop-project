# The Last Stand: Undead Uprising

## Descriere 
Un joc de tip shooter in care jucatorul se confrunta cu valuri de inamici intr-un timp limitat. Incepi cu o arma de baza si trebuie sa elimini inamicii care devin tot mai puternici pe masura ce avansezi. Pe parcurs, poti obtine noi arme, munitie si bonusuri care iti imbunatatesc abilitatile (sanatate, viteza, putere de atac). Fiecare nivel ofera o provocare tot mai mare, iar succesul depinde de gestionarea atenta a resurselor si a timpului.

(in lucru..)

## Comentarii 
  - referitor la cerintele din tema 2: trebuie sa mai tratez exceptii + commit cu derivata noua, in rest CRED ca le am pe toate (voi mai verifica)
  - am setat levelDuration din clasa levelManager la 10 secunde pentru a putea face verificari mai rapid (am uitat sa ii atribui valoarea default: ma gandesc sa las la 90 sau 120 de secunde)
    
### Features in dezvoltare
  - Integrarea unui sistem de colectare si / sau activare directa a perk-urilor la intersectia cu acestea (vor aparea random pe harta).
    ^(cel mai probabil ramane activare directa din motive mai mult sau mai putin evidente :)
  - Dezvoltarea unui meniu care sa afiseze informatii referitoare la armele din joc (la apasarea butonului Inventory din meniul principal)
    ^^ implicit voi renunta la dialogul din terminal, intrucat ideea mea este sa pot alege arma din inventar; daca dau play fara sa aleg arma, ori primesc una default, ori nu continua jocul pana nu aleg eu

### Probleme
 - Ar trebui sa implementez un sistem mai bun de detectare a coliziunilor, astfel incat sa nu se poata suprapune nici inamicii intre ei, nici jucatorul cu acestia
 - Nu am reusit sa determin inamicii sa se orienteze cu fata catre jucator
 - trebuie sa fac mici modificari in ceea ce priveste hitbox-ul inamicilor 
 - Probabil din cauza modului in care am incercat sa tratez pozitionarea inamicilor in raport cu jucatorul si coliziunile, acestia lasa impresia ca s-ar teleporta pe harta (nu e asa rau cum suna)
 - trebuie sa gestionez mai bine afisarea mesajelor informative (din message manager + ordinea de display message din game.cpp)
 - (nota) Primeam seg fault din cauza modului in care tratam avansarea in nivel, acum ar trebui sa fie in regula

## Gameplay
### Movement 
Jucătorul se poate deplasa folosind tastele W, A, S, D sau săgețile direcționale astfel:
- W / Săgeata sus: mișcare înainte;
- A / Săgeata stângă: mișcare la stănga;
- S / Săgeata jos: mișcare înapoi;
- D / Săgeata dreaptă: mișcare la dreapta.

### Combat
- Space: trage cu arma selectată.

### Audio Manager
- Tasta M comută între redare și pauză pentru muzica de fundal;
- Tasta = crește volumul melodiei cu două unități;
- Tasta - scade volumul melodiei cu două unități.

### General
- Esc: închide fereastra de joc.
- Enter: reîncepe jocul după ce s-a terminat (indiferent dacă a fost câștigat sau nu)

## Resurse 
Am folosit următoarele resurse:
- pentru textura jucătorului: https://opengameart.org/content/animated-top-down-survivor-player
- pentru textura inamicilor: tipurile de zombie de pe OpenGame Art si skeleton-ul de pe pinterest (revin cu link-uri daca le mai gasesc)
- pentru textura gloanțelor: https://dinopixel.com/bullet-pixel-art-42595
- pentru textura proiectilelor inamicilor de tip Skeleton: https://www.vhv.rs/viewpic/iobbxmo_heart-pixel-art-hd-png-download/
- pentru muzica de fundal: Higher Octane – Vans in Japan (din YouTube Audio Library, fără drepturi de autor)
- pentru font: Google Fonts - SedanSC-Regular, Google Fonts - BlackOpsOne-Regular
- pentru imaginile din background / battlefield: OpenGame Art (revin cu link-uri)

  
### Tema 0

- [ ] Nume proiect (poate fi schimbat ulterior)
- [ ] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [ ] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici
- [ ] constructori de inițializare cu parametri pentru fiecare clasă
- [ ] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [ ] `operator<<` pentru **toate** clasele pentru afișare (`std::ostream`) folosind compunere de apeluri cu `operator<<`
- [ ] cât mai multe `const` (unde este cazul) și funcții `private`
- [ ] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [ ] scenariu de utilizare **cu sens** a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [ ] minim 50-55% din codul propriu să fie C++, `.gitattributes` configurat corect
- [ ] tag de `git`: de exemplu `v0.1`
- [ ] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [ ] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [ ] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [ ] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [ ] smart pointers (recomandat, opțional)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [ ] funcții și atribute `static`
- [ ] STL
- [ ] cât mai multe `const`
- [ ] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [ ] minim 75-80% din codul propriu să fie C++
- [ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] minim 85% din codul propriu să fie C++
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

0. Biblioteci necesare pe Linux (presupunem sistem de operare bazat pe Debian)
```sh
sudo apt-get update && \
  sudo apt-get install libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev \
    libfreetype6-dev
```

Dacă lipsesc și alte biblioteci, ștergeți folder-ul de build de la pasul 1 și reconfigurați proiectul după ce ați instalat ce lipsea.

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
# sau ./scripts/cmake.sh build
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.


3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
# sau ./scripts/cmake.sh install
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

Observație: folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.


## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit
