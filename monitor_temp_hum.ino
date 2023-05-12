#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 12  
#define DHTTYPE DHT22
#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4
#define sensor1 26
#define sensor2 25
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Wokwi-GUEST";
const char* password = "";
String serverName = "https://api.thingspeak.com/update?api_key=X6FFT3YFJHSE23PS";

WiFiClient client;

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

void setup() {
  Serial.begin(115200);
  
  dht.begin();
  pinMode(sensor1, OUTPUT);
  pinMode(sensor2, OUTPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando na rede WiFi...");
  }
  Serial.println("Conectado!");
  
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Temp.: 0" + String(char(223)) + "C");
  lcd.setCursor(0, 1);
  lcd.print("Umidade: 0%");
  lcd.setCursor(0,3);
  lcd.print("LED 1 [ ]  LED 2 [ ]");

}

void loop() {
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  HTTPClient http;

  String serverPath = serverName + "&field1=" + String(temp) + "&field2=" + String(hum);

  http.begin(serverPath.c_str());
  
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Leitura não identificada!");
    return;
  }
  
  Serial.print("Umidade: ");
  Serial.print(hum);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println("°C");
  
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    Serial.println("Dados enviados com sucesso!");
  } else {
    Serial.print("Erro ao enviar dados. Código de resposta: ");
    Serial.println(httpResponseCode);
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(temp) + String(char(223)) + "C ");
  lcd.setCursor(0, 1);
  lcd.print("Umidade: " + String(hum) + "%   ");

  if (temp > 35 && hum > 70) {
    lcd.setCursor(0,3);
    lcd.print("LED 1 [*]  LED 2 [*]");
    digitalWrite(sensor1, HIGH);
    digitalWrite(sensor2, HIGH);
  } else if (hum > 70) {
      lcd.setCursor(0,3);
      lcd.print("LED 1 [ ]  LED 2 [*]");
      digitalWrite(sensor1, LOW);
      digitalWrite(sensor2, HIGH);
  } else if (temp > 35) {
      lcd.setCursor(0,3);
      lcd.print("LED 1 [*]  LED 2 [ ]");
      digitalWrite(sensor1, HIGH);
      digitalWrite(sensor2, LOW);
  } else {
    lcd.setCursor(0,3);
    lcd.print("LED 1 [ ]  LED 2 [ ]");
    digitalWrite(sensor1, LOW);
    digitalWrite(sensor2, LOW);
  }
  delay(5000);
}
