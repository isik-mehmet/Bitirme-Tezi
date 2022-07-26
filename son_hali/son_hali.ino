#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <dht11.h> // dht11 kütüphanesini kodlarımıza dahil ediyoruz.
int DhtPin=D4; // DhtPin olarak Dijital 2'yi belirliyoruz.
dht11 dht_sensor; // dht_sensor adında bir DHT11 nesnesi oluşturduk.
//*****************************************
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
//******************************************
const char *ssid     = "mehmet";
const char *password = "isikmehmet";
const char* host = "maker.ifttt.com";
const long utcOffsetInSeconds = 10800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "tr.pool.ntp.org", utcOffsetInSeconds);
int buzzer = D5;
int ld1 = D6;
int ld2 = D7;
int ld3 = D8;
void setup(){
  Serial.begin(115200);
  Serial.println("Email from Node Mcu");
  delay(100);
  lcd.begin();
  lcd.backlight(); 
  lcd.print("Berk");
  lcd.setCursor(6, 1);
  lcd.print("Kişmir");
  //*********************
   pinMode(buzzer,OUTPUT);
   pinMode(ld1,OUTPUT);
   pinMode(ld2,OUTPUT);
   pinMode(ld3,OUTPUT);
  //********************* 

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
}
//*************************
int alarm = 7;
int ilac_1 = 7;
int ilac_2 = 7;
int ilac_3 = 7;
//************************

void loop() {
   // ***********************************
  int chk = dht_sensor.read(DhtPin);
  int temp = dht_sensor.temperature;
  int hum = dht_sensor.humidity;
  Serial.print("Nem Orani (%): ");
  Serial.println(hum);
  Serial.print("Sicaklik (Celcius): ");
  Serial.println(temp);
 // *************************************

  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  int saat =timeClient.getHours();
  Serial.print(saat);
  Serial.print(":");
  int dakka=timeClient.getMinutes();
  Serial.print(dakka);
  Serial.print(":");
  int saniye=timeClient.getSeconds();
  Serial.println(saniye);
  lcd.begin();
  lcd.print("time:");
  lcd.setCursor(6, 0);
  lcd.print(saat);
  lcd.print(":");
  lcd.print(dakka);
  lcd.print(":");
  lcd.print(saniye);
  lcd.setCursor(0, 1);
  lcd.print("temp:");
  lcd.setCursor(5, 1);
  lcd.print(temp);
  lcd.setCursor(8, 1);
  lcd.print("hum:");
  lcd.print(hum);
 // ***********************************
 if( alarm < 7 ){
  tone(buzzer,300);
  alarm++;
 }
 else{
  noTone(buzzer);
 }
 if(ilac_1 < 7){
  digitalWrite(ld1,HIGH);
  ilac_1 ++; 
 }
 else{
  digitalWrite(ld1,LOW); 
 }
 if(ilac_2 < 7){
  digitalWrite(ld2,HIGH);
  ilac_2 ++; 
 }
 else{
  digitalWrite(ld2,LOW); 
 }
 if(ilac_3 < 7){
  digitalWrite(ld3,HIGH);
  ilac_3 ++; 
 }
 else{
  digitalWrite(ld3,LOW); 
 }
 //************************************
  if(dakka == 10 && saniye == 0 || saniye == 1){
    alarm = 0;
    ilac_1 = 0;
    WiFiClient client;
    const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
     String url = "/trigger/ilac_hatirlatici_1/with/key/etF88yMhhH_qkSh6Q_4VG_9x6xoh3btD3keYZ3hWmLG";
      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
}   
// ****************************************
  if(dakka == 11 && saniye == 0 || saniye == 1){
    alarm = 0;
    ilac_2 = 0;
    WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
     String url = "/trigger/ilac_hatirlatici_2/with/key/etF88yMhhH_qkSh6Q_4VG_9x6xoh3btD3keYZ3hWmLG";
      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
} 
// ****************************************
  if(dakka == 12 && saniye == 0 || saniye == 1){
    alarm = 0;
    ilac_3 = 0;
    WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
     String url = "/trigger/ilac_hatirlatici_3/with/key/etF88yMhhH_qkSh6Q_4VG_9x6xoh3btD3keYZ3hWmLG";
      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
}    
 
  delay(1000);
}
