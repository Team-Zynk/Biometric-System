void manualtime(struct tm & oldtime){
  if(SD.exists("/config/on.txt")){
  tft.fillScreen(TFT_WHITE);
   printer("Please contact the admin",0,40,3,480,TFT_BLUE);
   printer("To enter time manually",0,100,3,480,TFT_BLUE);
   printer("Place his finger",0,200,3,480,TFT_BLUE);
   printer("For authentication",0,260,3,480,TFT_BLUE);
   while(roll!=127){
      uint8_t p = finger.getImage();
      if (p != FINGERPRINT_OK)  continue;

      p = finger.image2Tz();
      if (p != FINGERPRINT_OK)  continue;

      p = finger.fingerFastSearch();
      roll=finger.fingerID;
   } 
  }
 tft.fillScreen(TFT_WHITE);
 b2.displayall();
 b3.displayall();
 b4.displayall();
 int arr[4];
 for(int i=0;i<4;i++){
  arr[i]=0;
 }
 uint16_t x,y;
 int x1=-1;
 int s=0;
 int i=0;
 tft.setCursor(10,5); 
   tft.setTextColor(TFT_BLACK);
   tft.setTextSize(2);
   tft.print("Enter Time");
   b4.stk[i].bgc=TFT_BLUE;
   b4.stk[i].display();
 while(true){
   while(!Touched(false,&x,&y)){
   }
   x1=b2.checkpress(x,y);
   int k=b4.checkpress(x,y);
   if(x1==11){
    k=(i+1)%4;
   }
   if(k!=-1){
    b4.stk[i].bgc=TFT_WHITE;
    b4.stk[i].display();
    arr[i]=s;
    i=k;
    s=arr[i];
    b4.stk[i].bgc=TFT_BLUE;
    b4.stk[i].display();
   }
   int qwe=b3.checkpress(x,y);
   if(qwe==0){
    b4.stk[i].bgc=TFT_WHITE;
    return;
   }
   if(qwe==1){
    b4.stk[i].bgc=TFT_WHITE;
    break;
   }
   if(x1>=0 && x1<10){
    s=(10*s)+x1;
   }
   if(x1==10){
    s=s/10;
   }
   tft.fillRect(140,((57*i)+44),60,35,TFT_WHITE);
   tft.setCursor(140,((57*i)+44));
   tft.setTextColor(TFT_BLACK);
   tft.setTextSize(2);
   tft.println(String(s));
   arr[i]=s;
   delay(200);
 }
  oldtime.tm_year = arr[0]-1900;  // Year - 1900
  oldtime.tm_mon = arr[1]-1;             // Month (0 - 11)
  oldtime.tm_mday = arr[2];           // Day of the month (1 - 31)
  oldtime.tm_hour = arr[3];           // Hour (0 - 23)
  oldtime.tm_min = 0;            // Minutes (0 - 59)
  oldtime.tm_sec = 0;             // Seconds (0 - 59)
  time_t customTime = mktime(&oldtime);
  // Set the system time
  struct timeval tv = { .tv_sec = customTime };
  settimeofday(&tv, nullptr);
//  tm::setTime(arr[3],0,0,arr[2],arr[1],arr[0]);
 getLocalTime(&oldtime);
}