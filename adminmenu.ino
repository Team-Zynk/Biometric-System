void adminmenu(){            //Admin  Access Window
  tft.fillScreen(TFT_WHITE);
  printer("Welcome Admin",0,200,3,480,TFT_BLUE);
  drawSdJpeg("/config/admlogo.jpg", 176, 20);
  delay(1000);
  tft.fillScreen(TFT_WHITE);
  drawSdJpeg("/config/iitlogo.jpg", 80, 40);
  printer("Admin Access Window",0,10,3,480,TFT_BLUE);
  drawSdJpeg("/config/exlogo.jpg", 445, 0);
  b1.displayall();
  uint16_t x,y; //Coordinates to detect touch position;
  int x1=-1;
  while(true){
   while(!Touched(false,&x,&y)){
   }
   x1=b1.checkpress(x,y);
   if(x>412 && x<480 && y<48 && y>0){
    break;
   }
   if(x1==0){
    if(roll!=127){
      tft.fillScreen(TFT_WHITE);
      printer("Access Denied",40,10,3,460,TFT_RED);
      printer("Only for super admin",40,60,3,460,TFT_RED);
      delay(2000);
      break;
    }else{
      markadmin();    //Mark arbitrary attendance
      break;
    }
   }else if(x1==1){
      readadmin();    //Read attendance
      break;
   }else if(x1==2){
      saver();         //Save attendance file for total attendance
      break;
   }else if(x1==3){
      if(roll!=127){
      tft.fillScreen(TFT_WHITE);
      printer("Access Denied",40,10,3,460,TFT_BLUE);
      printer("Only for super admin",40,60,3,460,TFT_RED);
      delay(2000);
      break;
    }else{
      appoint();        //Appoint admin
      break;
    }
   }else if(x1==4){    //Enroll finger print
      enroll();
      break;
   }else if(x1==5){    //Enroll finger print
    if(roll!=127){
      tft.fillScreen(TFT_WHITE);
      printer("Access Denied",40,10,3,460,TFT_RED);
      printer("Only for super admin",40,60,3,460,TFT_RED);
      delay(2000);
      break;
    }else{
      reset();    //Mark arbitrary attendance
      break;
    }
   }
 }
}