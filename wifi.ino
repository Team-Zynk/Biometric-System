bool wifi()
{  String uid,name,password ;
   String fileName="/WIFI_WPA2_Enterprise.txt"
   File dataFile;
   dataFile = SD.open(fileName,FILE_READ);
while (dataFile.available())
{   
   
     uid = dataFile.readStringUntil('\n');
     name = dataFile.readStringUntil('\n');
    password = dataFile.readStringUntil('\n');
  WiFi.begin(uid, WPA2_AUTH_PEAP,"", name,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      break;
    }
  }
  if(WiFi.status() == WL_CONNECTED)
   return true;
}

fileName="/WIFI.txt";
  dataFile = SD.open(fileName,FILE_READ);
while (dataFile.available())
{   
   
     uid = dataFile.readStringUntil('\n');
    password = dataFile.readStringUntil('\n');
    WiFi.begin(uid,password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      break;
    }
  }
  if(WiFi.status() == WL_CONNECTED)
   return true;
}
return false ;

}