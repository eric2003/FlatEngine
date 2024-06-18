#pragma once
#include <random>

class RandomHelper
{
public:
    static std::mt19937 gen;

    static void Init()
    {
        std::random_device rd;  // a seed source for the random number engine
        RandomHelper::gen = std::mt19937(rd()); // mersenne_twister_engine seeded with rd()
    }

    static int RandomInteger( int min, int max )
    {
        std::uniform_int_distribution<> distribution(min, max);
        int result = distribution(gen);
        return result;
    }

    static float RandomSingle(float min, float max)
    {
        std::uniform_real_distribution<float> distribution(min, max);
        float result = distribution(gen);
        return result;
    }
};


