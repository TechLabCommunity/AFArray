#include <AFArray.h>

AFArray<int> v1;
void setup(){
  Serial.begin(115200);
  //You can use operator.
  v1 += 4;
  v1 += 6;
  v1 += 4;
  v1 += 4;
  v1 += 0;
  v1 += 1;
  //Find all 4 in array.
  AFArray<unsigned int> result = v1.find(4);
  //Show all indexes.
  while (result.has_next())
    Serial.println(result.next());
  Serial.println();
}

void loop(){
  return;
}
