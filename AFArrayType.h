#ifndef AFARRAYTYPE_H
#define AFARRAYTYPE_H

#include "AFArrayBasicType.h"

class AFALong : public AFArrayBasicType<long>{

};

class AFAULong : public AFArrayBasicType<unsigned long>{

};

class AFAInt : public AFArrayBasicType<int>{

};

class AFAUInt : public AFArrayBasicType<unsigned int>{

};

class AFAFloat : public AFArrayBasicType<float>{

};

class AFADouble : public AFArrayBasicType<double>{

};

class AFAChar : public AFArrayBasicType<char>{

};

class AFArrayChar : public AFArrayBasicType<char*>{

};

#endif
