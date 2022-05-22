#ifndef UTILS_HPP
#define UTILS_HPP

namespace PyBezier {
namespace utils {

int binomial(int n, int k);

float determinant( float x0, float y0, float x1, float y1);

float remap(float value, float old_min, float old_max, float new_min, float new_max);

std::vector<float> range(float min, float max, float dx);

} // namespace utils
} // namespace PyBezier

#endif
