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
    Point Point::operator+(const Point &other);
    Point& Point::operator+=(const Point  &other);
    //Subtraction
    Point Point::operator-(const Point &other);
    Point& Point::operator-=(const Point  &other);
    //Multiplication
    Point Point::operator*(const Point &other);
    Point& Point::operator*=(const Point &other);
    Point Point::operator*(const double &other) const;
    Point& Point::operator*=(const double &other);

    //"Nice ToString()"
    friend std::ostream& operator<<(std::ostream& os, const Point &p);

    //Pythagorean theorem
    double magnitude() const;

    //Returns a point with distance 1 from origin
    Point normalized() const;
};