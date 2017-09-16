#ifndef AFARRAYTYPE_H
#define AFARRAYTYPE_H

#include "AFArrayExtended.h"

class AFALong : public AFArrayExtended<long>{

};

class AFAULong : public AFArrayExtended<unsigned long>{

};

class AFAInt : public AFArrayExtended<int>{

};

class AFAUInt : public AFArrayExtended<unsigned int>{

};

class AFAFloat : public AFArrayExtended<float>{

};

class AFADouble : public AFArrayExtended<double>{

};

class AFAChar : public AFArrayExtended<char>{

};

class AFArrayChar : public AFArrayExtended<char*>{

};

#endif
