#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
DHT dht(DHTPIN, DHTTYPE);
int M,sensor_analog;
const int sensor_pin = 34;

const char* ssid ="V2026";
const char* password ="ahmad2007";
#define CHAT_ID "6251237270"
#define BOTtoken "6707317096:AAEFy07nxDOEf4eHJHIREpp4V4Bq3mPK2sM"

WiFiClientSecure Client;
UniversalTelegramBot bot(BOTtoken, Client);
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.print("Conecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Tunggu dulu...monitoring akan segera dimulai", "");

  delay(2000);
  Serial.print("Workshop monitoring tanaman smk7 baleendah\n");
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_analog = analogRead(sensor_pin);
  M = (100 - ((sensor_analog/4095.00) * 100));
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if(isnan(h) || isnan(t) || isnan(M)) {
     Serial.println("Sensor tidak terbaca");
    return;
  }
  Serial.print("==monitoring tanaman\n");
  Serial.print("Humaditas udara: ");
  Serial.print(h);
  Serial.print(" %");
  Serial.print("Temperatur lingkungan: ");
  Serial.print(t);
  Serial.println(" C");
  Serial.print("Kelembapan air tahan: ");
  Serial.print(M);
  Serial.print(" %");
  bot.sendMessage(CHAT_ID, "Monitoring tanaman SMKN7 Baleendah");
  KirimPesanTelegram(h, t, M);
  delay(2000);
}
void KirimPesanTelegram(float h, float t, int M) {
  String pesan = "Suhu saat ini: " + String(t, 2) + " C\n" +
  "Humiditas udara saat ini: " + String(h, 2) + " %\n" +
  "Tingkat kelembapan tanah saat ini: " + String(M) + " %\n";

  if (bot.sendMessage(CHAT_ID, pesan, "Markdown")) {
    Serial.println("Pesan berhasil dikirim");
  } else {
    Serial.println("Gagal mengirim pesan");
  }
  delay(1000); 
}














