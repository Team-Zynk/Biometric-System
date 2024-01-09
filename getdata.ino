String getdata(uint16_t x){       //pick out data from stdinfo file saved on SD for an id number 
  String fileName=String("/config/")+String("stdinfo")+String(".txt");
  String ans="";
  if(SD.exists(fileName)){
    int d = 0;
    File dataFile;
    dataFile = SD.open(fileName,FILE_READ);
    while (dataFile.available()) {
      String line = dataFile.readStringUntil('\n');
      d++; 
      if(d==x){
        ans= line;
        break;
      }
    }
    dataFile.close();
    return ans;
    }else{
      return "";
    }
}