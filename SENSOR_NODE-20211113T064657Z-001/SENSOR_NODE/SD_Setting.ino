void sd_setup(){
  if (SD.begin(chipSelect))
  {
    //Serial.println("SD card is ready to use.");
  } else
  {
    //Serial.println("SD card initialization failed");
    return;
  }
}

void sd_write(){ 
  String dataFull;
  dataFull = clock_now + "," + String(t) +"," + String(h);
  
        File dataFile = SD.open("THS0819(OUT)_Datalogger.txt", FILE_WRITE);
        if (dataFile) {
          dataFile.println(dataFull);
          dataFile.close();
          // print to the serial port too:
          Serial.println(dataFull);
        }
          // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening THS0819(OUT)_Datalogger.txt");
        }
}
