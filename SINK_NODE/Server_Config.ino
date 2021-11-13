void server_setting(){
  server.on("/indht1", dht1);
  server.on("/indht2", dht2);
  server.on("/", []() {
    //command1=server.arg("command1");
    server.send(200, "text/html", serverIndeks );
  });
  server.begin();
}

void dht1(){
  t = server.arg("t");
  h = server.arg("h");
  rssi = (server.arg("rssi")).toInt();
  time1 = server.arg("time");
  server.send(200, "text/plan", "SUCCESS");
  temp_1 = t.toFloat();
  hum_1 = h.toFloat();
}
void dht2(){
  t2 = server.arg("t");
  h2 = server.arg("h");
  rssi2 = (server.arg("rssi")).toInt();
  time2 = server.arg("time");
  server.send(200, "text/plan", "SUCCESS");
  temp_2 = t2.toFloat();
  hum_2 = h2.toFloat();
}

void MQTT_connect() {
  int8_t ret;
  i = 0;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((i < 2) && (mqtt.connect() != 0)) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 1 seconds...");
       mqtt.disconnect();
       delay(500);  // wait 5 seconds
//       if (retries == 0) {
//         // basically die and wait for WDT to reset me
//         while (1);
//       }
      i++;
  }
  Serial.println("MQTT Connected!");
}
