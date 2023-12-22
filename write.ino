void write1(){
  File dataFile;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  String fileName = "/"+String(1900+timeinfo.tm_year) + String(1+timeinfo.tm_mon) + ".txt";
  int flag=0;
  int y = timeinfo.tm_mday;
  dataFile = SD.open(fileName,FILE_READ);
    while (dataFile.available()) {
      String line = dataFile.readStringUntil('\n');
        int lineId = line.substring(0, line.indexOf(",")).toInt();
        int lId = line.substring(line.indexOf(",")+1).toInt();
        if (lineId == roll && lId==y) {
            tft.setCursor(40,160);
            tft.setTextSize(2);
            tft.setTextColor(TFT_BLUE);
            tft.print("Already Marked");
            delay(500);
            flag=1;
            break;
          }
    }
  dataFile.close();
    if(flag==0){
  dataFile=SD.open(fileName,FILE_APPEND);
  dataFile.print(roll);
  dataFile.print(",");
  dataFile.print(y);
  dataFile.println();
  dataFile.close();
  pending();
  tft.setCursor(40,160);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(3);
  tft.println("Attendance Marked");
  delay(1000);
  tft.fillScreen(TFT_WHITE);
  read1();
    }
}