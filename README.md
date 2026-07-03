# ESP32 + RFID RC522 + LCD 1602 Access Control System

An access control system project based on the **ESP32 (HW-394)** microcontroller and the **RFID RC522** card reader. 
The code recognizes specific card UID numbers and displays a dedicated "Witaj User x" greeting, while blocking access for unknown cards.

### 🚀 Key Features:
* **No I2C Module Required:** The LCD 1602 display is connected directly to the ESP32 in 4-bit mode.
* **ESP32 Left-Side Optimization (Breadboard):** The code and connections are designed to use pins exclusively from the **left side of the ESP32**.
* **No Extra Female Jumper Wires:** The 5V power and Ground (GND) connections are routed "under the belly" of the ESP32 directly to the breadboard's side power rails.

---

## 📸 Project Media

![Project Overview](images/rfid1.jpg)
![RFID request](images/rfid4.jpg)
![User1](images/rfid2.jpg)
![User2](images/rfid3.jpg)

---

## 🛠️ Wiring Diagram

### LCD 1602 Display
All data lines are connected to the left side of the ESP32, and power is drawn from the 5V side power rail (bridged from the VN pin).

| LCD Pin | Function | ESP32 Pin / Breadboard Connection |
| :---: | :--- | :--- |
| **1 & 16** | VSS / K | **GND** (Blue Rail) |
| **2 & 15** | VDD / A | **5V / VN** (Red Rail) |
| **3** | V0 | **Potentiometer Middle Pin** (Contrast adjustment) |
| **4** | RS | **D15** (Left Side) |
| **5** | R/W | **GND** (Blue Rail) |
| **6** | E | **D4** (Left Side) |
| **11-14**| D4 - D7 | **D16, D17, D21, D22** (Sequentially in Row A) |

### RFID RC522 Reader
The reader communicates via the SPI bus using a safe 3.3V voltage level.

* **3.3V** -> **3V3** pin (ESP32 left side)
* **GND** -> **GND** pin (ESP32 left side)
* **SDA** -> **D5** pin
* **SCK** -> **D18** pin
* **MISO** -> **D19** pin
* **MOSI** -> **D23** pin
* **RST** -> **D2** pin

---

## 💻 Required Libraries
In the Arduino IDE:
* **MFRC522** (Library Manager -> Search "MFRC522" -> Install)

---

## ⚙️ Setup & Configuration (Important!)

1. **Serial Monitor Baud Rate:** To correctly read messages and card UID codes, you must open the *Serial Monitor* and set the baud rate to exactly **115200 baud** in the bottom right corner. Leaving it at the default 9600 baud will cause errors and corrupted characters (garbage text).
2. **Uploading the Program (Bootloader Workaround):** When uploading the code, if the console shows the `Connecting.......` message, you need to press and hold the **BOOT** button on the ESP32 board until the flashing percentage progress bar starts moving.

---
