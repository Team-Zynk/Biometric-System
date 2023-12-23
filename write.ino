void write1(){

  pending();
  File dataFile;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  Sd.mkdir((String)roll);
  String fileName="/"+(String)roll+"/"+"Dates Present"+".txt"; //Directory of Roll No. with file name as Dates Present


  String present_date = String(timeinfo.tm_mday) + "/"+String(1900+timeinfo.tm_year)+"/" + String(1+timeinfo.tm_mon) + ".txt";
  dataFile=SD.open(fileName,FILE_APPEND);
  dataFile.println(present_date);
  dataFile.close();
  
  tft.setCursor(40,160);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(3);
  tft.println("Attendance Marked");
  delay(1000);
  tft.fillScreen(TFT_WHITE);
  read1();
    }
