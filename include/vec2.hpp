#ifndef VEC2_HPP
#define VEC2_HPP

namespace PyBezier {

class Vec2 
{
private:
    float m_x;
    float m_y;

public:

    Vec2();
    Vec2(float x, float y);

    float getX() const;
    float getY() const;

    void setX(float x);
    void setY(float y);

    float length() const;
    Vec2 normalize() const;

    float distance( const Vec2& other) const;

    // Much more that can be implemented here like
    // arithmetic methods with specifying operators
};

} // namespace PyBezier

#endif
