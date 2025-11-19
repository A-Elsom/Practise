/*
 * Shape.cpp
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#include "Shape.h"
using std::string;

Shape::Shape(const string& borderColor, bool fill, const string& fillColor) {
    // TODO: implement me
    borderColor_ = borderColor;
    isFilled_ = fill;
    fillColor_ = fillColor;
}

string Shape::borderColor() const {
	// TODO: implement me
	return borderColor_;
}

void Shape::setBorderColor(const string& color) {
    // TODO: implement me
    borderColor_ = color;
}

bool Shape::fill() const {
    // TODO: implement me
    return isFilled_;
}
void Shape::setFill(bool fill) {
    // TODO: implement me
    isFilled_ = fill;
}

string Shape::fillColor() const {
	// TODO: implement me
	return fillColor_;
}

void Shape::setFillColor(const std::string& color) {
    // TODO: implement me
    fillColor_ = color;
}

float Shape::area() const
{
    return 0, 0;
}

float Shape::perimeter() const
{
    return 0.0;
}

