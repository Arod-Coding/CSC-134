// M6HW1
// Adrian Rodriguez
// 4/27/26

#include <iostream>
#include <string>
using namespace std;

// Rooms
enum Room {
    CONTROL = 0,
    STORAGE = 1,
    AIRLOCK = 2,
    NUM_ROOMS = 3
};

int main() {

    string roomNames[NUM_ROOMS] = {
        "Control Room",
        "Storage Lab",
        "Airlock"
    };

    string roomDescriptions[NUM_ROOMS] = {
        "Monitors flash red. A containment breach is in progress.",
        "Shelves of equipment line the walls. A keycard glows faintly.",
        "A heavy airlock door stands between you and freedom."
    };

    string roomDialogue[NUM_ROOMS] = {
        "ALERT: System failure detected. Find an exit.",
        "A note reads: 'Keycard required for emergency exit.'",
        "The door requires authorization to open."
    };

    // Game state
    int currentRoom = CONTROL;
    bool hasKeycard = false;
    bool gameRunning = true;

    cout << "=== SCIENCE LAB CONTAINMENT BREACH ===\n";

    while (gameRunning) {

        cout << "\nLocation: " << roomNames[currentRoom] << endl;
        cout << roomDescriptions[currentRoom] << endl;
        cout << roomDialogue[currentRoom] << endl;

        // Item pickup (Silver)
        if (currentRoom == STORAGE && !hasKeycard) {
            cout << "\nYou found a KEYCARD!\n";
            hasKeycard = true;
        }

        cout << "\nChoose action: (m)ove or (q)uit: ";
        char choice;
        cin >> choice;

        if (choice == 'q') {
            gameRunning = false;
        }
        else if (choice == 'm') {

            if (currentRoom == CONTROL) {
                cout << "You move into the Storage Lab...\n";
                currentRoom = STORAGE;
            }
            else if (currentRoom == STORAGE) {
                cout << "You head toward the Airlock...\n";
                currentRoom = AIRLOCK;
            }
            else if (currentRoom == AIRLOCK) {

                // GOLD: lock + win condition
                if (hasKeycard) {
                    cout << "\nKeycard accepted...\n";
                    cout << "Airlock opening...\n";
                    cout << "YOU ESCAPED THE FACILITY!\n";
                    gameRunning = false;
                } else {
                    cout << "LOCKED: Keycard required!\n";
                }
            }
        }
        else {
            cout << "Invalid input.\n";
        }
    }

    cout << "\nSimulation ended.\n";
    return 0;
}