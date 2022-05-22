#include <vector>

namespace PyBezier {
namespace utils {

int binomial(int n, int k)
{
    if (k > n)
        return -1;

    if (k == 0)
        return 1;

    int value = 1;
    for (int i = 1; i <= k; ++i)
    {
        value *= n - (k-i);
        value /= i;
    }

    return value;
}


float determinant( float x0, float y0, float x1, float y1)
{
    return x0 * y1 - x1 * y0;
}


float remap(float value, float old_min, float old_max, float new_min, float new_max)
{
    return ( ( value - old_min ) / (old_max - old_min) ) * (new_max - new_min) + new_min;
}

std::vector<float> range(float min, float max, float dx)
{
    float interval = max - min;
    int n = interval / dx;

    std::vector<float> res(n);
    
    for (int i=0; i < n; ++i)
    {
        res[i] = min + i * dx;
        
    }
    
    return res;
}


} // namespace utils
} // namespace PyBezier
