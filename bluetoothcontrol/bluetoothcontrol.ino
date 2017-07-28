#include <SoftwareSerial.h>
#include <map.h>
#include <env.h>
#include "bluetooth.h"
#include <CurieBLE.h>

struct item<unsigned char, unsigned long>* codes = getCodes();

/****************************************
 *                                      *
 *  Arduino functions                   *
 *                                      *
 ****************************************/
 
BLEPeripheral blePeripheral;       // BLE Peripheral Device (the board you're programming)
BLEService batteryService("180F"); 


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  Serial.println("=======================");

  Serial.print("Using remote with programming button ");
  Serial.print(ROBOT_IR_REMOTE_FUNC, HEX);
  Serial.println();

  pinMode(ROBOT_IR_PIN, INPUT);
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(13, HIGH);

    // read the audio every 400ms
    while (central.connected()) {
      long currentMillis = millis();
      // if 400ms have passed, read audio
      if ( sizeof(readAudio) > 0) {
        currAudio = readAudio ;
        sendAudiotoServer(currAudio);
      }
    }
    // when the phone dc's, turn off the LED:
    digitalWrite(13, LOW);
    Serial.print("Disconnected ");
    Serial.println(central.address());
  }
}

int sendAudiotoServer() { 
  
  return 0; 
} 
}

SoftwareSerial bluetooth(ROBOT_BT_RX_PIN, ROBOT_BT_TX_PIN);
Robot robot = new Robot(true);
struct item<unsigned char, int>* codes = getCodes();

/****************************************
 *                                      *
 *  Arduino functions                   *
 *                                      *
 ****************************************/

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("=======================");
}

void loop() {
//  unsigned short darkness = analogRead(A0);
//  if (Env::isDark(darkness)) {
//    arduino.turnLightsOn();
//  } else {
//    arduino.turnLightsOff();
//  }

  if (bluetooth.available()) {
    int code = bluetooth.read();
    if (code == 3) {
      return;
    }
    struct item<unsigned char, int>* item = findItemByValue(codes, code);
    if (item != NULL) {
      arduino.execute(item->key);
    }
  }

  delay(DELAY_LOOP);
}
