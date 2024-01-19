bool confirmation(String txt){
  tft.fillScreen(TFT_WHITE);
  
  printer("Are You Sure?",112,40,3,256,TFT_BLUE);
  printer(txt,112,110,3,256,TFT_BLUE);
  b5.displayall();
  uint16_t x,y;
  while(true){
  while(!Touched(false,&x,&y)){
  }
  int x1=b5.checkpress(x,y);
  if(x1==0){
    return false;
  }else if(x1==1){
    return true;
  }
  }
}