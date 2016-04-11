#include "NoiseTexture.h"


rgb NoiseTexture::value(const Vector2&, const Vector3& p) const {
    float t = noise.noise(k*p);
    t = (1 + t)/2;
    return rgb(t,t,t);
}

