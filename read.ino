void read1() {
    
    File dataFile;
    dataFile=SD.open("/config/daynum.txt",FILE_READ);
    uint16_t daynum=0;
    while(dataFile.available()){
    String line = dataFile.readStringUntil('\n');
    daynum=line.toInt();
    }
    dataFile.close();
    dataFile=SD.open("/config/delta.txt",FILE_READ);
    uint16_t delta=0;
    while(dataFile.available()){
    String line = dataFile.readStringUntil('\n');
    delta=line.toInt();
    }
    daynum=daynum+delta;
    dataFile.close();
    
    String fileName="/"+(String)roll+"/"+"Days_Present"+".txt";
    tft.fillScreen(TFT_WHITE);
    printer("Attendance Report",0,10,3,480,TFT_BLUE);
    drawSdJpeg("/config/rplogo.jpg", 400, 6);
    
    
  
    dataFile = SD.open(fileName,FILE_READ);
    String line = dataFile.readStringUntil('\n');
    dataFile.close();
    uint16_t att=line.toInt();

    printer("No. of days Present: "+line,0,140,2,480,TFT_DARKGREEN);
   
    printer("No. of days Absent: ",0,180,2,480,TFT_RED);
   
    tft.print(String(daynum-att));

    printer("Total Classes: ",0,220,2,480,TFT_BLACK);
    tft.print(String(daynum));
    tft.setTextColor(TFT_DARKGREEN);
    tft.setCursor(120,260);
    float percentage = (float)att / daynum * 100;
    tft.print(percentage,2);
    tft.print(" %   Attendance");
    delay(2500);
}