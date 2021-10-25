// --------------------------------------------------------
// Capteurs ultrsson US025(gauche et droit)
// --------------------------------------------------------
// 24/10/2021 - reprise du programme Yutaka2
/*
Le capteur US025 mesure la distance en cm de l'objet
La différence entre Gauche et Droit donne la position de l'adversaire

Le "timeout" est fixé à 3ms (soit 42cm / vitesse du son 340m/s)
La durée de mesure est environ 5 ms
*/
// ----- déclarations -----
#include Arduino

// ----- affichage -----
bool print_action;

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
uint8_t enface, toutpres, croisement_yeux, tresloin, trestresloin;
bool juste_devantG, juste_devantD, adv_agauche, adv_adroite;
bool tresloin_gauche, tresloin_droite;
uint8_t cpt_etatdeslieux=0;

// --------------------------------------------------------

void setup()
{
// ----- affichage
    Serial.begin(115200);                             // initialize the serial port
    print_action=true;

// ----- capteurs US avant
    pinMode(TRIGGER_G, OUTPUT);
    digitalWrite(TRIGGER_G, LOW);                     // trig G à LOW au repos
    pinMode(ECHO_G, INPUT);
    
    pinMode(TRIGGER_D, OUTPUT);
    digitalWrite(TRIGGER_D, LOW);                     // trig D à LOW au repos
    pinMode(ECHO_D, INPUT);
    
    MEASURE_TIMEOUT = 3000UL;                         // 2ms->28cm - 3ms->42cm
    cpt_etatdeslieux=0;                               // alternance gauche-droite
    
    enface=3;                                         // ecart maxi G et D (cm)
    toutpres=7;                                       // juste devant (cm)   
    croisement_yeux=20;                               // oeil droit voit à gauche & inversement (2ms)
    tresloin=42;                                      // distance précise mesurée en US (3ms)
    trestresloin=50;                                  // distance maxi (cm)
}
// --------------------------------------------------------

void loop() 
{
// ----- lecture et affichage simple
    affiche_les_US();
    delay(5);
    
// ----- lecture alternée Gauche et Droit
    //lecture_alternee_des_US();
    //affichage_des_distances();
}
// --------------------------------------------------------

void lecture_alternee_des_US()
{   
    juste_devantG=false;
    juste_devantD=false;
    adv_agauche=false;
    adv_adroite=false;
    tresloin_gauche=false;
    tresloin_droite=false;
  
    switch (cpt_etatdeslieux) {                         // lecture alternée
      case 0: USgauche();cpt_etatdeslieux=1;break;
      case 1: USdroite();cpt_etatdeslieux=0;break;}

    if(distanceG0>0&&distanceD0==0){                    // présence G uniquement
      if(distanceG0<=toutpres){juste_devantG=true;}
      else{
        if(distanceG0<=tresloin){
          if(distanceG0<=croisement_yeux){adv_agauche=true;}
          else{adv_adroite=true;}}
        else{tresloin_gauche=true;}}}
               
    if(distanceG0==0&&distanceD0>0){                    // présence D uniquement
      if(distanceD0<=toutpres){juste_devantD=true;}
      else{
        if(distanceD0<=tresloin){
          if(distanceD0<=croisement_yeux){adv_adroite=true;}
          else{adv_agauche=true;}}
        else{tresloin_droite=true;}}}

    if(distanceG0>0&&distanceD0>0){                     // 2 mesures US définies
      if(abs(distanceG0-distanceD0)<=enface){           // ADV en face
        if(distanceG0<=toutpres||distanceD0<=toutpres){
          juste_devantG=true; juste_devantD=true;}
        else{
          if(distanceG0<=tresloin||distanceD0<=tresloin){
            adv_agauche=true; adv_adroite=true;}
          else{tresloin_gauche=true; tresloin_droite=true;}}}
      else{
        if(distanceG0<distanceD0){                      // ADV à gauche
          if(distanceG0<=toutpres){juste_devantG=true;}
          else{
            if(distanceG0<=tresloin){adv_agauche=true;}
            else{tresloin_gauche=true;}}}
        else{                                           // ADV à droite
          adv_adroite=true;
          if(distanceD0<=toutpres){juste_devantD=true;}
          else{
            if(distanceD0<=tresloin){adv_adroite=true;}
            else{tresloin_droite=true;}}}}}
}
// --------------------------------------------------------

void affichage_des_distances()
{
    Serial.print("     dUS: ");
    if(tresloin_gauche){Serial.print(" . ");}else{Serial.print("   ");}
    if(adv_agauche){Serial.print(" * ");}else{Serial.print("   ");}
    if(juste_devantG){Serial.print("*** ");}else{Serial.print("    ");}
    Serial.print(distanceG0);
    Serial.print(" - ");
    Serial.print(distanceD0);
    if(juste_devantD){Serial.print(" ***");}else{Serial.print("    ");}
    if(adv_adroite){Serial.print(" * ");}else{Serial.print("   ");}
    if(tresloin_droite){Serial.print(" . ");}else{Serial.print("   ");}
    
    Serial.println("");
}
// --------------------------------------------------------

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
// ---------------------------------------------------------