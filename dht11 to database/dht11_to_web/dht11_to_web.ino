#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 4      // Pin where the DHT11 is connected
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
const char* ssid = "realme_9i";
const char* password = "1234abcde";

void setup() {
    Serial.begin(115200);
    dht.begin();

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop() {
    if ((WiFi.status() == WL_CONNECTED)) {
        HTTPClient http;
        http.begin("http://192.168.160.107/Temp_site/php/update_data.php"); // URL to the PHP script
        http.addHeader("Content-Type", "application/json");

        // Reading temperature and humidity values
        float temp = dht.readTemperature();
        float humidity = dht.readHumidity();

        if (isnan(temp) || isnan(humidity)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
        }

        // Prepare JSON payload
        String payload = "{\"temperature\": " + String(temp) + ", \"humidity\": " + String(humidity) + "}";

        // Send HTTP POST request
        int httpResponseCode = http.POST(payload);
        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    }

    // Wait before next measurement
    delay(10000); // 1 minute
}
