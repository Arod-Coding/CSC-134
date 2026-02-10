//ICSC 134
// M1LAB
// Adrian Rodriguez
// 01/26/2025

#include <iostream>
using namespace std;

int main() {
//cout << "Hello World!\n";
string name = "Adrian Rodriguez";
int apples = 255;
double pricePerApple = 0.25;

cout << "Welcome to " << name;
cout << "'s apple farm" << endl;

cout << "We have " << apples << " apples for sale" << endl;

cout << "price is $" << pricePerApple << "each." << endl;

//noe calculate total price
double totalPrice = (double) apples * pricePerApple;
cout << "Total price is: $" <<totalPrice
<<endl;
}