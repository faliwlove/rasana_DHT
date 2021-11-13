/* eFarming Datalogger V.1
 * Temperature And Humidity
 * Updated : 7:26, Saturday, 07/09/2019
 * This is Sink Node
*/

/* ALGORITMA :
 *  1. Inisiasi lilbrary LCD, WiFi, dan Adafruit IO Server
 *  2. Deklarasi variabel clientID, input temperature, dan
 *     humidity
 *  3. Mengkonfigurasikan WiFi, Server, dan LCD  
 *  4. Memulai program utama, yaitu menghadle data yang diterima,
 *     menampilkan data di LCD dan Web Lokal, dan mengirim data 
 *     ke Adafruit IO
 */

//=====================================LCD I2C============================================
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x3F, 20, 4);

//Indikator ujung kiri
byte customChar0[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
//signal bar 5(full)
byte customChar1[] = {
  B00000,
  B00000,
  B00000,
  B00001,
  B00011,
  B00111,
  B01111,
  B11111
};
//signal bar 4
byte customChar2[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00010,
  B00110,
  B01110,
  B11110
};
//signal bar 3
byte customChar3[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01100,
  B11100
};
//signal bar 2
byte customChar4[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01000,
  B11000
};
//signal bar 1
byte customChar5[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000
};
//degree celcius
byte customChar6[] = {
  B11100,
  B10100,
  B11100,
  B00000,
  B00111,
  B00100,
  B00100,
  B00111
};
//arrow simbol
byte customChar7[] = {
  B00000,
  B01000,
  B00100,
  B11110,
  B11110,
  B00100,
  B01000,
  B00000
};

//====================================ESP8266 WIFI========================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

const char* ssid = "EduFarm RR#1";
const char* password = "rasana#1";

const char* APssid = "THS0819_SINK_NODE";
const char* APpassword = "11111111";

//IPAddress ip (10, 10, 10, 1);
//IPAddress gateway (10, 10, 10, 1);
//IPAddress subnet (255, 255, 255, 0);

ESP8266WebServer server(80);
WiFiClient client;

//===============================ADAFRUIT IO LIBRARY======================================
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
//================================VARIABLE ADAFRUIT IO====================================

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "fikriabachtiar"
#define AIO_KEY         "ddd777b147ea43f18286f57ceebd2a77"
//================================OBJECT ADAFRUIT IO======================================
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Setup feeds for temperature & humidity
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");

Adafruit_MQTT_Publish temperature2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature_2");
Adafruit_MQTT_Publish humidity2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity_2");

//======================================VARIABLE==========================================
String t, h, t2, h2, time1, time2;
int rssi, rssi2;
int i = 0, z = 0, x = 1;
float temp_1, hum_1, temp_2, hum_2;
String serverIndeks;

void setup() {
  Serial.begin(9600);
  lcd_setting();  //Menginisiasi lcd
  wifi_setting(); //Menginisiasi pengaturan WiFi

  //Cek kondisi wifi
  if (WiFi.status() ==   WL_CONNECTED){
    lcd.clear();
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    lcd.home();
    lcd.write(0);
    lcd.setCursor(0, 2);
    lcd.print("Connected");
  }
  else{
    lcd.clear();
    Serial.println("");
    Serial.print("Not Connected");
    lcd.setCursor(0, 2);
    lcd.print("Not Connected");
  }

  //Display awal
  lcd.setCursor(1, 0);
  lcd.print(" Monitoring System");
  lcd.setCursor(0, 1);
  lcd.print(" of Smart eFarming");
  lcd.setCursor(19, 3);
  lcd.write(1);
  Serial.println(WiFi.localIP());
  Serial.println(long(WiFi.RSSI()));
  
  lcd.setCursor(0, 3);
  lcd.print(WiFi.softAPIP());

  //Memulai server
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  server_setting();
}

void loop() {
  server.handleClient();  //menghandle client yang ada
  htmlPart();             //pengaturan web lokal

  //cek kondisi wifi
  if (WiFi.status() ==   WL_CONNECTED){
    lcd.clear();
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    lcd.home();
    lcd.write(0);
    lcd.setCursor(0, 2);
    lcd.print("             ");
    lcd.setCursor(0, 2);
    lcd.print("Connected");
    lcd.setCursor(13, 2);
    lcd.print("       ");
    lcd.setCursor(19, 3);
    signal_strength(WiFi.RSSI());
  }
  else{
    lcd.clear();
    Serial.println("");
    Serial.print("Not Connected");
    lcd.setCursor(0, 2);
    lcd.print("             ");
    lcd.setCursor(0, 2);
    lcd.print("Not Connected");
  }

  //slide1
  lcd.setCursor(1, 0);
  lcd.print(" Monitoring System");
  lcd.setCursor(0, 1);
  lcd.print(" of Smart eFarming");
  lcd.setCursor(0, 3);
  lcd.print(WiFi.localIP());
 
  delay(1000);   


  //slide2
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Dalam GreenHouse");

  lcd.setCursor(0, 1);
  lcd.print("Temperature : ");
  lcd.print(t);
  lcd.write(6);
  lcd.setCursor(0, 2);
  lcd.print("Humidity    : ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(19, 3);
  signal_strength(rssi);
  
  lcd.setCursor(0, 3);
  lcd.print("Time");
  lcd.write(7);
  lcd.print(time1);
  delay(1000);


  //slide3
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Luar  GreenHouse");

  lcd.setCursor(0, 1);
  lcd.print("Temperature : ");
  lcd.print(t2);
  lcd.write(6);
  lcd.setCursor(0, 2);
  lcd.print("Humidity    : ");
  lcd.print(h2);
  lcd.print("%");
  lcd.setCursor(19, 3);
  signal_strength(rssi2);
  
  lcd.setCursor(0, 3);
  lcd.print("Time");
  lcd.write(7);
  lcd.print(time2);
  delay(500);

  //kirim data ke server adafruit io
  if(z < 2000){
    MQTT_connect();
   if (x==1) temperature.publish(temp_1);
   else if (x==2) humidity.publish(hum_1);
   else if (x==3) temperature2.publish(temp_2);
   else if (x==4) humidity2.publish(hum_2);
   x++;
   if (x==5)x=1;
   z=1;
  }
  delay(1);
  z++;
}
