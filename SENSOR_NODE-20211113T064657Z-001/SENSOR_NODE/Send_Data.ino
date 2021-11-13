void send_data(){
  if (WiFi.status() == WL_CONNECTED){
    //  data = "&t=" + String(t) +"&h=" + String(h);
   data = "&t=";
   data += String(t);
   data += "&h=";
   data += String(h);
   data += "&rssi=";
   data += String(rssi);
   data += "&time=";
   data += lcd_time;

   http.begin(client,"http://192.168.4.1/indht2");
   http.addHeader("content-type","application/x-www-form-urlencoded");
   http.POST(data);
   Serial.println(http.getString());
   http.writeToStream(&Serial);
   http.end();
   Serial.println("Data Send = " + data); 
  }
  else{
  }
  //delay(1000);
}
