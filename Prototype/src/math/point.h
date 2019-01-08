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
    //Cross Product
    Point Point::operator*(const Point &other) const;
    Point& Point::operator*=(const Point &other);
    //Factored product
    Point Point::operator*(const double &other) const;
    Point& Point::operator*=(const double &other);

    //"Nice ToString()"
    friend std::ostream& operator<<(std::ostream& os, const Point &p);
    std::string toString() const;

    //Distance from origin
    double magnitude() const;

    //Returns a point with distance 1 from origin
    Point normalized() const;

    //Returns a point rotated (anti-clockwise) around pivot by angle
    Point rotate(double angle, Point pivot = Point(0, 0));

    //Returns distance between this and other
    double distanceTo(const Point &other) const;

    //Returns the dot product of this and other
    double dot(const Point &other) const;

    //Returns x * other.y - y * other.x
    double antidot(const Point &other) const;

    //Returns the angle, in degrees, of the vector
    double toAngle() const;


};

//marked inline to prevent a multiple definition
inline Point operator*(double d, const Point& p)
{
    Point result = p;
    result *= d;
    return result;
}