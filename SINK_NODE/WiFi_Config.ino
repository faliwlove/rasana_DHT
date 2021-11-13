void wifi_setting(){
  WiFi.mode(WIFI_AP_STA);
  Serial.println("Disconnect from any other modes");
  WiFi.disconnect();
  WiFi.softAP(APssid, APpassword, 1, false, 6); 
//  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 2);
  lcd.print("Connecting");
  while ((WiFi.status() != WL_CONNECTED) && (i < 10)) {
    delay(500);   
    lcd.print(".");
    Serial.print(".");
    lcd.home();
    lcd.print(" ");
    lcd.setCursor(0, 3);
    lcd.print("               ");
    i++;
  }
}
