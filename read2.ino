int read2(int m, int y) {

  String fileName = "/"+String(y) + String(m) + ".txt";
   
    if(SD.exists(fileName)){
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
    dataFile.close();
    return d;
    }
}