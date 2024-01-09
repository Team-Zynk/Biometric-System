
#include "SPI.h"          // Libraries for TFT 3.5" and Touch
#include "TFT_eSPI.h"       
#include <TouchScreen.h>
TFT_eSPI tft = TFT_eSPI(); //tft variable defined as global 
 
 
 
bool Touched(boolean showTouch,uint16_t *x,uint16_t *y) {                   // function for touch detection

    TouchScreen ts = TouchScreen(4, 33, 32, 15, 300); //touch variable defined 
    const int coords[] = {420, 3900, 3600, 570};// portrait - left, right, top, bottom          // Coordinates found through calibration
    TSPoint p = ts.getPoint();
    pinMode(33, OUTPUT);      //restore shared pins
    pinMode(32, OUTPUT);
    digitalWrite(33, HIGH);   //because TFT control pins
    digitalWrite(32, HIGH);
    bool pressed = (p.z > 200 && p.z < 20000);
    if (pressed) {
          *x = map(p.y, coords[1], coords[0], 0, tft.width());            // these are for landscape could refer TouchScreen.h for portrait
          *y = map(p.x, coords[2], coords[3], 0, tft.height()); 
    if (showTouch) tft.fillCircle(*x, *y, 2, TFT_WHITE);             //showtouch true for showing marks at touch
      return true;
    }
    return false;
}
void write1();                // attendance mark function declared
class button{                 // button class to form round rectangular buttons
  public:
  int ln;    //length  (left to right)
  int wd;    //width    (top to bottom)
  int s;     //text size
  int x;     // top left x  [0,480] for our case in landscape
  int y;     // top left y  [0,320] for our case in landscape
  String txta;  //first word
  String txtb;  //second word
  uint16_t bgc; // background colour of button
  uint16_t tc;  // text colour of button
  button(){
    
  }
  button(int x1,int y1,int s1,String txta1,String txtb1,int ln1,uint16_t bgc1,uint16_t tc1){  //constructor

  x=x1;
  y=y1;
  s=s1;
  ln=ln1;
  txta=txta1;
  txtb=txtb1;
  wd=26*s;                  //height according to text size since it is tedious to get 26*s everytime
  bgc=bgc1;
  tc=tc1;
  }
  void display(){                             // to display text and button move to next line for two words
    tft.fillRoundRect(x,y,ln,wd,wd/4,bgc);
    tft.setTextColor(tc);
    tft.setTextSize(s);
    if(txtb==""){
      tft.setCursor(x+((ln-tft.textWidth(txta))/2),y+8*s);
      tft.println(txta);
    }else{
      tft.setCursor(x+((ln-tft.textWidth(txta))/2),y+2*s);
      tft.println(txta);
      tft.setCursor(x+((ln-tft.textWidth(txtb))/2),y+14*s);
      tft.println(txtb);
    }
  } 
  bool check(int x1, int y1){                 //check if this buttonwas pressed
    return (x1<x+ln && x1>x && y1<y+wd && y1>y);
  }
};

class Buttons{                // container for multiple buttons on same screen
 private:
 int ln=0;
 public:
 int n;                       // number of buttons
 int s;
 uint16_t bgc;
 uint16_t tc;
 button stk[12];              // since a maximum of 12 buttons was required // can be changed for more

 Buttons(int s1,uint16_t bgc1,uint16_t tc1){
  s=s1;
  bgc=bgc1;
  tc=tc1;
  ln=0;
 }
 void displayall(){         // display all buttons
  for(int i=0;i<n;i++){
    stk[i].display();
  }
 }
 int checkpress(int x,int y){   // check button that was pressed
  for(int i=0;i<n;i++){
    if(stk[i].check(x,y)){
      return i;
    }
  }
  return -1;
 }


 void insert(int x1,int y1,String txt1){         //to insert a new button with top left coordinates x,y with text txt1 (Could contain two words)
  String txta="";
  String txtb="";
  int i=0;
  while(i<txt1.length()){
   if(txt1[i]==' '){
    i++;
    while(i<txt1.length()){
      txtb=txtb+txt1[i];
      i++;
    }
   }
   txta=txta+txt1[i];
   i++;
  }
  int ln1;                                          
   if(tft.textWidth(txta)>tft.textWidth(txtb)){          //to get a standard size as max of all size of buttons
    ln1=tft.textWidth(txta);
   }else{
    ln1=tft.textWidth(txtb);
   }
   if(ln1>ln){
    ln=ln1;
   }
   for(int i=0;i<n;i++){
    stk[i].ln=ln;
   }
   stk[n]=button(x1,y1,s,txta,txtb,ln,bgc,tc);
  n=n+1;
 }
};

