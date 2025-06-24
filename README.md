# The Last Stand: Undead Uprising

## [RO]
## Descriere 
The Last Stand: Undead Uprising este un joc de tip shooter 2D, dezvoltat în C++ cu ajutorul bibliotecii SFML (versiunea 2.6). Arhitectura jocului respectă principiile programării orientate pe obiect, asigurând o structură clară și extensibilă a codului. 
*Proiectul a fost realizat ca parte a activității academice universitare.*

Jocul propune o experiență dinamică în care jucătorul trebuie să supraviețuiască valurilor succesive de inamici, generați progresiv pe durata fiecărui nivel. Acțiunea se desfășoară pe o hartă fixă, iar dificultatea crește treptat, atât prin numărul, cât și prin complexitatea inamicilor, pe măsură ce personajul avansează. 

La început, jucătorul are posibilitatea de a selecta una dintre cele patru arme disponibile: AK-47, M416, Shotgun sau Pistol, fiecare având particularități ce determină stilul de joc și strategiile de luptă împotriva celor patru tipuri de inamici. 

Pe parcurs, vor apărea pe hartă, aleatoriu, poțiuni ce oferă jucătorului efecte temporare, precum îmbunătățirea vitezei, refacerea sănătății sau creșterea puterii de atac, susținând astfel o diversificare și adaptare eficientă a strategiilor de joc.

Pentru toate detaliile și o experiență completă, te încurajez să te aventurezi în joc. Mulțumesc și distracție plăcută! :) 

### Features in dezvoltare
 - Implementarea unui meniu de endgame

### Probleme
 - Ar trebui să implementez un sistem mai bun de detectare a coliziunilor, astfel încât să nu se poată suprapune nici inamicii între ei, nici jucătorul cu aceștia
 - Nu am reușit sa determin inamicii să se orienteze cu fața către jucător

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


## [EN]
The Last Stand: Undead Uprising is a 2D shooter game developed in C++ using the SFML library (version 2.6). Its architecture follows object-oriented programming principles, ensuring a clear and extensible code structure.
*The project was developed as part of academic coursework at the university.*

The game offers a dynamic experience in which the player must survive successive waves of enemies progressively generated throughout each level. The action unfolds on a fixed map, with difficulty increasing steadily through both the number and complexity of enemies.

At the start, the player can choose one of four available weapons: AK-47, M416, Shotgun, or Pistol, each with unique characteristics that influence the gameplay and combat strategy against four distinct enemy types.

Throughout the game, potions spawn randomly on the map, granting temporary effects such as increased movement speed, health regeneration, or enhanced attack power, encouraging varied and adaptive combat strategies.

For all the details and the full experience, I invite you to immerse yourself in the game. Thank you, and enjoy! :)

## Gameplay
### Movement 
The player can move using the W, A, S, D keys or the arrow keys, as follows:
- W / Up Arrow: move forward
- A / Left Arrow: move left
- S / Down Arrow: move backward
- D / Right Arrow: move right

### Combat
- Spacebar: fires the selected weapon

### Audio Manager
M: toggles background music on/off
=: increases music volume by two units
-: decreases music volume by two units

### General
- Esc: closes the game window
- Enter: restarts the game after it ends (whether the player wins or loses)


### Cerințele proiectului 
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

Am folosit următoarele resurse:
- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- pentru textura jucătorului: https://opengameart.org/content/animated-top-down-survivor-player
- pentru textura inamicilor: tipurile de zombie de pe OpenGame Art si skeleton-ul de pe pinterest (revin cu link-uri dacă le mai gasesc)
- pentru textura gloanțelor: https://dinopixel.com/bullet-pixel-art-42595
- pentru textura proiectilelor inamicilor de tip Skeleton: https://www.vhv.rs/viewpic/iobbxmo_heart-pixel-art-hd-png-download/
- pentru textura perk-urilor: https://opengameart.org/content/simple-potion-animations
- pentru muzica de fundal: Higher Octane – Vans in Japan (din YouTube Audio Library, fără drepturi de autor)
- pentru font: Google Fonts - SedanSC-Regular, Google Fonts - BlackOpsOne-Regular
- pentru imaginile din background / battlefield: OpenGame Art (revin cu link-uri)
