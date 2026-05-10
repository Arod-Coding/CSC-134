// M7T2
// Adrian Rodriguez
// 05/04/2026

#include <iostream>
#include "Rectangle.h"
using namespace std;

// Constructor
Rectangle::Rectangle(double l, double w) {
    length = l;
    width = w;
}

// Setters
void Rectangle::setLength(double l) {
    length = l;
}

void Rectangle::setWidth(double w) {
    width = w;
}

// Getters
double Rectangle::getLength() const {
    return length;
}

double Rectangle::getWidth() const {
    return width;
}

// Area calculation
double Rectangle::getArea() const {
    return length * width;
}

int main() {

    double length, width;

    // INPUT VALIDATION (Silver + Gold requirement)

    do {
        cout << "Enter rectangle length: ";
        cin >> length;

        if (length <= 0) {
            cout << "Error: length must be greater than 0.\n";
        }

    } while (length <= 0);

    do {
        cout << "Enter rectangle width: ";
        cin >> width;

        if (width <= 0) {
            cout << "Error: width must be greater than 0.\n";
        }

    } while (width <= 0);

    // Create Rectangle object
    Rectangle box(length, width);

    // Output results
    cout << "\nRectangle Info:\n";
    cout << "Length: " << box.getLength() << endl;
    cout << "Width : " << box.getWidth() << endl;
    cout << "Area  : " << box.getArea() << endl;

    return 0;
}