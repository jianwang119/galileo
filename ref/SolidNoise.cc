#include "SolidNoise.h"


SolidNoise::SolidNoise()
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   RNG random(tv.tv_usec);
   
   int i;

   grad[0] = Vector3( 1, 1, 0);
   grad[1] = Vector3(-1, 1, 0);
   grad[2] = Vector3( 1,-1, 0);
   grad[3] = Vector3(-1,-1, 0);

   grad[4] = Vector3( 1, 0, 1);
   grad[5] = Vector3(-1, 0, 1);
   grad[6] = Vector3( 1, 0,-1);
   grad[7] = Vector3(-1, 0,-1);

   grad[8] = Vector3( 0, 1, 1);
   grad[9] = Vector3( 0,-1, 1);
   grad[10]= Vector3( 0, 1,-1);
   grad[11]= Vector3( 0,-1,-1);

   grad[12]= Vector3( 1, 1, 0);
   grad[13]= Vector3(-1, 1, 0);
   grad[14]= Vector3( 0,-1, 1);
   grad[15]= Vector3( 0,-1,-1);

   for (i = 0; i < 16; i++)
      phi[i] = i;

   // shuffle phi
   for (i = 14; i >= 0; i--) {
        int target = int(random()*i);
        int temp = phi[i+1];
        phi[i+1] = phi[target];
        phi[target] = temp;
   }
}

SolidNoise::SolidNoise(int seed)
{
   RNG random(seed);
   
   int i;

   grad[0] = Vector3( 1, 1, 0);
   grad[1] = Vector3(-1, 1, 0);
   grad[2] = Vector3( 1,-1, 0);
   grad[3] = Vector3(-1,-1, 0);

   grad[4] = Vector3( 1, 0, 1);
   grad[5] = Vector3(-1, 0, 1);
   grad[6] = Vector3( 1, 0,-1);
   grad[7] = Vector3(-1, 0,-1);

   grad[8] = Vector3( 0, 1, 1);
   grad[9] = Vector3( 0,-1, 1);
   grad[10]= Vector3( 0, 1,-1);
   grad[11]= Vector3( 0,-1,-1);

   grad[12]= Vector3( 1, 1, 0);
   grad[13]= Vector3(-1, 1, 0);
   grad[14]= Vector3( 0,-1, 1);
   grad[15]= Vector3( 0,-1,-1);

   for (i = 0; i < 16; i++)
      phi[i] = i;

   // shuffle phi
   for (i = 14; i >= 0; i--) {
        int target = int(random()*i);
        int temp = phi[i+1];
        phi[i+1] = phi[target];
        phi[target] = temp;
   }
}


float SolidNoise::turbulence(const Vector3& p, int depth)
const
{
   float sum = 0.0f;
   float weight = 1.0f;
   Vector3 ptemp(p);

   sum = fabs(noise(ptemp));
   
   for (int i = 1; i < depth; i++)
   {
      weight = weight * 2;
      ptemp.setX(p.x() * weight);
      ptemp.setY(p.y() * weight);
      ptemp.setZ(p.z() * weight);
      
      sum += fabs(noise(ptemp)) / weight;
   }
   return sum;
}

float SolidNoise::dturbulence(const Vector3& p, int depth, float d)
const {
   float sum = 0.0f;
   float weight = 1.0f;
   Vector3 ptemp(p);

   sum += fabs(noise(ptemp)) / d;

   for (int i = 1; i < depth; i++)
   {
       weight = weight * d;
       ptemp.setX(p.x() * weight);
       ptemp.setY(p.y() * weight);
       ptemp.setZ(p.z() * weight);
   
       sum += fabs(noise(ptemp)) / d;
   }
   return sum;
}

Vector3 SolidNoise::vectorTurbulence(const Vector3& p, int depth)
const {
   Vector3 sum(0.0, 0.0, 0.0);
   Vector3 ptemp = p + Vector3(5.1, 56.2, 25.8);
   float amp = 1.0;
   Vector3 off(0.321, 0.112, 0.724);

   for (int i = 0; i < depth; i++)
   {
       sum += vectorNoise(ptemp) * amp;
       amp = amp * 0.6;
       ptemp.setX( ptemp.x() * 2 + off.x() );
       ptemp.setY( ptemp.y() * 2 + off.y() );
       ptemp.setZ( ptemp.z() * 2 + off.z() );
   }
   return sum;
}

Vector3 SolidNoise::vectorNoise(const Vector3& p) const {
    int i, j, k;
    int fi, fj, fk;
    Vector3 sum, v;

    sum = Vector3(0.0, 0.0, 0.0);
    fi = int(floor(p.x()));
    fj = int(floor(p.y()));
    fk = int(floor(p.z()));
    for (i = fi; i <= fi+1; i++)
       for (j = fj; j <= fj+1; j++)
          for (k = fk; k <= fk+1; k++) {
               v = Vector3(p.x() - i, p.y() - j, p.z() - k);
               sum += vectorKnot(i, j, k, v);
          }
    return sum;
    
}

float SolidNoise::noise(const Vector3& p) const {
    int fi, fj, fk;
    float fu, fv, fw, sum;
    Vector3 v;

    fi = int(floor(p.x()));
    fj = int(floor(p.y()));
    fk = int(floor(p.z()));
    fu = p.x() - float(fi);
    fv = p.y() - float(fj);
    fw = p.z() - float(fk);
    sum = 0.0;

    v = Vector3(fu, fv, fw);
    sum += knot(fi, fj, fk, v);

    v = Vector3(fu - 1, fv, fw);
    sum += knot(fi + 1, fj, fk, v);

    v = Vector3(fu, fv - 1, fw);
    sum += knot(fi, fj + 1, fk, v);

    v = Vector3(fu, fv, fw -1);
    sum += knot(fi, fj, fk + 1, v);

    v = Vector3(fu -1, fv -1, fw);
    sum += knot(fi + 1, fj + 1, fk, v);

    v = Vector3(fu -1, fv, fw -1);
    sum += knot(fi + 1, fj, fk + 1, v);

    v = Vector3(fu, fv -1, fw -1);
    sum += knot(fi, fj + 1, fk + 1, v);

    v = Vector3(fu -1, fv -1, fw -1);
    sum += knot(fi + 1, fj + 1, fk + 1, v);
    
    return sum;
    
}
