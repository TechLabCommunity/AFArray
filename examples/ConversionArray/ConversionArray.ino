#include <AFArray.h>

void setup(){
  Serial.begin(115200);
  AFArray<int> v1;
  int *a;
  int n;
  for (int i=0; i<100; i++){
    v1 += random(0,100);
  }
  //get array from AFArray!
  a = v1.to_array(&n);
  for (int i=0; i<n; i++){
    Serial.println(a[i]);
  }
}

void loop(){
  return;
}
