#ifndef IMAGE_H
#define IMAGE_H 1

#include "rgb.h"
#include <math.h>
#include <stdlib.h>

class Image  
{
public:

   Image() {}
   Image(int w, int h);
   Image(int w, int h , rgb c);
   void safeSetPixel(int x, int y, rgb c) 
   {
      if (x >= 0 && x < w && y >= 0 && y < h)
         data[x][y] = c; 
   }
   void setPixel(int x, int y, rgb c) 
   {
      if (!(x >= 0 && x < w && y >= 0 && y < h))
      {
         cerr << "Image::setPixel    w = " << w << " h = " << h 
              << "     requested pixel (" << x << ", " << y << ")" 
              << endl;
         exit(0);
      }
      data[x][y] = c;
   }

   rgb getPixel(int x, int y) const 
   {
      x = ( x >= 0 ? x : 0);  
      x = ( x <  w ? x : w-1);  
      y = ( y >= 0 ? y : 0);  
      y = ( y <  h ? y : h-1);  
/*      if (!(x >= 0 && x < w && y >= 0 && y < h))
      {
         cerr << "Image::getPixel w = " << w << " h = " << h << endl
            << "       requested pixel (" << x << ", " << y << ")" 
            << endl;
         exit(0);
      }
*/      
      return data[x][y]; 
   }
   int width()  const { return w; }
   int height() const { return h; }
   void readPPM (char* file_name);
   void writePPM(ostream& s) const;

private:
   rgb **data;
   int w, h;
};


#endif
