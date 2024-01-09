bool wifi()
{ 
  String uid,name,password ;
   String fileName="/WIFI_WPA2_Enterprise.txt";
   File dataFile;
   WiFi.disconnect(true);
   WiFi.mode(WIFI_STA);
    int counter=0;
   if(SD.exists(fileName)){
   dataFile = SD.open(fileName,FILE_READ);
while (dataFile.available())
{   
   
     uid = dataFile.readStringUntil('\n');
     uid=uid.substring(0,uid.length()-1);
     name = dataFile.readStringUntil('\n');
     name=name.substring(0,name.length()-1);
    password = dataFile.readStringUntil('\n');
    WiFi.begin(uid.c_str(), WPA2_AUTH_PEAP,"", name.c_str(),password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      break;
    }
  }
  if(WiFi.status() == WL_CONNECTED){
   dataFile.close();
   Serial.println("Connected to wpa2");
   return true;
  }
  
}
  
   dataFile.close();
   }

fileName="/WIFI.txt";
 if(SD.exists(fileName)){
  dataFile = SD.open(fileName,FILE_READ);
  counter=0;
while (dataFile.available())
{   
   
     uid = dataFile.readStringUntil('\n');
     uid=uid.substring(0,uid.length()-1);
    password = dataFile.readStringUntil('\n');
    Serial.print(uid);
    Serial.print(",");
    Serial.print(password);
    WiFi.disconnect(true);
   WiFi.mode(WIFI_STA);
    WiFi.begin(uid.c_str(),password.c_str());
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      break;
    }
  }
  if(WiFi.status() == WL_CONNECTED){
    dataFile.close();
     return true;
  }
    
}

dataFile.close();
}
Serial.println(WiFi.status());
return false ;

}