void adminmenu(){            //Admin  Access Window
  tft.fillScreen(TFT_WHITE);
  drawSdJpeg("/iitlogo.jpg", 80, 40);
  printer("Admin Access Window",0,10,3,480,TFT_BLUE);
  b1.displayall();
  uint16_t x,y; //Coordinates to detect touch position;
  int x1=-1;
  while(x1!=5){
   while(!Touched(true,&x,&y)){
   }
   x1=b1.checkpress(x,y);
   if(x1==0){
    if(roll!=127){
      tft.fillScreen(TFT_WHITE);
      printer("Access Denied",40,10,3,460,TFT_BLUE);
      printer("Only for super admin",40,10,3,460,TFT_RED);
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
<<<<<<< HEAD
      saver();         //Save attendance file for total attendance
=======
      saver(10);
>>>>>>> 3c9927ecdcafde93107bdd4d27b06edbafaa19dd
      break;
   }else if(x1==3){
      if(roll!=127){
      tft.fillScreen(TFT_WHITE);
      printer("Access Denied",40,10,3,460,TFT_BLUE);
      printer("Only for super admin",40,10,3,460,TFT_RED);
      delay(2000);
      break;
    }else{
      appoint();        //Appoint admin
      break;
    }
   }else if(x1==4){    //Enroll finger print
      enroll();
      break;
   }
 }
}