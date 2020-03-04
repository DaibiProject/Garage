#include <AES.h>
#include "./printf.h"
#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
#define button 8
AES aes;

RF24 radio(7, 8); // CE, CSN 
const byte addresses[][6] = {"00001", "00002"}; 
boolean buttonState = 0; 

unsigned int keyLength = 128; // Taille de la clé
byte *key = (unsigned char*)"DbItbDotw200"; // Clé de cryptage
byte plain[] = "Close"; // Message a encrypter 
byte iv [N_BLOCK] ;
unsigned long long int myIv = 36753562; // CBC initialization vector; real iv = iv x2 ex: 01234567 = 0123456701234567

void setup ()
{
  Serial.begin (9600) ;
  
  pinMode(button, INPUT_PULLUP); 
  printf_begin();
  radio.begin(); 
  radio.openWritingPipe(addresses[0]); // 00001 
  radio.openReadingPipe(1, addresses[1]); // 00002 
  radio.setPALevel(RF24_PA_MIN);
}
 
void loop () 
{
  byte iv [N_BLOCK] ;
  int plainPaddedLength = sizeof(plain) + (N_BLOCK - ((sizeof(plain)-1) % 16)); // length of padded plaintext [B]
  byte cipher [plainPaddedLength]; // ciphertext (encrypted plaintext)
  byte check [plainPaddedLength]; // decrypted plaintext
  
  
  
  radio.stopListening(); 
  buttonState = digitalRead(button); 
  
  while (!radio.available()){
    Serial.println(buttonState);
    Serial.print("- key length : ");
    Serial.println(keyLength);
    aesTest (keyLength);
    delay(2000);
    radio.write(&buttonState, sizeof(buttonState)); 
    radio.write(&cipher, sizeof(cipher));
  }
  
}
 
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

  Serial.print("- plainPaddedLength:   ");
  Serial.println(plainPaddedLength);
  
  Serial.print("- cipher:  ");
  aes.printArray(cipher,(bool)false); //Message crypté
 
  Serial.print("- check:   ");
  aes.printArray(check,(bool)true); //Message dechiffré

  Serial.print("- iv:      ");
  aes.printArray(iv,16); //print iv
   
  printf("\n===================================================================================\n");
}
