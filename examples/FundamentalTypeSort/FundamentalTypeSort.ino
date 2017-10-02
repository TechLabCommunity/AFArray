#include <AFArrayType.h>

AFAInt v1;
void setup(){
  Serial.begin(115200);
  randomSeed(analogRead(0));
  for (int i=0; i<6; i++){
    v1.add(random(0, 30));
  }
  for (int i=0; i<v1.size(); i++)
    Serial.print(String(v1[i])+" ");
  //Ascending sort.
  v1.asc_sort();
  Serial.println();
  for (int i=0; i<v1.size(); i++)
    Serial.print(String(v1[i])+" ");
}

void loop(){
  return;
}
