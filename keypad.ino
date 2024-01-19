int keypad(String txt1,String txt2){
 tft.fillScreen(TFT_WHITE);
 b2.displayall();
 b3.displayall();
 uint16_t x,y;
 int x1=-1;
 int s=0;
 tft.setCursor(10,10); 
   tft.setTextColor(TFT_BLACK);
   tft.setTextSize(2);
   tft.println(txt1);
 tft.setCursor(10,70); 
   tft.setTextColor(TFT_BLACK);
   tft.setTextSize(2);
   tft.println(txt2+":");
 while(x1!=11){
   while(!Touched(false,&x,&y)){
   }
   x1=b2.checkpress(x,y);
   int qwe=b3.checkpress(x,y);
   if(qwe==0){
    return -1;
   }
   if(qwe==1){
    break;
   }
   if(x1>=0 && x1<10){
    s=(10*s)+x1;
   }
   if(x1==10){
    s=s/10;
   }
   tft.fillRect(10,100,200,100,TFT_WHITE);
   tft.setCursor(10,100);
   tft.setTextColor(TFT_BLACK);
   tft.setTextSize(2);
   tft.println(String(s));
   delay(200);
 }
 tft.fillScreen(TFT_WHITE);
 return s;
}