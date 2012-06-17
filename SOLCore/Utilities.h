#ifndef __UTILITIES_H
#define __UTILITIES_H

#define M_PI       3.14159265358979323846

#define _pad(x,n) unsigned char x[n]
namespace utl{
    template <typename T> inline const T abs(T const & x){
        return ( x<0 ) ? -x : x;
    }
}

#endif