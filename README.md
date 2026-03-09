# Solitude 408

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
pacman -S pacman -S mingw-w64-x86_64-gcc
```
8. Aller dans le dossier d'installation MSYS2:
```
msys64/home/<utilisateur>
``` 
9. Cloner le dépôt dedans.
```
git clone https://github.com/HugoAyaden/Solitude-408.git
``` 
10. Toujours dans le terminal MSYS2 MINGW64, aller à la racine du dépôt:
   ```
/Solitude-408
```
11. Toujours dans le terminal MSYS2 MINGW64, compiler le jeu avec:
```
make all
```
12. Toujours dans le terminal MSYS2 MINGW64, lancer le jeu avec:
```
./bin/Solitude408.exe
```
