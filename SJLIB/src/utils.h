#ifndef __UTILITIES_H
#define __UTILITIES_H

#define M_PI       3.14159265358979323846
#define ARRLEN(a) (sizeof(a)/sizeof(a[0])) 
#include <math.h>
#define OFFSETOF(type, field)    ((unsigned long) &(((type *) 0)->field))

namespace utl{
    template <typename T> inline const T abs(T const & x){
        return ( x<0 ) ? -x : x;
    }

    /* This function adjust the angle in a specified range
     */
    inline const float AdjustLimitsToAngle(float fAngle, float const fLowerBound, float const fUpperBound) {
        while(fAngle > fUpperBound) {
            fAngle -= (2.0f * (float)M_PI);
        }
        while(fAngle < fLowerBound) {
            fAngle += (2.0f * (float)M_PI);
        }
        return fAngle;
    }
}

#endif