
#include <Sample1.h>
#include <sys/time.h>
#include <unistd.h>

JitterSample1::JitterSample1(int _ns) : ns(_ns)
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   random = new RNG(tv.tv_usec);
}

int JitterSample1::generate(float* samples)
{
   for (int i = 0; i < ns; i++)
      samples[i] = float(i) / float(ns) + float((*random)()) / float(ns);
   return ns;
   
   // shuffle
   for (i = ns-2; i >= 0; i--) 
   {
      int target = int(float((*random)()) * float(i));
      float temp = samples[i+1];
      samples[i+1] = samples[target];
      samples[target] = temp;
   }
   return ns;

}
