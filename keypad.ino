int keypad(){
 tft.fillScreen(TFT_WHITE);
 b2.displayall();
 uint16_t x,y;
 int x1=-1;
 int s=0;
 tft.setCursor(10,60); 
   tft.setTextColor(TFT_BLACK);
   tft.setTextSize(2);
   tft.println("Entered number:");
 while(x1!=11){
   while(!Touched(true,&x,&y)){
   }
   x1=b2.checkpress(x,y);
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
 return s;
}