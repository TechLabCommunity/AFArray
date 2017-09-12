#include <AFArray.h>

AFArray<String> v1;

void setup(){
  Serial.begin(115200);
  //Add some elements.
  v1.add("Sentence 1");
  v1.add("Sentence 2");
  v1.add("Sentence 3");
  v1.add("Sentence 4");
  v1.add("Sentence 5");
  //Printing elements with for cycle.
  for (int i=0; i<v1.size(); i++){
    Serial.println(v1[i]);
  }
  delay(1000);
  Serial.println();
  //Printing elements with iterator.
  while (v1.has_next()){
    Serial.println(v1.next());
  }
  Serial.println();
}

void loop(){
  return;
}
