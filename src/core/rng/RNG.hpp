/*******************************************************************************
    \file
    RNG.hpp

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
#ifndef RNG_HPP
#define RNG_HPP

#include <climits>  //UINT_MAX defined here

namespace random
{
    //if you want a seed other than default_seed, make sure to call one of these before using
    //the Rand* functions.
    void SeedRNG(unsigned seed);                //custom seed
    void SeedRNG64(unsigned long seed);    //custom seed, 64-bit
    void SeedRNG(void);                         //seed based on clock
    //non-deterministic seed using random_device (calls SeedRNG with output from random_device).
    //note this is a seed for the pRNG using the output from random_device, not a seed for random_device,
    //since random_device uses hardware entropy and therefore doesn't require seeding.
    void SeedRNG_RandDevice(void);


    //random 32-bit integer type, uniform distribution between min and max inclusive
    template<typename int_type>
    int_type RandInt(int_type min, int_type max);
    //random 64-bit integer type, uniform distribution between min and max inclusive
    template<typename int_type>
    int_type RandInt64(int_type min, int_type max);
    //random 32-bit floating point type, uniform distribution between min and max inclusive
    template<typename flt_type>
    flt_type RandFlt(flt_type min, flt_type max);
    //random 64-bit floating point type, uniform distribution between min and max inclusive
    template<typename flt_type>
    flt_type RandFlt64(flt_type min, flt_type max);

    
    /*
    random number from hardware entropy. Slower than the pseudorandom functions and
    doesn't produce a uniform distribution, so only call this if you really want
    hardware randomness for some reason. You're probably better off just using
    SeedRNG_RandDevice() to seed the pRNG with a hardware-random value even in
    that case.
    Also only produces unsigned ints because that's how random_device is.
    */
    unsigned RandIntHardware(unsigned min = 0, unsigned max = UINT_MAX);

}
#include "RNG.inl"

#endif  //RNG_HPP