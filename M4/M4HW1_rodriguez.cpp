// M4HW1
// Adrian Rodriguez
// 03/23/2026

#include <iostream> 
using namespace std;

int main() {
    int num;
    int i = 1;

    // Input validation loop 
    while (true) {
        cout << "Enter a number from 1 to 12: ";
        cin >> num;

        if (num >= 1 && num <= 12) {
            break; // valid input, exit loop
        
        }
        cout << "Invalid input. Please try again." << endl;
    }
    // Times table loop
    while (i <= 12) {
        cout << num << " times " << i << " is " << (num * i) << "." << endl;
        i++;
    }

    return 0;
}