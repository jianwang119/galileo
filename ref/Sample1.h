
#ifndef _SAMPLE1_H_
#define _SAMPLE1_H_ 1

#include <RNG.h>

class Sample1 
{
public:
   virtual int generate(float* samples) = 0;
};

class JitterSample1 : public Sample1
{
public:
   JitterSample1(int _ns);
   virtual int generate(float* samples);
   int ns;
   RNG* random;
};

#endif // _SAMPLE1_H_
