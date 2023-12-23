int read1() {
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    String fileName="/"+(String)roll+"/"+"Days Present"+".txt";
    tft.fillScreen(TFT_WHITE);
    tft.setCursor(40,10);
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLUE);
    tft.println("Days Attended: ");
    File dataFile;
    dataFile = SD.open(fileName,FILE_READ);
    String line = dataFile.readStringUntil('\n');
    int d= line.toInt();
    tft.setCursor(240,10);
    tft.print(d);
    tft.setCursor(40,100);
    tft.print("in ");
    tft.print(&timeinfo,"%B");
    delay(2500);
    dataFile.close();
    return d;

}