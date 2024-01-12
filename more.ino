void admincheck(){
  File myfile;
  myfile=SD.open("/config/admin.txt",FILE_APPEND);
  myfile.close();
  myfile = SD.open("/config/admin.txt",FILE_READ);
    while (myfile.available() && k<10) {
      String line = myfile.readStringUntil('\n');
        int lineId = line.toInt();
        admin[k]=lineId;
        k=k+1;
    }
}

void appoint(){
  int x=keypad();
  if(k<9 && roll==127){
  File myfile;
  myfile=SD.open("/config/admin.txt",FILE_APPEND);
  myfile.print(x);
  myfile.println();
  myfile.close();
  admincheck();
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLUE);
  tft.print("Appointed # ");
  tft.print(x);
  tft.setCursor(40,60);
  tft.println("Enjoy new tools");
  delay(1000);
  }
  else{
    tft.fillScreen(TFT_BLUE);
    tft.setCursor(40,20);
    tft.setTextSize(3);
    tft.setTextColor(TFT_WHITE);
    tft.print("Can not appoint");
    tft.setCursor(40,60);
    tft.println("Admin");
    delay(1000);
  }
}

bool checkmore(){
  if(roll==127){
    return true;
  }
  int r=0;
  while(r<10){
    if(admin[r]==roll){
      return true;
    }
    r=r+1;
  }
  return false;
}

void enroll(){
  
  roll=keypad();
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,10);
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLUE);
  finger.getTemplateCount();
  delay(100);
  tft.print(F("Enrolling at "));
  tft.print(roll);
  String s=getdata(roll);
  tft.setCursor(40,60);
  tft.print(F("Name: "));
  tft.print(s.substring(0,s.indexOf(",")));
  tft.setCursor(40,110);
  tft.print(F("Entry Number: "));
  tft.print(s.substring(s.indexOf(",")+1));
  delay(2000);
  while (!getFingerprintEnroll());
}

bool getFingerprintEnroll() {
  int p = -1;
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLUE);
  tft.print(F("Waiting"));
  drawSdJpeg("/config/wtlogo.jpg", 176, 70);
  tft.setCursor(40,60);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    // switch (p) {
    // case FINGERPRINT_OK:
    //   break;
    // }
  }


 


  p = finger.image2Tz(1); 
  switch (p) {
    case FINGERPRINT_OK:
      tft.setCursor(40,100);
      tft.print(F("Image converted"));
      delay(1000);
      break;
    default:
      return false;
  }
  uint8_t p1= finger.fingerSearch();
  if(p1==FINGERPRINT_OK){
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.print(F("Already Exists at ID"));
  tft.setCursor(40,60);
  tft.print(finger.fingerID);
  delay(500);
  return false;
  }
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.print(F("Remove finger"));
  delay(500);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  p = -1;
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.print(F("Place again"));
  tft.setCursor(40,60);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    // switch (p) {
    // case FINGERPRINT_OK:
    //   break;
    // default:
    //   break;
    // }
  }

  delay(500);
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      tft.print(F("Image converted"));
      break;
    default:
      tft.print(F("Try Again"));
      delay(1000);
      return false;
  }
  delay(1000);
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.print(F("Creating model"));tft.print(F("for ")); tft.print(roll);
  delay(1000);
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    tft.print(F("Prints matched!"));
    drawSdJpeg("/config/pmlogo.jpg", 176, 70);
    delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    tft.print(F("Communication error"));
    delay(500);
    return false;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    tft.print(F("Did not match"));
    delay(1000);
    return false;
  } else {
    return false;
  }
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.print(F("Storing in ")); tft.print(roll);
  tft.setCursor(40,60);
  p = finger.storeModel(roll);
  if (p == FINGERPRINT_OK) {
    tft.print(F("Stored"));
    delay(2000);
    return true;
  } else {
    tft.print(F("ERROR"));
    return false;
  }
}