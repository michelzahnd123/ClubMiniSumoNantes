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
 1 | Comm | TX | bleu
 2 | Presence | JS40F_G | es
 3 | Comm | RX | vert
 4 | NoirBlanc | cny70_G | es
 5 | Bouton | contactAV | es - gris
12 | Led | led_work | s - jaune
13 | Comm | Beep | es - gris
14 | | | es - LIBRE
15 | Bouton | departON | es - bleu
16 | Accelero | M6050 (inter) | es - marron
17 | Comm | V LiPo | es - marron
18 | NoirBlanc | cny70_D | es
19 | NoirBlanc | cny70_AV | es
21 | I2C | SDA | es - jaune
22 | I2C | SCL | es - blanc
23 | Presence | JS40F_D | es
25 | | | es - LIBRE
26 | | | es - LIBRE
27 | | | es - LIBRE
32 | Moteur | moteurDroite (pwm) | es - blanc
33 | Moteur | moteurGauche (pwm) | es - blanc
34 | Distance | E03_RG (inter) | e
35 | Distance | E03_AG (inter) | e
36 | Distance | E03_AD (inter) | e
39 | Distance | E03_RD (inter) | e
VIN | 8V | | --
EN | RESET | arret robot | orange
