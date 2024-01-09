void read1() {
    File dataFile;;
    dataFile=SD.open("/config/daynum.txt",FILE_READ);
    uint16_t daynum=0;
    while(dataFile.available()){
    String line = dataFile.readStringUntil('\n');
    daynum=line.toInt();
    }
    dataFile.close();
    String fileName="/"+(String)roll+"/"+"Days_Present"+".txt";
    tft.fillScreen(TFT_WHITE);
    tft.setCursor(40,10);
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLUE);
    tft.println("Days Attended: ");
  
    dataFile = SD.open(fileName,FILE_READ);
    String line = dataFile.readStringUntil('\n');
    dataFile.close();
    uint16_t att=line.toInt();
    tft.setCursor(240,10);
    tft.print(line);
    tft.setCursor(40,100);
    tft.print("in this semester");
    tft.setCursor(40,190);
    float percentage = (float)att / daynum * 100;
    tft.print(percentage,2);
    tft.print(" %    Attendance");
    delay(2500);
}