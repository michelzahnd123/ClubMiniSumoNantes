// --------------------------------------------------------
// Capteurs CNY70 de la couleur NOIR/BLANC du sol
// Contacts AVANT (gauche et droit)
// --------------------------------------------------------
// 24/10/2021 - reprise du programme Yutaka2
/*
Le capteur CNY70 est un détournement des capteurs d'imprimante 2D
Il est sensible à la réflexion d'un obstacle situé à qqs mm de distance
Il est composé :
. d'une photodiode IR alimentée par 5V et 150 Ohm
. d'un phototransistor utilisé en commutation (passant/bloqué)
Le montage Yutaka2 est l'inverse de Yutaka1 :
. NOIR : 0 (gnd)
. BLANC : 1 (5V)
L'entrée de chaque cny70 est analogique pour prendre en compte la "noirceur" du NOIR

Les contacts AVANT sont de simples micro-interrupteurs à languette :
. contact : 1 (5V)
. libre : 0 (gnd)
Le câblage actuel est fait sur des broches analogiques (superflu pour contacts)

Codification du paramètre "priorité_recherche" au départ : 
  contact Gauche + contact Droit + bouton OnOff
      .               .               1           -> test vitesse 1 m       0
      1               .               1           -> adversaire à Gauche    1
      .               1               1           -> adversaire à Droite    2
      1               1               1           -> adversaire à l'arrière 3
      .               2               1           -> test sortie cube       4       
      2               .               1           -> echauffement moteurs   5
      2               2               1           -> vitesse arrière        6

*/
// ----- déclarations -----
#include Arduino

// ----- affichage -----
bool print_action;

// ----- On Off ----- ON (bleu : 2) - LED (vert : 3)
const int boutonOn  =2;                               // bouton démarrage
const int ledOn     =3;
bool bouton_entree;

uint8_t priorite_recherche;
uint8_t temps_attente;

/* ----- Yutaka 1 : entrées DIGITALES  ----- 
const int CNY70_A=22;                                 // CNY avant
const int contact_D=24;                               // contact droit
const int CNY70_D=26;                                 // CNY droit
const int contact_G=28;                               // contact gauche
const int CNY70_G=30;                                 // CNY gauche 
*/
// ----- entree ANALOGIQUES : Yutaka 2 -----
const int CNY70_A=A6;                                 // CNY A
const int contact_D=A8;                               // contact D
const int CNY70_D=A10;                                // CNY D
const int contact_G=A12;                              // contact G
const int CNY70_G=A14;                                // CNY G

// ----- capteurs CNY70 ----- (fils bleus)
bool cny70_A, cny70_G, cny70_D;
bool ligne_blanche;
uint8_t cpt_piste_noire, max_piste_noire;
int limite_noir_blanc;

// ----- contacts AVANT ----- (fils marron)
bool boutonD, boutonG;
bool contact_avant;
bool init_contactG0, init_contactG1, init_contactG2;
bool init_contactD0, init_contactD1, init_contactD2;

// --------------------------------------------------------

void setup()
{
// ----- affichage
    Serial.begin(115200);                             // initialize the serial port
    print_action=true;

// ----- Noir ou Blanc CNY70
    pinMode (CNY70_A,INPUT);                          // noir=0 - blanc=1
    pinMode (CNY70_G,INPUT);
    pinMode (CNY70_D,INPUT);
    cpt_piste_noire=0;
    max_piste_noire=25;                               // tout va bien (clignote 1/25)
    limite_noir_blanc=100;                            // luminosité /noir et blanc (std 500)

// ----- contact AV
    pinMode (contact_G,INPUT);                        // libre=0 - contact=1
    pinMode (contact_D,INPUT);

// ----- bouton On Off - LED fonctionnement
    pinMode (boutonOn,INPUT);                         // départ
    bouton_entree=false;
    temps_attente=5;                                  // nb secondes avant de bouger
    pinMode (ledOn,OUTPUT);                           // en route
    digitalWrite(ledOn, 0);

}
// --------------------------------------------------------

void loop()
{
// ----- appui boutons au départ
    //attend_signal_depart();
    
// ----- fonctionnement courant
    lecture_3_cny();
    lecture_contactsAV();
    affichage_des_capteurs();
}
// --------------------------------------------------------

// ----- FONCTIONS PRINCIPALES -----

