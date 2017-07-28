#include <CurieTimerOne.h>
#include <SoftwareSerial.h>
#include <CurieBLE.h>

/****************************************
 *                                      *
 *  Arduino functions                   *
 *                                      *
 ****************************************/

 /* Macros */ 

 #define SOUND_SENSOR A3
 #define LED A2
 #define ESP8266 D1
 #define threshold 100
 
BLEPeripheral blePeripheral;       // BLE Peripheral Device (the board you're programming)
BLEService batteryService("180F"); 


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  Serial.println("=======================");

  Serial.print("Using remote with programming button ");
  Serial.print(ROBOT_IR_REMOTE_FUNC, HEX);
  Serial.println();
  pins_init();
  pinMode(ROBOT_IR_PIN, INPUT);
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // Soundsensor, for debugging 
  int sensorValue = analogRead(SOUND_SENSOR);

  Serial.print("sensorValue ");
  Serial.println(sensorValue);
  if(sensorValue > THRESHOLD_VALUE){
    turnOnLED();
    delay(200);
  } 
  turnOffLED();
  
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
  digitalWrite(ESP8266, currAudio);
  return 0; 
} 


void pins_init(){
  pinMode(LED, OUTPUT);
  pinMode(SOUND_SENSOR, INPUT); 
}

void turnOnLED(){
  digitalWrite(LED,HIGH);
}

void turnOffLED(){
  digitalWrite(LED,LOW);
}