#include <WiFi.h> //Wifi library
#include "esp_wpa2.h"  //wpa2 library for connections to Enterprise networks like IITD_WiFi
#include "time.h" //time library
#include <FS.h>
#include <SD.h>  //SD card library
#include <JPEGDecoder.h> 
#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <ESP_Google_Sheet_Client.h> // Configures JSON objects to post on google sheets
HardwareSerial SerialPort(2);       // serial port for fingerprint sensor
const char* host = "arduino.php5.sk"; //external server domain for HTTP connection after authentification
struct tm oldtime;
Buttons b1=Buttons(2,TFT_SKYBLUE,TFT_BLACK);
Buttons b2 =Buttons(2,TFT_SKYBLUE,TFT_BLACK);
int admin[10];
int roll=-1;
int k=1;

void Forcetime(){
  getLocalTime(&oldtime);
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  tft.setTextSize(2);
  tft.setCursor(60,280);
  tft.setTextColor(TFT_BLACK);
  tft.fillRect(60,280,480,20,TFT_WHITE);
  tft.println(&timeinfo, "%A, %B %d %Y %H:%M");
}
void printLocalTime() //print the local time once sync with wifi
{ tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(60,280);
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  if(timeinfo.tm_min!=oldtime.tm_min){
  tft.fillRect(60,280,480,20,TFT_WHITE);
  tft.println(&timeinfo, "%A, %B %d %Y %H:%M");
  oldtime=timeinfo;
  }
}

String stringgen(int x){       //to generate string for a given column number in google sheets
  String ans="";
  while(x!=0){
    ans=String((char(((x-1)%26)+'A')))+ans;
    x=(x-1)/26;
  }
  return ans;
}

void printer(String txt,uint16_t x,uint16_t y,uint16_t s,uint16_t ln,uint16_t color)
{ // print center aligned text
tft.setTextSize(s);
tft.setTextColor(color);
tft.setCursor(x+(ln-(tft.textWidth(txt)))/2,y);
tft.print(txt);
}


