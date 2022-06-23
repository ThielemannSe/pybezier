#include <math.h>
#include <stdexcept>
#include <iostream>

#include <bezier.hpp>
#include <vec2.hpp>
#include <utils.hpp>


namespace PyBezier {

Bezier::Bezier(std::vector<Vec2> points): m_points(points) {}
Bezier::Bezier(std::vector<std::vector<float>> points) {
    for (const auto& p: points) {
        if (p.size() != 2)
            throw std::invalid_argument("Nested arrays must have length of two");

        m_points.push_back( Vec2(p[0], p[1]) );
    }
}

int Bezier::order() const
{
    return m_points.size() - 1;
}

float Bezier::length(float dx) const
{
    std::vector<float> ts = utils::range(0., 1. + dx, dx);
    std::vector<Vec2> points = multiple_at(ts);
    float length = 0.;
    for (int i=0; i < points.size()-1; ++i)
    {
        length += points[i].distance(points[i+1]); 
    }
    return length;
}


Vec2 Bezier::startpoint() const
{
    return m_points.front();
}


Vec2 Bezier::endpoint() const
{
    return m_points.back();
}


Vec2 Bezier::at(float t) const
{
    if ( 1 < t || t < 0)
        throw std::range_error("t must be in range [0,1]");

    int n = order();
    float x = 0;
    float y = 0;

    for (int k=0; k <= n; ++k) {
        float B = _B(t, n, k);

        x += B * m_points[k].getX();
        y += B * m_points[k].getY();
    }       
    return Vec2(x, y);
}


std::vector<Vec2> Bezier::multiple_at(std::vector<float> ts) const {
    int n = ts.size();
    std::vector<Vec2> res(n);

    for (int i = 0; i < n; ++i)
    {
        res[i] = at(ts[i]);  
    }
    return res;
}


float Bezier::_B(float t, int n, int k) const
{
    return utils::binomial(n, k) * pow(t, k) * pow( (1-t), n - k );
}


std::vector<float> Bezier::create_LUT(float dx) const
{   
    std::vector<float> ts = utils::range(0, 1+dx, dx);

    std::vector<Vec2> points = multiple_at(ts);
    int n = points.size();
    std::vector<float> d(n, 0.0);

    float length = 0.0;

    for (int i=1; i < n; ++i)
    {
        length += points[i].distance(points[i-1]);
        d[i] = length;
    }

    return d;
}


float Bezier::dist_to_T(float distance, const std::vector<float>& LUT) const
{   
    if (distance == 0.0)
        return 0.0;
    
    float arcLength = LUT.back();
    int n = LUT.size();

    if ( distance > arcLength || distance < 0)
        throw std::range_error( "Given distance is out of range");

    float t = 0;

    for (int i=0; i < n; ++i)
    {
        if (LUT[i] <= distance && distance <= LUT[i+1]) {
            t = utils::remap(distance, LUT[i], LUT[i+1], (float)i / (float)(n-1), (float)(i+1)/(float)(n-1));
            return t;
        }       
    }

    return -1;
}


std::vector<Vec2> Bezier::sample_equidistant(float step, float dx, float overhead) const
{   
    // std::cout << "sampling equidistant" << std::endl;
    std::vector<float> LUT = create_LUT(dx);

    // std::vector<float> distances = utils::range( (0 + overhead), LUT.back(), step );

    std::vector<float> distances;
    float length = LUT.back();

    float current_distance = 0.0;
    while (current_distance <= length)
    {
        distances.push_back(current_distance);
        current_distance += step;
    }

    int n = distances.size();
    std::vector<Vec2> points(n);

    float t;
    for (int i=0; i < n; ++i )
    {   
        t = dist_to_T(distances[i], LUT);
        points[i] = at(t);
    }
    return points;
}



Vec2 Bezier::derivative(float t) const
{
    int n = order();

    if (n-1 <= 0)
        return Vec2(0, 0);

    float x = 0;
    float y = 0;

    for (int k=0; k < n; ++k)
    {
        float B = _B(t, n-1, k);

        x += B * (m_points[k+1].getX() - m_points[k].getX());
        y += B * (m_points[k+1].getY() - m_points[k].getY());
    }

    x *= n;
    y *= n;

    return Vec2(x, y);
}


Vec2 Bezier::derivative2(float t) const
{
    int n = order();

    float x = 0;
    float y = 0;

    for (int k=0; k < n-1; ++k)
    {
        float B = _B(t, n-2, k);

        x += B * (m_points[k+2].getX() - 2 * m_points[k+1].getX() + m_points[k].getX());
        y += B * (m_points[k+2].getY() - 2 * m_points[k+1].getY() + m_points[k].getY());
    }

    x *= n * (n-1);
    y *= n * (n-1);

    return Vec2(x, y);
}


float Bezier::curvature(float t) const
{
    Vec2 d = derivative(t);
    Vec2 d2 = derivative2(t);

    float nominator = utils::determinant(d.getX(), d.getY(), d2.getX(), d2.getY());
    float denominator = pow(d.length(), 3);

    return nominator/denominator;
}

} // namespace PyBezier
