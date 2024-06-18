#include "RandomHelper.h"

std::mt19937 RandomHelper::gen;

class RandomHelperInit
{
public:
    RandomHelperInit()
    {
        RandomHelper::Init();
    }
};

RandomHelperInit _RandomHelperInit;

