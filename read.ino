int read1() {
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    String fileName = "/"+String(1900+timeinfo.tm_year) + String(1+timeinfo.tm_mon) + ".txt";
    tft.fillScreen(TFT_WHITE);
    tft.setCursor(40,10);
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLUE);
    tft.println("Days Attended: ");
    int d = 0;
    File dataFile;
    dataFile = SD.open(fileName,FILE_READ);
    while (dataFile.available()) {
      String line = dataFile.readStringUntil('\n');
        int lineId = line.substring(0, line.indexOf(",")).toInt();
        if (lineId == roll) {
            d=d+1;
          }
    }
    tft.setCursor(240,10);
    tft.print(d);
    tft.setCursor(40,100);
    tft.print("in ");
    tft.print(&timeinfo,"%B");
    delay(2500);
    dataFile.close();
    return d;
}