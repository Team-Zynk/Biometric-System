gvoid google(){           //get student data from sheet
   tft.fillScreen(TFT_WHITE);
   tft.setTextColor(TFT_BLUE);
   tft.setTextSize(3);
   tft.setCursor(40,10);
   tft.print("Connecting to WiFi");
   WiFi.begin("Xiaomi 11T Pro","nahi pata");
   int counter =0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      break;
    }
  }
  //hi
  
  if(WiFi.status() != WL_CONNECTED){
    tftreset();
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLUE);
    tft.setTextSize(3);
    tft.setCursor(40,10);
    tft.print("Could not connect");
    delay(700);
  }else{
    String fileName=String("/")+String("stdinfo")+String(".txt");
    File dataFile;
    if(SD.exists(fileName))
        SD.remove(fileName);
    String private_key ="";
    dataFile = SD.open("/key.txt",FILE_READ);
    while(dataFile.available()){
    private_key+=  dataFile.readStringUntil('\n');
    }
    dataFile.close();

    dataFile = SD.open("/service.txt",FILE_READ);
    String account = dataFile.readStringUntil('\n');
    String account_id = dataFile.readStringUntil('\n');
    account = account.substring(0);
    account_id = account_id.substring(0);
    dataFile.close();

    dataFile =SD.open("/sheet.txt",FILE_READ);
    String sheet_id = dataFile.readStringUntil('\n');
    sheet_id = sheet_id.substring(0);
    dataFile.close();

    dataFile=SD.open(fileName,FILE_APPEND);
    int k=0;
    uint16_t strength=0;
    bool taskComplete = false;
    GSheet.begin(account ,account_id, private_key);
    while(!taskComplete){
    bool ready = GSheet.ready();
    // int tot=0;
    if (ready && !taskComplete)
    {
        
        FirebaseJson response;
        String s="Sheet1";
        s=s+"!A"+String(k+1)+":B"+String(k+5);
        bool success = GSheet.values.get(&response /* returned response */, sheet_id /* spreadsheet Id to read */, s /* range to read */);
        size_t count = response.iteratorBegin();
        size_t count = response.iteratorBegin();
            for (size_t i = 3; i < count; i++)
            {
                FirebaseJson::IteratorValue value = response.valueAt(i);
                dataFile.print(value.value.c_str());
                dataFile.print(",");
                i++;
                value = response.valueAt(i);
                dataFile.print(value.value.c_str());
                dataFile.println();
                strength++;
            }
            response.iteratorEnd();
            k=k+5;
        }
        if(k!=strength){
        taskComplete = true;
        dataFile.close();
        }
    }
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    tftreset();
    if(SD.exists("/strength.txt")){
      SD.remove("/strength.txt");
    }
    dataFile=SD.open("/strength.txt",FILE_APPEND);
    dataFile.print(String(strength-1));
    dataFile.close();
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLUE);
    tft.setTextSize(3);
    tft.setCursor(40,60);
    tft.print("Database Updated");
    tft.setCursor(40,110);
    tft.print("Succesfully");
    delay(1000);
  }
  }