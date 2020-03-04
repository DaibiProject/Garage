#include <AES.h>
#include "./printf.h"
#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
#define led 12 
AES aes;
 
RF24 radio(13, 14); // CE, CSN 
const byte addresses[][6] = {"00001", "00002"}; 
boolean buttonState;

//unsigned int keyLength [1] = {128}; // Taille de la clé
//byte *key = (unsigned char*)"DbItbDotw200"; // Clé de cryptage
//byte plain[] = "Open"; // Message a encrypter 
//byte iv [N_BLOCK] ;
//unsigned long long int myIv = 36753562; // CBC initialization vector; real iv = iv x2 ex: 01234567 = 0123456701234567

void setup() { 
  
  Serial.begin (9600) ;
  pinMode(led, OUTPUT); 
  printf_begin();
  radio.begin(); 
  radio.openWritingPipe(addresses[1]); // 00002 
  radio.openReadingPipe(1, addresses[0]); // 00001 
  radio.setPALevel(RF24_PA_MIN); 
} 
 
void loop() { 
  
  // byte iv [N_BLOCK] ;
  // int plainPaddedLength = sizeof(plain) + (N_BLOCK - ((sizeof(plain)-1) % 16)); // length of padded plaintext [B]
  // byte cipher [plainPaddedLength]; // ciphertext (encrypted plaintext)
  // byte check [plainPaddedLength]; // decrypted plaintext  
  //buttonState = LOW;
  byte cipher[17];
  
  delay(5); 
  radio.startListening(); 
  while (radio.available()){ 
    radio.read(&buttonState, sizeof(buttonState)); 
    Serial.println(buttonState);
    if (buttonState == HIGH) { 
      Serial.println("Button on");
      digitalWrite(led, HIGH); 
      Serial.println("LED allumee");
  
      radio.read(&cipher, sizeof(cipher));
      Serial.print("- cipher:  ");
      for (int i=0; i < 18; i++){
        Serial.print(cipher[i]);
      }
      Serial.println("");
      // aes.printArray(cipher,(bool)false); // Message crypté
  } else if (buttonState == LOW) {
      Serial.println("Button off");
      digitalWrite(led, LOW); 
      Serial.println("LED eteinte");
  }
    delay(200);
  }
  
}

/*
void aesTest (int bits)
{
  aes.iv_inc();
  
  byte iv [N_BLOCK] ;
  int plainPaddedLength = sizeof(plain) + (N_BLOCK - ((sizeof(plain)-1) % 16)); // length of padded plaintext [B]
  byte cipher [plainPaddedLength]; // ciphertext (encrypted plaintext)
  byte check [plainPaddedLength]; // decrypted plaintext
  
  aes.set_IV(myIv);
  aes.get_IV(iv);
 
  Serial.print("- encryption time [us]: ");
  unsigned long ms = micros ();
  aes.do_aes_encrypt(plain,sizeof(plain),cipher,key,bits,iv);
  Serial.println(micros() - ms);
 
  aes.set_IV(myIv);
  aes.get_IV(iv);
  
  Serial.print("- decryption time [us]: ");
  ms = micros ();
  aes.do_aes_decrypt(cipher,aes.get_size(),check,key,bits,iv); 
  Serial.println(micros() - ms);
  
  Serial.print("- plain:   ");
  aes.printArray(plain,(bool)true); //Message envoyé
 
  Serial.print("- cipher:  ");
  aes.printArray(cipher,(bool)false); //Message crypté
 
  Serial.print("- check:   ");
  aes.printArray(check,(bool)true); //Message dechiffrépadding

  Serial.print("- iv:      ");
  aes.printArray(iv,16); //print iv
  
  printf("\n===================================================================================\n");
}
*/
