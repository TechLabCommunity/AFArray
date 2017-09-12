#include <AFArray.h>

AFArray<int> v1, v2, v3, concat;
void setup(){
  Serial.begin(115200);
  for (int i=0; i<20; i++){
    v1.add(i);
  }
  for (int i=50; i<60; i++){
    v2.add(i);
  }
  for (int i=100; i<120; i++){
    v3.add(i);
  }
  concat = v1 + v2 + v3;
  for (int i=0; i<concat.size(); i++){
    Serial.println(concat[i]);
  }
}

void loop(){
  return;
}
