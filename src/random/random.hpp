#ifndef RANDOM_StrangeWhiskers
#define RANDOM_StrangeWhiskers

#include <ctime>
#include <cstdlib>

namespace strange_whiskers::random{

int GetBoundedRandomInteger(int lowerBound, int upperBound);
void Initialize();

}
#endif