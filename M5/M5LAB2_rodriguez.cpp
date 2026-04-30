// M5LAB2
//Adrian Rodriguez

#include <iostream>
#include <iomanip>
using namespace std;

//Function prototypes
double getLength();
double getWidth();
double getArea(double length, double width);
void displayData (double length, double width, double area);

int main()
{
    // Calculates the area of a rectangle.

        double length,
                    width,
                                area;

                                    length = getLength();
                                        width = getWidth();
                                            area = getArea(length, width);
                                            displayData(length, width, area);
                                                return 0;

                                                }

                                                // Get Length

                                                double getLength() {
                                                    double length;
                                                        cout << "Enter the length of the rectangle: ";
                                                            cin >> length;
                                                                return length;
                                                                }

                                                                // get width

                                                                double getWidth() {
                                                                    double width;
                                                                        cout << "Enter the width of the rectangle: ";
                                                                            cin >> width;
                                                                                return width;
                                                                                }

                                                                                // get area

                                                                                double getArea(double length, double width) {
                                                                                    return length * width;
                                                                                    }

                                                                                    // display data

                                                                                    void displayData(double length, double width, double area) {
                                                                                        cout << fixed << setprecision(2);
                                                                                            cout << "\nRectangle Data\n";
                                                                                                cout << "----------------------\n";
                                                                                                    cout << "Length: " << length << endl;
                                                                                                        cout << "Width : " << width << endl;
                                                                                                            cout << "Area  : " << area << endl;
                                                                                                            }