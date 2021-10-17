// ---------------------------------------------------------
// ----- Commmande Yutaka 2 après amélioration de YUTAKA
// ----- création 18/5/2021
// ---------------------------------------------------------
//
// 8/8/20 - commande pont en H
// 9/8/20 - fusion avec Commande servo ES08D
// 20/8/20 - allume laser 5V - 30mA
// 30/8/20 - soudage des capteurs sur robot - 31/8/20 - premiers tests
// 3/9/20 - nouvelle carte MEGA2560PRO
// 9/9/20 - librairie SharpIR2.01
// 22/9/20 - capteurs US a l'avant ald IR : trop instable
// 22/10/20 - simplification YUTAKA : servo, pas-à-pas, laser, proximité, US radar
// 28-31/10/20 - assemblage & programme & test
// ... concours reporté ...
//
// 18/5/21 - YUTAKA 2 assemblé !!!
// 18/5/21 - inversion capteurs CNY70 noir=1 & blanc=0 +++ bouton ON inversé 1<->0
// 19/5/21 - PWM maxi = 200 (alimentation pas assez puissante !!!)
// 19/5/21 - écart de vitesse avant/arrière = 4%
// 20/5/21 - nettoyage&changement moteurs (375rpm) + new mega2560pro
// 21/5/21 - circuit on-off : bouton ON rétabli ... résistance de pull-down !!!
// 22/5/21 - mesures vitesse, poussée, poids
// 24/5/21 - tests ... corrections & améliorations YK2
// 25/5/21 - 1ère seconde : pas de capteur
// 27/5/21 - entrees analogiques : 3*cny70 & 2*contact
// 28/5/21 - configuration dynamique capteurs : il sait quand il gagne !!!
// 29/5/21 - rencontre Yutaka 1
// 31/5/21 - TEST de parcours et sortie du cube
// 2/6/21 - installation des moteurs 375-E & 375-F >> recule en tournant !!!
// 3/6/21 - ré-installation des moteurs 375-C & 375-D >> même problème 
// 4/6/21 - remplacement entretoise par 11 rondelles - prog 6 échauffement moteurs
// 5/6/21 - prog 7 essais de vitesse arrière
// 6/6/21 - isolement des constantes de temps

// 12/6/21 - concours THIONVILLE 5e place sur 14 robots
/*            déplacement de 1 mètre (trop long pour démo) : réduire à 0.5 m
              rotation trop rapide pour détection des capteurs us : scan
              manque adhérence des pneus (patine) : pneus JSUMO
              se lève verticalement : appui derrière les roues
              diamètre roue : 45 > 33 voire 26
              en cas de face à face : esquiver */
              
// 21/9/21 - réduction distance test : 1 m -> 0.5 m (666 ms ald 1325 ms en Vmaxi)
/*            temps 1ère seconde dojo : 450ms (en Vitesse moyenne)
              calibrage des vitesses : max, moy, min
              meilleur équilibre avec patin glisseur à l'avant centre
              scanner si pas d'adversaire en phase test + 
              distance de croisement des yeux à 20cm, tresloin à 42cm
              temps de retournement au départ */


// --------------------------------------------------------------------
// ----- constantes et variables -----
// --------------------------------------------------------------------

// ----- moteurs CC ----- 8-9-10-11 (12V) (blanc, vert, marron, gris)
// avant   : 1 ... 0
// arriere : 0 ... 1
// stop    : 0 ... 0
// frein   : 1 ... 1                                  ... !!! uniquement circuit ZK-5AD

const int moteur1av =8;                               // moteur A (gauche)- D0 (blanc)
const int moteur1arr=9;                               //                    D1 (vert)
const int moteur2av =10;                              // moteur B (droit) - D2 (marron)
const int moteur2arr=11;                              //                    D3 (gris)

int forceGauche, forceDroite, duree_run, duree_brake, duree_wait;
int duree_run_max, duree_run_moy, duree_run_min;
int tps_run_arriere1, tps_run_arriere2, tps_run_arriere3;

int fmaxGaucheA, fmoyGaucheA, fminGaucheA;            // PWM mot G avance
int fmaxGaucheR, fmoyGaucheR, fminGaucheR;            // recule
int fmaxDroiteA ,fmoyDroiteA, fminDroiteA;            // PWM mot D avance
int fmaxDroiteR ,fmoyDroiteR, fminDroiteR;             // recule

/* ----- entrées DIGITALES ----- 
const int CNY70_A=22;                                 // CNY avant
const int contact_D=24;                               // contact droit
const int CNY70_D=26;                                 // CNY droit
const int contact_G=28;                               // contact gauche
const int CNY70_G=30;                                 // CNY gauche 
*/
// ----- entree ANALOGIQUES -----
const int CNY70_A=A6;                                 // CNY A
const int contact_D=A8;                               // contact D
const int CNY70_D=A10;                                // CNY D
const int contact_G=A12;                              // contact G
const int CNY70_G=A14;                                // CNY G

// ----- capteurs CNY70 ----- (fils bleus)
boolean cny70_A, cny70_G, cny70_D;
boolean oldcny70_A, oldcny70_G, oldcny70_D;
boolean ligne_blanche, oldligne_blanche;
uint8_t cpt_piste_noire, max_piste_noire;
uint8_t temps_ligne_blanche;
int limite_noir_blanc;

// ----- contacts AVANT ----- (fils marron)
boolean cont_G, cont_D, contact_avant;
boolean oldcont_G, oldcont_D;
uint8_t temps_deux_appuis;
uint8_t pousse_devant, oldpousse_devant;

// ----- capteurs US025A ----- G(16-17) - D(18-19)
const byte TRIGGER_G  = 17;                          // trig G (blanc)
const byte ECHO_G     = 16;                          // echo G (jaune)
const byte TRIGGER_D  = 19;
const byte ECHO_D     = 18;
const float SOUND_SPEED = 340.0 / 1000;               // vitesse du son
unsigned long MEASURE_TIMEOUT = 3000UL;               // 2ms = 28cm (4ms=55cm)... 350m/s
long measure;                                         // mesure
float resultatcm;
uint8_t distanceG, distanceD;
uint8_t distanceG0, distanceD0;                       // = 0 si très très loin
uint8_t old_distanceG, old_distanceD;
uint8_t enface, toutpres, croisement_yeux, tresloin, trestresloin;
uint8_t attaque_devant, oldattaque_devant;
uint8_t recherche_devant, oldrecherche_devant;
boolean juste_devantG, juste_devantD, adv_agauche, adv_adroite;
boolean oldjuste_devantG, oldjuste_devantD, oldadv_agauche, oldadv_adroite;
uint8_t cpt_etatdeslieux=0;

