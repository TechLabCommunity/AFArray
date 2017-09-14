#ifndef AFArray_H
#define AFArray_H

#include "GenericIterator.h"

#define INIT_DIMENSION 20
#define MAX_LENGTH_ARRAY 160

template <typename T> class AFArray : public GenericIterator<T>{

  protected:

    T* arr;

    unsigned int n, real_len, index;

    void amortize();

    void init();

    void inline incr();

  public:

    //Constructors

    AFArray();

    AFArray(const AFArray<T>*);

    AFArray(const T*, const unsigned int);

    ~AFArray();

    //Some useful functions

    AFArray<unsigned int>& find(const T&);

    AFArray<T>& slice(const unsigned int, const unsigned int, const unsigned int = 1);

    const T* to_array(int * = -1);

    void add(const T&);

    void reset();

    unsigned int size();

    unsigned int n_occurrences (const T&);

    bool is_full();

    bool is_valid_index(const unsigned int);

    bool operator==(const AFArray<T>&);

    bool operator!=(const AFArray<T>&);

    //Generic Iterator

    bool has_next();

    const T& next();

    //Operator

    T& operator[](const unsigned int);

    AFArray<T>& operator=(const AFArray<T>&);

    AFArray<T>& operator+(const T&);

    AFArray<T>& operator+(const AFArray<T>&);

    AFArray<T>& operator+=(const T&);

    AFArray<T>& operator+=(const AFArray<T>&);

};

template <class T>
void AFArray<T>::init(){
  arr = new T[real_len = INIT_DIMENSION];
  n = 0;
  index = 0;
  GenericIterator<T>::index_iterator = 0;
}

template <class T>
void inline AFArray<T>::incr(){
  if (n > 0)
    index++;
  n++;
}

template <class T>
void AFArray<T>::amortize(){
  if (real_len == MAX_LENGTH_ARRAY)
    return;
  T copy_arr[real_len];
  for (unsigned int i=0; i<n; i++){
    copy_arr[i] = arr[i];
  }
  memset(arr, 0, real_len);
  if (real_len * 2 > MAX_LENGTH_ARRAY)
    real_len = MAX_LENGTH_ARRAY;
  else
    real_len *= 2;
  arr = new T[real_len];
  for (unsigned int i=0; i<n; i++){
    arr[i] = copy_arr[i];
  }
}

template <class T>
AFArray<T>::AFArray(){
  init();
}

template <class T>
AFArray<T>::AFArray(const AFArray<T>* acopy){
  (*this) = (*acopy);
}

template <class T>
AFArray<T>::AFArray(const T* acopy, const unsigned int len){
  init();
  for (unsigned int i=0; i<len; i++){
    add(acopy[i]);
  }
}

template <class T>
AFArray<T>::~AFArray(){
  delete[] arr;
}

template <class T>
void AFArray<T>::add(const T& el){
  if (index == real_len-1){
    amortize();
  }
  if (is_full())
    return;
  incr();
  arr[index] = el;
}

template <class T>
void AFArray<T>::reset(){
  delete[] arr;
  init();
}

template <class T>
unsigned int AFArray<T>::size(){
  return n;
}

template <class T>
unsigned int AFArray<T>::n_occurrences (const T& el){
  return find(el).size();
}

template <class T>
bool AFArray<T>::is_full(){
  return index == MAX_LENGTH_ARRAY-1;
}

template <class T>
AFArray<unsigned int>& AFArray<T>::find(const T& el){
  AFArray<unsigned int> index_list;
  for (unsigned int i=0; i<size(); i++){
    if (el == arr[i])
      index_list.add(i);
  }
  return index_list;
}

template <class T>
T& AFArray<T>::operator[](const unsigned int i){
  if (!is_valid_index(i))
    return;
  return arr[i];
}

template <class T>
AFArray<T>& AFArray<T>::slice(const unsigned int start, const unsigned int end, const unsigned int step){
  unsigned int _start = start, _end = end, _step = step;
  AFArray<T>* new_arr = new AFArray<T>();
  if (_end >= n)
    _end = n-1;
  if (n == 0 || _start >= _end)
    return *new_arr;
  for (unsigned int i=_start; i<=_end; i+=_step){
    new_arr->add(arr[i]);
  }
  return *new_arr;
}

template <class T>
AFArray<T>& AFArray<T>::operator=(const AFArray<T>& el){
  if (this != &el) {
    reset();
    for (unsigned int i=0; i<el.size(); i++){
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
  for (unsigned int i=0; i<el.size(); i++){
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
bool AFArray<T>::operator==(const AFArray<T>& el){
  if (size() != el.size())
    return false;
  for (int i=0; i<size(); i++){
    if (arr[i] != el[i]){
      return false;
    }
  }
  return true;
}

template <class T>
bool AFArray<T>::operator!=(const AFArray<T>& el){
  return !((*this) == el);
}

template <class T>
bool AFArray<T>::is_valid_index(const unsigned int i){
  return i < n;
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

template <class T>
const T* AFArray<T>::to_array(int *len){
  (*len) = 0;
  if (n == 0)
    return 0;
  T *temp = new T[n];
  (*len) = n;
  for (unsigned int i=0; i<n; i++){
    temp[i] = arr[i];
  }
  return temp;
}

#endif
