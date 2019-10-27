#include "WiFi.h"
 
const char* ssid = "nombre-red";
const char* password =  "contraseña-red";
 
void setup() {

  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando a WiFi..");
  }
 
  Serial.println("Conectado a la red WiFi");
 
}
 
void loop() {}
