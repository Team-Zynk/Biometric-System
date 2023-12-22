void month(){
  File myfile;
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(3);
  tft.print(F("Enter month"));
  delay(1000);
  int m=keypad();
  tft.setCursor(240,20);
  tft.println(m);
  tft.setCursor(40,60);
  tft.print(F("Enter year"));
  delay(1000);
  int y=keypad();
  tft.setCursor(240,60);
  tft.println(y);
  String fileName = "/"+String(y) + String(m) + "read.txt";
  if(SD.exists(fileName)){
    SD.remove(fileName);
  }
  myfile=SD.open(fileName,FILE_APPEND);
  myfile.print("Roll Number");
  myfile.print(",");
  myfile.print("DAYS ATTENDED");
  myfile.println();
  finger.getTemplateCount();
  delay(1000);
  for (uint8_t x = 1; x<=(finger.templateCount+1); x++)
  {   myfile.print(x);
      myfile.print(",");
      roll=x;
      int d=read2(m,y);
      myfile.print(d);
      myfile.println();
  }
  myfile.close();
  tft.setCursor(40,120);
  tft.println("File Saved");
  delay(1000);
}

void year(){
  File myfile;
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(3);
  tft.print(F("Enter year"));
  delay(1000);
  int y=keypad();
  tft.setCursor(240,20);
  tft.println(y);
  String fileName = "/"+String(y)+"read"+ ".txt";
  if(SD.exists(fileName)){
    SD.remove(fileName);
  }
  myfile=SD.open(fileName,FILE_APPEND);
  myfile.print("Roll Number");
  myfile.print(",");
  myfile.print("DAYS ATTENDED");
  myfile.println();
  finger.getTemplateCount();
  delay(1000);
  for (uint8_t x = 1; x<=(finger.templateCount+1); x++)
  {   myfile.print(x);
      myfile.print(",");
      roll=x;
      int d=read3(y);
      myfile.print(d);
      myfile.println();
  }
  myfile.close();
  tft.setCursor(40,120);
  tft.println("File Saved");
  delay(1000);
}



void save(){
//   tft.fillScreen(TFT_WHITE);
//   b3.displayall();
//   uint16_t x,y;
//  int x1=-1;
//  int s=0;
//  while(x1!=2){
//    while(!Touched(true,&x,&y)){
//    }
//    x1=b3.checkpress(x,y);
//    if(x1==0){
//     month();
//     break;
//    }else if(x1==1){
//     year();
//     break;
//    }
// }
   saver(10);
}

