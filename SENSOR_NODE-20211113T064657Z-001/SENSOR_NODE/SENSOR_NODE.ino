  /* eFarming Datalogger V.1
   * Temperature and Humidity
   * Updated : 7:27 Saturday, 07/09/2019
   * This is Sensor Node
   * Fikri Achmad
  */

/* ALGORITMA :
 *  1. Inisiasi library DHT, SD Card, RTC, dan WiFi
 *  2. Deklarasi variabel temperature, humidity, dan jam
 *  3. Memulai main program yang terdiri dari koneksi wifi, memulai sensor(DHT)
 *     mensetting RTC, dan memulai SD Card module
 *  4. Pembacaan sensor, pengiriman data hasil pembacaan ke sink node, dan  
 *     penulisan data ke SD Card
 */

//=========================================DHT=============================================
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

//====================================ESP8266 WIFI=========================================
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "THS0819_SINK_NODE";       // Nama SSID AP/Hotspot
const char* password = "11111111";       // Password Wifi
String host = "http://192.168.4.1/indht2";

//IPAddress ip (10, 10, 10, 32);
//IPAddress gateway (10, 10, 10, 1);
//IPAddress subnet (255, 255, 255, 0);

WiFiClient client;
HTTPClient http;

//====================================RTC DS3231===========================================
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

String clock_time, clock_day, clock_date, clock_now, lcd_time;
String rtc_hour, rtc_minute, rtc_second, rtc_day, rtc_date, rtc_month, rtc_year;  
  
//==================================Inisiasi library SD Card Module===============================
#include <SPI.h>
#include <SD.h>

#define chipSelect 16

//=========================================Variabel Program========================================
String data;
float t, h;
long rssi;
int i = 0;
int x = 0;
//===========================SETUP==================================
void setup(){
  Serial.begin(9600);
  wifi_setup();   //Memulai setup WiFi
  dht.begin();    //Menginisiasi Sensor DHT
  rtc_setup();    //Menginisiasi RTC
  sd_setup();     //Menginisiasi SD Card Module
}
//===========================Program Utama============================
void loop(){
  delay(1000);
//Membaca data waktu di RTC
  time_RTC();         

//Membaca data sensor DHT
  t = dht.readTemperature();
  h = dht.readHumidity();
  x = 0;
//Membaca Kekuatan sinyal Sink Node
  rssi = WiFi.RSSI(); 
//Mengirimkan data ke sink node
  send_data();        
//Menulis data ke SD Card
  sd_write();         
}
