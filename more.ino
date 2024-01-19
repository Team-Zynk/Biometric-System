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
  int x=keypad("ADMIN ACCESS","ID number");
  if(x==-1){
    return;
  }
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
  
  roll=keypad("ENROLL","ID Number");
  if(roll<=-1 || roll>=127){
    return;
  }
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
  tft.print(s.substring(1,s.indexOf(",")-1));
  tft.setCursor(40,110);
  tft.print(F("Entry Number: "));
  tft.print(s.substring(s.indexOf(",")+2,s.length()-2));
  delay(2000);
  if(!confirmation("To Enroll for "+s.substring(s.indexOf(",")+2,s.length()-2))){return;}
  while (!getFingerprintEnroll());
}

bool getFingerprintEnroll() {
  int p = -1;
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLUE);
  tft.print(F("Waiting"));
  drawSdJpeg("/config/wtlogo.jpg", 176, 160);
 drawSdJpeg("/config/exlogo.jpg", 445, 0);
  tft.setCursor(40,60);
  uint16_t x=0,y=0;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    if(Touched(false,&x,&y)){
       if(x>412 && x<480 && y<48 && y>0){
        return true;
      }
    }
    switch (p) {
    case FINGERPRINT_OK:
      tft.println("Image taken");
      delay(500);
      break;
    case FINGERPRINT_NOFINGER:
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.println("Communication error");
      delay(500);
      break;
    case FINGERPRINT_IMAGEFAIL:
      tft.println("Imaging error");
      delay(500);
      break;
    default:
      tft.println("Unknown error");
      delay(500);
      break;
    }
  }

  tft.fillScreen(TFT_WHITE);
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLUE);
  drawSdJpeg("/config/wtlogo.jpg", 176, 160);
  tft.setCursor(40,20);
 
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      tft.println("Image converted");
      delay(200);
      break;
    case FINGERPRINT_IMAGEMESS:
      tft.println("Image too messy");
      delay(500);
      return false;
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.println("Communication error");
      delay(500);
      return false;
    case FINGERPRINT_FEATUREFAIL:
      
      return false;
    case FINGERPRINT_INVALIDIMAGE:
      
      return false;
    default:
      tft.println("Unknown error");
      delay(500);
      return false;
  }
  // uint16_t p1= finger.fingerSearch();
  // if(p1==FINGERPRINT_OK){
  // tft.fillScreen(TFT_WHITE);
  // tft.setCursor(40,20);
  // tft.print(F("Already Exists at ID"));
  // tft.setCursor(40,60);
  // tft.print(finger.fingerID);
  // delay(500);
  // return false;
  // }
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.print(F("Remove finger and wait"));
  delay(1000);
  p = 0;
  drawSdJpeg("/config/exlogo.jpg", 445, 0);
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
    if(Touched(false,&x,&y)){
       if(x>412 && x<480 && y<48 && y>0){
        return true;
      }
    }
  }
  p = -1;
  
  int done=0;
  bool complete=false;
  while(done<4 && !complete){
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.print(F("Place again"));
  drawSdJpeg("/config/exlogo.jpg", 445, 0);
  tft.setCursor(40,60);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    if(Touched(false,&x,&y)){
       if(x>412 && x<480 && y<48 && y>0){
        return true;
      }
    }
    switch (p) {
    case FINGERPRINT_OK:
      tft.println("Image taken");
      delay(500);
      break;
    case FINGERPRINT_NOFINGER:
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.println("Communication error");
      delay(500);
      break;
    case FINGERPRINT_IMAGEFAIL:
      tft.println("Imaging error");
      delay(500);
      break;
    default:
      tft.println("Unknown error");
      delay(500);
      break;
    }
  }
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  delay(500);
  p = finger.image2Tz(2);
  bool sure=false;
  switch (p) {
    case FINGERPRINT_OK:
      tft.println("Image converted");
      sure=true;
      delay(200);
      break;
    case FINGERPRINT_IMAGEMESS:
      tft.println("Image too messy");
      delay(500);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.println("Communication error");
      delay(500);
      break;
    case FINGERPRINT_FEATUREFAIL:
    
      break;
    case FINGERPRINT_INVALIDIMAGE:
      
      break;
    default:
      tft.println("Unknown error");
      delay(500);
      break;
  }
  
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.print(F("Creating model"));tft.print(F("for ")); tft.print(roll);
  delay(500);
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  if(sure){
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    tft.print(F("Prints matched!"));
    drawSdJpeg("/config/pmlogo.jpg", 176, 70);
    complete=true;
    delay(500);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    tft.print(F("Communication error"));
    delay(500);
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    tft.print(F("Did not match"));
    delay(500);
  } else {
    tft.print(F("Unknown Error"));
    delay(500);
  }
  }
  done++;
  }
  if(!complete){
    tft.fillScreen(TFT_WHITE);
    tft.setCursor(40,20);
    tft.println("TRY AGAIN");
    delay(1000);
    return false;
  }
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.print(F("Storing in ")); tft.print(roll);
  tft.setCursor(40,60);
  p = finger.storeModel(roll);
  if (p == FINGERPRINT_OK) {
    tft.print(F("Stored"));
    delay(500);
    return true;
  } else {
    tft.print(F("ERROR"));
    return false;
  }
  
}



bool getFingerprintEnrolladmin() {
  int p = -1;
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLUE);
  tft.print(F("Waiting"));
  drawSdJpeg("/config/wtlogo.jpg", 176, 160);
  tft.setCursor(40,60);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      tft.println("Image taken");
      delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.println("Communication error");
      delay(1000);
      break;
    case FINGERPRINT_IMAGEFAIL:
      tft.println("Imaging error");
      delay(1000);
      break;
    default:
      tft.println("Unknown error");
      delay(1000);
      break;
    }
  }

  tft.fillScreen(TFT_WHITE);
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLUE);
  drawSdJpeg("/config/wtlogo.jpg", 176, 160);
  tft.setCursor(40,20);
 
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      tft.println("Image converted");
      delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
      tft.println("Image too messy");
      delay(1000);
      return false;
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.println("Communication error");
      delay(1000);
      return false;
    case FINGERPRINT_FEATUREFAIL:
      
      return false;
    case FINGERPRINT_INVALIDIMAGE:
      
      return false;
    default:
      tft.println("Unknown error");
      delay(1000);
      return false;
  }
  uint16_t p1= finger.fingerSearch();
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
  tft.print(F("Remove finger and wait"));
  delay(2000);
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
    switch (p) {
    case FINGERPRINT_OK:
      tft.println("Image taken");
      delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.println("Communication error");
      delay(1000);
      break;
    case FINGERPRINT_IMAGEFAIL:
      tft.println("Imaging error");
      delay(1000);
      break;
    default:
      tft.println("Unknown error");
      delay(1000);
      break;
    }
  }
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  delay(500);
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      tft.println("Image converted");
      delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
      tft.println("Image too messy");
      delay(1000);
      return false;
    case FINGERPRINT_PACKETRECIEVEERR:
      tft.println("Communication error");
      delay(1000);
      return false;
    case FINGERPRINT_FEATUREFAIL:
    
      return false;
    case FINGERPRINT_INVALIDIMAGE:
      
      return false;
    default:
      tft.println("Unknown error");
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
    tft.print(F("Unknown Error"));
    delay(1000);
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