/*
 * Square.h
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */
#include "Rectangle.h"
#include <string>
#ifndef SQUARE_H_
#define SQUARE_H_

using std::string;

// Squre inherits from Rectangle
// Override the necessary functions
class Square : public Rectangle{
public:
	// It should be impossible to create a square without additional info
	Square(float side, const string& borderColor, bool fill = false, const string& fillColor = "");
	Square(const Square& other) = default;
    ~Square() = default;

    // Choose which functions to implement here
    void changeSide(float);
    void setHeight(float) override;
    void setWidth(float) override;
    void area(float);
    void perimeter(float);
    void side();

private:
    float side_;
};

#endif /* SQUARE_H_ */
