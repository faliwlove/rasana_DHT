void signal_strength(int x){
  if (abs(x) >= 20 && abs(x) <= 43){
      lcd.write(1);
    }
    else if (abs(x) >= 43 && abs(x) <= 67){
      lcd.write(2);
    }
    else if (abs(x) >= 67 && abs(x) <= 70){
      lcd.write(3);
    }
   else if (abs(x) >= 70 && abs(x) <= 80){
      lcd.write(4);
    }
    else if (abs(x) >= 80 && abs(x) <= 100){
      lcd.write(5);
    }
}
