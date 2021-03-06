#ifndef AFARRAYTYPE_H
#define AFARRAYTYPE_H

#include <Arduino.h>
#include "AFArray.h"

class AFALong : public AFArraySortable<long>{

  public:

    AFALong& operator=(AFArray<long>&);

};

AFALong& AFALong::operator=(AFArray<long>& el){
  AFArray<long>::operator=(el);
  return *this;
}

class AFAULong : public AFArraySortable<unsigned long>{

  public:

    AFAULong& operator=(AFArray<unsigned long>&);

};

AFAULong& AFAULong::operator=(AFArray<unsigned long>& el){
  AFArray<unsigned long>::operator=(el);
  return *this;
}

class AFAInt : public AFArraySortable<int>{

  public:

    AFAInt& operator=(AFArray<int>&);

};

AFAInt& AFAInt::operator=(AFArray<int>& el){
  AFArray<int>::operator=(el);
  return *this;
}

class AFAUInt : public AFArraySortable<unsigned int>{

    public:

      AFAUInt& operator=(AFArray<unsigned int>&);

};

AFAUInt& AFAUInt::operator=(AFArray<unsigned int>& el){
  AFArray<unsigned int>::operator=(el);
  return *this;
}

class AFAFloat : public AFArraySortable<float>{

  public:

    AFAFloat& operator=(AFArray<float>&);

};

AFAFloat& AFAFloat::operator=(AFArray<float>& el){
  AFArray<float>::operator=(el);
  return *this;
}

class AFADouble : public AFArraySortable<double>{

  public:

    AFADouble& operator=(AFArray<double>&);

};

AFADouble& AFADouble::operator=(AFArray<double>& el){
  AFArray<double>::operator=(el);
  return *this;
}

class AFAChar : public AFArraySortable<char>{

  public:

    AFAChar& operator=(AFArray<char>&);

};

AFAChar& AFAChar::operator=(AFArray<char>& el){
  AFArray<char>::operator=(el);
  return *this;
}


class AFAString : public AFArraySortable<String>{

  public:

    static AFAString& explode(const String&, const String&);

    static AFAString& explode(const char, const String&);

    static AFAString& explode(const char*, const String&);

    static String implode(const String&, AFAString&);

    static String implode(const char, AFAString&);

    static String implode(const char*, AFAString&);

    String implode(const String&);

    String implode(const char);

    String implode(const char*);

    AFAString& operator=(AFArray<String>&);

};

AFAString& AFAString::explode(const String& delimiter, const String& s){
  AFAString* explosion = new AFAString;
  String group_set = "";
  unsigned int length = s.length(), length_del = delimiter.length(), i = 0;
  bool is_del = false;
  while(i < s.length()){
    if (i+length_del-1 < length){ // delimiter?
      unsigned int j = i, k = 0;
      is_del = true;
      while (k < length_del){
        if (delimiter[k] != s[j]){
          is_del = false;
          break;
        }
        j++;
        k++;
      }//while
      if (is_del){
        explosion->add(group_set);
        group_set = "";
        i = i+length_del;
        if (i >= length)
          break;
        is_del = false;
      }
    }//if
    group_set += s[i];
    i++;
  }//while
  if (group_set.length() > 0 || is_del)
    explosion->add(group_set);
  return *explosion;
}

AFAString& AFAString::explode(const char delimiter, const String& s){
  return AFAString::explode(String(delimiter), s);
}

AFAString& AFAString::explode(const char* delimiter, const String& s){
  return AFAString::explode(String(delimiter), s);
}

String AFAString::implode(const String& glue, AFAString& list){
  if (list.size() == 0)
    return "";
  String glued = list[0];
  for (unsigned int i=1; i<list.size(); i++){
    glued += (glue + list[i]);
  }
  return glued;
}

String AFAString::implode(const char delimiter, AFAString& s){
  return AFAString::implode(String(delimiter), s);
}

String AFAString::implode(const char* delimiter, AFAString& s){
  return AFAString::implode(String(delimiter), s);
}

String AFAString::implode(const String& delimiter){
  return AFAString::implode(delimiter, *this);
}

String AFAString::implode(const char delimiter){
  return AFAString::implode(String(delimiter));
}

String AFAString::implode(const char* delimiter){
  return AFAString::implode(String(delimiter));
}

AFAString& AFAString::operator=(AFArray<String>& el){
  AFArray<String>::operator=(el);
  return *this;
}

#endif
