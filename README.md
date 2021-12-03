# ClubMiniSumoNantes
_Plateforme C Nantes Club de robots Mini SUMO_

## AMBITION
L'ambition du projet est de concevoir et réaliser plusieurs robots et de s'engager dans le tournoi national de SUMO.
Le groupe est composé de membres du FabLab de Nantes, Plateforme C.


## BRANCHES
Le répertoire GitHub est structuré est 3 branches correspondant au niveau de validation des fonctionnalités :
1. **Branche MAIN**
    - Branche de référence du code pour le robot et tous les clones que nous que nous souhaitons réaliser.
    - L'intérêt de cette branche est de constituer le code de référence pour optimiser finement la stratégie.

2. **Branche DEV**
    - Branche de stockage des fonctionnalités qui commencent à fonctionner de manière autonome.
    - L'intérêt de cette branche est de tester la compatibilité et les interfaces entre les fonctionnalités.

3. **Branche Test-PIO**
    - Branche temporaire pour les fonctionnalités spécifiques en cours de développement.
    - L'intérêt de cette branche est de faciliter l'échange du code entre membres du groupe ;)

  
## CODAGE
### Les partis pris
Plusieurs options ont été prises concernant le codage et la façon de coder un robot dans le groupe PCS :
- **C++** Arduino sur processeur ESP32
- **P**rogrammation **O**rientée **O**bjet
- Gestion des versions avec **GIT** et gestion distante **GitHub**
- Editeur de code **VSCode** et **platformIO**
  
### Compilation
Afin que chaque membre du projet puisse apporter sa contribution, nous avons défini l'arborescence utile.

> lib

    Chaque classe d'ojets a ses propres fichiers stockée dans **lib**
      - entête de la classe "fichier.h"
      - description des membres de la classe "fichier.cpp"

> src

    Contient le programme principal "main.cpp" (void Setup & void Loop)
    Il est destiné à tester le fonctionnement de la classe.

