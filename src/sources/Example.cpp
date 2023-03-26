#include "Example.hpp"
#include "Eigen/Dense"

int MAC(int x, int y, int& sum)
{
    sum += x*y;
    return sum;
}

int add(int x, int y)
{
    return x + y;
}