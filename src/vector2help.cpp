#include "vector2help.hpp"
#include <cmath>

double length(const Vector2d &v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void normalize(Vector2d &v) {
	v *= (1.0 / length(v));
}

void setLength(Vector2d &v, double d) {
	normalize(v);
	v *= d;
}

Vector2d normalized(const Vector2d &v) {
	Vector2d newV = v;
	return newV * (1.0 / length(newV));
}

Vector2d angleToVector(double angle) {
    return Vector2d(cos(2*3.14*angle/360),sin(2*3.14*angle/360));
}
