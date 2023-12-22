void readadmin(){
  tft.fillScreen(TFT_BLUE);
  tft.setCursor(40,10);
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  tft.println(F("Input the ID"));
  tft.setCursor(40,60);
  tft.println("On Keypad");
  delay(2000);
  roll=keypad();
  read1();
}