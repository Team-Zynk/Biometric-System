bool gettime(struct tm & oldtime){
  tft.fillScreen(TFT_WHITE);
  drawSdJpeg("/config/timelogo.jpg", 176, 130);
   printer("Fetching time from server",0,10,3,480,TFT_BLUE);
  if(wifi()){
    unsigned long st;
    int ctr=0;
    while(!getLocalTime(&oldtime,5000) && ctr<3){
    configTime(19800,0,"pool.ntp.org");
    Serial.print(". ");
    ctr++; 
    }
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    tftreset();
    if(getLocalTime(&oldtime)){
    printer("Succesfully fetched time",0,60,3,480,TFT_BLUE);
    delay(1000);
    return true;
    }else{
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      tftreset();
      manualtime(oldtime);
      return false;
    }
  }else{
    WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      tftreset();
    manualtime(oldtime);
    return false;
  }
  return false;
}