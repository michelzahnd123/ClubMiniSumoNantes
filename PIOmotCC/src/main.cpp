// --------------------------------------------------------
// Mouvement des moteurs à Courant Continu
// Bouton de démarrage et LED de fonctionnement
// --------------------------------------------------------
// 23/10/2021 - tests Yutaka1 et Yutaka2 en arduino > OK
/*
Un moteur est activé par un pont en H (circuit de puissance)
Le pont en H est commandé par 2 paramètres :
      Moteur AVANT (entier) - Moteur ARRIERE (booléen))
    avance        1 à 255           0
    recule        0                 1 à 255
    roue libre    0                 0
    freinage      1                 1
La broche "moteur AV" est PWM
La broche "moteur ARR" est digitale ou PWM

Un déplacement du robot résulte du mouvement des 2 moteurs
Le déplacement est paramétré par 2 entiers :
    Vitesse GAUCHE 0 à 255 & vitesse DROITE 0 à 255

Le bouton de démarrage est un simple micro-interrupteur à languette
La LED est allumée lorsque les moteurs fonctionnent
*/
// ----- déclarations -----
#include Arduino

// câblage des moteurs
const int moteur1av =8;                // moteur A (gauche)- D0 (blanc)
const int moteur1arr=9;                //                    D1 (vert)
const int moteur2av =10;               // moteur B (droit) - D2 (marron)
const int moteur2arr=11;               //                    D3 (gris)

// calibrage des moteurs
int fmaxGaucheA, fmoyGaucheA, fminGaucheA;            // PWM mot G avance
int fmaxGaucheR, fmoyGaucheR, fminGaucheR;            // recule
int fmaxDroiteA ,fmoyDroiteA, fminDroiteA;            // PWM mot D avance
int fmaxDroiteR ,fmoyDroiteR, fminDroiteR;            // recule

bool print_action, print_vitesse;                     // affichage
int forceGauche, forceDroite;
int duree_run, duree_brake, duree_wait;
int duree_run_max, duree_run_moy, duree_run_min;
int tps_run_arriere1, tps_run_arriere2, tps_run_arriere3;

// bouton ON & LED de mouvement moteurs
const int boutonOn  =2;                               // bouton démarrage
bool bouton_entree;
uint8_t temps_attente;
const int ledOn     =3;                               // LED verte

// --------------------------------------------------------

void setup()
{
// affichage
    Serial.begin(115200);                             // initialize the serial port
    print_action=true;                                // 1 à 3 ms
    print_vitesse=true;                               // 1 à 2 ms

// moteurs CC
    pinMode (moteur1av,OUTPUT);                       // moteur A (gauche)
    analogWrite(moteur1av, 0);
    pinMode (moteur1arr,OUTPUT);
    digitalWrite(moteur1arr, 0); 
    pinMode (moteur2av,OUTPUT);                       // moteur B (droit)
    analogWrite(moteur2av, 0);
    pinMode (moteur2arr,OUTPUT);
    digitalWrite(moteur2arr, 0);

// constantes de vitesse et de temps
    constantes_de_temps();                            // temps et durées des actions
    calibrage_des_moteurs();                          // vitesses avec corrections

// bouton ON & LED mvt
    pinMode (boutonOn,INPUT);                         // départ
    bouton_entree=false;
    temps_attente=5;                                  // nb secondes avant de bouger
    pinMode (ledOn,OUTPUT);                           // LED "en route"
    digitalWrite(ledOn, 0);
}
// --------------------------------------------------------

void loop()
{
    attend_signal_depart();                           // appui bouton
    echauffement_moteurs();                           // calibrage AVANT et ARRIERE
//  run_and_brake();                                  // TEST officiel sur 1m
}
// --------------------------------------------------------

// ----- INITIALISATION -----

void constantes_de_temps()
{
    duree_run=666;                                    // si TEST sur 1 mètre ->> 1325 <<-
    duree_brake=100;                                  // durée freinage
    duree_wait=1000;                                  // temps entre 2 essais

    duree_run_min=600;                                // vitesse min
    duree_run_moy=500;                                // vitesse Moy
    duree_run_max=400;                                // échauffement 40 cm à vitesse MAX    
    
    tps_run_arriere1=500;                             // progression en ARR à vit mini
    tps_run_arriere2=450;                             // temps ARR à vitesse moyenne
    tps_run_arriere3=400;                             // à vitesse MAX
}
// ---------------------------------------------------------

void calibrage_des_moteurs()
// Vitesses mini, moyenne et MAXI - En avant et et arrière
{
    fminGaucheA=90;                                   // vitesse mot G
      fminDroiteA=90;                                 // vitesse mot D
    fminGaucheR=77;                                   // vitesse mot G recule
      fminDroiteR=80;                                 // vitesse mot D recule
    
    fmoyGaucheA=150;
      fmoyDroiteA=150;
    fmoyGaucheR=100;
      fmoyDroiteR=110;
    
    fmaxGaucheA=250;
      fmaxDroiteA=250;
    fmaxGaucheR=120;
      fmaxDroiteR=150;
}
// ---------------------------------------------------------

