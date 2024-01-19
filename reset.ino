void reset(){
  if(SD.exists("/config/on.txt")){
  tft.fillScreen(TFT_WHITE);
   printer("Please contact the admin",0,40,3,480,TFT_BLUE);
   printer("To confirm reset database",0,100,3,480,TFT_BLUE);
   printer("Place his finger",0,200,3,480,TFT_BLUE);
   printer("For authentication",0,260,3,480,TFT_BLUE);
   while(roll!=127){
      roll=getFingerprintID();
   } 
  }
  if(!confirmation("To erase all data")){return;}
  finger.emptyDatabase();
  deleteAllFiles();
  tft.fillScreen(TFT_WHITE);
  printer("Reset Successful",0,30,3,480,TFT_BLUE);
  printer("Please restart the device",0,90,3,480,TFT_BLUE);
  while(true){};
}

void deleteAllFiles()
{ File dataFile;
  for(int i=1;i<127;i++){
  dataFile = SD.open("/"+String(i)+"/");
  while (true){
    File next = dataFile.openNextFile();
    if (!next)
      break;
    next.close();
    SD.remove(next.name());
  }
  dataFile.close();
 }

     SD.remove("/config/pending.txt");
    SD.remove("/config/daynum.txt");
    SD.remove("/config/delta.txt");
    SD.remove("/config/last_date.txt");
    SD.remove("/config/strength.txt");
    SD.remove("/config/stdinfo.txt");
    SD.remove("/config/admin.txt");
    SD.remove("/config/on.txt");

    dataFile=SD.open("/config/delta.txt",FILE_APPEND);
      dataFile.print("0");
      dataFile.close();
    dataFile=SD.open("/config/daynum.txt",FILE_APPEND);
    dataFile.print("0");
    dataFile.close();
}