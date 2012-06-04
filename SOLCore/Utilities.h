#ifndef __UTILITIES_H
#define __UTILITIES_H

namespace utl{
    template <typename T> inline const T abs(T const & x){
        return ( x<0 ) ? -x : x;
    }
}

#endif