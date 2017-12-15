#include "point.h"
#include <cmath>

Point::Point() : x(0.0), y(0.0)
{

}

Point::Point(double _x, double _y) : x(_x), y(_y)
{

}

Point Point::operator+(const Point &other)
{
    Point result = *this;
    result += other;
    return result;
}

Point& Point::operator+=(const Point &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Point Point::operator-(const Point &other)
{
    Point result = *this;
    result -= other;
    return result;
}

Point& Point::operator-=(const Point &other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Point Point::operator*(const Point &other)
{
    Point result = *this;
    result *= other;
    return result;
}

Point& Point::operator*=(const Point &other)
{
    x = (x * other.x - y * other.y);
    y = (x * other.y + y * other.x);

    return *this;
}

Point Point::operator*(const double &other) const
{
    Point result = *this;
    result *= other;
    return result;
}

Point& Point::operator*=(const double &other)
{
    x *= other;
    y *= other;

    return *this;
}

std::ostream & operator<<(std::ostream & os, const Point & p)
{
    os << "Point(" << p.x << ", " << p.y << ")";
    return os;
}

double Point::magnitude() const
{
    return sqrt(x * x + y * y);
}

Point Point::normalized() const
{
    double mag = magnitude();
    if (mag > 0) {
        return *this * (1.0 / mag);
    }
    else {
        return Point(0, 0);
    }
}

const Point Point::empty = Point(0, 0);
const Point Point::up = Point(0, 1);
const Point Point::down = Point(0, -1);
const Point Point::right = Point(1, 0);
const Point Point::left = Point(-1, 0);


