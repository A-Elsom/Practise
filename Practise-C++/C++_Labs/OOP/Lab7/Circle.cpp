/*
 * Circle.cpp
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#include "Circle.h"
# define M_PI           3.14159265358979323846  /* pi */
using std::string;


Circle::Circle(float radius, const string& borderColor, bool fill, const string& fillColor) : Shape(borderColor, fill, fillColor) {
    // TODO: implement me
    radius_ = radius;
}

float Circle::radius() const {
	// TODO: implement me
	return radius_;
}

void Circle::setRadius(float radius) {
    // TODO: implement me
    radius_ = radius;
}

float Circle::area() const
{
    return M_PI * (radius_ * radius_);
}

float Circle::perimeter() const
{
    return 2 * M_PI * radius_;
}