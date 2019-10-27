#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "nombre-red";
const char* password =  "contraseña-red";
 
void setup() {
 
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
 
  Serial.println("Conectado a la red WiFi");
 
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { // Verifica que se encuentre conectado a WiFi
 
    HTTPClient http;
 
    http.begin("http://localhost:3000/smoke-alert"); // Especifica URL de la petición
    int httpCode = http.GET();                                        // Realiza la petición
 
    if (httpCode > 0) { // Verifica el código de estado
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error al realizar la petición.");
    }
 
    http.end(); // Libera los recursos
  }
 
  delay(10000);
 
}
