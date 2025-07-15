#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <mbedtls/md.h>
#include <mbedtls/base64.h>
#include <time.h>

#define WIFI_SSID "jop"
#define WIFI_PASSWORD "123456789"
#define API_KEY "."
#define API_SECRET "."
#define ACCESS_TOKEN "."
#define ACCESS_TOKEN_SECRET "."

Adafruit_BMP280 bmp;
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastTweetTime = 0;
const unsigned long TWEET_INTERVAL = 2 * 60 * 1000;

String urlEncode(const String& str) {
  String encoded = "";
  for (int i = 0; i < str.length(); i++) {
    char c = str[i];
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') 
        || c == '-' || c == '_' || c == '.' || c == '~') {
      encoded += c;
    } else {
      encoded += '%';
      char hex[3];
      sprintf(hex, "%02X", c);
      encoded += hex;
    }
  }
  return encoded;
}
String calcularHMACSHA1(const String& key, const String& message) {
  unsigned char hmac[20];
  unsigned char base64Hmac[64];
  size_t base64Len = 0;

  mbedtls_md_context_t ctx;
  mbedtls_md_init(&ctx);
  const mbedtls_md_info_t* info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA1);
  mbedtls_md_setup(&ctx, info, 1);
  mbedtls_md_hmac_starts(&ctx, (const unsigned char*)key.c_str(), key.length());
  mbedtls_md_hmac_update(&ctx, (const unsigned char*)message.c_str(), message.length());
  mbedtls_md_hmac_finish(&ctx, hmac);
  mbedtls_md_free(&ctx);

  mbedtls_base64_encode(base64Hmac, sizeof(base64Hmac), &base64Len, hmac, sizeof(hmac));

  return String((char*)base64Hmac);
}

void setup() {
  Serial.begin(115200);
  randomSeed(micros());
  conectarWiFi();
  sincronizarTiempo();
  inicializarSensores();
}

void loop() {
  float temperaturaDHT = dht.readTemperature();
  float humedad = dht.readHumidity();
  float temperaturaBMP = bmp.readTemperature();
  float presion = bmp.readPressure() / 100.0F;
  float altitud = bmp.readAltitude(1013.25);

  if (!isnan(temperaturaDHT) && !isnan(humedad) && 
      !isnan(temperaturaBMP) && !isnan(presion)) {
    imprimirLecturas(temperaturaDHT, humedad, temperaturaBMP, presion, altitud);

    unsigned long tiempoActual = millis();
    if (tiempoActual - lastTweetTime >= TWEET_INTERVAL) {
      String mensaje = generarMensajeTweet(temperaturaDHT, humedad, temperaturaBMP, presion, altitud);
      if (enviarTweet(mensaje)) {
        lastTweetTime = tiempoActual;
      } else {
        Serial.println("Fallo al enviar tweet. Reintentando...");
      }
    }
  } else {
    Serial.println("Error en la lectura de sensores");
  }

  delay(50000);
}

void conectarWiFi() {
  Serial.println("Conectando a WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi.");
  Serial.println("IP: " + WiFi.localIP().toString());
}

void sincronizarTiempo() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Sincronizando tiempo con NTP...");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("\nTiempo sincronizado.");
}

void inicializarSensores() {
  if (!bmp.begin(0x76)) {
    Serial.println("No se encontró el sensor BMP280.");
    while (1);
  }
  
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, 
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X2, 
                  Adafruit_BMP280::FILTER_X4,
                  Adafruit_BMP280::STANDBY_MS_500);
  
  dht.begin();
}

void imprimirLecturas(float tempDHT, float hum, float tempBMP, float pres, float alt) {
  Serial.printf("DHT22 - Temp: %.2f°C, Humedad: %.2f%%\n", tempDHT, hum);
  Serial.printf("BMP280 - Temp: %.2f°C, Presión: %.2f hPa, Altitud: %.2f m\n", tempBMP, pres, alt);
}

String generarMensajeTweet(float tempDHT, float hum, float tempBMP, float pres, float alt) {
  String tweet = "Reporte de sensores 🌡️☀️:\n";
  tweet += "DHT22 - Temp: " + String(tempDHT, 1) + "°C, Hum: " + String(hum, 1) + "%\n";
  tweet += "BMP280 - Temp: " + String(tempBMP, 1) + "°C, Presión: " + String(pres, 1) + " hPa\n";
  tweet += "#CircuitosElectricosyElectronicos #Episi";
  return tweet;
}


String crearEncabezadoOAuth(const String& mensajeTweet) {
  String nonce = String(random(1000000000));
  String timestamp = String(time(nullptr));

  String paramString = 
    "oauth_consumer_key=" + urlEncode(API_KEY) + 
    "&oauth_nonce=" + urlEncode(nonce) +
    "&oauth_signature_method=HMAC-SHA1" +
    "&oauth_timestamp=" + urlEncode(timestamp) +
    "&oauth_token=" + urlEncode(ACCESS_TOKEN) +
    "&oauth_version=1.0";

  String baseString = 
    "POST&" + 
    urlEncode("https://api.twitter.com/2/tweets") + 
    "&" + 
    urlEncode(paramString);

  String signingKey = 
    urlEncode(API_SECRET) + 
    "&" + 
    urlEncode(ACCESS_TOKEN_SECRET);


  String signature = calcularHMACSHA1(signingKey, baseString);

  String header = "OAuth ";
  header += "oauth_consumer_key=\"" + urlEncode(API_KEY) + "\", ";
  header += "oauth_nonce=\"" + urlEncode(nonce) + "\", ";
  header += "oauth_signature=\"" + urlEncode(signature) + "\", ";
  header += "oauth_signature_method=\"HMAC-SHA1\", ";
  header += "oauth_timestamp=\"" + urlEncode(timestamp) + "\", ";
  header += "oauth_token=\"" + urlEncode(ACCESS_TOKEN) + "\", ";
  header += "oauth_version=\"1.0\"";

  return header;
}


bool enviarTweet(const String& mensajeTweet) {
  if (WiFi.status() != WL_CONNECTED) {
    conectarWiFi();
    return false;
  }

  HTTPClient http;
  const char* url = "https://api.twitter.com/2/tweets";
  http.begin(url);

  String authHeader = crearEncabezadoOAuth(mensajeTweet);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", authHeader);


  String escapedTweet = mensajeTweet;
  escapedTweet.replace("\\", "\\\\"); 
  escapedTweet.replace("\"", "\\\"");
  escapedTweet.replace("\n", "\\n");

  String payload = "{\"text\":\"" + escapedTweet + "\"}";

  // Depuración
  Serial.println("Debug - OAuth Header: " + authHeader);
  Serial.println("Debug - Payload: " + payload);

  int httpResponseCode = http.POST(payload);
  String response = http.getString();

  Serial.println("Código de respuesta: " + String(httpResponseCode));
  Serial.println("Respuesta: " + response);

  http.end();
  return httpResponseCode == 201;
}

