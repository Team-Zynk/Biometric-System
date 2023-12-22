int read3(int y){
  int d = 0;
  int m=1;
  while(m<13){
    String fileName = "/"+ String(y) + String(m) + ".txt";
    if(SD.exists(fileName)){
    File dataFile;
    dataFile = SD.open(fileName,FILE_READ);
    while (dataFile.available()) {
      String line = dataFile.readStringUntil('\n');
        int lineId = line.substring(0, line.indexOf(",")).toInt();
        if (lineId == roll) {
            d=d+1;
          }
    }
    dataFile.close();
    }
    m=m+1;
  }
  return d;
}