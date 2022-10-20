#include <WiFi.h>

#define PINO 22

const char *ssid = "wifi";
const char *password = "password";

WiFiServer server(80);

void relay_wifi();

void setup() {
    Serial.begin(115200);

    pinMode(PINO, OUTPUT);

    digitalWrite(PINO, LOW);

    Serial.println();
    Serial.print("Conectando-se a ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("WiFi conectada: Endereço de IP:");
    Serial.println(WiFi.localIP());
    server.begin();

    Serial.println("WiFi status:");
    Serial.println(WiFi.status());

    Serial.println("macAddress:");
    Serial.println(WiFi.macAddress());
}

void loop() {

    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        Serial.print(".");

        delay(1000);
    }

    relay_wifi();
}

void relay_wifi() {
    WiFiClient client = server.available();

    if (client) {
        Serial.println("Novo Cliente");
        String currentLine = "";

        while (client.connected()) {

            if (client.available()) {
                char c = client.read();
                Serial.write(c);

                if (c == '\n') {

                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        client.print("<h2>Clique <a href=\"/H1\">AQUI</a> para ligar o led.</h2><br>");
                        client.print("<h2>Clique <a href=\"/L1\">AQUI</a> para desligar o led.</h2><br>");
                        client.println();
                        break;
                    } else {
                        currentLine = "";
                    }

                } else if (c != '\r') {
                    currentLine += c;
                }

                if (currentLine.endsWith("GET /H1")) {
                    Serial.println("ligado");
                    digitalWrite(PINO, HIGH);
                } else if (currentLine.endsWith("GET /L1")) {
                    Serial.println("desligado");
                    digitalWrite(PINO, LOW);
                }
            }
        }
        client.stop();
        Serial.println("Fim");
    }
}