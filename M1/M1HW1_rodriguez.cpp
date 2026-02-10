// CSC 134
// M1HW1 - Movie Talk
// 01/21/26
// Adrian Rodriguez

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
string movieName = "Challengers";
int releaseYear = 2024;
double boxOffice = 96.1;

cout << fixed << setprecision(2);

cout << "Movie: " << movieName << endl;
cout << "Released in: " << releaseYear << endl;
cout << "Box office gross : $" << boxOffice << " million" << endl;
cout << endl;

// Favorite movie quote from my chosen scene
cout << "Favorite quote:" << endl;

cout << "\"Tashi Duncan: You don't know what tennis is.\"" << endl;
cout << "\"Patrick Zweig: What is it?\"" << endl;
cout << "\"Tashi Duncan: It's a relationship.\"" << endl;
cout << "\"Patrick Zweig: Is that what you and Anna Mueller had today?\"" << endl;
cout << "\"Tashi Duncan: It is, actually. For about fifteen seconds there, we were actually playing tennis. And we undertood each other completely. So did everyone watching. It's like we were in love. Or like we didn't exist. We went somewhere really beautiful together.\"" << endl;
cout << endl;
}