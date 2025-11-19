/*
 * Rectangle.cpp
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#include "Rectangle.h"

using std::string;

Rectangle::Rectangle(float width, float height, const string& borderColor, bool fill, const string& fillColor) : Shape(borderColor, fill, fillColor){
    // TODO: implement me
    width_ = width;
    height_ = height;
}

float Rectangle::width() const {
	// TODO: implement me
	return width_;
}

float Rectangle::height() const {
	// TODO: implement me
	return height_;
}

void Rectangle::setWidth(float width) {
    // TODO: implement me
    width_ = width;
}

void Rectangle::setHeight(float height) {
    // TODO: implement me
    height_ = height;
}

float Rectangle::perimeter() const
{
    return height_ * 2 + width_ * 2;
}

float Rectangle::area() const
{
    return height_ * width_;
}

