#include <WiFi.h>
#include <HTTPClient.h>

int redLed = 13;
int greenLed = 12;
int buzzer = 8;
int smokeA0 = A5;

int sensorThres = 150;

const char* ssid = "nombre-red";
const char* password =  "contraseña-red";

void setup() { 
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  
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
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);

  if (analogSensor > sensorThres) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 1000);
    
    // Verifica que se encuentre conectado a WiFi
    if ((WiFi.status() == WL_CONNECTED)) {

      HTTPClient http;

      // Especifica URL de la petición
      http.begin("http://localhost:3000/smoke-alert");
      int httpCode = http.GET(); // Realiza la petición

      // Verifica el código de estado de la respuesta
      if (httpCode > 0) { // Verifica el código de estado

          String payload = http.getString();
          Serial.println(httpCode);
          Serial.println(payload);
        }

      else {
        Serial.println("Error al realizar la petición.");
      }
      
      // Libera los recursos
      http.end();
    }
    delay(60000);
  }
  else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(1000); 
}
