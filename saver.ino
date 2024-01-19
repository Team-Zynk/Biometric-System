void saver(){
   tft.fillScreen(TFT_WHITE);
   tft.setTextColor(TFT_BLUE);
   tft.setTextSize(3);
   tft.setCursor(40,10);
   File dataFile;
   dataFile=SD.open("/config/daynum.txt",FILE_READ);
   uint16_t daynum=0;
   while(dataFile.available()){
    String line = dataFile.readStringUntil('\n');
    daynum=line.toInt();
   }
   dataFile.close();
   dataFile=SD.open("/config/strength.txt",FILE_READ);
   uint16_t strength=0;
   while(dataFile.available()){
    String line = dataFile.readStringUntil('\n');
    strength=line.toInt();
   }
   dataFile.close();
   String fileName = "/config/"+String("pending") + ".txt"; 
   if(SD.exists(fileName)){
   printer("Connecting",0,228,3,480,TFT_BLUE);
   drawSdJpeg("/config/wlogo.jpg", 176, 50);
    
  //  WiFi.begin("Xiaomi 11T Pro","nahi pata");
  //  int counter =0;
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  //   counter++;
  //   if(counter>=60){ //after 30 seconds timeout - reset board
  //     break;
  //   }
  // }
  if(!wifi()){
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    tftreset();
    
    tft.setTextColor(TFT_BLUE);
    tft.setTextSize(3);
    tft.setCursor(40,10);
    tft.print("Could not connect");
    delay(700);
  }else{
    configTime(19800,0,"pool.ntp.org");
    bool m=true;
    GSheet.begin("firebase-adminsdk-qhwbj@attendance-system-397119.iam.gserviceaccount.com", "attendance-system-397119", "-----BEGIN PRIVATE KEY-----\nMIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQCv0J3gb4LCFMkX\nOVIH2haq9jPMgUV7I9EYUQsmyWJMvV/4yCOdSzxibX46UUv/nxDekjwnTla3bTZ2\n4C8gWbwIr5bbjjpWjXirDPF2/sf/+PTFgc3LSz27xmtfBCrgnuiHIMkPPdd1bxmF\nA10WCiXSziwGlRTshmqF7PsK33opnhZC0Gdm3NguPMPz81lAkoY0juJONqomiCpl\nu4u5Z+kWaNa4y6vN0PoOPy+un8Hcf4VywOBkIhbH2PCoXp2U9MmpV60OoCinJF+P\nVPL/tYEjEHnRTKB7B+wRAWRGf+CXGTe2nIGA2Fvf8TqUZg2K0+9iAGvCnDNOHWDr\nbx4gYxTjAgMBAAECggEABMxIKrJQWrSPglM9olo4ySSb6EZU25XwJF491CqlxJtc\nbaEkm6vMc5EyYywJy2mPX8uU2avBIRNZa6gVkSfxwjjsgIRioi8NLnnVcx5j3d/w\n6hzvPU+J2UCCeJ7X/rZHeTyTUBerdBh6lU8wsKPJQXX/7JQP9J58dLgxZ6wOnOkY\nXkKWuVZC4jYFMugzsF9Dq686eSXQ9jby/Y2p3p3FjUuZUp761Xuq89eOX0099kKe\ntGosgbF5GMpGrT+WeCFWqo3Mmv/crjgdfO+H82s50ISbOY6/zWvlZwNERqdlOFb9\nU0uGddgGUDaLw8Zgmc8njfcS+22nsAhE5Bf0rsCJ0QKBgQDwK6wB2lec4NO6kbvy\n4tbQRodlrQvxEJuYsZiK8pfg0KYOqarhol+RQGg85+bjFrpsmyFLgbwceqTqyn5l\nEipyvCMRpwhFGdkXuHnmk7VXGRjsX8kv/rrIgex0tJtywtw4QP/LPce4lxTuiUVK\nnS+om+YVBZ1zEHaxX4tjJKJ1cwKBgQC7ZxcWVVfltenxtHZwFr5+5qwSS/WIMzVT\nJw2vyvGAkb6vaHlBMXRaWImyBvljGiMkkxQI2BhtfSwVZL6NbmvBXTcEfu3jZayn\nzh8gUzZzgTYRiP3XYFx60FPyOrKQXOdg5RDCYDIJqjaw6K7p+lglsS++zFzYww+L\nWj45jt2G0QKBgQCokg6N0mGyM7+IcOeZaAvcbdR00gvSrJR5jRWDWRiu6+PR4NaW\nvjATtEA1l5NgCsDYn92zsKCG4LJGNdCXQjPXCiQXLMTKM4VDd/DfnQcn1e6/Yc/F\nRyZ0u3RqyaVd3FVTipO/ZGJ9NlWzw1eGMmOUFbBdSu6jJ4gXoPclpD3+7wKBgCh0\nCXzNsWqpyTVe0k5B6p80JiLQ+NCM1U782CyBb35kd7gfokUbatVx1U9zx/PHmZx0\nj1eVZjiEU7bOh3+6PVKBT7YNvEZhFVMn4Ho23EM0ujowyzLp3yy3uddJKnCVTXES\nIXsEDukdMC8iG1fwrYR9aiQSs1wrRzi6o0IDf/hxAoGBAJcBBg1py5QQSsfhwIGM\nIiBxGC25adKnjbgw97b7JzoTZud0CNW3k8cZNlWrx0jKP5CAcRl4BK2eBnRrYhed\nyioqGRUxMQnYrlynMxWL6vo7YSTC+7sa6EP+xhsY8K7irMDrgSHH895oJfla1RvN\n63Id4h3+RmFUhyL8zKI7J3id\n-----END PRIVATE KEY-----\n");
    dataFile=SD.open(fileName,FILE_READ);
    String date="";
    while(dataFile.available()){
    date=dataFile.readStringUntil(',');

    if(m){
      m=checklastdate(date);
    }
    bool taskComplete = false;

    if(!m){
    while(!taskComplete){
    bool ready = GSheet.ready();

    if (ready && !taskComplete)
    { FirebaseJson response;
        // Instead of using FirebaseJson for response, you can use String for response to the functions
        // especially in low memory device that deserializing large JSON response may be failed as in ESP8266
        FirebaseJson valueRange;
       String s="Sheet1!"+stringgen(daynum+3)+"1";
        valueRange.add("majorDimension", "COLUMNS");  
        valueRange.set("values/[0]/[0]",date);
        // valueRange.set("values/[0]/[1]", "A");
        // valueRange.set("values/[0]/[2]", "A");
        // valueRange.set("values/[0]/[3]", "A");
        // valueRange.set("values/[0]/[4]", "L");
      
        // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append

        bool success = GSheet.values.append(&response /* returned response */, "1hfmKLyTc_rjSeS1E3KvEp9h04tVyG9RGldDozgvCun0" /* spreadsheet Id to append */, s /* range to append */, &valueRange /* data range to append */);
        if (success){
            taskComplete=true;
        }
        
    }
    }
    }else{
      m=false;
      daynum--;
    }
    taskComplete=false;
    
    String line = dataFile.readStringUntil('\n');
    
    while(!taskComplete){
      bool ready = GSheet.ready();
    if (ready && !taskComplete)
    { FirebaseJson response;
        // Instead of using FirebaseJson for response, you can use String for response to the functions
        // especially in low memory device that deserializing large JSON response may be failed as in ESP8266
        FirebaseJson valueRange; 
       String s="Sheet1!"+stringgen(daynum+3)+String(1000);
       String data=String(strength)+","+line;
        valueRange.add("majorDimension", "COLUMNS");
        valueRange.add("range", s);
        valueRange.set("values/[0]/[0]",data);
        
        // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append
        bool success = GSheet.values.update(&response /* returned response */, "1hfmKLyTc_rjSeS1E3KvEp9h04tVyG9RGldDozgvCun0" /* spreadsheet Id to append */, s /* range to append */, &valueRange /* data range to append */);
        if (success){
            
              taskComplete=true;
            
        }
        }
    }
    
    daynum++;
    }
    dataFile.close();
    SD.remove("/config/pending.txt");
    SD.remove("/config/daynum.txt");
    SD.remove("/config/delta.txt");
    SD.remove("/config/last_date.txt");
      dataFile=SD.open("/config/delta.txt",FILE_APPEND);
      dataFile.print("0");
      dataFile.close();
      dataFile=SD.open("/config/last_date.txt",FILE_APPEND);
      dataFile.print(date);
      dataFile.close();
    dataFile=SD.open("/config/daynum.txt",FILE_APPEND);
    dataFile.print(daynum);
    dataFile.close();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
     tftreset();
    tft.fillScreen(TFT_WHITE);
    printer("Attendance Uploaded",0,60,3,480,TFT_BLUE);
    printer("Succesfully",0,110,3,480,TFT_BLUE);
    delay(1000);
  }
  }
    else{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    tftreset();
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLUE);
    tft.setTextSize(3);
    tft.setCursor(40,60);
    tft.print("Already Uploaded");
    delay(1000);
   }
}