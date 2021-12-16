#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define Buzzer 2
#define LED1 3
#define LED2 4

MFRC522 rfid(SS_PIN, RST_PIN);

byte led1 = 0;
byte led2 = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Please put your card..");
  SPI.begin();
  rfid.PCD_Init();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print("NUID tag is :");
  tone(Buzzer, 700);
  delay(200);
  noTone(Buzzer);
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  Serial.println();
  ID.toUpperCase();

  if (ID.substring(1) == "15 75 FE 28" && led1 == 0 ) {
    digitalWrite(LED1, HIGH);
    Serial.println("LED1 is ON..");
    led1 = 1;
  } else if (ID.substring(1) == "15 75 FE 28" && led1 == 1 ) {
    digitalWrite(LED1, LOW);
    Serial.println("LED1 is OFF..");
    led1 = 0;
  } else if (ID.substring(1) == "2A A5 E9 81" && led2 == 0 ) {
    digitalWrite(LED2, HIGH);
    Serial.println("LED2 is ON..");
    led2 = 1;
  } else if (ID.substring(1) == "2A A5 E9 81" && led2 == 1 ) {
    digitalWrite(LED2, LOW);
    Serial.println("LED2 is OFF..");
    led2 = 0;
  } else {
    Serial.print("Wrong card!Please put correct card!");
  }

}
