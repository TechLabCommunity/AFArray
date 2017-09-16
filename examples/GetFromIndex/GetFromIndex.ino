#include <AFArray.h>

AFArray<String> list_phrase;

void setup(){
  Serial.begin(115200);
  for (int i=0; i<7; i++){
    list_phrase.add("Sent "+String(i));
  }
  unsigned int a[5] = {10, 2, 3, 5, 4};
  AFArray<String> part = list_phrase.get_from_indexes(a, 5);
  while(part.has_next()){
    Serial.println(part.next());
  }

}

void loop(){
  return;
}
