#include <math.h>

#include <vec2.hpp>

namespace PyBezier {

Vec2::Vec2(): m_x(0), m_y(0) {}
Vec2::Vec2(float x, float y): m_x(x), m_y(y) {}

float Vec2::getX() const
{
    return m_x;
}

float Vec2::getY() const
{
    return m_y;
}

void Vec2::setX(float x)
{
    m_x = x;
}

void Vec2::setY(float y)
{
    m_y = y;
}

float Vec2::length() const
{
    return sqrt( m_x * m_x + m_y * m_y );
}


float Vec2::distance(const Vec2& other) const
{
    return sqrt( (m_x - other.m_x) * (m_x - other.m_x) + (m_y - other.m_y) * (m_y - other.m_y));
}


Vec2 Vec2::normalize() const
{
    float l = length();
    return Vec2( m_x / l, m_y / l);
}


} // namespace PyBezier
