#ifndef RGB_H
#define RGB_H

#include <assert.h>
#include <iostream.h>


class rgb  {
public:
    
    rgb() {}
    rgb(float r, float g, float b) { data[0] = r; data[1] = g; data[2] = b; }
    rgb(const rgb &c) 
            { data[0] = c.r(); data[1] = c.g(); data[2] = c.b(); }
    float r() const { return data[0]; }
    float g() const { return data[1]; }
    float b() const { return data[2]; }

    rgb operator+() const { return rgb( data[0], data[1], data[2]); }
    rgb operator-() const { return rgb(-data[0],-data[1],-data[2]); }
    float operator[](int i) const {assert(i >= 0 && i < 3); return data[i];}
    float& operator[](int i) {assert(i >= 0 && i < 3); return data[i];} 

    rgb& operator+=(const rgb &c) { data[0] += c[0]; data[1] += c[1];
            data[2] += c[2]; return *this; } 
    rgb& operator-=(const rgb &c) { data[0] -= c[0]; data[1] -= c[1];
            data[2] -= c[2]; return *this; } 
    rgb& operator*=(const rgb &c) { data[0] *= c[0]; data[1] *= c[1];
            data[2] *= c[2]; return *this; } 
    rgb& operator/=(const rgb &c) { data[0] /= c[0]; data[1] /= c[1];
            data[2] /= c[2]; return *this; } 
    rgb& operator*=(float f) { data[0] *= f; data[1] *= f;
            data[2] *= f; return *this; } 
    rgb& operator/=(float f) { data[0] /= f; data[1] /= f;
            data[2] /= f; return *this; } 

    float data[3];
};

inline bool operator==(rgb c1, rgb c2) {
    return (c1.r() == c2.r() && c1.g() == c2.g() && c1.b() == c2.b()); }
inline bool operator!=(rgb c1, rgb c2) {
    return (c1.r() != c2.r() || c1.g() != c2.g() || c1.b() != c2.b()); }

inline istream &operator>>(istream &is, rgb &c) {
     return (is >> c[0] >> c[1] >> c[2]); }
inline ostream &operator<<(ostream &os, rgb c) {
     return (os << c[0] << " " << c[1] << " " << c[2]); }

inline rgb operator+(rgb c1, rgb c2) {
     return rgb(c1.r()+c2.r(), c1.g()+c2.g(), c1.b()+c2.b());}
inline rgb operator-(rgb c1, rgb c2) {
     return rgb(c1.r()-c2.r(), c1.g()-c2.g(), c1.b()-c2.b());}
inline rgb operator*(rgb c1, rgb c2) {
     return rgb(c1.r()*c2.r(), c1.g()*c2.g(), c1.b()*c2.b());}
inline rgb operator/(rgb c1, rgb c2) {
     return rgb(c1.r()/c2.r(), c1.g()/c2.g(), c1.b()/c2.b());}
inline rgb operator*(rgb c, float f) {
     return rgb(c.r()*f, c.g()*f, c.b()*f);}
inline rgb operator*(float f, rgb c) {
     return rgb(c.r()*f, c.g()*f, c.b()*f);}
inline rgb operator/(rgb c, float f) {
     return rgb(c.r()/f, c.g()/f, c.b()/f);}



#endif
