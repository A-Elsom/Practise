/*
 * Rectangle.h
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#include <string>
#ifndef RECTANGLE_H_
#define RECTANGLE_H_
#include "Shape.h"
using std::string;

// The rectangle class
// Serves also as base for Square
// Adds the functions height and width
// to those supported by Shape
class Rectangle :public Shape{
public:
	// It should be impossible to create a rectangle without additional data
	Rectangle(float width, float height, const string& borderColor, bool fill = false, const string& fillColor = "");
	Rectangle(const Rectangle& other) = default;
	~Rectangle() = default;

	// Getters and setters for width and height
	float width() const;
	float height() const;
	virtual void setWidth(float width);
    virtual void setHeight(float height);
    float area() const override;
    float perimeter() const override;

	// TODO:
	// Choose which functions to implement here
private:
	// TODO:
    // Add private (or protected?) member variables
protected:
    float width_, height_;
};

#endif /* RECTANGLE_H_ */
