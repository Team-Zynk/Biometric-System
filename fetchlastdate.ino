bool checklastdate(const String& dt){           //check if last date on sheets is same as current  
    File dataFile;
    dataFile=SD.open("/config/daynum.txt",FILE_READ);
    uint16_t daynum=0;
    while(dataFile.available()){
    String line = dataFile.readStringUntil('\n');
    daynum=line.toInt();
    }
    dataFile.close();
    bool taskComplete = false;
    String lastdate="";
    GSheet.begin("firebase-adminsdk-qhwbj@attendance-system-397119.iam.gserviceaccount.com", "attendance-system-397119", "-----BEGIN PRIVATE KEY-----\nMIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQCv0J3gb4LCFMkX\nOVIH2haq9jPMgUV7I9EYUQsmyWJMvV/4yCOdSzxibX46UUv/nxDekjwnTla3bTZ2\n4C8gWbwIr5bbjjpWjXirDPF2/sf/+PTFgc3LSz27xmtfBCrgnuiHIMkPPdd1bxmF\nA10WCiXSziwGlRTshmqF7PsK33opnhZC0Gdm3NguPMPz81lAkoY0juJONqomiCpl\nu4u5Z+kWaNa4y6vN0PoOPy+un8Hcf4VywOBkIhbH2PCoXp2U9MmpV60OoCinJF+P\nVPL/tYEjEHnRTKB7B+wRAWRGf+CXGTe2nIGA2Fvf8TqUZg2K0+9iAGvCnDNOHWDr\nbx4gYxTjAgMBAAECggEABMxIKrJQWrSPglM9olo4ySSb6EZU25XwJF491CqlxJtc\nbaEkm6vMc5EyYywJy2mPX8uU2avBIRNZa6gVkSfxwjjsgIRioi8NLnnVcx5j3d/w\n6hzvPU+J2UCCeJ7X/rZHeTyTUBerdBh6lU8wsKPJQXX/7JQP9J58dLgxZ6wOnOkY\nXkKWuVZC4jYFMugzsF9Dq686eSXQ9jby/Y2p3p3FjUuZUp761Xuq89eOX0099kKe\ntGosgbF5GMpGrT+WeCFWqo3Mmv/crjgdfO+H82s50ISbOY6/zWvlZwNERqdlOFb9\nU0uGddgGUDaLw8Zgmc8njfcS+22nsAhE5Bf0rsCJ0QKBgQDwK6wB2lec4NO6kbvy\n4tbQRodlrQvxEJuYsZiK8pfg0KYOqarhol+RQGg85+bjFrpsmyFLgbwceqTqyn5l\nEipyvCMRpwhFGdkXuHnmk7VXGRjsX8kv/rrIgex0tJtywtw4QP/LPce4lxTuiUVK\nnS+om+YVBZ1zEHaxX4tjJKJ1cwKBgQC7ZxcWVVfltenxtHZwFr5+5qwSS/WIMzVT\nJw2vyvGAkb6vaHlBMXRaWImyBvljGiMkkxQI2BhtfSwVZL6NbmvBXTcEfu3jZayn\nzh8gUzZzgTYRiP3XYFx60FPyOrKQXOdg5RDCYDIJqjaw6K7p+lglsS++zFzYww+L\nWj45jt2G0QKBgQCokg6N0mGyM7+IcOeZaAvcbdR00gvSrJR5jRWDWRiu6+PR4NaW\nvjATtEA1l5NgCsDYn92zsKCG4LJGNdCXQjPXCiQXLMTKM4VDd/DfnQcn1e6/Yc/F\nRyZ0u3RqyaVd3FVTipO/ZGJ9NlWzw1eGMmOUFbBdSu6jJ4gXoPclpD3+7wKBgCh0\nCXzNsWqpyTVe0k5B6p80JiLQ+NCM1U782CyBb35kd7gfokUbatVx1U9zx/PHmZx0\nj1eVZjiEU7bOh3+6PVKBT7YNvEZhFVMn4Ho23EM0ujowyzLp3yy3uddJKnCVTXES\nIXsEDukdMC8iG1fwrYR9aiQSs1wrRzi6o0IDf/hxAoGBAJcBBg1py5QQSsfhwIGM\nIiBxGC25adKnjbgw97b7JzoTZud0CNW3k8cZNlWrx0jKP5CAcRl4BK2eBnRrYhed\nyioqGRUxMQnYrlynMxWL6vo7YSTC+7sa6EP+xhsY8K7irMDrgSHH895oJfla1RvN\n63Id4h3+RmFUhyL8zKI7J3id\n-----END PRIVATE KEY-----\n");
    while(!taskComplete){
    bool ready = GSheet.ready();
    if (ready && !taskComplete)
    {
        
        FirebaseJson response;
        String s="Sheet1!"+stringgen(daynum+2)+"1"+":"+stringgen(daynum+2)+"1";
        bool success = GSheet.values.get(&response /* returned response */, "1hfmKLyTc_rjSeS1E3KvEp9h04tVyG9RGldDozgvCun0" /* spreadsheet Id to read */, s /* range to read */);
        size_t count = response.iteratorBegin();
            for (size_t i = 3; i < count; i++)
            {
                FirebaseJson::IteratorValue value = response.valueAt(i);
                lastdate=value.value.c_str();
                lastdate=lastdate.substring(1,lastdate.length()-1);
            }
            response.iteratorEnd();
            if(success){
             taskComplete = true;
            }
        }
        
    }
    Serial.println(lastdate);
    delay(500);
    Serial.println(dt);
    delay(500);
    if(dt==lastdate){
      SD.remove("/config/delta.txt");
      dataFile=SD.open("/config/delta.txt",FILE_APPEND);
      dataFile.print("0");
      dataFile.close();
      return true;
    }else{
      return false;
    }
    
  }