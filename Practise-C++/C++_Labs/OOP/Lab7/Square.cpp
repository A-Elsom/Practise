/*
 * Square.cpp
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#include "Square.h"
using std::string;

Square::Square(float side, const string& borderColor, bool fill, const string& fillColor) : Rectangle(side, side, borderColor, fill, fillColor) {
    // TODO: implement me
    side_ = side;
}

void Square::setHeight(float newHeight)
{
    height_ = newHeight;
    width_ = newHeight;
}

void Square::setWidth(float newWidth)
{
    height_ = newWidth;
    width_ = newWidth;
}

void Square::changeSide(float newSide)
{
    side_ = newSide;
}
