#include <AESLib.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>
 
//nRF24L01
#define CE_PIN 13
#define CSN_PIN 14

RF24 radio(CE_PIN,CSN_PIN);
const byte addresses[][5] = {"03499", "02989", "51914", "44204"};

void aes() {
// AES
byte key = (unsigned char)"DbItbDotw200";                         // Clé de cryptage
// byte iv [N_BLOCK];
// unsigned long long int myIv = 36753562;                          // Vecteur d'initialisation
byte open_msg[] = "Open";                                           // Message (Open)
byte messageCode[]= "";
aes128_enc_single(key, open_msg);                                   // pour chiffrer

for (int i = 0; i < (sizeof(open_msg)-1); i++) {
  messageCode[i] = open_msg[i];
 }
Serial.println("Envoie des données");
radio.stopListening();

while (radio.available()){ 
  for (int i = 0; i < sizeof(open_msg)-1; i++){
    radio.write(&messageCode[i], sizeof(messageCode[i]));
    Serial.print(messageCode[i]);                                      // Message crypter
  }
}
}

void setup() {
 
   /* Initialisation du port série */
  Serial.begin(115200);
  delayMicroseconds(10);
  /* Initialisation radio */
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(100);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(0);
  radio.enableDynamicPayloads();
  radio.openWritingPipe(addresses[0]);                              // 03499 
  radio.openReadingPipe(1, addresses[1]);                           // 02989                            
  radio.printDetails();
  delayMicroseconds(10);
}

void loop() {
aes();  

    /*  Serial.println("Reception de la confirmation");
      radio.startListening(); 
      while (radio.available()){ 
        radio.read(&message, sizeof(message)); 
        */
}