void attend_signal_depart()
{
    bouton_entree = false;

// attend appui bouton
    if(print_action){Serial.println("Attend : appui pare-choc et appui bouton");}
    while(bouton_entree==false){                      // attend départ
      bouton_entree = digitalRead(boutonOn);
      delay(5);}

// 5 secondes avant de bouger
    Serial.print("compte ");
    Serial.print(temps_attente);
    Serial.println(" secondes ...");
        
    for(uint8_t cpt=0;cpt<temps_attente; cpt++){      // compte 5 secondes
      digitalWrite(ledOn,LOW);
      delay(950);
      digitalWrite(ledOn,HIGH);
      delay(50);}
}
// ---------------------------------------------------------

// ----- FONCTIONS PRINCIPALES -----

void run_and_brake()
// ----- TEST OFFICIEL en VITESSE MAX -----
// pour les 2 épreuves : calcul Vitesse (m/s) et mesure Poussée (gf)
{
    avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
      delay(duree_run);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);
//
    Serial.print("Vitesse G: ");
    Serial.print(fmaxGaucheA);
    
    Serial.print("   D: ");
    Serial.print(fmaxDroiteA);
    
    Serial.print("     durée: ");
    Serial.println(duree_run);
    Serial.println("Fin de TEST - Attente RESET");
    Serial.println("");
    while(1){;}                                       // RESET pour sortir de là !!!
}
// ---------------------------------------------------------

void echauffement_moteurs()
// ----- VERIFICATION du CALIBRAGE AVANT ET ARRIERE des MOTEURS -----
{
// Déplacement : Vitesse mini
    avance_tout_droit(fminGaucheA, fminDroiteA);
      delay(duree_run_min);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);

    if(print_action){Serial.print("");}
    if(print_vitesse){
      Serial.print("Vitesse G: ");
      Serial.print(fminGaucheA);
      Serial.print("   D: ");
      Serial.print(fminDroiteA);
      Serial.print("     durée: ");
      Serial.println(duree_run_min);}

    recule_tout_droit(fminGaucheR, fminDroiteR);
      delay(tps_run_arriere1);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);

    if(print_action){Serial.print("");}
    if(print_vitesse){
      Serial.print("        G: ");
      Serial.print(fminGaucheR);
      Serial.print("   D: ");
      Serial.print(fminDroiteR);
      Serial.print("     durée: ");
      Serial.println(duree_run_min);}
      
// Déplacement : Vitesse Moyenne
    avance_tout_droit(fmoyGaucheA, fmoyDroiteA);
      delay(duree_run_moy);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);

    if(print_action){Serial.print("");}
    if(print_vitesse){
      Serial.print("Vitesse G: ");
      Serial.print(fmoyGaucheA);
      Serial.print("   D: ");
      Serial.print(fmoyDroiteA);
      Serial.print("     durée: ");
      Serial.println(duree_run_moy);}
      
    recule_tout_droit(fmoyGaucheR, fmoyDroiteR);
      delay(tps_run_arriere2);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);

    if(print_action){Serial.print("");}
    if(print_vitesse){
      Serial.print("        G: ");
      Serial.print(fmoyGaucheR);
      Serial.print("   D: ");
      Serial.print(fmoyDroiteR);
      Serial.print("     durée: ");
      Serial.println(duree_run_moy);}
      
// Déplacement : Vitesse MAXI
    avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
      delay(duree_run_max);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);

    if(print_action){Serial.print("");}
    if(print_vitesse){
      Serial.print("Vitesse G: ");
      Serial.print(fmaxGaucheA);
      Serial.print("   D: ");
      Serial.print(fmaxDroiteA);
      Serial.print("     durée: ");
      Serial.println(duree_run_max);}
      
    recule_tout_droit(fmaxGaucheR, fmaxDroiteR);
      delay(tps_run_arriere3);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);

    if(print_action){Serial.print("");}
    if(print_vitesse){
      Serial.print("        G: ");
      Serial.print(fmaxGaucheR);
      Serial.print("   D: ");
      Serial.print(fmaxDroiteR);
      Serial.print("     durée: ");
      Serial.println(duree_run_max);}
    
  Serial.println("Fin d'échauffement - Attente RESET");
  Serial.println("");
  while(1){;}                                         // RESET pour sortir de là !!!
}
// ---------------------------------------------------------

// ----- SOUS FONCTIONS -----

void avance_tout_droit(int fGauche, int fDroite)
{
  if(print_action){Serial.print("avance tout droit");
    if(print_vitesse){
      Serial.print("  G: ");
      Serial.print(fGauche);
      Serial.print("  D: ");
      Serial.print(fDroite);
      Serial.print("   ");}}
    
  digitalWrite(ledOn,HIGH);

    analogWrite(moteur1av, fGauche);                  // mot G avant
    digitalWrite(moteur1arr, 0); 

    analogWrite(moteur2av, fDroite);                  // mot D avant
    digitalWrite(moteur2arr, 0);
}
// ---------------------------------------------------------

