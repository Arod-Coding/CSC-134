
// M6LAB1 - Slime Roulette
// Adrian Rodriguez
// 4/22/26

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// Function prototypes
void loadMagazine(vector<char>& mag,
                  int slime, int water);
void displayMagazine(const vector<char>& mag);
char fireShot(vector<char>& mag);

int main() {
    vector<char> magazine;

    int slime = 3;
    int water = 2;

    loadMagazine(magazine, slime, water);
    displayMagazine(magazine);

    if (!magazine.empty()) {
        char s = fireShot(magazine);
        cout << "You fired: " << s << endl;
    }

    displayMagazine(magazine);

    int playerHP = 3;
    int dealerHP = 3;
    char choice;
    char shot;
    slime = 1;
    water = 1;
    bool skip_next = false;

    while (playerHP > 0 && dealerHP > 0) {

        cout << "PLAYER: " << playerHP << " HP" << endl;
        cout << "DEALER: " << dealerHP << " HP" << endl;

        loadMagazine(magazine, slime, water);
        displayMagazine(magazine);

        // PLAYER TURN
        cout << "Your turn: fire at (s)elf or (d)ealer: ";
        cin >> choice;

        if (choice == 's' || choice == 'S') {
            cout << "You turn the gun on yourself...";

            if (!magazine.empty()) {
                char s = fireShot(magazine);

                if (s == 'S') {
                    cout << "SLIMED! (-1hp)\n";
                    playerHP -= 1;
                }
                else if (s == 'W') {
                    cout << "Water!\n";
                    skip_next = true;
                }
            }
        }
        else {
            cout << "You aim at the dealer...";

            if (!magazine.empty()) {
                char s = fireShot(magazine);

                if (s == 'S') {
                    cout << "SLIMED! (-1hp)\n";
                    dealerHP -= 1;
                }
                else {
                    cout << "Water!\n";
                }
            }
        }

        // reload if empty
        if (magazine.empty()) {
            slime++;
            water++;
            loadMagazine(magazine, slime, water);
            displayMagazine(magazine);
        }

        // DEALER TURN
        if (skip_next) {
            cout << "Skipping dealer's turn..." << endl;
            skip_next = false;
        }
        else {
            cout << "Dealer fires...\n";

            if (!magazine.empty()) {
                char s = fireShot(magazine);

                if (choice == 's' || choice == 'S') {
                    cout << "Dealer shoots self...";

                    if (s == 'S') {
                        cout << "SLIMED! (-1hp)\n";
                        dealerHP -= 1;
                    }
                    else {
                        cout << "Water!\n";
                    }
                }
                else {
                    cout << "Dealer shoots you...";

                    if (s == 'S') {
                        cout << "SLIMED! (-1hp)\n";
                        playerHP -= 1;
                    }
                    else {
                        cout << "Water!\n";
                    }
                }
            }

            // reload if empty
            if (magazine.empty()) {
                slime++;
                water++;
                loadMagazine(magazine, slime, water);
                displayMagazine(magazine);
            }
        }
    }

    return 0;
}

// FUNCTIONS (unchanged)

void loadMagazine(vector<char>& mag,
                  int slime, int water) {
    mag.clear();

    for (int i = 0; i < slime; i++) mag.push_back('S');
    for (int i = 0; i < water; i++) mag.push_back('W');

    random_device rd;
    mt19937 gen(rd());
    shuffle(mag.begin(), mag.end(), gen);
}

void displayMagazine(const vector<char>& mag) {
    int s = 0, w = 0;

    for (char shell : mag) {
        if (shell == 'S') s++;
        else w++;
    }

    cout << "Magazine: " << mag.size()
         << " remaining ("
         << s << " slime, "
         << w << " water)\n";
}

char fireShot(vector<char>& mag) {
    char shell = mag.back();
    mag.pop_back();
    return shell;