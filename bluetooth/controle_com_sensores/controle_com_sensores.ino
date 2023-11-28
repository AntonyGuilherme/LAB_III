#include "BluetoothSerial.h"

//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
const char *pin = "1234"; // Change this to more secure PIN.

String device_name = "ESP32-BT-Slave";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;



void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

void acionarMotor(String direcao) {
  if (direcao.startsWith("frente")) {
      Serial.println("Comando recebido - frente");
  }
  else if (direcao.startsWith("tras")) {
        Serial.println("Comando recebido - tras");
        SerialBT.print("tras");
  }
  else {
      Serial.println(direcao);
  }
}

void loop() {

  String content = "";
  char character;
      
  while(SerialBT.available()) {
      character = SerialBT.read();
      content.concat(character);
  }

  if (content != "") {
    acionarMotor(content);
  }

  delay(100);
}

