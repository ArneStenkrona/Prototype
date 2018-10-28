#pragma once
#include <string>
#include <ostream>

class Point {
public:
    double x;
    double y;
    Point();
    Point(double _x, double _y);

    //(0,0)
    static const Point empty;
    //(0,1)
    static const Point up;
    //(0,-1)
    static const Point down;
    //(-1,0)
    static const Point left;
    //(1,0)
    static const Point right;

    //Arithmetic operators
    //Addition
    Point Point::operator+(const Point &other) const;
    Point& Point::operator+=(const Point  &other);
    //Subtraction
    Point Point::operator-(const Point &other) const;
    Point& Point::operator-=(const Point  &other);
    //Multiplication
    Point Point::operator*(const Point &other) const;
    Point& Point::operator*=(const Point &other);
    Point Point::operator*(const double &other) const;
    Point& Point::operator*=(const double &other);

    //"Nice ToString()"
    friend std::ostream& operator<<(std::ostream& os, const Point &p);

    //Pythagorean theorem
    double magnitude() const;

    //Returns a point with distance 1 from origin
    Point normalized() const;

    //Returns a point rotated around pivot by angle
    Point rotate(double angle, Point pivot);

    //Returns distance between this and other
    double distanceTo(const Point &other) const;

    //Returns the dot product of this and other
    double dot(const Point &other) const;

    //Returns the cross product of this and other
    double cross(const Point &other) const;

    //Returns the angle, in degrees, of the vector
    double toAngle() const;


    std::string toString() const;
};


//marked inline to prevent a multiple definition
inline Point operator*(double d, const Point& p)
{
    Point result = p;
    result *= d;
    return result;
}