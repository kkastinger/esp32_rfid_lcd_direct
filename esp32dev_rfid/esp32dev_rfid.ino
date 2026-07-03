#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

// piny lewa strona
#define RST_PIN   2     // pin rst dla gpio2
#define SS_PIN    5     // Pin SDA (ss) dla gpio5

MFRC522 mfrc522(SS_PIN, RST_PIN); // instancja czytnika rfid

// piny lcd conf
const int rs = 15, en = 4, d4 = 16, d5 = 17, d6 = 21, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(115200);
  
  // lcd inicjalizacja
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicjalizacja...");
  
  // spi i rfid
  SPI.begin();
  mfrc522.PCD_Init();
  
  delay(1000);
  
  // ekran startowy
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zbliz karte RFID");
  Serial.println("System gotowy. Zbliż kartę...");
}

void loop() {
  // chech czy jest nowa karta
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // odczytywanie danych z karty
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // UID jako string
  String cardUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    cardUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  cardUID.toUpperCase();

  // UID w konsoli
  Serial.print("Wykryto UID: ");
  Serial.println(cardUID);

  // sprawdzanie dostepu karty
  lcd.clear();
  
  if (cardUID == "A52BD6AB") {
    // pierwsza karta
    lcd.setCursor(0, 0);
    lcd.print("Witaj User 1!");      
    lcd.setCursor(0, 1);
    lcd.print("ID: " + cardUID);    
    Serial.println("Dostęp przyznany dla: User 1");
    
  } else if (cardUID == "74BED6FE") {
    // druga karta
    lcd.setCursor(0, 0);
    lcd.print("Witaj User 2!");     
    lcd.setCursor(0, 1);
    lcd.print("ID: " + cardUID);    
    Serial.println("Dostęp przyznany dla: User 2");
    
  } else {
    // obca karta
    lcd.setCursor(0, 0);
    lcd.print("Nieznana karta!");
    lcd.setCursor(0, 1);
    lcd.print("Brak dostepu!");
    Serial.println("ALARM: Nieautoryzowana próba dostępu!");
  }

  delay(3000); // komunikat - 3 sekundy

  // reset stanu czytnika
  mfrc522.PICC_HaltA();       // komunikacja z obecna karta - stop
  mfrc522.PCD_StopCrypto1();  // stop - szyfrowanie
  
  // powrot do main (glowny ekran)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zbliz karte RFID");
}