# ClubMiniSumoNantes
_Plateforme C Nantes Club de robots Mini SUMO_

## AMBITION
L'ambition du projet est de concevoir et réaliser plusieurs robots et de s'engager dans le tournoi national de SUMO.
Le groupe est composé de membres du FabLab de Nantes, Plateforme C :
- volontaires pour dépenser gracieusement du temps pour fabriquer, expérimenter, tester, valider des éléments ou composants,
- motivés par le défi que représente la compétition nationale de robots autonomes dans la catégorie "Mini SUMO".


## DOCUMENTATION
Toute la documentation (conception, test, plans et schémas) du projet est mise en commun et libre d'accès (public).
Les éléments des domaines "mécanique" et "électronique" sont rangés et stockés dans un répertoire **Google Drive**.
Le codage est géré, documenté et stocké dans ce même répertoire **GitHub**.

### Mécanique & électronique
La structure du stockage "Google Drive" est liée aux éléments essentiels et aux choix de conception :
1. **Mécanique**
    - Structure du robot à 2 roues
    - Motorisation brushless
    - Roues et pneus silicone
    - Lame avant (secret de M. Takayuki)
2. **Electronique**
    - Processeur ESP32 programmé en C++
    - Capteurs de distance et de présence
    - Alimentation LiPo 3S et Circuits Imprimés

### Code
Le répertoire GitHub est structuré est 3 branches correspondant au niveau de validation des fonctionnalités :
1. **Branche Test-PIO**
    - Branche libre permettant d'écrire, modifier, tester, vérifier une fonctionnalité "pour voir" , tout en commençant à gérer le code.
    - Les sous-projets de la banche Test-PIO constituent le point d'entrée des fonctionnalités du robot : moteur, capteur, ...
    - L'intérêt de cette branche est de faciliter l'échange du code entre membres du groupe ;)
2. **Branche DEV**
    - Branche de stockage des fonctionnalités qui commence à fonctionner de manière autonome.
    - Les fonctions fusionnées (mergées) dans la branche DEV peuvent encore comporter des bugs, ou ne pas s'interfacer correctement entre elles.
    - L'intérêt de cette branche est de tester la compatibilité et les interfaces entre les fonctionnalités.
3. **Branche MAIN**
    - Branche de référence du code pour le robot et tous les clones que nous que nous souhaitons réaliser.
    - Le code fusionné dans la branche MAIN est (en principe) exempt d'erreur, il a été testé, revu et validé par le groupe PCS.
    - L'intérêt de cette branche est de constituer un code de référence sain pour s'aventurer dans l'optimisation des stratégies.
  
  
  ## CODAGE
  ### Les partis pris
  Plusieurs options ont été prises concernant le codage et la façon de coder un robot dans le groupe PCS :
  - **C++** Arduino sur processeur ESP32
  - **P**rogrammation **O**rientée **O**bjet
  - Gestion des versions avec **GIT** et gestion distante **GitHub**
  - Editeur de code **VSCode** et **platformIO**
  
  ### Compilation
  Afin que chaque membre du projet puisse apporter une contribution efficace, nous avons défini une arborescence de rangement des fichiers.
  La création d'un mini projet dans la branche Test-PIO génère automatiquement une liste de fichiers et répertoires secondaires :
> * .pio

      Non utilisé en première approche
      Contient les librairies externes téléchargées pour le mini projet
> * .vscode

      Non utilisé
      Contient les fichiers .json
> * include

      Non utilisé
      Le fichier REDAME recommande :
        - le dépôt du fichier principal dans le répertoire "src" 
        - la création d'un fichier entête .h (en C) partageable entre plusieurs projets
        - mais nous n'utiliserons pas ce répertoire pour stocker le .h
> * lib

      Chaque classe d'ojets aura son propre fichier.h et fichier.cpp stocké dans lib
      Répertoire recommandé et utilisé pour stocker :
        - l'entête de la classe fichier.h
        - la description des membres de la classe fichier.cpp
      on peut également ajouter un niveau d'arborescence à l'intérieur de lib (cf README.lib)
> * src

      Contient le programme principal "main.cpp"
      Il est initialisé automatiquement à la création du petit projet (void Setup & void Loop)
      En principe ce programme est destiné à tester le fonctionnement de la classe
> * test

      Non utilisé sauf mise en oeuvre d'une procédure de test unitaire
> * .gitignore

      Initialisé automatiquement dans une version minimaliste
      Nous avons créé un ".gitignore" très complet au niveau du projet PCS
> * .plateformio.ini

      Initialisé automatiquement avec les paramètres :
        - platform = espressif32
        - board = esp32doit-devkit-v1
        - framework = arduino
      Auquel, il faut éventuellement ajouter :
        - monitor_speed = 115200


## VIE DU PROJET
### Jalonnement du projet
A ce jour, la date d'arrivée du projet correspond au Tournoi de Mini SUMO à THIONVILLE (57).
Ce sera l'une des 2 dates : 21/5/2022 ou 11/6/2022.
Nous organiserons quelques points intermédiaires pour assurer la réalisation :
- bilan 2021 avant les fêtes de fin d'année, par exemple le 16/12/2021 au 38 Breil,
- bilan de l'hiver, par exemple le 10 février 2022 au 38 Breil,
- bilan de printemps, par exemple le 14 avril 2022 à Plateforme C.
Ces bilans pourraient être l'occasion d'inviter d'autre personnes de PING.

### Carte **kanban**
Pour tenir compte de la bonne volonté des membres de l'équipe étendue du projet, 
de leurs contraintes d'agenda et de leur disponibilité, nous proposons une méthode de participation "à la carte" :
- A chaque idée ou tâche identifiée pour faire progresser le projet est rédigée une carte "kanban"
- La carte est rédigée le plus précisément possible : problème, type de sujet, fonction attendue, urgence
- Liste des éléments concrets définissant le résultat attendu
- La carte est affectée à une personne de l'équipe si "ça va de soi" !

Exemple de cartes réalisées ou en cours :
>  * allumer une LED en programmation objet sur ESP32 pour signaler la détection de l'adversaire
>  * allumer une série de 4 LED (rouge, verte, blanche et bleue) en "chenille" pour marquer la victoire du combat
>  * appui bouton pour déclencher le décomptage du temps avant combat
>  * configurer la carte de contrôle ESP pour faire tourner les moteurs brushless dans les 2 sens et permettre l'esquive
>  * simuler les mouvements combinés des 2 moteurs avec un joystick pour visualiser le comportement du robot

Exemples de cartes à réaliser :
>  * lire le capteur noir-blanc cny70 en digital pour gestion de la position du robot sur le dohyo
>  * lire le capteur cny70 en analogique pour calibrer la "couleur" du noir avant le combat

La réunion du jeudi à PlateformeC ou à 38 Breil est l'occasion de :
- Revoir les cartes kanban en-cours,
- Les avancer au fur et à mesure de leur réalisation,
- Les clôturer lorsque terminées :)

### WIKI
Le projet est l'occasion d'acquérir des nouvelles connaissances et de les partager entre nous.
C'est aussi une excellente occasion de formaliser ces nouvelles acquisitions et les diffuser plus largement.
Nous proposons de choisir les sujets et de créer les fiches WIKI correspondantes.

Exemple de cartes WIKI à réaliser :
> * configuration de la carte de contrôle ESC pour optimisation des paramètres (direction, son, largeur d'impulsion)
> * utilisation du capteur GP2Y0-E03 pour mesurer la présence & la distance avec connexion I2C



