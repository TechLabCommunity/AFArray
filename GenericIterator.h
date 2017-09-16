#ifndef GENERICITERATOR_H
#define GENERICITERATOR_H

template <typename T> class GenericIterator{

  protected:

    unsigned long index_iterator = 0;

  public:

    virtual bool has_next();

    virtual T& next();

};

#endif
