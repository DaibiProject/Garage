#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
#include <Servo.h> 
 
#define button 11 
 
RF24 radio(7, 8); // CE, CSN 
const byte addresses[][6] = {"00001", "00002"}; 
Servo myServo; 
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
    
          Serial.print("--->");
          Serial.print(cl[5]);
          Serial.print(cl[6]);
          Serial.print(cl[7]);
          Serial.print(cl[8]);
          Serial.print(cl[9]);
          Serial.println("");
          delay(500);

}
void setup() { 
  pinMode(button, INPUT); 
  myServo.attach(5); 
  radio.begin(); 
  radio.openWritingPipe(addresses[0]); // 00001 
  radio.openReadingPipe(1, addresses[1]); // 00002 
  radio.setPALevel(RF24_PA_MIN); 
} 
 
void loop() { 
  delay(5); 
  radio.startListening(); 
  if ( radio.available()) { 
    while (radio.available()) { 
      int angleV = 0; 
      radio.read(&angleV, sizeof(angleV)); 
      myServo.write(angleV); 
    } 
    delay(5); 
    radio.stopListening(); 
    buttonState = digitalRead(button); 
    radio.write(&buttonState, sizeof(buttonState)); 
    radio.write(&cl[5], sizeof(cl[5]));
    radio.write(&cl[5], sizeof(cl[6]));
    radio.write(&cl[5], sizeof(cl[7]));
    radio.write(&cl[5], sizeof(cl[8]));
    radio.write(&cl[5], sizeof(cl[9]));
  } 
} 
