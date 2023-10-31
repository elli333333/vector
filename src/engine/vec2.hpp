//
// Created by ellie on 10/20/23.
//

#ifndef VECTOR_VEC2_HPP
#define VECTOR_VEC2_HPP

#include "common.hpp"

namespace vector {

    template<typename T>
    class vec2 {
    private:
        typedef std::pair<T, T> coord;
    public:
        vec2(coord _origin, coord _destination);

        coord origin;
        coord destination;
    };



} // vector

#endif //VECTOR_VEC2_HPP
