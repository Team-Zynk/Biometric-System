void write1(){

  pending();
  File dataFile;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  SD.mkdir("/"+(String)roll);
  String fileName="/"+(String)roll+"/"+"Dates Present"+".txt"; //Directory of Roll No. with file name as Dates Present


  String present_date = String(timeinfo.tm_mday) + "/"+String(1900+timeinfo.tm_year)+"/" + String(1+timeinfo.tm_mon) + ".txt";
  dataFile=SD.open(fileName,FILE_APPEND);
  dataFile.println(present_date);
  dataFile.close();
  fileName="/"+(String)roll+"/"+"Days Present"+".txt"; //Directory of Roll No. with file name as Days Present
  dataFile = SD.open(fileName,FILE_READ);
  String line = dataFile.readStringUntil('\n');
  int present_days= line.toInt();
  present_days+=1;
  dataFile.close();
  SD.remove(fileName);
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
