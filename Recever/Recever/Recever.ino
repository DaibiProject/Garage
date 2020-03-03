#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
 
#define led 22 
 
RF24 radio(7, 8); // CE, CSN 
const byte addresses[][6] = {"00001", "00002"}; 
boolean buttonState = 0; 

int A=5;
int B=2;
int C=7;
int D=9;
int E=6;
int F=4;
int G=3;
int H=1;
int I=0;
int J=8;

int cle[] = {C,B,F,A,C,E,A,B,D,E};
int cl[10] = {H,F,A,E,I,B,A,C,G,D};

void clo(){
  delay(1000);
  for (int i=0; i < 10; i++){
    if (i+1 <= sizeof(cle))
    {
        cl[i] = abs(cl[i] - cle[i]);
     
       
          Serial.print(cl[i]);
                  
    }   }
    
         
}

void setup() { 
  Serial.begin (9600) ;
  pinMode(22, OUTPUT); 
  radio.begin(); 
  radio.openWritingPipe(addresses[1]); // 00002 
  radio.openReadingPipe(1, addresses[0]); // 00001 
  radio.setPALevel(RF24_PA_MIN); 
} 
 
void loop() { 
  //clo();
  
  delay(5); 
  radio.stopListening(); 
  int potValue = analogRead(A0); 
  int angleValue = map(potValue, 0, 1023, 0, 180); 
  radio.write(&angleValue, sizeof(angleValue)); 
 
  delay(5); 
  radio.startListening(); 
  while (!radio.available()); 
  radio.read(&buttonState, sizeof(buttonState)); 
  if (buttonState == HIGH) { 
  digitalWrite(led, HIGH); 
  Serial.println("LED allumer");
    
  radio.read(&cl[5], sizeof(cl[5]));
  radio.read(&cl[5], sizeof(cl[6]));
  radio.read(&cl[5], sizeof(cl[7]));
  radio.read(&cl[5], sizeof(cl[8]));
  radio.read(&cl[5], sizeof(cl[9]));

 } 
  else { 
    digitalWrite(led, LOW); 
  } 
  if (int cl[10] = {H,F,A,E,I,(cl[5]),(cl[6]),(cl[7]),(cl[8]),(cl[9])}) {
  Serial.print("Le code est bon");
} 
}
