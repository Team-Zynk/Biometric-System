void readadmin(){
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(40,10);
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLUE);
  tft.println(F("Type ID number"));
  tft.setCursor(40,60);
  tft.println("On Keypad");
  delay(2000);
  roll=keypad();
  read1();
}