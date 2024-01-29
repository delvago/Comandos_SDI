 #include <SDI12.h>

#define SERIAL_BAUD 115200 /*!< The baud rate for the output serial port */
#define DATA_PIN 25 /* D7 es gpio 13*         /*!< The pin of the SDI-12 data bus */
#define POWER_PIN 22       /*!< The sensor power pin (or -1 if not switching power) */

/** Define the SDI-12 bus */
SDI12 mySDI12(DATA_PIN);

/**
  '?' is a wildcard character which asks any and all sensors to respond
  'I' indicates that the command wants information about the sensor
  '!' finishes the command
*/
//String myCommand = "0A2!"; // Example response 0+1835.30+27.0+1
                                             //address+VWC+Temperature+Conductivity
String myCommand = "?!"; // Responde el Adress actual del sensor

void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial)
    ;

  Serial.println("Opening SDI-12 bus...");
  mySDI12.begin();
  delay(500);  // allow things to settle

  // Power the sensors;
  if (POWER_PIN > 0) {
    Serial.println("Powering up sensors...");
    pinMode(POWER_PIN, OUTPUT);
    digitalWrite(POWER_PIN, HIGH);
    delay(200);
  }
}

void loop() {
  mySDI12.sendCommand(myCommand);
  delay(300);                    // wait a while for a response
  while (mySDI12.available()) {  // write the response to the screen
    Serial.write(mySDI12.read());
  }
  delay(2000);  // print again in three seconds
}
