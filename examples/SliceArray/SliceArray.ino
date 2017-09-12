#include <AFArray.h>

AFArray<int> v1, v2;
void setup(){
  Serial.begin(115200);
  for (int i=0; i<100; i++){
    v1 += i;
  }
  //Take all elements from 10 to 30 included with step 2.
  v2 = v1.slice(10, 30, 2);
  for (int i=0; i<v2.size(); i++){
    Serial.println(String(v2[i])+" ");
  }
  Serial.println();
}

void loop(){
  return;
}
