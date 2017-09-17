# AFArray

Simple Array Structure for Arduino Framework with template.

**Version 0.1.1**

## Road To Version 0.2

In next version, fundamental type will be implemented with extended methods.

```C++
AFAString list_string;
AFAString exploded = list_string.explode("||", "Hi||I'm||so||happy!");
while(exploded.has_next()){
  Serial.println(exploded.next()); // [Hi, I'm, so, happy!]
}
```

## Compatibility

Tested with ATmega328p, ESP32, ESP8266.

## Declare and initialize

With AFArray is very simple to initialize:
```C++
AFArray<int> v1;
```
As you can see from Header, there are some copy contructors too.
Comparing operator == and != are implemented.
```C++
if (v1 == v2)
  Serial.println("This two AFArray are equal!");
```

## Adding elements
AFArray has only one method to insert an element in tail.

```C++
v1.add(3);
v1.add(6);
v1.add(9);
Serial.println("Size : "+v1.size()); // Size : 3
```
**Note:** if element is inserted, _add_ method will return true, otherwise false. This could happen when AFArray reaches maximum size (MAX_LENGTH_ARRAY).
To check it, use _is_full_ method. 

AFArray has many overrided operators, add method could be replace by:

```C++
v1 += 9;
v1 = v1 + 100;
```
operators are overrided for AFArray too.
```C++
AFArray<int> v2;
AFArray<int> v3;
//...Add elements in v2 and v3
AFArray<int> v4 = v3 + v2;
```
## Accessing elements

AFarray ovverides [] operator. So

```C++
int a = v1[10];
```

is correct. But, if you aren't sure if an index exists, use _is_valid_index_ method before:

```C++
int a;
if (v1.is_valid_index(10))
  a = v1[10];
```

In the same way, you can set values:

```C++
if (v1.is_valid_index(10))
  v1[10] = -4;
```
If you don't want to waste your time, _set_ method fit the bill :ok_hand: :

```C++
if (v1.set(10, -4))
  Serial.println("-4 has inserted.");
```

## Useful methods

### find and n_occurrences

If your type has overrided compare operator ==, _find(x)_ returns an _AFArray<unsgined int>_ that contains all indexes where x is in. _n_occurrences_
returns only number of occurrences.

```C++
  v1.add(3);
  v1.add(-3);
  v1.add(0);
  v1.add(3);
  v1.add(10);
  AFArray<unsigned int> list_indexes = v1.find(3); //list_indexes has [0, 3] elements.
  Serial.println(v1.n_occurrences(3)); //Prints "2".
```

### slice

Sometimes, you need a part of a list with a specific step. _slice_ method returns an AFArray<T> with all elements from start index to end one
with a step (default = 1).


```C++
  v1.add(2);
  v1.add(1);
  v1.add(10);
  v1.add(-4);
  v1.add(12);
  v1.add(6);
  AFArray<int> part = v1.slice(1, 5, 2); //1, -4, 6.
```
### reset
_reset_() method destroy object and recreate it.


### to_array

AFArray could be converted into array with template type.

```C++
  v1.add(2);
  v1.add(1);
  v1.add(10);
  int n;
  int *arr = v1.to_array(&n);
```

## Generic iterator (experimental)

AFArray inherits GenericIterator, a very stupid iterator.

```C++
  while (v1.has_next())
    Serial.println(v1.next());
```
When while cycle exits, you can iterate it again.
