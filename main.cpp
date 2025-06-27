#include <WiFi.h>
#include <WiFiClient.h>      // ✅ Cliente sin SSL
#include <HTTPClient.h>

// Red WiFi
const char* ssid = "Galaxy A04e 892";
const char* password = "12345678b";

// Enlace Ngrok con HTTP (no HTTPS)
const char* serverName = "http://9e4f-186-163-11-16.ngrok-free.app/api/posicion";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi conectado");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(client, serverName);  // ✅ Con cliente HTTP sin SSL
    http.addHeader("Content-Type", "application/json");

    float lat = -12.0464 + random(-50, 50) / 10000.0;
    float lng = -77.0428 + random(-50, 50) / 10000.0;

    String json = "{\"lat\": " + String(lat, 6) + ", \"lng\": " + String(lng, 6) + "}";
    Serial.println("➡️ Enviando: " + json);

    int code = http.POST(json);
    Serial.print("📶 Código respuesta: ");
    Serial.println(code);

    if (code > 0) Serial.println("✅ Respuesta: " + http.getString());
    else Serial.println("❌ Error al enviar");

    http.end();
  } else {
    Serial.println("🚫 WiFi no conectado");
  }

  delay(10000);
}
