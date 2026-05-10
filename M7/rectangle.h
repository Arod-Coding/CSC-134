#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
    double length;
    double width;

public:
    // Constructor
    Rectangle(double l, double w);

    // Setters
    void setLength(double l);
    void setWidth(double w);

    // Getters
    double getLength() const;
    double getWidth() const;

    // Function to compute area
    double getArea() const;
};

#endif