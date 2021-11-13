void wifi_setup(){
  ESP.eraseConfig();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
//  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  
  while ((i < 10) && (WiFi.status() != WL_CONNECTED)){
    delay(500);
    Serial.print(".");
    i++;
  }
  
  if (WiFi.status() == WL_CONNECTED){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.println(WiFi.localIP());
  }
  else{
    Serial.println("Not Connected, Data Only Save To SD Card");
  }
}
