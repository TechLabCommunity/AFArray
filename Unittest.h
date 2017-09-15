#include <Arduino.h>

class Unittest{

  private:

    void inline printTest(unsigned int);

  public:

    Unittest();

    void areEqual(unsigned int, bool, bool = false);

    void areNotEqual(unsigned int, bool, bool = false);

};

void inline Unittest::printTest(unsigned int id){
  Serial.print("Test "+String(id)+": ");
}

Unittest::Unittest(){

}

void Unittest::areEqual(unsigned int id, bool cond, bool block){
  printTest(id);
  if (!cond){
    Serial.println("failed.");
    if (block){
      Serial.println("You need to solve it.");
      while(1){}
    }
  }else{
    Serial.println("OK");
  }
}

void Unittest::areNotEqual(unsigned int id, bool cond, bool block){
  areEqual(id, !cond, block);
}
