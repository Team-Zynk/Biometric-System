bool Touched(boolean showTouch,uint16_t *x,uint16_t *y) {
    
    TSPoint p = ts.getPoint();
    pinMode(33, OUTPUT);      //restore shared pins
    pinMode(32, OUTPUT);
    digitalWrite(33, HIGH);   //because TFT control pins
    digitalWrite(32, HIGH);
    bool pressed = (p.z > 200 && p.z < 20000);
    if (pressed) {
          *x = map(p.y, coords[1], coords[0], 0, tft.width()); 
          *y = map(p.x, coords[2], coords[3], 0, tft.height()); 
    if (showTouch) tft.fillCircle(*x, *y, 2, TFT_WHITE);
      return true;
    }
    return false;
}