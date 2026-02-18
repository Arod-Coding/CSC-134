/*
CSC 134
M2T2 - Receipt calculator
Adrian Rodriguez
02/09/2026
Goal: A correct looking receipt that handles sales tax.
Assumption: Sales tax is 8% (varies by county)
*/

#include <iostream>
using namespace std;
// if you don't use namespace, type std::cout every time instead of cout (also cin)

int main() {
    // Today's roleplay: we're making the receipt printer for a restaurant.
    // Declare all variables
    string meal_name = "Burger Platter";   // change to anything
    double meal_price = 5.99;              // $5.99
    double tax_rate = 0.08;                // 8% is 8/100 ("per cent")
    double tip_amount; 
    double tax_amount;                     // $ of the actuua; tax charged
    double totoal_price;                   // meal + tip + tax


    // Get user input
    cout << "Welcome to the CSC 134 Grill." << endl;

    //Do the calculation

    //present the output

return 0; // no errors 

}