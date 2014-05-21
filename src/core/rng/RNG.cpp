/*******************************************************************************
    \file
    RNG.cpp

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

#include "pch.h"

#include "RNG.hpp"
#include <chrono>
#include <random>

namespace random
{
    std::mt19937 mt_rng(std::mt19937::default_seed);
    std::mt19937_64 mt64_rng(std::mt19937_64::default_seed);
    std::random_device device_rng;  //default constructor picks a valid source of entropy for the system it is being run on

    void SeedRNG(unsigned int seed)
    {
        mt_rng.seed(seed);
        mt64_rng.seed(seed);
    }

    void SeedRNG64(unsigned long seed)
    {
        mt_rng.seed(unsigned(seed));
        mt64_rng.seed(seed);
    }

    void SeedRNG(void)
    {
        std::chrono::system_clock::time_point mytime = std::chrono::system_clock::now();
        std::chrono::system_clock::duration d = mytime.time_since_epoch();
        SeedRNG64(static_cast<unsigned long>(d.count()));
    }

    void SeedRNG_RandDevice(void)
    {
        SeedRNG(RandIntHardware());
    }

    unsigned RandIntHardware(unsigned min, unsigned max)
    {
        return ((device_rng() + min) % max);
    }
}
