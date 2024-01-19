void pending(){
  File dataFile;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  String date = String(timeinfo.tm_mday)+"/"+String(1+timeinfo.tm_mon)+"/"+String(1900+timeinfo.tm_year)+",";
     dataFile=SD.open("/config/delta.txt",FILE_READ);
   uint16_t delta=0;
   while(dataFile.available()){
    String line = dataFile.readStringUntil('\n');
    delta=line.toInt();
   }
   dataFile.close();
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
  if(SD.exists("/config/last_date.txt")){
    File newFile=SD.open("/config/last_date.txt",FILE_READ);
    String ldt="";
    while(newFile.available()){
    ldt=newFile.readStringUntil('\n');
    }
    date=date.substring(0,date.length()-1);
     Serial.print(ldt);
    Serial.print(",");
    Serial.print(date);
    if(ldt!=date){
      delta++;
    }
  }else{
    delta++;
  }
  dataFile.print(roll);
  dataFile.print(",");
  dataFile.close();
  }else{
  dataFile = SD.open(fileName,FILE_APPEND);
  dataFile.print(roll);
  dataFile.print(",");
  dataFile.close();  
  }
  SD.remove("/config/delta.txt");
  dataFile=SD.open("/config/delta.txt",FILE_APPEND);
  dataFile.print(delta);
  dataFile.close();
}