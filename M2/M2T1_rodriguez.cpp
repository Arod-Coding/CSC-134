//ICSC 134
// M2T1
// Adrian Rodriguez
// 02/09/2025

#include <iostream>
using namespace std;

int main() {
//cout << "Hello World!\n";
string name;
int apples;
double pricePerApple;

cout << "Please enter your name: ";
cin >> name;

cout << "Enter the number of apples: ";
cin >> apples;

cout << "Enter the price per apple: ";
cin >> pricePerApple;

cout << "Welcome to " << name << "'s apple farm" << endl;

cout << "We have " << apples << " apples for sale" << endl;

cout << "Price is $" << pricePerApple << " each." << endl;

//noe calculate total price
double totalPrice = (double) apples * pricePerApple;
cout << "Total price is: $" <<totalPrice
<<endl;
}