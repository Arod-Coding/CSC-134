// M6T1
// Adrian Rodriguez
// 04/15/2026

#include <iostream>
using namespace std;

// Function declarations
void part1();
void part2();

int main() {
    part1();
    part2();
    return 0;
}


// Part 1: No Arrays

void part1() {
    const int DAYS = 5;
    int count = 0;
    int cars_today;
    int total = 0;
    double average;

    cout << "\nPART 1: No Arrays\n";
    cout << "Enter number of cars for Monday through Friday.\n";

    while (count < DAYS) {
        cout << "Day " << count + 1 << ": ";
        cin >> cars_today;
        total += cars_today;
        count++;
    }

    average = static_cast<double>(total) / DAYS;
    cout << "Total cars: " << total << endl;
    cout << "Average per day: " << average << endl;
}


// Part 2:Using Arrays

void part2() {
    const int SIZE = 5;
    int cars[SIZE];
    double sum = 0;
    double average;

    cout << "\nPART 2: Using Arrays\n";
    cout << "Enter number of cars for Monday through Friday.\n";

    // Input loop
    for (int i = 0; i < SIZE; i++) {
        cout << "Day " << i + 1 << ": ";
        cin >> cars[i];
    }

    // Sum loop
    for (int i = 0; i < SIZE; i++) {
        sum += cars[i];
    }

    average = sum / SIZE;

    cout << "Total cars: " << sum << endl;
    cout << "Average per day: " << average << endl;

}