void write1(){

 
  File dataFile;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  SD.mkdir("/"+(String)roll);
  String fileName="/"+(String)roll+"/"+"Dates_Present"+".txt"; //Directory of Roll No. with file name as Dates Present
  String present_date = String(timeinfo.tm_mday) + "/"+String(1900+timeinfo.tm_year)+"/" + String(1+timeinfo.tm_mon);
  String last_date="/"+(String)roll+"/"+"Last_Date"+".txt";
  dataFile = SD.open(last_date,FILE_READ);
  String line = dataFile.readStringUntil('\n');
  line=line.substring(0,line.length()-1);
  dataFile.close();
  Serial.print(line);
  Serial.print(",");
  Serial.print(present_date);
  Serial.print(",");

  if(line==present_date)
  {tft.setCursor(40,160);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(3);
  tft.println("Already Marked");
  delay(1000);
  tft.fillScreen(TFT_WHITE);
  read1();
  return;
  }
  else
  { SD.remove(last_date);
  dataFile=SD.open(last_date,FILE_APPEND);
  dataFile.println(present_date);
  dataFile.close();
  }
  
  pending();
  dataFile=SD.open(fileName,FILE_APPEND);
  dataFile.println(present_date);
  dataFile.close();
  fileName="/"+(String)roll+"/"+"Days_Present"+".txt"; //Directory of Roll No. with file name as Days Present
  dataFile = SD.open(fileName,FILE_READ);
  line = dataFile.readStringUntil('\n');
  int present_days= line.toInt();
  present_days+=1;
  dataFile.close();
  SD.remove(fileName);
  dataFile=SD.open(fileName,FILE_APPEND);
  dataFile.println(present_days);
  dataFile.close();
  tft.setCursor(40,160);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(3);
  tft.println("Attendance Marked");
  delay(1000);
  tft.fillScreen(TFT_WHITE);
  read1();
    }
