// CSC 134
// M5HW1
// Adrian Rodriguez
// 4/13/26

#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
void question1();
void question2();
void question3();
void question4();
void question5();

// Main menu (Question 6)
int main() {
    int choice = 0;

    do {
        cout << "\n===== M5HW1 Menu =====\n";
        cout << "1. Average Rainfall\n";
        cout << "2. Volume of a Block\n";
        cout << "3. Roman Numerals\n";
        cout << "4. Geometry Calculator\n";
        cout << "5. Distance Traveled\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: question1(); break;
            case 2: question2(); break;
            case 3: question3(); break;
            case 4: question4(); break;
            case 5: question5(); break;
            case 6: cout << "Goodbye!\n"; break;
            default:
                cout << "Invalid choice. Please select 1 through 6.\n";
        }

    } while (choice != 6);

    return 0;
}

// ================= Question 1 =================
void question1() {
    string m1, m2, m3;
    double r1, r2, r3;

    cout << "\nEnter month: ";
    cin >> m1;
    cout << "Enter rainfall for " << m1 << ": ";
    cin >> r1;

    cout << "Enter month: ";
    cin >> m2;
    cout << "Enter rainfall for " << m2 << ": ";
    cin >> r2;

    cout << "Enter month: ";
    cin >> m3;
    cout << "Enter rainfall for " << m3 << ": ";
    cin >> r3;

    double avg = (r1 + r2 + r3) / 3.0;

    cout << fixed << setprecision(2);
    cout << "The average rainfall for "
         << m1 << ", " << m2 << ", and " << m3
         << " is " << avg << " inches.\n";
}

// ================= Question 2 =================
void question2() {
    double width, length, height;

    cout << "\nEnter width: ";
    cin >> width;
    cout << "Enter length: ";
    cin >> length;
    cout << "Enter height: ";
    cin >> height;

    if (width <= 0 || length <= 0 || height <= 0) {
        cout << "All dimensions must be greater than zero.\n";
        return;
    }

    double volume = width * length * height;
    cout << "The volume of the block is " << volume << ".\n";
}

// ================= Question 3 =================
void question3() {
    int num;

    cout << "\nEnter a number (1 - 10): ";
    cin >> num;

    if (num < 1 || num > 10) {
        cout << "Number must be between 1 and 10.\n";
        return;
    }

    cout << "The Roman numeral version of " << num << " is ";

    switch (num) {
        case 1: cout << "I"; break;
        case 2: cout << "II"; break;
        case 3: cout << "III"; break;
        case 4: cout << "IV"; break;
        case 5: cout << "V"; break;
        case 6: cout << "VI"; break;
        case 7: cout << "VII"; break;
        case 8: cout << "VIII"; break;
        case 9: cout << "IX"; break;
        case 10: cout << "X"; break;
    }
    cout << endl;
}

// ================= Question 4 =================
void question4() {
    int choice;
    double radius, length, width, base, height;
    const double PI = 3.14159;

    cout << "\nGeometry Calculator\n";
    cout << "1. Area of a Circle\n";
    cout << "2. Area of a Rectangle\n";
    cout << "3. Area of a Triangle\n";
    cout << "4. Quit\n";
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    if (choice < 1 || choice > 4) {
        cout << "The valid choices are 1 through 4.\n";
        return;
    }

    if (choice == 1) {
        cout << "Enter the circle's radius: ";
        cin >> radius;
        if (radius < 0) {
            cout << "The radius cannot be less than zero.\n";
            return;
        }
        cout << "The area is " << PI * radius * radius << endl;
    }

    else if (choice == 2) {
        cout << "Enter length: ";
        cin >> length;
        cout << "Enter width: ";
        cin >> width;
        if (length < 0 || width < 0) {
            cout << "Length and width must be positive.\n";
            return;
        }
        cout << "The area is " << length * width << endl;
    }

    else if (choice == 3) {
        cout << "Enter base: ";
        cin >> base;
        cout << "Enter height: ";
        cin >> height;
        if (base < 0 || height < 0) {
            cout << "Only enter positive values for base and height.\n";
            return;
        }
        cout << "The area is " << base * height * 0.5 << endl;
    }
}

// ================= Question 5 =================
void question5() {
    int speed, hours;

    cout << "\nWhat is the speed of the vehicle in mph? ";
    cin >> speed;
    cout << "How many hours has it traveled? ";
    cin >> hours;

    if (speed < 0 || hours < 1) {
        cout << "Speed must be non-negative and time must be at least 1.\n";
        return;
    }

    cout << "\nHour   Distance Traveled\n";
    cout << "-----------------------\n";

    for (int i = 1; i <= hours; i++) {
        cout << setw(4) << i << setw(10) << speed * i << endl;
    }
}