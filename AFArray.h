#ifndef AFARRAY_H
#define AFARRAY_H

#define INIT_DIMENSION 20

template <typename T> class GenericIterator{

  protected:

    unsigned long index_iterator = 0;

  public:

    virtual bool has_next();

    virtual T& next();

};

template <typename T> class AFArray : public GenericIterator<T>{

  private:

    static unsigned int MAX_LENGTH_ARRAY;

  protected:

    T* arr;

    unsigned int n, real_len, index;

    void amortize();

    void init();

    void inline incr();

    void reverse(T*, unsigned int, unsigned int);

  public:

    //Constructors

    AFArray();

    AFArray(const AFArray<T>*);

    AFArray(const T*, const unsigned int);

    ~AFArray();

    //Some useful functions

    AFArray<unsigned int>& find(const T);

    AFArray<T>& slice(const unsigned int, const unsigned int, const unsigned int = 1);

    T* to_array(int * = -1);

    bool add(const T);

    bool set(const unsigned int, const T);

    AFArray<T>& get_from_indexes(AFArray<unsigned int>&);

    AFArray<T>& get_from_indexes(const unsigned int*, unsigned int);

    void reset();

    void reverse();

    unsigned int size();

    unsigned int n_occurrences (const T);

    bool is_full();

    bool is_valid_index(const unsigned int);

    bool remove_from_index(const unsigned int);

    //Generic Iterator

    bool has_next();

    T& next();

    //Operator

    T& operator[](const unsigned int);

    AFArray<T>& operator=(AFArray<T>&);

    AFArray<T>& operator+(const T);

    AFArray<T>& operator+(AFArray<T>&);

    AFArray<T>& operator+=(const T);

    AFArray<T>& operator+=(AFArray<T>&);

    bool operator==(AFArray<T>&);

    bool operator!=(AFArray<T>&);

};


template <typename T> class AFArraySortable  : public AFArray<T>{

  private:

    void sort(AFArray<T>&, unsigned int, unsigned int);

  public:

    void asc_sort();

    void desc_sort();

};

template <class T>
void AFArraySortable<T>::sort(AFArray<T>& arr, unsigned int left, unsigned int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
      if (left < j)
            sort(arr, left, j);
      if (i < right)
            sort(arr, i, right);
}

template <class T>
void AFArraySortable<T>::asc_sort(){
  if (this->n > 1)
    sort(*this, 0, this->n-1);
}

template <class T>
void AFArraySortable<T>::desc_sort(){
  asc_sort();
  AFArray<T>::reverse();
}

template <class T>
unsigned int AFArray<T>::MAX_LENGTH_ARRAY = 150;

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
AFArray<T>& AFArray<T>::get_from_indexes(AFArray<unsigned int>& list_index){
  AFArray<T>* ret = new AFArray<T>;
  if (list_index.size() == 0 || size() == 0)
    return *ret;
  while(list_index.has_next()){
    unsigned int i = list_index.next();
    if (is_valid_index(i))
      ret->add(arr[i]);
  }
  return *ret;
}

template <class T>
AFArray<T>& AFArray<T>::get_from_indexes(const unsigned int *arr, unsigned int len){
  AFArray<unsigned int> to_pass (arr, len);
  return get_from_indexes(to_pass);
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
bool AFArray<T>::add(T el){
  if (index == real_len-1){
    amortize();
  }
  if (is_full())
    return false;
  incr();
  arr[index] = el;
  return true;
}

template <class T>
bool AFArray<T>::set(const unsigned int index, const T el){
  if (!is_valid_index(index))
    return false;
  arr[index] = el;
  return true;
}

template <class T>
void AFArray<T>::reset(){
  delete[] arr;
  init();
}

template <class T>
void AFArray<T>::reverse(T* arr, unsigned int left, unsigned int right){
  if (left < right){
    T temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
    reverse(arr, ++left, --right);
  }
}

template <class T>
void AFArray<T>::reverse(){
  if (n > 1)
    reverse(arr, 0, n-1);
}

template <class T>
unsigned int AFArray<T>::size(){
  return n;
}

template <class T>
unsigned int AFArray<T>::n_occurrences (const T el){
  return find(el).size();
}

template <class T>
bool AFArray<T>::is_full(){
  return index == MAX_LENGTH_ARRAY-1;
}

template <class T>
AFArray<unsigned int>& AFArray<T>::find(const T el){
  AFArray<unsigned int> index_list;
  for (unsigned int i=0; i<size(); i++){
    if (el == arr[i])
      index_list.add(i);
  }
  return index_list;
}

template <class T>
T& AFArray<T>::operator[](const unsigned int i){
  return arr[i];
}

template <class T>
AFArray<T>& AFArray<T>::slice(const unsigned int start, const unsigned int end, const unsigned int step){
  unsigned int _start = start, _end = end, _step = step;
  AFArray<T>* new_arr = new AFArray<T>();
  if (_end >= n)
    _end = n-1;
  if (n == 0 || _start >= _end || _step == 0)
    return *new_arr;
  for (unsigned int i=_start; i<=_end; i+=_step){
    new_arr->add(arr[i]);
  }
  return *new_arr;
}

template <class T>
AFArray<T>& AFArray<T>::operator=(AFArray<T>& el){
  if (this != &el) {
    reset();
    for (unsigned int i=0; i<el.size(); i++){
      add(el[i]);
    }
  }
  return *this;
}

template <class T>
AFArray<T>& AFArray<T>::operator+(const T el){
  add(el);
  return *this;
}

template <class T>
AFArray<T>& AFArray<T>::operator+(AFArray<T>& el){
  for (unsigned int i=0; i<el.size(); i++){
    add(el[i]);
  }
  return *this;
}

template <class T>
AFArray<T>& AFArray<T>::operator+=(AFArray<T>& el){
  (*this) = (*this) + el;
  return *this;
}

template <class T>
AFArray<T>& AFArray<T>::operator+=(const T el){
  (*this) = (*this) + el;
  return *this;
}

template <class T>
bool AFArray<T>::operator==(AFArray<T>& el){
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
bool AFArray<T>::operator!=(AFArray<T>& el){
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
bool AFArray<T>::remove_from_index(const unsigned int index){
  if (!is_valid_index(index)){
    return false;
  }
  AFArray<T>* temp = new AFArray<T>();
  for (unsigned int i=0; i<size(); i++){
    if (i!=index){
      temp->add(arr[i]);
    }
  }
  arr = temp;
  return true;
}

template <class T>
T& AFArray<T>::next(){
  return arr[GenericIterator<T>::index_iterator++];
}

template <class T>
T* AFArray<T>::to_array(int *len){
  T *buffer = new T[n];
  (*len) = 0;
  if (n == 0)
    return buffer;
  (*len) = n;
  for (unsigned int i=0; i<n; i++){
    buffer[i] = arr[i];
  }
  return buffer;
}

#endif
