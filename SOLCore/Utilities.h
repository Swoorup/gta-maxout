#ifndef __UTILITIES_H
#define __UTILITIES_H

#define M_PI       3.14159265358979323846

#define _pad(x,n) unsigned char x[n]
#define OFFSETOF(type, field)    ((unsigned long) &(((type *) 0)->field))

namespace utl{
    template <typename T> inline const T abs(T const & x){
        return ( x<0 ) ? -x : x;
    }
}

#endif