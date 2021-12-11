# ClubMiniSumoNantes
_Plateforme C Nantes Club de robots Mini SUMO_

## INTRODUCTION
L'ambition du projet est de concevoir et réaliser plusieurs robots et de s'engager dans le tournoi national de SUMO.
Le groupe est composé de membres du FabLab de Nantes, Plateforme C.


## BRANCHES
Le répertoire GitHub est structuré est 3 branches :
1. **Branche MAIN**
    - Elle contient la version stable du code. Le code a été testé, revu et validé.
    - Le but de cette branche est de constituer le code de référence pour les clones que nous souhaitons réaliser.
    - Le code de référence sera le point de départ pour optimiser finement la stratégie.

2. **Branche DEV**
    - Elle contient les fonctionnalités terminées.
    - Les fonctionnalités peuvent avoir encore des bugs ou ne pas s'interfacer correctement entre elles.
    - L'intérêt de cette branche est de faire des tests et de permettre les échanges de code entre les membres du groupe.

3. **Branche de fonctionnalités**
    - Elle sert à développer les fonctionnalités.
    - Elle est vouée à disparaître lorsque la fonctionnalité est terminée.

  
## DEVELOPPEMENT
### Les choix techniques
Plusieurs options ont été prises concernant la conception des robots :
- **C++** (*Arduino*)
- **ESP32**
- **P**rogrammation **O**rientée **O**bjet
- IDE : **platformIO**
  
### L'arborescence du projet
Afin que chaque membre puisse apporter sa contribution, nous utilisons l'arborescence :

```bash
.
├── RobotSumo # dossier racine du projet
│   ├── lib # dossier contenant les libs crées pour le projet
│   │   ├── Moteur # exemple de lib sous forme d'un sous projet
│   │   │   └── src # source de la lib
│   │   │       ├── main.cpp
│   │   │       ├── moteur.cpp
│   │   │       └── moteur.h
│   │   └── ...
│   └── src # source du projet principal
│       ├── main.cpp
│       └── ...
├── Test # dossier de tests divers
│   └── ...
└── Resource # dossier de ressources du projet
    └── ...
```


> lib

    Chaque fonctionnalité crées pour le projet est dans son propre dossier PlatfomeIO.
    Ce qui permet de tester chaque fonctionnalité individuellement.
    Elles sont rangées dans le dossier "Lib" du projet pour être utilisées par le code source du projet principal.

> src

    Contient le programme principal "main.cpp"
    Il est destiné à tester le fonctionnement de la classe.

# Affectation des broches ESP32

GPIO | Classe | Instance | Entree/Sortie
----- | ----- | ----- | -----
 2 | presence | JS40F AG | es
 4 | noir blanc | cny70 G | es
 5 | bouton | contact AV | 
12 | sortie | LED work | s
13 | | | es
14 | | | e
15 | bouton | depart ON | e
16 | M6050 | inter | es
17 | | | es
18 | noir blanc | cny70 D | es
19 | noir blanc | cny70 AV | es
21 | I2C | SDA | es
22 | I2C | SCL | es
23 | presence | JS40F AD | es
25 | | | es
26 | | | es
27 | | | es
32 | sortie pwm | moteur droit | es
33 | sortie pwm | moteur gauche | es
34 | | reserve inter E03 | e
35 | | reserve inter E03 | e
36 | | reserve inter E03 | e
39 | | reserve inter E03 | e
VIN | 5V | alimentation robot | --
EN | RESET | arret robot | --
