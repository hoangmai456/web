#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* ===== WIFI CÓ SẴN ===== */
const char* ssid = "ten wifi";
const char* password = "matkhau";

ESP8266WebServer server(80);

/* ===== HTML TRANG WEB ===== */
const char PAGE[] PROGMEM = R"rawliteral(

#dán file html vào đây

)rawliteral";

/* ===== SETUP ===== */
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Dang ket noi WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Da ket noi WiFi");
  Serial.print("📡 IP ESP8266: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send_P(200, "text/html", PAGE);
  });

  server.on("/arrow", []() {
    if (server.hasArg("dir")) {
      Serial.println(server.arg("dir"));
    }
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

/* ===== LOOP ===== */
void loop() {
  server.handleClient();
}
