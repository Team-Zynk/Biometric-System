bool checklastdate(const String& dt){           //check if last date on sheets is same as current  
    File dataFile;
    dataFile=SD.open("/daynum.txt",FILE_READ);
    uint16_t daynum=0;
    while(dataFile.available()){
    String line = dataFile.readStringUntil('\n');
    daynum=line.toInt();
    }
    dataFile.close();
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

    
    bool taskComplete = false;
    String lastdate="";
    GSheet.begin(account ,account_id, private_key);
    while(!taskComplete){
    bool ready = GSheet.ready();
    if (ready && !taskComplete)
    {
        
        FirebaseJson response;
        String s="Sheet1!"+stringgen(daynum+2)+"1"+":"+stringgen(daynum+2)+"1";
        bool success = GSheet.values.get(&response /* returned response */, sheet_id /* spreadsheet Id to read */, s /* range to read */);
        size_t count = response.iteratorBegin();
            for (size_t i = 3; i < count; i++)
            {
                FirebaseJson::IteratorValue value = response.valueAt(i);
                lastdate=value.value.c_str();
                lastdate=lastdate.substring(1,s.length()-1);
            }
            response.iteratorEnd();
            if(success){
             taskComplete = true;
            }
        }
        
    }

    if(dt==lastdate){
      return true;
    }else{
      return false;
    }
    
  }