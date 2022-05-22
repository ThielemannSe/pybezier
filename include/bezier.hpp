#ifndef BEZIER_HPP
#define BEZIER_HPP

#include <vector>

#include <vec2.hpp>

namespace PyBezier {

class Bezier
{
protected:
    std::vector<Vec2> m_points;

public:

    Bezier(std::vector<Vec2> points);
    Bezier(std::vector<std::vector<float>> points);

    int order() const;
    float length(float dx) const;

    Vec2 at(float t) const;
    std::vector<Vec2> multiple_at(std::vector<float> ts) const;
    
    std::vector<Vec2> sample_equidistant(float step, float dx, float overhead) const;

    float curvature(float t) const;

    Vec2 derivative(float t) const;
    Vec2 derivative2(float t) const;

protected:
    float _B(float t, int order, int k) const;

    std::vector<float>create_LUT( float dx ) const;

    float dist_to_T(float distance, const std::vector<float>& LUT) const;

    
};


class LinearBezier: public Bezier 
{
    LinearBezier(std::vector<Vec2> points);
    LinearBezier(std::vector<std::vector<float>> points);
};

} // namespace PyBezier

#endif
