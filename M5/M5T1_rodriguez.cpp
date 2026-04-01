// CSC 134
// M5T1
// Adrian Rodriguez
// 3/23/2026

#include <iostream>
using namespace std;

//Function Prototypes
void say_hello();
int give_the_answer();
int double_a_number(int num);

int main () {
    cout << "Hello from main()" << endl;

    // Call void function
    say_hello();

    // Call value-returning function
    int my_answer = give_the_answer ();
    cout << "The answer is: " << my_answer << endl;

    // Call function with perameter
    int twotimes = double_a_number(7);
    cout << "Here's another number: " << twotimes << endl;

    return 0;

}

// Function Definition 
void say_hello() {
    cout << "Hi from say_hello()" << endl;
}

int give_the_answer() {
    return 42;
}

int double_a_number(int num) {
    return num * 2;
}