void recule_tout_droit(int fGauche, int fDroite)
{
  if(print_action){Serial.print("recule tout droit");
    if(print_vitesse){
      Serial.print("  G: -");
      Serial.print(fGauche);
      Serial.print("  D: -");
      Serial.print(fDroite);
      Serial.print("   ");}}
    
  digitalWrite(ledOn,HIGH);
  
    analogWrite(moteur1arr, fGauche);                 // mot G arrière
    digitalWrite(moteur1av, 0); 

    analogWrite(moteur2arr, fDroite);                 // mot D arrière
    digitalWrite(moteur2av, 0);
}
// ---------------------------------------------------------

void stop_mouvement()
{
  //if(print_action){Serial.println("arret");}
  digitalWrite(ledOn,LOW);
  
    analogWrite(moteur1av, 0);                        // stop mot G
    digitalWrite(moteur1arr, 0); 

    analogWrite(moteur2av, 0);                        // stop mot D
    digitalWrite(moteur2arr, 0);
}
// ---------------------------------------------------------

void freinage()
{
  if(print_action){Serial.print("freinage brusque ");}
  digitalWrite(ledOn,LOW);
  
    digitalWrite(moteur1av, 1);                       // frein mot G
    digitalWrite(moteur1arr, 1); 

    digitalWrite(moteur2av, 1);                       // frein mot D
    digitalWrite(moteur2arr, 1);
}
// ---------------------------------------------------------

void tourne_a_droite(int fGauche, int fDroite)
{
  if(print_action){Serial.print("tourne à droite  ");
    if(print_vitesse){
      Serial.print("  G: ");
      Serial.print(fGauche);
      Serial.print("  D: ");
      Serial.print("0");
      Serial.print("   ");}}
    
  digitalWrite(ledOn,HIGH);
  
    analogWrite(moteur1av, fGauche);                  // mot G avant
    digitalWrite(moteur1arr, 0); 

    digitalWrite(moteur2arr, 0);                      // mot D stop
    digitalWrite(moteur2av, 0);
}
// ---------------------------------------------------------

void sur_place_droite(int fGauche, int fDroite)
{
  if(print_action){Serial.print("sur place droite ");
    if(print_vitesse){
      Serial.print("  G: ");
      Serial.print(fGauche);
      Serial.print("  D: -");
      Serial.print(fDroite);
      Serial.print("   ");}}

  digitalWrite(ledOn,HIGH);
  
    analogWrite(moteur1av, fGauche);                  // mot G avant
    digitalWrite(moteur1arr, 0); 

    analogWrite(moteur2arr, fDroite);                 // mot D arrière
    digitalWrite(moteur2av, 0);
}
// ---------------------------------------------------------

void tourne_a_gauche(int fGauche, int fDroite)
{
  if(print_action){Serial.print("tourne à gauche  ");
    if(print_vitesse){
      Serial.print("  G: ");
      Serial.print("0");
      Serial.print("  D: ");
      Serial.print(fDroite);
      Serial.print("   ");}}
  
  digitalWrite(ledOn,HIGH);
  
    digitalWrite(moteur1arr, 0);                      // mot G stop
    digitalWrite(moteur1av, 0); 

    analogWrite(moteur2av, fDroite);                  // mot D avant
    digitalWrite(moteur2arr, 0);
}
// ---------------------------------------------------------

void sur_place_gauche(int fGauche, int fDroite)
{
  if(print_action){Serial.print("sur place gauche ");
    if(print_vitesse){
      Serial.print("  G: -");
      Serial.print(fGauche);
      Serial.print("  D: ");
      Serial.print(fDroite);
      Serial.print("   ");}}
  
  digitalWrite(ledOn,HIGH);
  
    analogWrite(moteur1arr, fGauche);                 // mot G arrière
    digitalWrite(moteur1av, 0); 

    analogWrite(moteur2av, fDroite);                  // mot D avant
    digitalWrite(moteur2arr, 0);
}
// ---------------------------------------------------------

void esquive_a_droite(int fGauche, int fDroite)
{
  if(print_action){Serial.print("esquive droite   ");
    if(print_vitesse){
      Serial.print("  G: ");
      Serial.print("0");
      Serial.print("  D: -");
      Serial.print(fDroite);
      Serial.print("   ");}}
  
  digitalWrite(ledOn,HIGH);
  
    digitalWrite(moteur1arr, 0);                      // mot G stop
    digitalWrite(moteur1av, 0); 

    analogWrite(moteur2arr, fDroite);                 // mot D arriere
    digitalWrite(moteur2av, 0);
}
// ---------------------------------------------------------

void esquive_a_gauche(int fGauche, int fDroite)
{
  if(print_action){Serial.print("esquive gauche   ");
    if(print_vitesse){
      Serial.print("  G: -");
      Serial.print(fGauche);
      Serial.print("  D: ");
      Serial.print("0");
      Serial.print("   ");}}
  
  digitalWrite(ledOn,HIGH);
  
    analogWrite(moteur1arr, fGauche);                 // mot G arriere
    digitalWrite(moteur1av, 0); 

    digitalWrite(moteur2arr, 0);                      // mot D stop
    digitalWrite(moteur2av, 0);
}
// ---------------------------------------------------------
// ---------------------------------------------------------