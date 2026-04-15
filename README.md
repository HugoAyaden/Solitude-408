

# Solitude 408
![Logo Solitude-408](https://drive.google.com/uc?export=view&id=1uMf0oEomDBRDKd7BwGhxYXi_xNRHaE6f)
## Membres du projet:

 - AMARA Louay
 - AYADEN Hugo
 - DOS SANTOS Mathis
 - LEFEVRE TAUGOURDEAU Bastien

## Projet de L2 informatique 2025-2026
### Durée de projet du 13 janvier 2026 au 17 avril 2026

### Description du projet:

Solitude 408 est un jeu de survie d'horreur où deux collègues à bord d'un vaisseau spatial doivent survivre 24h face à un alien avant d'être secourus. L'équipe spatiale devra détecter l'alien avec des caméras de sécurité tout en faisant attention à l'énergie du vaisseau spatial. Pour cela, l'équipe peut gérer la lumière des différentes salles pour économiser de l'énergie au dépend de sa sécurité, bloquer les portes de la salle de contrôle pour se défendre. Le seul objectif, survivre 24h.

### Mécaniques de gameplay :

 - Algorithme de décision making pour les monstres
 - Stystème de boucle de gameplay


### Outils utilisés:
 - SDL2 (fenêtre du jeu)
 - SDL2_image
 - SDL2_ttf
 - Compilateur GCC
 - Langage C
 - Gimp (images)
 - Audacity (sons)

### Lien Gantt prévisionnel(Google Sheet):
[Google Sheet prévisionnel](https://docs.google.com/spreadsheets/d/10BtX8lV49BRHHMKD-WF7gbojdl62evs0IOK-swW39dE/edit?usp=sharing)

### Lien Gantt temps réel(Google Sheet):
[Google Sheet réel](https://docs.google.com/spreadsheets/d/161Telb0sQAwwcge502TN28Llk9Ka9GpzFWoxdfIsfsk/edit?usp=drive_link)

### Lien Livrables (Google drive):
[Google Drive Livrables](https://drive.google.com/drive/folders/1sYh54YUGxozC2EAchAByC7XBdANsIjq6?usp=sharing)

### Documentation doxygene:

link

### Comment jouer?:
Votre objectif est de survivre 5 minutes aux attaques du monstre pendant chaque nuit.
Pour vous défendre, il vous faut:
 - Regardez les caméras pour déduire la position du monstre.
 - Fermer la porte si le monstre apparaît devant celle-ci.
Il vous faut aussi gérer votre batterie jusqu'à la fin de la nuit:
- Laisser les lumières des portes et la lumière générale drainent la batterie
La lumière permet de voir si le monstre est à la porte.

Il y a deux monstres dans le jeu. Pour les contrer :
Monstre: Il faut fermer les portes.
Mimique: La lumière générale doit être éteinte.

Note: Si les deux monstres vous attaquent en même temps, le mimique passera AVANT le monstre,
il vous faudra donc éteindre les lumières PUIS les rallumer et fermer les portes.

Avec votre souris, vous pouvez déplacer la caméra de jeu pour afficher les portes et les boutons.
Pour cela, il faut que la souris soit aux extrémités gauche ou droite de la fenêtre de jeu.


### Installation(Linux):

1. Dans le terminal Linux, installer les packages suivant:
2. Build-essential (make + gcc):
```
sudo  apt update
sudo  apt install build-essential
```
3. pkg-config:
```
sudo  apt install pkg-config
```
4. Sdl 2:
```
sudo  apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```
------------------------------------
Si vous voulez utiliser Git :

4. Git:
```
sudo  apt install git
```
5. Clone:
```
git clone https://github.com/HugoAyaden/Solitude-408.git
```
------------------------------------

SINON

------------------------------------
4. Télécharger le dépôt.
```
Code -> Download zip
```
------------------------------------

5 Entrez dans la racine du dépôt:
```
cd Solitude-408
```
6. Ouvrez un nouveau terminal dans la racine du dépôt et compiler le jeu avec:
```
make all
```
7. Toujours dans le terminal, lancer le jeu avec:
```
./bin/Solitude408
```

### Installation(Windows+MSYS2):
1. Télécharger et installer Msys2: 
[Lien MSYS2](https://www.msys2.org/)

2. Lancer MSYS2 MINGW64 (icon bleu)
3. Dans le terminal MSYS2 MINGW64, installer les packages suivant:
4. Make:
```
pacman -S make
```
5. SDL2:
```
pacman -S mingw-w64-x86_64-SDL2 \
          mingw-w64-x86_64-SDL2_image \
          mingw-w64-x86_64-SDL2_ttf \
          mingw-w64-x86_64-SDL2_mixer
```
6. Pkgconf:
```
 pacman -S mingw-w64-x86_64-pkgconf
```
7. GCC:
```
pacman -S mingw-w64-x86_64-gcc
```
8. Dans l'explorateur de fichiers :
```
C:/msys64/home/<utilisateur>
```

------------------------------------
Si vous voulez utiliser Git :

9. Dans le terminal MSYS2 MINGW64, Git:
```
pacman -S git
```
10. Dans le terminal MSYS2 MINGW64, clone:
```
git clone https://github.com/HugoAyaden/Solitude-408.git
```
------------------------------------

SINON

------------------------------------
9. Télécharger le dépôt.
```
Code -> Download zip
```
10. Déziper le dépôt dans le dossier suivant:.
```
C:/msys64/home/<utilisateur>/<le_depot>
``` 
11. Toujours dans le terminal MSYS2 MINGW64, aller à la racine du dépôt:
   ```
cd C:/msys64/home/<utilisateur>/Solitude-408/
```
12. Toujours dans le terminal MSYS2 MINGW64, compiler le jeu avec:
```
make all
```
13. Toujours dans le terminal MSYS2 MINGW64, lancer le jeu avec:
```
./bin/Solitude408.exe
```
