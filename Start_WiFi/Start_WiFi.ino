#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi credentials (Access Point mode)
const char* ssid = "ESP8266-Server";
const char* password = "12345678";

// Web server on port 80
ESP8266WebServer server(80);

// Dummy data (you can replace later)
int counter = 0;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  // Start Access Point
  WiFi.softAP(ssid, password);

  Serial.println("WiFi Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Routes
  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();
  Serial.println("Server Started");
}

// ================= LOOP =================
void loop() {
  server.handleClient();
}

// ================= WEB PAGE =================
void handleRoot() {
  String html = R"====(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ESP8266 Server</title>
    <script>
      function fetchData() {
        fetch('/data')
          .then(response => response.text())
          .then(data => {
            document.getElementById("data").innerHTML = data;
          });
      }

      setInterval(fetchData, 1000);
    </script>
  </head>
  <body onload="fetchData()">
    <h1>ESP8266 Local Server</h1>
    <h2>Data:</h2>
    <div id="data">Loading...</div>
  </body>
  </html>
  )====";

  server.send(200, "text/html", html);
}

// ================= DATA API =================
void handleData() {
  counter++;  // simulate changing data

  String data = "Counter: " + String(counter);
  server.send(200, "text/plain", data);
}