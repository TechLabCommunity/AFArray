#ifndef AFARRAYEXTENDED_H
#define AFARRAYEXTENDED_H

#include "AFArray.h"

template <typename T> class AFArrayExtended : public AFArray<T>{

  public:

    AFArray<unsigned int>& find(const T);

    bool add(T);

    bool set(const unsigned int, T);

    unsigned int n_occurrences (T);

    AFArray<T>& operator=(AFArray<T>);

    AFArray<T>& operator+(T);

    AFArray<T>& operator+=(T);



};


template <class T>
AFArray<unsigned int>& AFArrayExtended<T>::find(const T el){
  return AFArray<T>::find(el);
}

template <class T>
bool AFArrayExtended<T>::add(T el){
  return AFArray<T>::add(el);
}

template <class T>
bool AFArrayExtended<T>::set(const unsigned int index, const T el){
  return AFArray<T>::set(index, el);
}

template <class T>
unsigned int AFArrayExtended<T>::n_occurrences(T el){
  return AFArray<T>::n_occurrences(el);
}

template <class T>
AFArray<T>& AFArrayExtended<T>::operator=(AFArray<T> el){
  if (this != &el) {
    AFArray<T>::reset();
    for (unsigned int i=0; i<el.size(); i++){
      add(el[i]);
    }
  }
  return *this;
}

template <class T>
AFArray<T>& AFArrayExtended<T>::operator+(T el){
  add(el);
  return *this;
}

template <class T>
AFArray<T>& AFArrayExtended<T>::operator+=(T el){
  (*this) = (*this) + el;
  return *this;
}

#endif
