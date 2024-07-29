#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi ayarları
const char* ssid = "*************";         // WiFi ağ adınız
const char* password = "************"; // WiFi ağ şifreniz

const int mq2Pin = A0; // MQ2 sensörünün bağlı olduğu analog pin
const int greenLedPin = D1; // Yeşil LED pini
const int yellowLedPin = D2; // Sarı LED pini
const int redLedPin = D3; // Kırmızı LED pini
const int buzzerPin = D5; // Buzzer pini

// LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(D6, D7, D1, D2, D3, D4); // LCD'nin pinlerini tanımla

ESP8266WebServer server(80); // Web sunucusu için port numarası

void setup() {
  Serial.begin(115200); // Seri haberleşmeyi başlat
  pinMode(mq2Pin, INPUT); // MQ2 pinini giriş olarak ayarla
  pinMode(greenLedPin, OUTPUT); // Yeşil LED pini çıkış olarak ayarla
  pinMode(yellowLedPin, OUTPUT); // Sarı LED pini çıkış olarak ayarla
  pinMode(redLedPin, OUTPUT); // Kırmızı LED pini çıkış olarak ayarla
  pinMode(buzzerPin, OUTPUT); // Buzzer pini çıkış olarak ayarla
  
  lcd.begin(16, 2); // LCD'yi başlat (16 sütun, 2 satır)
  lcd.print("Gas Level:"); // İlk mesajı yazdır

  // WiFi bağlantısını başlat
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // IP adresini yazdır

  // Web sunucusu yapılandırması
  server.on("/", handleRoot); // Ana sayfa isteği için
  server.begin(); // Web sunucusunu başlat
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // İstemcileri işle
  
  int sensorValue = analogRead(mq2Pin); // MQ2 sensöründen analog değeri oku
  Serial.print("Gaz Algılandı: ");
  Serial.println(sensorValue); // Algılanan gaz değerini seri monitöre yazdır
  
  // LCD'de gaz seviyesini güncelle
  lcd.setCursor(0, 1);
  lcd.print("                "); // Satırı temizle
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);

  // Tüm LED'leri ve buzzeri kapat
  digitalWrite(greenLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);

  // Gaz seviyesine göre LED'leri ve buzzeri kontrol et
  if (sensorValue < 650) {
    digitalWrite(greenLedPin, HIGH); // Düşük gaz seviyesi
  } else if (sensorValue >= 650 && sensorValue < 1000) {
    digitalWrite(yellowLedPin, HIGH); // Orta gaz seviyesi
  } else {
    digitalWrite(redLedPin, HIGH); // Yüksek gaz seviyesi
    delay(1000);
    digitalWrite(buzzerPin, HIGH); // Buzzer'ı çalıştır
    Serial.println("Uyarı: Yüksek gaz seviyesi! (Very Polluted Air)");
  }

  delay(1000); // 1 saniye bekle
}

// Web sunucusu ana sayfa isteğini işleyin
void handleRoot() {
  int sensorValue = analogRead(mq2Pin); // MQ2 sensöründen analog değeri oku
  String airQuality;
  String color;

  if (sensorValue < 650) {
    airQuality = "Temiz Hava (Clean Air)";
    color = "green"; // Yeşil renk
  } else if (sensorValue >= 650 && sensorValue < 1000) {
    airQuality = "Kirli Hava (Polluted air)";
    color = "yellow"; // Sarı renk
  } else {
    airQuality = "Cok Kirli Hava (Very Polluted Air)";
    color = "red"; // Kırmızı renk
  }

  String html = "<html><head><title>Gaz Algilama Sistemi (Gas Detection System) </title>";
  html += "<meta http-equiv=\"refresh\" content=\"2\">"; // Sayfanın her 2 saniyede yenilenmesi için meta etiketi
  html += "<style>";
  html += "body { background-color: gray; color: white; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }"; // Arka plan lacivert, yazılar beyaz, ortalama
  html += "h2 { color: white; }"; // Tüm h2 etiketleri beyaz
  html += "</style>";
  html += "</head><body>";
  html += "<div>";
  html += "<h1>Gaz Algilama Sistemi (Gas Detection System) </h1>";
  html += "<h2>Gaz Seviyesi (Gas Level): " + String(sensorValue) + "</h2>";
  html += "<h2 style='color:" + color + "'>Hava Kalitesi (Air Quality): " + airQuality + "</h2>";
  html += "</div>";
  html += "<h2>Enes Merdud</h2>";
  html += "</body></html>";
  server.send(200, "text/html", html); // HTML sayfasını gönder
}