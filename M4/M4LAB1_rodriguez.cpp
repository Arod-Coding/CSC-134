// M4LAB1
// Adrian Rodriguez
// 03/23/26

#include <iostream>
using namespace std;

int main() {
    int width, height;

// Ask the user for the wifth and height
cout << "Enter the width of the block: ";
cin >> width;
cout << "Enter the height of the block: ";
cin >> height;

// Outer loop controls thr rows (height)
for (int i = 0; i < height; i++) {
    // Inner loop controls the columns (width)
    for (int j = 0; j < width; j++) {
        cout << "* ";
    }
    // Move to the next line after finishing a row
    cout << endl;
}

return 0;
}