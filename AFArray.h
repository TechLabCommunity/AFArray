#ifndef AFArray_H
#define AFArray_H

#include "GenericIterator.h"

#define INIT_DIMENSION 20
#define MAX_LENGTH_ARRAY 160

template <typename T> class AFArray : public GenericIterator<T>{

  protected:

    T* arr;

    uint32_t n, real_len, index;

    void amortize();

    void init();

  public:

    AFArray();

    AFArray(const AFArray<T>*);

    ~AFArray();

    void add(const T&);

    void reset();

    uint32_t size();

    bool is_full();

    bool is_valid_index(uint32_t);

    const T& operator[](uint32_t);

    AFArray<uint32_t>& find(T&);

    AFArray<T>& slice(uint32_t, uint32_t, uint32_t = 1);

    AFArray<T>& operator=(const AFArray<T>&);

    AFArray<T>& operator+(const T&);

    AFArray<T>& operator+(const AFArray<T>&);

    AFArray<T>& operator+=(const T&);

    AFArray<T>& operator+=(const AFArray<T>&);

    bool has_next();

    const T& next();


};

template <class T>
void AFArray<T>:: init(){
  arr = new T[real_len = INIT_DIMENSION];
  n = 0;
  index = -1;
  GenericIterator<T>::index_iterator = 0;
}

template <class T>
void AFArray<T>::amortize(){
  T copy_arr[real_len];
  for (uint32_t i=0; i<n; i++){
    copy_arr[i] = arr[i];
  }
  memset(arr, 0, real_len);
  if (real_len * 2 > MAX_LENGTH_ARRAY)
    real_len = MAX_LENGTH_ARRAY;
  else
    real_len += INIT_DIMENSION;
  arr = new T[real_len];
  for (uint32_t i=0; i<n; i++){
    arr[i] = copy_arr[i];
  }
}

template <class T>
AFArray<T>::AFArray(){
  init();
}

template <class T>
AFArray<T>::AFArray(const AFArray<T>* acopy){
  arr = 0;
  arr = new T[real_len = acopy->size()*2];
  for (uint32_t i=0; i<acopy->size(); i++){
    arr[i] = acopy[i];
  }
  index = acopy->size()-1;
  n = acopy->size();
}

template <class T>
AFArray<T>::~AFArray(){
  delete[] arr;
}

template <class T>
void AFArray<T>::add(const T& el){
  if (is_full())
    return;
  if (index == real_len-1){
    amortize();
  }
  index++;
  n++;
  arr[index] = el;
}

template <class T>
void AFArray<T>::reset(){
  delete[] arr;
  init();
}

template <class T>
uint32_t AFArray<T>::size(){
  return n;
}

template <class T>
bool AFArray<T>::is_full(){
  return index == MAX_LENGTH_ARRAY-1;
}

template <class T>
AFArray<uint32_t>& AFArray<T>::find(T& el){
  AFArray<uint32_t>* index_list = new AFArray<uint32_t>();
  for (uint32_t i=0; i<size(); i++){
    if (el == arr[i])
      index_list->add(i);
  }
  return index_list;
}

template <class T>
const T& AFArray<T>::operator[](uint32_t i){
  return arr[i];
}

template <class T>
AFArray<T>& AFArray<T>::slice(uint32_t start, uint32_t end, uint32_t step){
  AFArray<T>* new_arr = new AFArray<T>();
  if (end >= n)
    end = n-1;
  for (uint32_t i=start; i<=end; i+=step){
    new_arr->add(arr[i]);
  }
  return *new_arr;
}

template <class T>
AFArray<T>& AFArray<T>::operator=(const AFArray<T>& el){
  if (this != &el) {
    reset();
    for (uint32_t i=0; i<el.size(); i++){
      add(el[i]);
    }
  }
  return *this;
}

template <class T>
AFArray<T>& AFArray<T>::operator+(const T& el){
  add(el);
  return *this;
}

template <class T>
AFArray<T>& AFArray<T>::operator+(const AFArray<T>& el){
  for (uint32_t i=0; i<el.size(); i++){
    add(el[i]);
  }
  return *this;
}

template <class T>
AFArray<T>& AFArray<T>::operator+=(const AFArray<T>& el){
  (*this) = (*this) + el;
  return *this;
}

template <class T>
AFArray<T>& AFArray<T>::operator+=(const T& el){
  (*this) = (*this) + el;
  return *this;
}

template <class T>
bool AFArray<T>::is_valid_index(uint32_t i){
  return i >= n;
}

template <class T>
bool AFArray<T>::has_next(){
  if (GenericIterator<T>::index_iterator >= n){
    GenericIterator<T>::index_iterator = 0;
    return false;
  }
  return true;
}

template <class T>
const T& AFArray<T>::next(){
  return arr[GenericIterator<T>::index_iterator++];
}


#endif
