void pending(){
  File dataFile;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  String date = String(timeinfo.tm_mday)+"/"+String(1+timeinfo.tm_mon)+"/"+String(1900+timeinfo.tm_year)+",";
  
  String fileName="/config/"+String("pending")+".txt";
  bool m=SD.exists(fileName);
  dataFile = SD.open(fileName,FILE_READ);
  bool f=false;
  while (dataFile.available()) {  
      String line = dataFile.readStringUntil('\n');
      line=line.substring(0,line.indexOf(",")+1);
      Serial.print(line);
      if(line==date){
        f=true;
        break;
      }
  }
  dataFile.close();
  if(!f){
  dataFile = SD.open(fileName,FILE_APPEND);
  if(m){
  dataFile.println();
  }
  dataFile.print(date);
  dataFile.print(roll);
  dataFile.print(",");
  dataFile.close();
  }else{
  dataFile = SD.open(fileName,FILE_APPEND);
  dataFile.print(roll);
  dataFile.print(",");
  dataFile.close();  
  }
}