#ifndef SAMPLE2_H
#define SAMPLE2_H

#include <Vector2.h>
#include <RNG.h>

// This is the base class for all sampling strategies over two dimensions.

class Sample2 {
public:
  virtual int generate(Vector2*) = 0;
};


class JitterSample2 : public Sample2 {
public:
   JitterSample2(int m, int n);
   virtual int generate(Vector2*);
   int m, n;
   RNG* random; 
};

class HamSample2 : public Sample2 {
public:
   HamSample2(int num);
   virtual int generate(Vector2*);
   int n;
   RNG* random; 
};

#endif
