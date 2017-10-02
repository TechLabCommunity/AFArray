#include <AFArrayType.h>

AFAString v1;
void setup(){
  Serial.begin(115200);
  String s = "this,is,an,amazing,function!";
  v1 = AFAString::explode(',', s);
  //print separated elements.
  while(v1.has_next())
    Serial.print(v1.next()+" ");
  //rejoin string.
  Serial.println();
  String sr = v1.implode(',');
  Serial.println(sr);
}

void loop(){
  return;
}
