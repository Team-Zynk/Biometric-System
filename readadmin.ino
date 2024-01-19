void readadmin(){
  
  roll=keypad("READ ATTENDANCE","ID Number");
  if(roll==-1){
    return;
  }
  read1();
}