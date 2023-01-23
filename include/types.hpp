#ifndef TYPES
#define TYPES
#include <functional>

using ElementID = unsigned int;
using TimeOffset = unsigned int;
using Time = unsigned int;
using ProbabilityGenerator = std::function<double()>;

#endif