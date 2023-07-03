#include "random.hpp"
namespace strange_whiskers::random
{
    int GetBoundedRandomInteger(int lowerBound, int upperBound)
    {
        return (std::rand() % (upperBound - lowerBound + 1)) + lowerBound;
    }

    void Initialize()
    {
        std::srand(std::time(nullptr));
    }
}