void HomeScreen(){  // The Homescreen for the attendance system
tft.fillScreen(TFT_WHITE);
drawSdJpeg("/config/c_logo.jpg", 0, 0);  //The Background image
printer("Designed & Developed by",0,10,2,480,TFT_BLACK);
Forcetime();
}

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&SerialPort); //Serialport 2 given to fingerprint 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialPort.begin(57600,Serial1,16,17);
  delay(1000);
  digitalWrite(22, HIGH); 
  digitalWrite(15, HIGH);
  digitalWrite( 5, HIGH);
  WiFi.disconnect(true);   //Disconnect wifi
  WiFi.mode(WIFI_OFF);
  tftreset();
  tft.begin();
  tft.init();
  tft.setSwapBytes(true);
  tft.setRotation(1);            //Set Rotation to landscape
  tft.fillScreen(TFT_WHITE);
  tft.setTextSize(4);
  digitalWrite(5, HIGH);
    if (!SD.begin()) {
    printer("SD card mount failed",100,40,2,300,TFT_RED);
    delay(1000);
    return;
  }
     uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    printer("No SD card attatched",100,40,2,300,TFT_RED);
    delay(1000);
    return;
  }

   drawSdJpeg("/config/iitlogo.jpg", 80, 60);  // This draws a jpeg pulled off the SD Card
   printer("INITIALIZATION",0,10,3,480,TFT_BLUE);
   for(int i=0;i<3;i++){
    tft.print(". ");
    delay(500);
   }
  delay(500);     
  google();          //update student info file from google sheets
  
  
  finger.begin(57600);     // set the data rate for the sensor serial port
  delay(100); 
  if (finger.verifyPassword()) {
   tft.fillScreen(TFT_WHITE);
   printer("Found Fingerprint Sensor",10,10,3,460,TFT_BLUE);
   delay(500);
  } else {
   tft.fillScreen(TFT_WHITE);
   printer("Did not find",10,10,3,460,TFT_BLUE);
   printer("fingerprint sensor",10,60,3,460,TFT_BLUE);
   delay(1000);
    return;
  }

  finger.getTemplateCount();  //get number of fingerprints stored

   if(!SD.exists("/config/on.txt")){
   roll=127;
   while (!getFingerprintEnroll()){};
   File file;
   file=SD.open("/config/on.txt",FILE_WRITE);
   file.close();
  }
  admincheck();

  if (finger.templateCount == 0) {
   printer("Did not find",10,60,3,460,TFT_BLUE);
   printer("Any fingerprint data",10,110,3,460,TFT_BLUE);
   delay(1000);
  }
  else {
   printer(String(finger.templateCount)+" Fingerprints found",10,60,3,460,TFT_BLUE);
   delay(1000);
  }

  if(!SD.exists("/config/daynum.txt")){       //Initialize number of days file
    File dataFile=SD.open("/daynum.txt",FILE_APPEND);
    dataFile.print("0");
    dataFile.close();
  }

  if(!SD.exists("/config/strength.txt")){       //Initialize strength file
    File dataFile=SD.open("/strength.txt",FILE_APPEND);
    dataFile.print("0");
    dataFile.close();
  }

   //disconnect form wifi to set new wifi connection
  // WiFi.mode(WIFI_STA); //init wifi mode
  // // Example1 (most common): a cert-file-free eduroam with PEAP (or TTLS)

 
  // // delay(500);
  // WiFi.begin("Xiaomi 11T Pro","nahi pata");

  // // Example 2: a cert-file WPA2 Enterprise with PEAP
  // //WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_IDENTITY, EAP_USERNAME, EAP_PASSWORD, ca_pem, client_cert, client_key);
  // // Example 3: TLS with cert-files and no password
  // //WiFi.begin(ssid, WPA2_AUTH_TLS, EAP_IDENTITY, NULL, NULL, ca_pem, client_cert, client_key);
  // int counter =0;
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  //   counter++;
  //   if(counter>=60){ //after 30 seconds timeout - reset board
  //     break;
  //   }
  // }
     //Get time from the server
 

  //Insert all buttons

  b1.insert(40,50,"Mark Attendance");
  b1.insert(270,50,"Read Attendance");
  b1.insert(40,130,"Save file");
  b1.insert(270,130,"Appoint Admin");
  b1.insert(40,210,"Enroll");
  b1.insert(270,210,"EXIT PAGE");
  b2.insert(320,250,"0");
  b2.insert(240,10,"1");
  b2.insert(320,10,"2");
  b2.insert(400,10,"3");
  b2.insert(240,90,"4");
  b2.insert(320,90,"5");
  b2.insert(400,90,"6");
  b2.insert(240,170,"7");
  b2.insert(320,170,"8");
  b2.insert(400,170,"9");
  b2.insert(240,250,"Del");
  b2.insert(400,250,"Next");
  tft.fillScreen(TFT_WHITE);
  printer("INITIALIZATION",0,60,4,480,TFT_BLUE);
  printer("FINISHED",0,120,4,480,TFT_BLUE);
  delay(1000);
  HomeScreen();
}
void loop() {
   printLocalTime();
   roll=getFingerprintID(); 
   if(roll!=-1){
    if(checkmore()){
      adminmenu();
    }else{
    write1();
    }
    HomeScreen();
   }
   roll=-1;      
}

int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK){
     tft.fillScreen(TFT_WHITE);
     tft.setCursor(40,20);
     tft.setTextSize(4);
     tft.setTextColor(TFT_RED);
     tft.setCursor(40,120);
     tft.println(F("Did Not Match"));
     delay(1000); 
     HomeScreen();
     return -1;
  }
  
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,10);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(2);
  tft.print(F("Found ID Number "));
  tft.print(finger.fingerID);
  String s=getdata(finger.fingerID);
  tft.setCursor(40,60);
  tft.print(F("Name: "));
  tft.print(s.substring(1,s.indexOf(",")-1));
  tft.setCursor(40,110);
  tft.print(F("Entry Number: "));
  Serial.println();
  tft.print(s.substring(s.indexOf(",")+2,s.length()-2));
  delay(1000);  
  return finger.fingerID;
}

void tftreset(){             //Reset pinmodes of tft after wifi connection breaks/ since they share common pins
  pinMode(TFT_RD, OUTPUT);
  digitalWrite(TFT_RD, HIGH);
   pinMode(TFT_D0, OUTPUT); digitalWrite(TFT_D0, HIGH);
    pinMode(TFT_D1, OUTPUT); digitalWrite(TFT_D1, HIGH);
    pinMode(TFT_D2, OUTPUT); digitalWrite(TFT_D2, HIGH);
    pinMode(TFT_D3, OUTPUT); digitalWrite(TFT_D3, HIGH);
    pinMode(TFT_D4, OUTPUT); digitalWrite(TFT_D4, HIGH);
    pinMode(TFT_D5, OUTPUT); digitalWrite(TFT_D5, HIGH);
    pinMode(TFT_D6, OUTPUT); digitalWrite(TFT_D6, HIGH);
    pinMode(TFT_D7, OUTPUT); digitalWrite(TFT_D7, HIGH);
}