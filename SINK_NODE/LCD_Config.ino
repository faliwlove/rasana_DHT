void lcd_setting(){
  lcd.begin();
  lcd.clear();
  lcd.createChar(0, customChar0);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.createChar(6, customChar6);
  lcd.createChar(7, customChar7);
  lcd.home();
  lcd.print(" ");
  lcd.print(" Monitoring System");
  lcd.setCursor(0, 1);
  lcd.print(" of Smart eFarming");
  lcd.setCursor(19, 3);
  lcd.write(1);
}
