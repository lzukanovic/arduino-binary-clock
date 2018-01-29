#include <Servo.h>
#define C5  523
#define D5  587
#define E5  659



Servo myservo;
int sekunda=0;
int minuta=0;
int ura=0;
int potprejm;
int potprejh;
int i = 0;
int poz=180;
boolean spr=true;

void setup() {
  pinMode(1, OUTPUT);pinMode(2, OUTPUT);pinMode(3, OUTPUT);pinMode(4, OUTPUT);pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);pinMode(7, OUTPUT);pinMode(8, OUTPUT);pinMode(9, OUTPUT);pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);pinMode(12, OUTPUT);pinMode(13, OUTPUT);//ledice do sm
  pinMode(A0,INPUT);//potm
  pinMode(A1,INPUT);//poth
  myservo.attach(A2);//servo
  pinMode(A3,INPUT);//switch
  pinMode(A4,OUTPUT);//piezo
  //Serial.begin(9600);
}


void loop() {
  
  if(digitalRead(A3)==0){
     spr=true;
  }
  if(digitalRead(A3)==1&&spr){
     bootsng(C5);
     delay(50);
     bootsng(E5);
     delay(150);
     bootsng(D5);
     delay(200);
     bootsng(E5);
     spr=false;

  }

  if(digitalRead(A3)==1){
     clockCount(); 
     priziganje();

  
     int potm=(int)(60.0/1024.0*analogRead(A0));   
     int poth=(int)(24.0/1024.0*analogRead(A1)); 
     
     if(potm>potprejm+0.9||potm<potprejm-0.9){
       nastaviMinute(potm);
       potprejm=potm;
     }
     if(poth>potprejh+0.9||poth<potprejh-0.9){
       nastaviUre(poth);
       potprejh=poth;
     }

     if(poz<((60-sekunda)/60.0)*180){
       myservo.write(poz+1);
       poz++;
       delay(1);    
      }
    
     if(poz>((60-sekunda)/60.0)*180){
         myservo.write(poz-1);
         poz--;
         delay(1);
      }

           //Serial.println(sekunda);
           //Serial.print(minuta);
          // Serial.print(ura);
  }
    else{
      myservo.write(180);
      for(int a=13;a>0;a--){
      digitalWrite(a,LOW);
      }
   }
}
void nastaviMinute(int potm){
  minuta=potm;
  sekunda=0;
  }
void nastaviUre(int poth){
    ura=poth;
  }
void clockCount(){
  static unsigned long zadnji = 0;
  if(millis()- zadnji>= 1000){
    zadnji=millis();
    sekunda++;
    
    }
      if (sekunda >= 60) {
        minuta++;
        sekunda = 0; 
      }
      if (minuta >=60) {
        ura++;
        minuta = 0; 
      }
      if (ura >=24) {
        ura = 0;
        minuta = 0; 
        sekunda = 0;
      }  
  }

void priziganje()
{
  int digih=ura%10;
  int digimin=minuta%10;
  if(digimin == 1 || digimin == 3 || digimin == 5 || digimin == 7 || digimin == 9) {  digitalWrite(1, HIGH);} else {  digitalWrite(1, LOW);}
  if(digimin == 2 || digimin == 3 || digimin == 6 || digimin == 7) {digitalWrite(2, HIGH);} else {digitalWrite(2,LOW);}
  if(digimin == 4 || digimin == 5 || digimin == 6 || digimin == 7) {digitalWrite(3, HIGH);} else {digitalWrite(3,LOW);}
  if(digimin == 8 || digimin == 9) {digitalWrite(4, HIGH);} else {digitalWrite(4,LOW);}

  if((minuta >= 10 && minuta < 20) || (minuta >= 30 && minuta < 40) || (minuta >= 50 && minuta < 60))  {digitalWrite(5, HIGH);} else {digitalWrite(5,LOW);}
  if(minuta >= 20 && minuta < 40)  {digitalWrite(6, HIGH);} else {digitalWrite(6,LOW);}
  if(minuta >= 40 && minuta < 60) {digitalWrite(7, HIGH);} else {digitalWrite(7,LOW);}

  if(digih == 1 || digih == 3 || digih == 5 || digih == 7 || digih == 9) {digitalWrite(8, HIGH);} else {digitalWrite(8,LOW);}
  if(digih == 2 || digih == 3 || digih == 6 || digih == 7) {digitalWrite(9, HIGH);} else {digitalWrite(9,LOW);}
  if(digih == 4 || digih == 5 || digih == 6 || digih == 7) {digitalWrite(10, HIGH);} else {digitalWrite(10,LOW);}
  if(digih == 8 || digih == 9) {digitalWrite(11, HIGH);} else {digitalWrite(11,LOW);}
  
  if(ura >= 10 && ura < 20)  {digitalWrite(12, HIGH);} else {digitalWrite(12,LOW);}
  if(ura >= 20 && ura < 24)  {digitalWrite(13, HIGH);} else {digitalWrite(13,LOW);}
}

void bootsng(int del){
  long elapsed_time = 0;
    for(int x=0;x<200;x++){
    analogWrite(A4,255);
    delayMicroseconds(del);
    analogWrite(A4,0);
    delayMicroseconds(del);
    }
}
