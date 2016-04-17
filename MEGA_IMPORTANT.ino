#include <Wire.h>
#include <LiquidCrystal.h>
#include <DS1302RTC.h>
#include <Time.h>
#include <dht11.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
dht11 DHT11; 

#define DHT11PIN 6 

DS1302RTC RTC(9, 7, 8);
#define DS1302_GND_PIN 33
#define DS1302_VCC_PIN 35

const int CapteurPin = 13;
int interrupteur = LOW;       
int etat = 0;             
int Capteur = 0;  
int tempsa;
int tempsb;
int compteur;
float vitesse1=0;
float tempssec = 0;
int vitessekmh=0;
float distanceparcourue = 0;
int ValBatterie;
int affichageBatterie;
int BouttonReglage;
int BouttonReglagePin=A1;
int etatBouttonReglage;
int Plus;
int Moins;
int PlusPin;
int MoinsPin;
int BouttonChangement;
int BouttonChangementPin;
int etatBouttonChangement;
int Unit;
int distancetotalparcourue;
int vitessems;

void setup() 
{
lcd.begin(20,4);
  pinMode(CapteurPin, INPUT);    
  digitalWrite(DS1302_GND_PIN, LOW);
  pinMode(DS1302_GND_PIN, OUTPUT);

  digitalWrite(DS1302_VCC_PIN, HIGH);
  pinMode(DS1302_VCC_PIN, OUTPUT);
  setSyncProvider(RTC.get);       
  delay ( 2000 );
  lcd.clear();
}


void loop() 
{
   BouttonReglage = digitalRead(BouttonReglagePin);

  if (BouttonReglage == LOW) {    

    if (etatBouttonReglage == 0) {   
  calcul_vitesse();
  mesure_temperature();
  heure();
  lecture_batterie();
  }
  
  else 
  {
reglage();
    

  }

  }
}

void calcul_vitesse()
{
   Capteur = digitalRead(CapteurPin);

  if (Capteur == LOW) {    

    if (etat == 0) {
   
tempsa = millis();
 compteur = compteur + 1;  
     distancetotalparcourue + distanceparcourue;
    }  
         
     
  }
  
  else 
  {
tempsb=millis();
    int tempsfin=0;
    tempsfin=millis()-tempsa;
    tempssec=(float)tempsfin/1000;
    vitesse1=0.61/(float)tempssec;
    vitessekmh=(float)vitesse1*3.6;
    delay(200);

    
   
    if(compteur=1) {
if(Unit == 1) {
  lcd.clear();  
  lcd.setCursor(0,1);
  lcd.print("VITESSE: ");
  lcd.print(vitessekmh);
  lcd.setCursor(13,1);
  lcd.print("km/h");
}
if(Unit == 0) {
  vitessems = vitessekmh/3,6;
  
  lcd.clear();  
  lcd.setCursor(0,1);
  lcd.print("VITESSE: ");
  lcd.print(vitessems);
  lcd.setCursor(13,1);
  lcd.print("km/h");
}
   lcd.setCursor(0,2);
  lcd.print("Distance: "); 
  lcd.print(distanceparcourue);
  lcd.setCursor(19,2);
  lcd.print("m");
  
  

    }
compteur = 0;
    

  }

}

void mesure_temperature()
{
    int chk = DHT11.read(DHT11PIN); 


  lcd.setCursor(0,3);
  lcd.print("Temperature: "); 
  lcd.print(DHT11.temperature); 
  lcd.setCursor(15,3);
  lcd.print("'C");
    
}

void heure()
{
static int sday = 0; 

 lcd.setCursor(7, 0);
  print2digits(hour()+2);
  lcd.print(":");
  print2digits(minute()-10);
   
   switch (hour()) 
   {
  case 24:
    lcd.print("00");
    break;
  case 25:
    lcd.print("01");
    break;
  case 26:
    lcd.print("02");
    break;
   }
}

void print2digits(int number)
{
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);

}

void lecture_batterie() {
  ValBatterie = analogRead(A0);
  
  affichageBatterie = map(ValBatterie, 970, 1023, 0, 100);
  
if (affichageBatterie > 99) 
  {
    lcd.setCursor(16,0);
}

else  {
lcd.setCursor(17,0);
}

  lcd.print(ValBatterie);
  lcd.setCursor(19,0);
  lcd.print("%");
  delay(100);
  
}

void reglage()
{
  
  
   Plus = digitalRead(PlusPin);
   Moins = digitalRead(MoinsPin);
   BouttonChangement = digitalRead(BouttonChangementPin);


  if (BouttonChangement == HIGH) {    

    if (etatBouttonChangement == 0)
    {   

 if (Moins == HIGH) {    
Unit = 0;
lcd.clear();
lcd.setCursor(6,0);
lcd.print("Reglage");
lcd.setCursor(0,2);
lcd.print("Unite: m/s");
 }
 
 if (Plus == HIGH) {    
Unit = 1;
lcd.clear();
lcd.setCursor(6,0);
lcd.print("Reglage");
lcd.setCursor(0,2);
lcd.print("Unite: km/h");
 }
  
    }
    
  }
   else 
  {
 if (Moins == HIGH) {    
distanceparcourue--;
lcd.clear();
lcd.setCursor(6,0);
lcd.print("Reglage");
lcd.setCursor(0,2);
lcd.print("Valeur: ");
lcd.setCursor(8,2);
lcd.print(distanceparcourue);
 }
 
 if (Plus == HIGH) {    
distanceparcourue++;
lcd.clear();
lcd.setCursor(6,0);
lcd.print("Reglage");
lcd.setCursor(0,2);
lcd.print("Valeur: ");
lcd.setCursor(8,2);
lcd.print(distanceparcourue);
 }
    

  }
 
}
