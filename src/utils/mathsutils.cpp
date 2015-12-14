#include "mathsutils.h"

using namespace BQ;

MathsUtils::MathsUtils()
{
    twister.seed(time(0));
}

int MathsUtils::randomInt(int l_bound, int u_bound)
{
    std::uniform_int_distribution<int> distribution(l_bound,u_bound);

    return distribution(twister);
}

float MathsUtils::randomFloat(float l_bound, float u_bound)
{
    std::uniform_real_distribution<float> distribution(l_bound,u_bound);

    return distribution(twister);
}

int MathsUtils::nxtPow2(int x)
{
    if (x < 0)
    {
            return 0;
    }

    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return x+1;
}

int MathsUtils::getPow2(int x)
{
    int pow = 0;
    while (((x & 1) == 0) && x > 1) /* While x is even and > 1 */
    {
       x >>= 1;
       pow ++;
    }
     return(pow);
}

