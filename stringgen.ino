String stringgen(int x){
  String ans="";
  while(x!=0){
    ans=String((char(((x-1)%26)+'A')))+ans;
    x=(x-1)/26;
  }
  return ans;
}