void attend_signal_depart()
{
    boutonG=false;                                    // entrée G
    boutonD=false;                                    // entree D
    init_contactG0 = false;                           // passage à 1 >> à gauche
    init_contactG1 = false;                           // passage à 1 zéro
    init_contactG2 = false;                           // second passage >> échauffement moteurs
    init_contactD0 = false;                           // passage à 1 >> à droite
    init_contactD1 = false;                           // passage à zéro
    init_contactD2 = false;                           // second passage >> test de sortie cube
    bouton_entree = false;                            // début décompte 5"
    priorite_recherche=0;                             // sélection 
    
// ----- appui pare chocs + bouton vert

    if(print_action){Serial.println("Attend : appui pare-choc et appui bouton");}
    while(bouton_entree==false){                      // attend départ

      if(init_contactG0==false){
        boutonG=digitalRead(contact_G);                // lecture G
        delay(5);
        if(boutonG==true){init_contactG0=true;}}
      else{                                            // init_contactG0==true
        if(init_contactG1==false){
          boutonG=digitalRead(contact_G);              // lecture G
          delay(5);
          if(boutonG==false){init_contactG1=true;}}
        else{                                          // init_contactG1==true
          if(init_contactG2==false){
            boutonG=digitalRead(contact_G);            // lecture G
            delay(5);
            if(boutonG==true){init_contactG2=true;}}}}

      if(init_contactD0==false){
        boutonD=digitalRead(contact_D);                // lecture D
        delay(5);
        if(boutonD==true){init_contactD0=true;}}
      else{                                            // init_contactD0==true
        if(init_contactD1==false){
          boutonD=digitalRead(contact_D);              // lecture D
          delay(5);
          if(boutonD==false){init_contactD1=true;}}
        else{                                          // init_contactD1==true
          if(init_contactD2==false){
            boutonD=digitalRead(contact_D);            // lecture D
            delay(5);
            if(boutonD==true){init_contactD2=true;}}}}

      bouton_entree = digitalRead(boutonOn);           // bouton ON
      test_noir_et_blanc();
      delay(5);}
    
    // ... bouton_entree=true : choix du mouvement initial
    if((init_contactG0==false)&&(init_contactD0==false)){
      priorite_recherche=0;}                            // TEST QUALIF : poussée, vitesse

    if((init_contactG0==true)&&(init_contactG2==false)&&(init_contactD0==false)){
      priorite_recherche=1;}                            // adversaire A GAUCHE
      
    if((init_contactG0==false)&&(init_contactD0==true)&&(init_contactD2==false)){
      priorite_recherche=2;}                            // adversaire A DROITE
    
    if((init_contactG0==true)&&(init_contactG2==false)&&(init_contactD0==true)&&(init_contactD2==false)){
      priorite_recherche=3;}                            // adversaire DERRIERE

    if((init_contactG0==false)&&(init_contactD0==true)&&(init_contactD2==true)){
      priorite_recherche=4;}                            // TEST de SORTIE CUBE

    if((init_contactG0==true)&&(init_contactG2==true)&&(init_contactD0==false)){
      priorite_recherche=5;}                            // ECHAUFFEMENT MOTEURS

    if((init_contactG0==true)&&(init_contactG2==true)&&(init_contactD0==true)&&(init_contactD2==true)){
      priorite_recherche=6;}                            // ESSAIS vitesse ARRIERE
      
// ----- 5 secondes avant de bouger

    if(print_action){Serial.println("Bouton(s) appuyé(s) ");
      Serial.print("priorité de recherche : ");
      Serial.println(priorite_recherche);
      switch (priorite_recherche) {
        case 0: Serial.println("   TEST : QUALIFICATION vitesse, poussée");break;
        case 1: Serial.println("   adversaire à GAUCHE : tourne à GAUCHE");break;
        case 2: Serial.println("   adversaire à DROITE : tourne à DROITE");break;
        case 3: Serial.println("   adversaire DERRIERE : sur place GAUCHE");break;
        case 4: Serial.println("   TEST : PARCOURS & SORTIE DU CUBE");break;
        case 5: Serial.println("   ECHAUFFEMENT DES MOTEURS");break;
        case 6: Serial.println("   TESTE de la VITESSE DE RECUL");break;}
        
      Serial.print("compte ");
      Serial.print(temps_attente);
      Serial.println(" secondes ...");
      Serial.println("");}
        
    for(uint8_t cpt=0;cpt<temps_attente; cpt++){        // attend & compte 5 secondes
      digitalWrite(ledOn,LOW);
      delay(950);
      digitalWrite(ledOn,HIGH);
      delay(50);}
}
// ---------------------------------------------------------

// ----- SOUS FONCTIONS -----

void test_noir_et_blanc()
// Vérifie que le dohyo est NOIR avant le départ
{
    lecture_3_cny();
    cpt_piste_noire=cpt_piste_noire+1;
    
    if(!ligne_blanche){                                 // les 3 CNY sont NOIRS
      if(cpt_piste_noire>max_piste_noire){       
        digitalWrite(ledOn,HIGH);
        cpt_piste_noire=0;}
      else{digitalWrite(ledOn,LOW);}
      }
    else{                                               // au moins 1 CNY est BLANC
      digitalWrite(ledOn,HIGH);}
}
// ---------------------------------------------------------

void lecture_3_cny()
// cny BLANC si Valeur > Seuil  - DANGER si au moins 1 CNY est BLANC
{
    cny70_G = 1;    
    if(analogRead(CNY70_G)>=limite_noir_blanc){cny70_G=0;}
    cny70_A = 1;      
    if(analogRead(CNY70_A)>=limite_noir_blanc){cny70_A=0;}
    cny70_D = 1;    
    if(analogRead(CNY70_D)>=limite_noir_blanc){cny70_D=0;}

    ligne_blanche=cny70_G||cny70_A||cny70_D;
}
// ---------------------------------------------------------

void lecture_contactsAV()
{
    boutonG = digitalRead(contact_G);
    boutonD = digitalRead(contact_D);
     
    contact_avant=boutonG||boutonD;
}
// ---------------------------------------------------------

void affichage_des_capteurs()
{
    if(print_action==true){Serial.println("");}
    
// ----- CNY70 -----
    if(cny70_G==1){Serial.print("yG: bl ");}
    else          {Serial.print("yG: .. ");}
    if(cny70_A==1){Serial.print("  yA: BL ");}
    else          {Serial.print("  yA: .. ");}
    if(cny70_D==1){Serial.print("  yD: bl ");}
    else          {Serial.print("  yD: .. ");}

// ----- Contact AVANT -----
    if(boutonG==1){Serial.print("   cG: AP");}
    else          {Serial.print("   cG: . ");}
    if(boutonD==1){Serial.print("  cD: AP");}
    else          {Serial.print("  cD: . ");}
    
    if(print_action==true){Serial.print("   ");}
    else{Serial.println("");}
}
// ---------------------------------------------------------
// ---------------------------------------------------------