// M3LAB1
// Adrian Rodriguez
// 3/5/26

#include <iostream>
using namespace std;

// funtion prototypes
void search_trail();
void search_cabin();
void follow_footprints();
void explore_deeper();

int main() {

    int choice;

    cout << "======================================" << endl;
    cout << "        THE MISSING CLASSMATE         " << endl;
    cout << "======================================" << endl << endl;

    cout << "One of your classmates went missing during" << endl;
    cout << "a field trip in the woods." << endl;
    cout << "You decide to help search for them." << endl << endl;

    cout << "What do you do?" << endl;
    cout << "______________________________________" << endl;
    cout << "[1] Search the forest trail 🌲" << endl;
    cout << "[2] Check the old cabin nearby 🏚️" << endl;

    cout <<"> ";
    cin >> choice;

    if (choice == 1) {
        search_trail();
    }
    else if (choice == 2) {
        search_cabin();
    }
    else { 
        cout << "I didn't understand that." << endl;
    }

    cout << endl << "********** GAME OVER **********" << endl << endl;
    
    return 0;
}

// functions

void search_trail() {
    cout << endl;
    cout << "You walk along the forest trail." << endl;
    cout << "🌲🌲🌲🌲🌲🌲🌲🌲🌲" << endl;
    cout << "After a while, you see footprints leading off the path." << endl << endl;

    cout << "What do you do?" << endl;
    cout << "--------------------------------------" << endl;
    cout << "[1] Follow the footprints 👣" << endl;
    cout << "[2] Ignore them and go deeper into the woods 🌲" << endl;

    int choice;
    cout << ">";
    cin >> choice;

    if (choice == 1) {
        follow_footprints();
    }
    else if (choice == 2) {
        explore_deeper();
    }
}

void search_cabin() {
    cout << endl;
    cout << "You walk to the old cabin." << endl;
    cout << "       _______" << endl;
    cout << "      /      /|" << endl;
    cout << "     /______/ |" << endl;
    cout << "     |  _ _ | |" << endl;
    cout << "     | | | || |" << endl;
    cout << "     |______|/" << endl << endl;

    cout << "The door is open, but nobody is inside" << endl;
    cout << "You search around for a while." << endl;
    cout << "Eventually you realize..." << endl;
    cout << "You are lost in the woods." << endl;
    cout << "BAD ENDING: Now you are lost too." << endl;
}

void follow_footprints() {
    cout << endl;
    cout << "You follow the footprints deeper into thr woods." << endl;
    cout << "👣  👣  👣  👣  👣" << endl << endl;

    cout << "Suddebly you hear someone calling for help." << endl;
    cout << "It's your missing classmate!" << endl << endl;

    cout << "You help them and together you find the trial." << endl;
    cout << "You both make it back safely." << endl;
    cout << endl;
    cout << "GOOD ENDING: You found your classmate!" << endl;
}

void explore_deeper() {
    cout << endl;
    cout << "You walk deeper and deeper into the forest." << endl << endl;
    cout << "🌲🌲🌲🌲🌲🌲🌲🌲🌲" << endl;
    cout << "Everything starts to look the same." << endl << endl;

    cout << "You realize you don't know where you are anymore." << endl;
    cout << "You are completely lost." << endl << endl;

    cout << "BAD ENDING: Now you are lost too." << endl;
}