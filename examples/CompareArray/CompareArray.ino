#include <AFArray.h>

AFArray<String> v1, v2, v3;

void setup(){
  Serial.begin(115200);
  //Add some elements.
  v1.add("Sentence 1");
  v1.add("Sentence 2");
  v1.add("Sentence 3");
  v1.add("Sentence 4");
  v1.add("Sentence 5");
  //Printing elements with for cycle.
  v2 = v1;
  v3 = v1.slice(2, 5);
  //v2 and v1 have same elements?
  if (v2 == v1)
    Serial.println("v2 and v1 are equal!");
  if (v3 != v1)
    Serial.println("v2 and v1 are not equal!");
}

void loop(){
  return;
}
