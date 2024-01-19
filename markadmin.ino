void markadmin(){  
  roll=keypad("MARK ATTENDANCE","ID Number");
  if(roll==-1){
    return;
  }
  write1();
}