// ----- On Off ----- ON (bleu : 2) - LED (vert : 3)
const int boutonOn  =2;                               // bouton démarrage
const int ledOn     =3;
boolean bouton_entree, premier_round, premiere_seconde;
int duree_1er_round, temps_1ere_seconde_gd;
int temps_1ere_seconde_arr, temps_1ere_seconde_av;
boolean boutonD, boutonG;
boolean init_contactG0, init_contactG1, init_contactG2;
boolean init_contactD0, init_contactD1, init_contactD2;
uint8_t temps_attente;
unsigned long duree_totale_combat;

// ---- variables générales
unsigned long tempszero, temps0, temps1, temps2, temps3;
boolean print_distance, print_tempscycle, print_action, print_config, print_vitesse;
uint8_t temps_de_cycle, temps_de_cyclecourt;
uint8_t priorite_recherche,oldrecherche, urgence, oldurgence;

// ----- configuration dynamique
unsigned long cnyG, cnyA, cnyD, Lign;
unsigned long capG, capD, Pous;
unsigned long disG, disD, jdG, jdD, adG, adD, Atta;
unsigned long Rech, Urge;

// ----- resume -----
boolean double_appui, avant_ligne;
unsigned long tps_double_appui, tps_avant_ligne,tps_tout_droit;
int nb_tout_droit;
boolean magic_1, magic_2, magic_3, match_gagne, fin_du_match;
unsigned long tps_magic_1, tps_magic_12, tps_magic_123;

