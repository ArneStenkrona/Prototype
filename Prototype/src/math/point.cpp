#include "point.h"
#include <cmath>
# define M_PI           3.14159265358979323846  /* pi */

Point::Point() : x(0.0), y(0.0)
{

}

Point::Point(double _x, double _y) : x(_x), y(_y)
{

}

Point Point::operator+(const Point &other) const
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

Point Point::operator-(const Point &other) const
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

Point Point::operator*(const Point &other) const
{
    Point result = *this;
    result *= other;
    return result;
}

Point& Point::operator*=(const Point &other)
{
    double tempX = x;
    x = (x * other.x - y * other.y);
    y = (tempX * other.y + y * other.x);
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

#define PI 3.14159265
Point Point::rotate(double angle, Point pivot)
{
    Point p = Point(x, y);
    double s = sin(angle*PI / 180);
    double c = cos(angle*PI / 180);

    // translate point back to origin:
    p.x -= pivot.x;
    p.y -= pivot.y;

    // rotate point
    double xnew = p.x * c - p.y * s;
    double ynew = p.x * s + p.y * c;

    // translate point back:
    p.x = xnew + pivot.x;
    p.y = ynew + pivot.y;
    return p;
}

double Point::distanceTo(const Point &other) const
{
    return (*this - other).magnitude();
}

double Point::dot(const Point & other) const
{
    return x * other.x + y * other.y;
}

double Point::antidot(const Point & other) const
{
    return x * other.y - y * other.x;
}

constexpr double radToDeg(double rad) { return rad * (180 / M_PI); }
double Point::toAngle() const
{
    if (x == 0.0 && y == 0.0) return 0;
    return radToDeg(atan2(y, x));
}

std::string Point::toString() const
{
    return "Point(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

const Point Point::empty = Point(0, 0);
const Point Point::up = Point(0, 1);
const Point Point::down = Point(0, -1);
const Point Point::right = Point(1, 0);
const Point Point::left = Point(-1, 0);


