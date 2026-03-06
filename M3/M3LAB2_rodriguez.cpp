// M3Lab2
// Adrian Rodriguez
// 3/6/26
// Program: Convert numerical grade to letter grade

#include <iostream>
using namespace std;

int main()  {

    // Variable to store numerical grade
    int grade; 
    char letterGrade;

    // Ask user for input
    cout << "Enter your grade (0-100): ";
    cin >> grade;

    // Determine Letter grade
    if (grade >= 90 && grade <= 100) {
        letterGrade = 'A';
    }
    else if (grade >= 80 && grade <= 89) {
        letterGrade = 'B';
    }
    else if (grade >= 70 && grade <= 79) {
        letterGrade = 'C';
    }
    else if (grade >= 60 && grade <= 69) {
        letterGrade = 'D';
    }
    else if (grade >= 0 && grade <= 59) {
        letterGrade = 'F';
    }
    else {
        cout << "Invalid grade entered." << endl;
        return 1; //Exit program if input is invalid
    }

    // Display
    cout << "Your letter grade is: " << letterGrade << endl;

    return 0;
}