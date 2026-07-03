#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

// pin conf
#define RST_PIN   2     // Reset pin for GPIO2
#define SS_PIN    5     // SDA (SS) pin for GPIO5

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID reader instance

//  LCD conf pins 
const int rs = 15, en = 4, d4 = 16, d5 = 17, d6 = 21, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(115200); // initialize serial communication
  
  // LCD initialization
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicjalizacja...");
  
  // SPI and RFID initialization
  SPI.begin();
  mfrc522.PCD_Init();
  
  delay(1000);
  
  // Standby/Start screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zbliz karte RFID");
  Serial.println("System ready. Scan card...");
}

void loop() {
  // check if a new card is present
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // read data from the card
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // convert UID array to hex string
  String cardUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    cardUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  cardUID.toUpperCase();

  // print UID to Serial Monitor
  Serial.print("Detected UID: ");
  Serial.println(cardUID);

  // Access control validation 
  lcd.clear();
  
  if (cardUID == "A52BD6AB") {
    // first card authorization
    lcd.setCursor(0, 0);
    lcd.print("Witaj User 1!");      
    lcd.setCursor(0, 1);
    lcd.print("ID: " + cardUID);    
    Serial.println("Access granted for: User 1");
    
  } else if (cardUID == "74BED6FE") {
    // second card authorization
    lcd.setCursor(0, 0);
    lcd.print("Witaj User 2!");     
    lcd.setCursor(0, 1);
    lcd.print("ID: " + cardUID);    
    Serial.println("Access granted for: User 2");
    
  } else {
    // Unknown card / Access denied
    lcd.setCursor(0, 0);
    lcd.print("Nieznana karta!");
    lcd.setCursor(0, 1);
    lcd.print("Brak dostepu!");
    Serial.println("ALERT: Unauthorized access attempt!");
  }

  delay(3000); // Keep message on screen for 3 seconds

  // Reset RFID reader state for the next scan 
  mfrc522.PICC_HaltA();       // Stop communication with current card
  mfrc522.PCD_StopCrypto1();  // Stop encryption
  
  // Return to standby screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zbliz karte RFID");
}