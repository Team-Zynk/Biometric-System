void adminmenu(){
  tft.fillScreen(TFT_WHITE);
  drawSdJpeg("/iitlogo.jpg", 80, 40);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_BLUE);  tft.setTextSize(3);
  tft.setCursor((480-tft.textWidth("Admin Access Window"))/2,0);
  tft.println("Admin Access Window");
  b1.displayall();
  uint16_t x,y;
 int x1=-1;
 int s=0;
 while(x1!=5){
   while(!Touched(true,&x,&y)){
   }
   x1=b1.checkpress(x,y);
   if(x1==0){
    if(roll!=127){
      tft.fillScreen(TFT_WHITE);
      tft.setTextColor(TFT_RED);
      tft.setTextSize(3);
      tft.setCursor(70,50);
      tft.println("ACCESS DENIED");
      tft.setCursor(20,120);
      tft.println("Only for Super Admin");
      delay(2000);
      break;
    }else{
      markadmin();
      break;
    }
   }else if(x1==1){
      readadmin();
      
      break;
   }else if(x1==2){
      saver(10);
      break;
   }else if(x1==3){
      if(roll!=127){
      tft.fillScreen(TFT_WHITE);
      tft.setTextColor(TFT_RED);
      tft.setTextSize(3);
      tft.setCursor(50,50);
      tft.println("ACCESS DENIED");
      tft.setCursor(20,120);
      tft.println("Only for Super Admin");
      delay(2000);
      break;
    }else{
      appoint();
      break;
    }
   }else if(x1==4){
      enroll();
      break;
   }
 }
}