// ----- parcours -----
int cpt_parcours, choix_parcours;
int temps_1ere_seconde_dojo, temps_sortie_cube;
uint8_t cpt_scan, nb_scan;
//
// ---------------------------------------------------------
// ---------------------------------------------------------
void setup()
{
// ----- affichage
    Serial.begin(115200);                             // initialize the serial port
    
// ----- constantes de vitesse et de temps
    constantes_de_temps();                            // temps et durées des actions
    vitesses_des_moteurs();                           // vitesses avec corrections
    
// ----- moteurs CC
    pinMode (moteur1av,OUTPUT);                       // moteur A (gauche)
    analogWrite(moteur1av, 0);
    pinMode (moteur1arr,OUTPUT);
    digitalWrite(moteur1arr, 0); 
    pinMode (moteur2av,OUTPUT);                       // moteur B (droit)
    analogWrite(moteur2av, 0);
    pinMode (moteur2arr,OUTPUT);
    digitalWrite(moteur2arr, 0);
      
// ----- Noir ou Blanc CNY70
    pinMode (CNY70_A,INPUT);                          // noir=0 - blanc=1
    pinMode (CNY70_G,INPUT);
    pinMode (CNY70_D,INPUT);
    cpt_piste_noire=0;
    max_piste_noire=25;                               // tout va bien (clignote 1/25)

// ----- contact AV
    pinMode (contact_G,INPUT);                        // libre=0 - contact=1
    pinMode (contact_D,INPUT);

// ----- capteurs US avant
    pinMode(TRIGGER_G, OUTPUT);
    digitalWrite(TRIGGER_G, LOW);                     // trig G à LOW au repos
    pinMode(ECHO_G, INPUT);
    pinMode(TRIGGER_D, OUTPUT);
    digitalWrite(TRIGGER_D, LOW);                     // trig D à LOW au repos
    pinMode(ECHO_D, INPUT);
    MEASURE_TIMEOUT = 3000UL;                         // 2ms->28cm - 3ms->42cm
    cpt_etatdeslieux=0;                               // alternance gauche-droite

// ----- bouton On Off
    pinMode (boutonOn,INPUT);                         // départ
    bouton_entree=false;
    pinMode (ledOn,OUTPUT);                           // en route
    digitalWrite(ledOn, 0);

// ----- déroulement du combat
    premiere_seconde=true;                            // tout début
    premier_round=true;                               // première partie du combat

// ----- configutation dynamique
    cnyG=0; cnyA=0; cnyD=0;                           // long (compteur)
    capG=0; capD=0;                                   // long
    disG=0; disD=0;                                   // long
    jdG=0; jdD=0; adG=0; adD=0;                       // long
    Rech=0; Atta=0; Pous=0; Lign=0; Urge=0;           // long

    oldcny70_A=0; oldcny70_G=0; oldcny70_D=0;         // booleen
    oldligne_blanche=0;                               // booleen
    
    oldcont_G=0; oldcont_D=0;                         // booleen
    oldpousse_devant=4;                               // uint8_t

    old_distanceG=0; old_distanceD=0;                 // uint8_t
    oldjuste_devantG=0; oldjuste_devantD=0;           // booleen
    oldadv_agauche=0; oldadv_adroite=0;               // booleen
    oldattaque_devant=4;                              // uint8_t

    oldurgence=1;                                     // uint8_t
    oldrecherche=0;                                   // uint8_t

// ----- resume du match
    double_appui=false; avant_ligne=false;
    tps_double_appui=0; tps_avant_ligne=0;
    tps_tout_droit=0; nb_tout_droit=0;
    magic_1=false; magic_2=false; magic_3=false;
    tps_magic_1=0; tps_magic_12=0; tps_magic_123=0;
    match_gagne=false; fin_du_match=false;

// ----- parcours
    cpt_parcours=0; choix_parcours=0;
    cpt_scan=0;

// ----- signal départ et temporisation 5"
    attend_signal_depart();                           // appui : 1, 2 ou 3 boutons + GO ON !!!
    tempszero=millis();                               // temps 0 pour comptage des temps et durées
    temps0=tempszero;
}
//
// ---------------------------------------------------------
// ---------------------------------------------------------
void loop() 
{
// ----- lecture des capteurs -----
  if(priorite_recherche>0&&priorite_recherche<5){     // boucle capteurs + action (sauf test)
      etat_des_lieux_capteurs();                      // capteurs & urgence
      affichage_des_capteurs();}

// ----- action -----    
  switch (urgence) {
    case 0:// ....................................... // TEST : 1 mètre (poussée, vitesse)
      run_and_brake();
      break;
    case 1:// ....................................... // recherche adversaire
      recherche_adversaire();
      break;
    case 2:// ....................................... // détection présence >> attaque
      presence_attaque();
      break;   
    case 3:// ....................................... // contact direct AVANT
      contact_poussee();
      break;
    case 4:// ....................................... // ligne blanche >> réaction /défence
      blanc_dessous();
      break;
    case 5:// ....................................... // TEST : parcours dojo & sortie du CUBE
      parcours_dojo();
      break;
    case 6:// ....................................... // avant TEST : échauffement moteurs
      echauffement_moteurs();
      break;
    case 7:// ....................................... // avant TEST : vitesse arrière
      test_vitesse_arriere();
      break;}

// ----- gestion du temps de combat -----
    temps1=millis();                                  // prise de temps dans la boucle
    temps2=temps1-temps0;                             // durée de la boucle
      temps0=temps1;                                  // mémorisation pour prochaine boucle
    temps3=temps1-tempszero;                          // temps total de combat

  if(print_tempscycle){                               // temps et durée combat
    Serial.print("  ");
    Serial.print(temps2);
    Serial.print(" ms - cumul: ");
    Serial.print(temps3);
    if(print_distance==false){Serial.println("  ");}}

// ----- fin du match ? -----
  marque_evenement();                                 // enregistre les événements
  if(fin_du_match==true){
    resume_du_match();
    while(1){;}}                                      // ..... arret du combat !!!

  if(print_config){                                   // config capteurs et paramètres
    configuration();
    affiche_configuration();
    Serial.println("");}

// ----- première seconde AVANCE sans capteurs -----
  if(premiere_seconde==true){
    if(((priorite_recherche==1)||(priorite_recherche==2))&&(temps3>temps_1ere_seconde_gd)){
      premiere_seconde=false;}
    if((priorite_recherche==3)&&(temps3>temps_1ere_seconde_arr)){
      premiere_seconde=false;}
    if((priorite_recherche==4)&&(temps3>temps_1ere_seconde_dojo)){
      premiere_seconde=false;}}

// ----- premier round (3 secondes) -----
  if(temps3<=duree_1er_round){premier_round=true;}    // ..... combat standard .....
  else{premier_round=false;}
    
// ----- fin de match (175 secondes : 180-5) -----
  if(temps3>duree_totale_combat){
    resume_du_match();
    while(1){;}}                                      // ----- arrêt du combat -----
}
// ---------------------------------------------------------
// sous programmes ...
// MOTEURS CC
// ---------------------------------------------------------
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
//
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
//
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
//
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
//
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
//
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
//
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
//
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
//
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
//
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
//
// ---------------------------------------------------------
// ----- DEMARRAGE -----
// ---------------------------------------------------------
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
      //affiche_les_US();
      delay(5);}
    
    // ... bouton_entree=true : choix du mouvement initial
    if((init_contactG0==false)&&(init_contactD0==false)){
      priorite_recherche=0;urgence=0;}                  // TEST QUALIF : poussée, vitesse

    if((init_contactG0==true)&&(init_contactG2==false)&&(init_contactD0==false)){
      priorite_recherche=1;}                            // adversaire A GAUCHE
      
    if((init_contactG0==false)&&(init_contactD0==true)&&(init_contactD2==false)){
      priorite_recherche=2;}                            // adversaire A DROITE
    
    if((init_contactG0==true)&&(init_contactG2==false)&&(init_contactD0==true)&&(init_contactD2==false)){
      priorite_recherche=3;}                            // adversaire DERRIERE

    if((init_contactG0==false)&&(init_contactD0==true)&&(init_contactD2==true)){
      priorite_recherche=4;}                            // TEST de SORTIE CUBE

    if((init_contactG0==true)&&(init_contactG2==true)&&(init_contactD0==false)){
      priorite_recherche=5;urgence=6;}                  // ECHAUFFEMENT MOTEURS

    if((init_contactG0==true)&&(init_contactG2==true)&&(init_contactD0==true)&&(init_contactD2==true)){
      priorite_recherche=6;urgence=7;}                  // ESSAIS vitesse ARRIERE
      
    oldrecherche=priorite_recherche;
      
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
      Serial.println(" secondes ...");}
        
    for(uint8_t cpt=0;cpt<temps_attente; cpt++){        // attend & compte 5 secondes
      digitalWrite(ledOn,LOW);
      delay(950);
      digitalWrite(ledOn,HIGH);
      delay(50);}
}
// ---------------------------------------------------------
void test_noir_et_blanc()
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
//
// ---------------------------------------------------------
void marque_evenement()
{
  if(cont_G==1&&cont_D==1){                             // ..... DOUBLE APPUI .....
    
    if(double_appui==false){                            // moment double appui
      tps_double_appui=temps3;
      double_appui=true;}
      
    if (ligne_blanche==false){                          // temps de cycle en charge
      tps_tout_droit=tps_tout_droit+temps2;
      nb_tout_droit=nb_tout_droit+1;}

    if(cny70_A==1){                                     // ----- ligne blanche -----
      if(avant_ligne==false){
        tps_avant_ligne=temps3;                         // moment ligne blanche
        avant_ligne=true;}

      if(magic_1==true){
        if(magic_2==true){
          magic_3=true;                                 // magic 3
          tps_magic_123=temps3;}}
      else{
        magic_1=true;                                   // magic 1
        tps_magic_1=temps3;}}
    else{                                               // ----- pas de ligne blanche -----
      if(magic_1==true){
        magic_2=true;                                   // magic 2
        tps_magic_12=temps3;}}}
  else{                                                 // ..... PAS DE DOUBLE APPUI .....
    if(magic_1==true){
      if(magic_2==true){
        if(cny70_A=1&&cny70_G==0&&cny70_D==0){          // magic 3
          magic_3=true;
          tps_magic_123=temps3;}}
          
      if((cny70_A==0)&&(cny70_G==1||cny70_D==1)){       // magic 2
        magic_2=true;
        tps_magic_12=temps3;}}}      
    
  match_gagne=magic_1&&magic_2&&magic_3;                // bilan de l'attaque
  if(match_gagne==true){fin_du_match=true;}
  if(priorite_recherche==0&&magic_1==true){fin_du_match=true;}
  if((priorite_recherche==4)&&(magic_1==true||temps3>temps_sortie_cube))
    {fin_du_match=true;}
}
// ---------------------------------------------------------
void resume_du_match()
{
      Serial.println("");
      Serial.print("Priorité: ");
      Serial.print(priorite_recherche);
      switch (priorite_recherche) {
        case 0: Serial.println("   TEST QUALIFICATION");break;
        case 1: Serial.println("   adversaire à GAUCHE");break;
        case 2: Serial.println("   adversaire à DROITE");break;
        case 3: Serial.println("   adversaire DERRIERE");break;
        case 4: Serial.println("   TEST SORTIE du CUBE");break;
        case 5: Serial.println("   ECHAUFFEMENT MOTEURS");break;
        case 6: Serial.println("   ESSAIS vitesse ARRIERE");break;}
      
      Serial.println("Evenements: ");
      Serial.print("  appui sur les 2 contacts avant: ");
      Serial.print(tps_double_appui);
      Serial.println(" ms ");
      
      Serial.print("  touche ligne blanche en charge: ");
      Serial.print(tps_avant_ligne);
      Serial.println(" ms ");

      Serial.print("  temps de cycle en poussee: ");
      Serial.print(int(tps_tout_droit/nb_tout_droit));
      Serial.println(" ms ");

      Serial.print("  magic 1: ");
      Serial.print(tps_magic_1);
      Serial.print("     magic 2: ");
      Serial.print(tps_magic_12);
      Serial.print("     magic 3: ");
      Serial.println(tps_magic_123);

      Serial.print("  durée totale du combat: ");
      Serial.print(temps3);
      Serial.println(" ms");      

      if(match_gagne){Serial.println("Point YUKO gagné !!!  ");}
      Serial.println("");
}
// ---------------------------------------------------------
// ----- CAPTEURS -----
// ---------------------------------------------------------
void etat_des_lieux_capteurs()
{
    ligne_blanche=false;
    contact_avant=false;
    pousse_devant=0;    
    juste_devantG=false;
    juste_devantD=false;
    attaque_devant=0;
    adv_agauche=false;
    adv_adroite=false;
    recherche_devant=0;
    //
    lecture_3_cny();
    if(ligne_blanche){
      urgence=4;
      if(priorite_recherche==0){urgence=0;}             // run & brake
      if(priorite_recherche==4){urgence=5;}}            // TEST : parcours & sortie cube
    
    else {                                              // sur le NOIR > lecture contacts
      cont_G = digitalRead(contact_G);                  // 0=rien <> 1=CONTACT (on pousse)
      cont_D = digitalRead(contact_D);
      contact_avant=cont_G||cont_D;
      if(contact_avant){
        urgence=3;
        if(cont_G==1&&cont_D==0){pousse_devant=1;}      // pousse à gauche
        if(cont_G==0&&cont_D==1){pousse_devant=2;}      // pousse à droite
        if(cont_G==1&&cont_D==1){pousse_devant=3;}}     // pousse tout droit : G+D
        
      else {                                            // pas de contact > LECTURE ULTA-SONS ********
        if(premiere_seconde){
          switch (priorite_recherche){     
            case 1: USgauche();break;                   // adversaire à gauche - sens trigonométrique
            case 2: USdroite();break;                   // adversaire à droite - sens horaire
            case 3: USgauche();break;}}                 // adversaire derrière - sens trigo
        else{
          switch (cpt_etatdeslieux) {                           // lecture alternée
            case 0: USgauche();cpt_etatdeslieux=1;break;        // ... US gauche
            case 1: USdroite();cpt_etatdeslieux=0;break;}}      // ... US droit */            
        
        if(distanceG0>0&&distanceD0==0){                        // présence uniquement à gauche
            if(distanceG0<=toutpres){
              juste_devantG=true;urgence=3;pousse_devant=1;}
            else{
              if(distanceG0<=tresloin){
                if(distanceG0<=croisement_yeux){
                  adv_agauche=true;urgence=2;attaque_devant=1;}
                else{
                  adv_adroite=true;urgence=2;attaque_devant=2;}}
              else{
                urgence=1;recherche_devant=1;}}}
                
        if(distanceG0==0&&distanceD0>0){                        // présence uniquement à droite
            if(distanceD0<=toutpres){
              juste_devantD=true;urgence=3;pousse_devant=2;}
            else{
              if(distanceD0<=tresloin){
                if(distanceD0<=croisement_yeux){
                  adv_adroite=true;urgence=2;attaque_devant=2;}
                else{
                  adv_agauche=true;urgence=2;attaque_devant=1;}}
              else{
                urgence=1;recherche_devant=2;}}}
                
        if(distanceG0>0&&distanceD0>0){                         // 2 mesures US définies
            if(abs(distanceG0-distanceD0)<=enface){             // ADV en face
              if(distanceG0<=toutpres||distanceD0<=toutpres){
                urgence=3;pousse_devant=3;}
              else{
                if(distanceG0<=tresloin||distanceD0<=tresloin){
                  urgence=2;attaque_devant=3;}
                else{
                  urgence=1;recherche_devant=3;}}}
            else{
              if(distanceG0<distanceD0){                        // ADV à gauche
                adv_agauche=true;
                if(distanceG0<=toutpres){
                  juste_devantG=true;urgence=3;pousse_devant=1;}
                else{
                  if(distanceG0<=tresloin){
                    urgence=2;attaque_devant=1;}
                  else{
                    urgence=1;recherche_devant=1;}}}
              else{                                             // ADV à droite
                adv_adroite=true;
                if(distanceD0<=toutpres){
                  juste_devantD=true;urgence=3;pousse_devant=2;}
                else{
                  if(distanceD0<=tresloin){
                    urgence=2;attaque_devant=2;}
                  else{
                    urgence=1;recherche_devant=2;}}}}}
          
        if(distanceG0==0&&distanceD0==0){                       // les 2 mesures sont nulles : SCAN
          urgence=1;
          recherche_devant=0;}
            
        if(priorite_recherche==4){                              // TEST : parcours & sortie cube
          urgence=5;}

        if(priorite_recherche==5){                              // AVANT test : échauffement moteurs
          urgence=6;}
          
        if(priorite_recherche==6){                              // ESSAIS vitesse de RECUL
          urgence=7;}          
        }                                                       // fin de else : pas de CONTACT
      }                                                         // fin de else : pas de LIGNE BLANCHE
}
// ---------------------------------------------------------
void lecture_3_cny()
{
    cny70_G = 1;                                              // danger/ 1 : BLANC (bord du dojo)    
    if(analogRead(CNY70_G)>=limite_noir_blanc){cny70_G=0;}    // OK    / 0 : NOIR (centre du dojo)
    cny70_A = 1;      
    if(analogRead(CNY70_A)>=limite_noir_blanc){cny70_A=0;}
    cny70_D = 1;    
    if(analogRead(CNY70_D)>=limite_noir_blanc){cny70_D=0;}

    ligne_blanche=cny70_G||cny70_A||cny70_D;                  // 1 au moins des 3 CNY est BLANC
}
// ---------------------------------------------------------
void USgauche()
{
      digitalWrite(TRIGGER_G, HIGH);                    // impulsion 10us
      delayMicroseconds(10);
      digitalWrite(TRIGGER_G, LOW);
          
      measure = pulseIn(ECHO_G, HIGH, MEASURE_TIMEOUT); 
      resultatcm = measure / 20.0 * SOUND_SPEED;        // mesure G : 5ms
      distanceG = int(resultatcm);
      if(distanceG==0||distanceG>trestresloin){distanceG0=0;}
        else{distanceG0=distanceG;}
      delay(1);
}
// ---------------------------------------------------------
void USdroite()
{
      digitalWrite(TRIGGER_D, HIGH);                    // impulsion 10us
      delayMicroseconds(10);
      digitalWrite(TRIGGER_D, LOW);
          
      measure = pulseIn(ECHO_D, HIGH, MEASURE_TIMEOUT);
      resultatcm = measure / 20.0 * SOUND_SPEED;        // mesure D : 5ms
      distanceD = int(resultatcm);
      if(distanceD==0||distanceD>trestresloin){distanceD0=0;}
        else{distanceD0=distanceD;}
      delay(1);
}
// ---------------------------------------------------------
void affiche_les_US()
{
      USgauche();
        Serial.print("usG: ");
        Serial.print(distanceG0);    
      USdroite();
        Serial.print("   usD: ");
        Serial.println(distanceD0);
}
// ---------------------------------------------------------
void affichage_des_capteurs()
{
  if(print_distance){
    if(print_action==true){Serial.println("");}
    
// ----- CNY70 -----
    if(cny70_G==1){Serial.print("yG: bl ");}
    else          {Serial.print("yG: .. ");}
    if(cny70_A==1){Serial.print("  yA: BL ");}
    else          {Serial.print("  yA: .. ");}
    if(cny70_D==1){Serial.print("  yD: bl ");}
    else          {Serial.print("  yD: .. ");}

// ----- Contact AVANT -----
    if(cont_G==1){Serial.print("   cG: AP");}
    else         {Serial.print("   cG: . ");}
    if(cont_D==1){Serial.print("  cD: AP");}
    else         {Serial.print("  cD: . ");}
    
// ----- Indicateurs -----
    Serial.print("  ps: ");
    Serial.print(pousse_devant);                      // 1, 2, 3, 4 ... G, D, G+D, indéfini
    
// ----- Distance US avant -----
    Serial.print("     dUS: ");
    if(adv_agauche){Serial.print(" * ");}else{Serial.print("   ");}
    if(juste_devantG){Serial.print("*** ");}else{Serial.print("    ");}
    Serial.print(distanceG0);
    if((attaque_devant==1)||(pousse_devant==1)){Serial.print("  <<-  ");}
    if((attaque_devant==2)||(pousse_devant==2)){Serial.print("  ->>  ");}
    if((attaque_devant==3)||(pousse_devant==3)){Serial.print("  !!!  ");}
    if((attaque_devant==0||attaque_devant==4)&&(pousse_devant==0||pousse_devant==4))
      {Serial.print("       ");}
    Serial.print(distanceD0);
    if(juste_devantD){Serial.print(" ***");}else{Serial.print("    ");}
    if(adv_adroite){Serial.print(" * ");}else{Serial.print("   ");}

// ----- Indicateurs -----
    Serial.print("   at: ");
    Serial.print(attaque_devant);
    Serial.print("   urg: ");
    Serial.print(urgence);
    Serial.print("   pri: ");
    Serial.print(priorite_recherche);
    
    if(print_action==true){Serial.print("   ");}
    else{Serial.println("");}
  }
}
// ---------------------------------------------------------
void configuration()
/* tous les compteurs sont des entiers "long"
      cnyG=0; cnyA=0; cnyD=0;
      capG=0; capD=0;
      disG=0; disD=0;
      jdG=0; jdD=0; adG=0; adD=0;
      Rech=0; Atta=0; Pous=0; Lign=0; Urge=0; 
    temps2 : durée de la boucle écoulée
 */
{  
// ----- état des CNY70 -----
    if(cny70_G==oldcny70_G){cnyG=cnyG+temps2;}                // cny70_G : booleen (0:noir - 1:blanc)
      else{cnyG=0;}
    if(cny70_A==oldcny70_A){cnyA=cnyA+temps2;}
      else{cnyA=0;}
    if(cny70_D==oldcny70_D){cnyD=cnyD+temps2;}
      else{cnyD=0;}
    
    oldcny70_G=cny70_G;
    oldcny70_A=cny70_A;
    oldcny70_D=cny70_D;
    
// ----- état des contacts avant -----
    if(cont_G==oldcont_G){capG=capG+temps2;}                  // cont_G : booleen (0:rien - 1:appui)
      else{capG=0;}
    if(cont_D==oldcont_D){capD=capD+temps2;}
      else{capD=0;}
    
    oldcont_G=cont_G;
    oldcont_D=cont_D;
    
// -----  état des capteurs ULTRA SONS -----
    if(juste_devantG==oldjuste_devantG){jdG=jdG+temps2;}      // juste_devant : booleen (0 - 1: distanceG<=toutpres)
      else{jdG=0;}
    if(juste_devantD==oldjuste_devantD){jdD=jdD+temps2;}
      else{jdD=0;}
    if(adv_agauche==oldadv_agauche){adG=adG+temps2;}          // adv_agauche : booleen (0 - 1: distanceG<=tresloin)
      else{adG=0;}
    if(adv_adroite==oldadv_adroite){adD=adD+temps2;}
      else{adD=0;}

    oldjuste_devantG=juste_devantG;
    oldjuste_devantD=juste_devantD;
    oldadv_agauche=adv_agauche;
    oldadv_adroite=adv_adroite;

// ----- paramètres dynamiques -----
    if(ligne_blanche==oldligne_blanche){Lign=Lign+temps2;}    // ligne_blanche : booleen (0:OK 3 noirs - 1:danger)
      else{Lign=0;}
    if(pousse_devant==oldpousse_devant){Pous=Pous+temps2;}    // pousse_devant : uint8_t (1, 2, 3 ou 4)
      else{Pous=0;}
    if(attaque_devant==oldattaque_devant){Atta=Atta+temps2;}  // attaque_devant : uint8_t (1, 2, 3 ou 4)
      else{Atta=0;}
    if(urgence==oldurgence){Urge=Urge+temps2;}                // urgence : uint8_t (0, 1, 2, 3, 4 ou 5)
      else{Urge=0;}
    if(priorite_recherche==oldrecherche){Rech=Rech+temps2;}   // priorite_recherche : uint8_t (0, 1, 2, 3 ou 4)
      else{Rech=0;}
    
    oldligne_blanche=ligne_blanche;
    oldpousse_devant=pousse_devant;
    oldattaque_devant=attaque_devant;
    oldurgence=urgence;
    oldrecherche=priorite_recherche;
}
// ---------------------------------------------------------
void affiche_configuration()
{
// ----- priorité recherche-----
    Serial.print("rech: ");
    Serial.print(Rech);

// ----- centre NOIR - ligne BLANCHE-----
    Serial.print("      G: ");
    Serial.print(cnyG);
    Serial.print("  A: ");
    Serial.print(cnyA);
    Serial.print("  D: ");
    Serial.print(cnyD);
    Serial.print("  lign: ");
    Serial.print(Lign);

// ----- contact AVANT -----
    Serial.print("      cG: ");
    Serial.print(capG);
    Serial.print("  cD: ");
    Serial.print(capG);
    Serial.print("  pous: ");
    Serial.print(Pous);

// ----- distance US -----
    Serial.print("      jdG: ");
    Serial.print(jdG);
    Serial.print("  adG: ");
    Serial.print(adG);
    Serial.print("  jdD: ");
    Serial.print(jdD);
    Serial.print("  adD: ");
    Serial.print(adD);
    Serial.print("  atta: ");
    Serial.print(Atta);

// ----- urgence -----
    Serial.print("      urge: ");
    Serial.print(Urge);
    Serial.println("");
}
// ---------------------------------------------------------
// ----- ACTIONS -----
// ---------------------------------------------------------
void vitesses_des_moteurs()
{  
// ----- affichage sur moniteur -----

    print_distance=false;//      3 à 7 ms ... total 14 = 6 + 8 (poussée)
    print_action=false;//        1 à 3 ms ..
    print_tempscycle=false;//    1 ms     .
    print_vitesse=false;//       1 à 2 ms
    print_config=false; //       8 à 10 ms

// ----- vitesse MINI -----
    fminGaucheA=90;                                   // vitesse mot G          ald 95
      fminDroiteA=90;                                 // vitesse mot D          ald 100
    fminGaucheR=77;                                   // vitesse mot G recule   ald 90
      fminDroiteR=80;                                 // vitesse mot D recule   ald 100
    //duree_run=1750;                                   // vitesse min   

// ----- vitesse MOYENNE -----
    fmoyGaucheA=150;                                  // ald 150
      fmoyDroiteA=150;                                // ald 150
    fmoyGaucheR=100;                                  // ald 120
      fmoyDroiteR=110;                                // ald 150
    //duree_run=1500;                                 // vitesse Moy
    
// ----- vitesse MAXI -----
    fmaxGaucheA=250;                                  // ald 250
      fmaxDroiteA=250;                                // ald 230
    fmaxGaucheR=120;                                  // ald 160
      fmaxDroiteR=150;                                // ald 250
    //duree_run=1325;                                 // temps pour TEST : 1 m à MAX en avant
    duree_run=666;                                    // temps pour TEST : 0.5 m
      
}
// ---------------------------------------------------------
void constantes_de_temps()
{    
    duree_run_min=600;                                // vitesse min
    duree_run_moy=500;                                // vitesse Moy
    duree_run_max=400;                                // échauffement 40 cm à vitesse MAX    
    
    duree_brake=100;                                  // durée freinage
    duree_wait=1000;                                  // temps entre 2 essais
    
    tps_run_arriere1=500;                             // progression en ARR à vit mini
    tps_run_arriere2=450;                             // temps ARR à vitesse moyenne
    tps_run_arriere3=400;                             // à vitesse MAX
    
    temps_ligne_blanche=30;                           // tps de traversée ligne blanche
    limite_noir_blanc=100;                            // luminosité entre noir et blanc (std 500)

    enface=3;                                         // ecart maxi G et D (cm)
    toutpres=7;                                       // juste devant (cm)   
    croisement_yeux=20;                               // oeil droit voit à gauche & inversement (2ms)
    tresloin=42;                                      // distance précise mesurée en US (3ms)
    trestresloin=50;                                  // distance maxi (cm)
    
    temps_attente=5;                                  // nb secondes avant de bouger
    temps_1ere_seconde_gd=125;                        // duree de la 1ere seconde G et D
    temps_1ere_seconde_arr=250;                       // retournement : adv en arrière
    temps_1ere_seconde_av=200;                        // en avant après retournement
    temps_1ere_seconde_dojo=450;                      // centre du dojo ... (vitesse moyenne)
    nb_scan=12;                                       // periodicite de scan en recherche adv    
    
    duree_1er_round=3000;                             // durée du 1er round : 3"
    duree_totale_combat=175000;                       // durée MAXi d'une manche 3' (moins 5")
    temps_sortie_cube=60000;                          // 1 minute maxi pour sortir le cube
    
    temps_de_cycle=5;                                 // rotation loop 1 action : 5ms
    temps_de_cyclecourt=3;                            // action indéfinie
    temps_deux_appuis=8;                              // tps de cycle : poussée 2 contacts
}
// ---------------------------------------------------------
void run_and_brake()
// urgence 0 : Run test and brake (mesure vitesse et poussée) (priorite_recherche=0)
// ----- TEST OFFICIEL en VITESSE MAX -----
// ----- + CALIBRAGE des MOTEURS EN AVANT (V min, V moy et V max) -----
{
    avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
    //avance_tout_droit(fmoyGaucheA, fmoyDroiteA);
    //avance_tout_droit(fminGaucheA, fminDroiteA);
    
      delay(duree_run);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);

    recule_tout_droit(fmaxGaucheR, fmaxDroiteR);
    //recule_tout_droit(fmoyGaucheR, fmoyDroiteR);
    //recule_tout_droit(fminGaucheR, fminDroiteR);
    
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
    while(1){;}                                           // RESET pour sortir de là !!!
}
// ---------------------------------------------------------
void recherche_adversaire()
// urgence 1 : aucune présence de l'adversaire + pas d'alerte des capteurs >>> recherche
// ----- EN COMBAT !!! -----
{   
  if(premier_round){                                      // début du combat
    switch (priorite_recherche){     
      case 1:                                             // DEPART : adversaire à gauche
          if(premiere_seconde){
            sur_place_gauche(fmaxGaucheA, fmaxDroiteA);
            delay(temps_1ere_seconde_gd);
            stop_mouvement();
            avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
            delay(temps_1ere_seconde_av);}
          else{
            tourne_a_gauche(fmoyGaucheA, fmoyDroiteA);
            delay(temps_de_cycle);}
          stop_mouvement(); 
          break;
      case 2:                                             // DEPART : adversaire à droite
          if(premiere_seconde){
            sur_place_droite(fmaxGaucheA, fmaxDroiteA);
            delay(temps_1ere_seconde_gd);
            stop_mouvement();
            avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
            delay(temps_1ere_seconde_av);}
          else{
            tourne_a_droite(fmoyGaucheA, fmoyDroiteA);
            delay(temps_de_cycle);}
          stop_mouvement();
          break;
      case 3:                                             // DEPART : adversaire derrière
          if(premiere_seconde){
            sur_place_gauche(fmaxGaucheA, fmaxDroiteA);
            delay(temps_1ere_seconde_arr);
            avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
            delay(temps_1ere_seconde_av);}
          else{
            sur_place_gauche(fmoyGaucheA, fmoyDroiteA);
            delay(temps_de_cycle);}
          stop_mouvement();
          break;}}
  else{                                                   // après le 1er round
    switch (recherche_devant){     
      case 1:
        tourne_a_gauche(fmoyGaucheA, fmoyDroiteA);
        delay(temps_de_cycle);
        stop_mouvement();
        break;
      case 2:
        tourne_a_droite(fmoyGaucheA, fmoyDroiteA);
        delay(temps_de_cycle);
        stop_mouvement();
        break;
      case 3:
        avance_tout_droit(fmoyGaucheA, fmoyDroiteA);
        delay(temps_de_cycle);
        stop_mouvement();
        break;
      default:                                            // adversaire non détecté : SCAN
        if(cpt_scan==nb_scan){
          cpt_scan=0;
          sur_place_gauche(fmaxGaucheA, fmaxDroiteA);
          delay(temps_de_cycle);
          stop_mouvement();}
        else{cpt_scan=cpt_scan+1;}
        break;}}
}
// ---------------------------------------------------------
void presence_attaque()
// urgence 2 : adversaire détecté par les US025 à l'avant >>> à l'attaque !!!
// ----- EN COMBAT !!! -----
{       
    switch (attaque_devant) {
      case 1:                                         // à gauche
        tourne_a_gauche(fmoyGaucheA, fmoyDroiteA);
        delay(temps_de_cyclecourt);
        stop_mouvement();
        break;
      case 2:                                         // à droite
        tourne_a_droite(fmoyGaucheA, fmoyDroiteA);
        delay(temps_de_cyclecourt);
        stop_mouvement();
        break;
      case 3:                                         // tout droit
        avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
        delay(temps_de_cycle);
        stop_mouvement();
        break;}
}
// ---------------------------------------------------------
void contact_poussee()
// urgence 3 : contact Avant ou détection Tout Pres à l'Avant >>> on pousse fort !!!
// ----- EN COMBAT !!! -----
{
    switch (pousse_devant) {
      case 1:                                             // à gauche
        tourne_a_gauche(fmaxGaucheA, fmaxDroiteA);
        delay(temps_de_cycle);
        stop_mouvement();
        break;
      case 2:                                             // à droite
        tourne_a_droite(fmaxGaucheA, fmaxDroiteA);
        delay(temps_de_cycle);
        stop_mouvement();
        break;
      case 3:                                             // tout droit
        avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
        delay(temps_deux_appuis);
        stop_mouvement();
        break;}
}
// ---------------------------------------------------------
void blanc_dessous()
// urgence 4 : ligne blanche sous le robot >>> on dégage !!!
// ----- EN COMBAT !!! -----
{
  if(ligne_blanche){                                      // 0=noir (les 3 sont noirs) <> 1=ligneblanche (mini 1 blanc)
    if(cny70_A){                                          // .....  G A D
      if(cny70_G){
        if(cny70_D){                                      // .....  1 1 1 tout est blanc dessous (DOJO BLANC)
              stop_mouvement();
              delay(temps_de_cycle);}
        else {                                            // .....  1 1 0 Gauche + avant
              esquive_a_gauche(fmaxGaucheR, fmaxDroiteR);
              delay(temps_ligne_blanche);
              stop_mouvement();}}
      else {
        if(cny70_D){                                      // .....  0 1 1 avant + Droit
              esquive_a_droite(fmaxGaucheR, fmaxDroiteR);
              delay(temps_ligne_blanche);
              stop_mouvement();}
        else {                                            // .....  0 1 0 uniquement AVant
              recule_tout_droit(fmaxGaucheR, fmaxDroiteR);
              delay(temps_ligne_blanche);
              stop_mouvement();}}}
    else {                                                // AVANT NOIR
      if(cny70_G){
        if(cny70_D){                                      // .....  1 0 1 latéraux G et D (ligne BLANCHE dépassée)
              recule_tout_droit(fmaxGaucheR, fmaxDroiteR);
              delay(temps_ligne_blanche);
              stop_mouvement();}
        else {                                            // .....  1 0 0 Gauche (touche le BORD)
              esquive_a_gauche(fmaxGaucheR, fmaxDroiteR);
              delay(temps_ligne_blanche);
              stop_mouvement();}}
      else {
        if(cny70_D){                                      // .....  0 0 1 Droite (touche le BORD)
              esquive_a_droite(fmaxGaucheR, fmaxDroiteR);
              delay(temps_ligne_blanche);
              stop_mouvement();}
        else {;}}}}                                       // .....  0 0 0 aucun cny70 n'est blanc
//
}
// ---------------------------------------------------------
void parcours_dojo()
// urgence 5 : parcours du dojo de facon aléatoire avec les capteurs US (priorite_recherche=4)
// ----- TEST OFFICIEL -----
{
  if(premiere_seconde){
      avance_tout_droit(fmoyGaucheA, fmoyDroiteA);
      delay(temps_1ere_seconde_dojo);
      freinage();
      delay(duree_brake);
      stop_mouvement();}
  
  else{
    if(ligne_blanche){
      stop_mouvement();
      while(1){;}}                                        // FIN de test !!!
    
    if(distanceG0>0&&distanceD0>0){                       // 2 distances définies
      if(abs(distanceG0-distanceD0)<enface){
        avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
        delay(temps_de_cycle);
        stop_mouvement();}
      else{
        if(distanceG0<distanceD0){
          tourne_a_gauche(fmaxGaucheA, fmaxDroiteA);
          delay(temps_de_cycle);
          stop_mouvement();}
        if(distanceG0>distanceD0){
          tourne_a_droite(fmaxGaucheA, fmaxDroiteA);
          delay(temps_de_cycle);
          stop_mouvement();}}}

    if(distanceG0>0&&distanceD0==0){                      // CUBE à gauche
      if(distanceG0<croisement_yeux){
        tourne_a_gauche(fmoyGaucheA, fmoyDroiteA);}
      else{
        tourne_a_droite(fmoyGaucheA, fmoyDroiteA);}
      delay(temps_de_cycle);
      stop_mouvement();}
    
    if(distanceG0==0&&distanceD0>0){                      // CUBE à droite
      if(distanceD0<croisement_yeux){
        tourne_a_droite(fmoyGaucheA, fmoyDroiteA);}
      else{
        tourne_a_gauche(fmoyGaucheA, fmoyDroiteA);}
      delay(temps_de_cycle);
      stop_mouvement();}
      
    if(distanceG0==0&&distanceD0==0){                     // parours du DOJO basse vitesse
      if(cpt_scan==nb_scan){
        cpt_scan=0;
        sur_place_gauche(fmaxGaucheA, fmaxDroiteA);
        delay(temps_de_cycle);
        stop_mouvement();}
      else{
        cpt_scan=cpt_scan+1;}}
  }
}
// ---------------------------------------------------------
void echauffement_moteurs()
// urgence 6 : Echauffement des moteurs pour équilibrage (priorite_recherche=5)
// ----- VERIFICATION du CALIBRAGE AVANT ET ARRIERE des MOTEURS -----
{
    for (int echauf=0; echauf < 2; echauf++){
      avance_tout_droit(fminGaucheA, fminDroiteA);
      delay(duree_run_min);
      freinage();
      delay(duree_brake);
      stop_mouvement();
      delay(duree_wait);
      if(print_action){Serial.println("");}
      
      recule_tout_droit(fminGaucheR, fminDroiteR);
      delay(duree_run_min);
      freinage();
      delay(duree_brake);
      stop_mouvement();
      delay(duree_wait);
      if(print_action){Serial.println("");}
      
      avance_tout_droit(fmoyGaucheA, fmoyDroiteA);
      delay(duree_run_moy);
      freinage();
      delay(duree_brake);
      stop_mouvement();
      delay(duree_wait);
      if(print_action){Serial.println("");}
      
      recule_tout_droit(fmoyGaucheR, fmoyDroiteR);
      delay(duree_run_moy);
      freinage();
      delay(duree_brake);
      stop_mouvement();
      delay(duree_wait);
      if(print_action){Serial.println("");}
      
      avance_tout_droit(fmaxGaucheA, fmaxDroiteA);
      delay(duree_run_max);
      freinage();
      delay(duree_brake);
      stop_mouvement();
      delay(duree_wait);
      if(print_action){Serial.println("");}
      
      recule_tout_droit(fmaxGaucheR, fmaxDroiteR);
      delay(duree_run_max);
      freinage();
      delay(duree_brake);
      stop_mouvement();
      delay(duree_wait);
      if(print_action){Serial.println("");}}
    //
    Serial.print("Vitesse G: ");
    Serial.print(fminGaucheA);
    Serial.print("   D: ");
    Serial.print(fminDroiteA);
    Serial.print("     durée: ");
    Serial.println(duree_run_min);
     
    Serial.print("        G: ");
    Serial.print(fminGaucheR);
    Serial.print("   D: ");
    Serial.print(fminDroiteR);
    Serial.print("     durée: ");
    Serial.println(duree_run_min);
    
    Serial.print("Vitesse G: ");
    Serial.print(fmoyGaucheA);
    Serial.print("   D: ");
    Serial.print(fmoyDroiteA);
    Serial.print("     durée: ");
    Serial.println(duree_run_moy);
    
    Serial.print("        G: ");
    Serial.print(fmoyGaucheR);
    Serial.print("   D: ");
    Serial.print(fmoyDroiteR);
    Serial.print("     durée: ");
    Serial.println(duree_run_moy);
    
    Serial.print("Vitesse G: ");
    Serial.print(fmaxGaucheA);
    Serial.print("   D: ");
    Serial.print(fmaxDroiteA);
    Serial.print("     durée: ");
    Serial.println(duree_run_max);
    
    Serial.print("        G: ");
    Serial.print(fmaxGaucheR);
    Serial.print("   D: ");
    Serial.print(fmaxDroiteR);
    Serial.print("     durée: ");
    Serial.println(duree_run_max);
    
    Serial.println("Fin d'échauffement - Attente RESET");
    Serial.println("");
    while(1){;}                                           // RESET pour sortir de là !!!
}
// ---------------------------------------------------------
void test_vitesse_arriere()
// urgence 7 : Essais de mesure de VITESSE ARRIERE (priorite_recherche=6)
// ----- CALIBRAGE des MOTEURS EN ARRIERE (V min, V moy et V max) -----
{
// ----- vitesse ARRIERE MINI -----
    recule_tout_droit(fminGaucheR, fminDroiteR);
      delay(tps_run_arriere1);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);
      
    Serial.print("Vitesse G: ");
    Serial.print(fminGaucheR);
    Serial.print("   D: ");
    Serial.print(fminDroiteR);
    Serial.print("     durée: ");
    Serial.println(tps_run_arriere1);

// ----- vitesse ARRIERE MOYEN -----
    recule_tout_droit(fmoyGaucheR, fmoyDroiteR);
      delay(tps_run_arriere2);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);
    
    Serial.print("Vitesse G: ");
    Serial.print(fmoyGaucheR);
    Serial.print("   D: ");
    Serial.print(fmoyDroiteR);
    Serial.print("     durée: ");
    Serial.println(tps_run_arriere2);    

// ----- vitesse ARRIERE MAXI -----
    recule_tout_droit(fmaxGaucheR, fmaxDroiteR);
      delay(tps_run_arriere3);
    freinage();
      delay(duree_brake);
    stop_mouvement();
      delay(duree_wait);
      
    Serial.print("Vitesse G: ");
    Serial.print(fmaxGaucheR);
    Serial.print("   D: ");
    Serial.print(fmaxDroiteR);
    Serial.print("     durée: ");
    Serial.println(tps_run_arriere3);
//
    Serial.println("Fin de TEST vitesse ARRIERE - Attente RESET");
    Serial.println("");
    while(1){;}                                           // RESET pour sortir de là !!!
}
// ---------------------------------------------------------
// ---------------------------------------------------------
