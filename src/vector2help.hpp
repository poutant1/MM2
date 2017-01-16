#ifndef MM2_VECHELP_HPP
#define MM2_VECHELP_HPP

#include <SFML/System.hpp>

typedef sf::Vector2<double> Vector2d;

//Returns the euclidean norm of vector v.
double length(const Vector2d &v);

//Divides vector v by it's length, effectively making its length 1.
void normalize(Vector2d &v);

//Sets vector v's length to given value d without altering the vector's direction.
void setLength(Vector2d &v, double d);

//Returns a new vector with length 1 and same direction as v.
Vector2d normalized(const Vector2d &v);

Vector2d angleToVector(double angle);

#endif
