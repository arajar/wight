/*******************************************************************************
    \file
    RNG.inl

    \author
    M.J. Gardner

    \date
    2014

    \brief
    A wrapper for the most commonly useful parts of C++11 <random>.
    Meant to make <random> as easy to use as C rand(), while preserving
    the advantages of <random> over C rand().

    There is an excellent video on the benefits and use of <random> here:
    http://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
    which was a large part of my motivation to create this.
*******************************************************************************/
#ifndef RNG_INL
#define RNG_INL

/*
    exposing <random> to people including RNG.hpp is kind of annoying,
    but ways of keeping it hidden (pimpl, extern template, not using templates)
    aren't really worth it in this case.
    
    On an actual large project <random> (and the other std headers here) 
    would probably go in the precompiled header
*/
#include <random>
#include <cassert>      //Don't want to let people call these with min > max! Undefined behavior is bad.
#include <type_traits>  //using in static_assert to prevent compilation with inappropriate template params

namespace random
{
    extern std::mt19937 mt_rng;
    extern std::mt19937_64 mt64_rng;
    extern std::random_device device_rng;  //default constructor picks a valid source of entropy for the system it is being run on

    template<typename int_type>
    int_type RandInt(int_type min, int_type max)
    {
        assert(min <= max);
        static_assert(std::is_integral<int_type>::value, "not an int type\n");
        std::uniform_int_distribution<int_type> dist(min, max);
        return dist(mt_rng);
    }

    template<typename int_type>
    int_type RandInt64(int_type min, int_type max)
    {
        assert(min <= max);
        static_assert(std::is_integral<int_type>::value, "not an int type\n");
        std::uniform_int_distribution<int_type> dist(min, max);
        return dist(mt64_rng);
    }

    template<typename flt_type>
    flt_type RandFlt(flt_type min, flt_type max)
    {
        assert(min <= max);
        static_assert(std::is_floating_point<flt_type>::value, "not a floating point type\n");
        std::uniform_real_distribution<flt_type> dist(min, max);
        return dist(mt_rng);
    }

    template<typename flt_type>
    flt_type RandFlt64(flt_type min, flt_type max)
    {
        assert(min <= max);
        static_assert(std::is_floating_point<flt_type>::value, "not a floating point type\n");
        std::uniform_real_distribution<flt_type> dist(min, max);
        return dist(mt64_rng);
    }

}

#endif //RNG_INL