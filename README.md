# ClubMiniSumoNantes
_Plateforme C Nantes Club de robots Mini SUMO_

## INTRODUCTION
L'ambition du projet est de concevoir et réaliser plusieurs robots et de s'engager dans le tournoi national de SUMO.
Le groupe est composé de membres du FabLab de Nantes, Plateforme C.


## BRANCHES
Le répertoire GitHub est structuré est 3 branches :
1. **Branche MAIN**
    - Elle contient la version stable du code
    - Branche de référence du code pour le robot et tous les clones que nous que nous souhaitons réaliser.
    - L'intérêt de cette branche est de constituer le code de référence pour optimiser finement la stratégie.

2. **Branche DEV**
    - Branche de stockage des fonctionnalités qui commencent à fonctionner de manière autonome.
    - L'intérêt de cette branche est de tester la compatibilité et les interfaces entre les fonctionnalités.

3. **Branche Test-PIO**
    - Branche temporaire pour les fonctionnalités spécifiques en cours de développement.
    - L'intérêt de cette branche est de faciliter l'échange du code entre membres du groupe ;)

  
## Developpement
### Les choix technique
Plusieurs options ont été prises concernant la conseption des robot :
- **C++** (*Arduino*)
- ESP32
- **P**rogrammation **O**rientée **O**bjet
- IDE : **platformIO**
  
### L'arborescence du projet
Afin que chaque membre du projet puisse apporter sa contribution, nous avons défini l'arborescence utile.

```bash
.
├── RobotSumo # dossier racine du projet
│   ├── lib # dossier contenant les libs crée pour le projet
│   │   ├── Moteur # exemple de lib sous la forme d'un sous projet
│   │   │   └── src # source de la lib
│   │   │       ├── main.cpp
│   │   │       ├── moteur.cpp
│   │   │       └── moteur.h
│   │   └── ...
│   └── src # souce du projet principale
│       ├── main.cpp
│       └── ...
├── Test # dossier de test divers
│   └── ...
└── Resource # dossier de resource du projet
    └── ...
```



> lib

    Chaque Bibliothère crées pour le projet est dans son propre projet PlatfomeIO qui permet des les tester individuelement
    Elle sont dans le dossier Lib du projet pour être utiliser par le code pricipale.

> src

    Contient le programme principal "main.cpp" (void Setup & void Loop)
    Il est destiné à tester le fonctionnement de la classe.

