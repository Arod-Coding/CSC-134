// M6LAB2
// Adrian Rodriguez
// 4/27/26

#include <iostream>
#include <string>
using namespace std;

// Define constants for directions
enum Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    NUM_DIRECTIONS = 4
};

// Direction strings for output
const string DIRECTION_NAMES[NUM_DIRECTIONS] = {
    "north", "east", "south", "west"
};

// Define constants for rooms
enum Room {
    ENTRANCE_HALL = 0,
    LIBRARY = 1,
    KITCHEN = 2,
    GARDEN = 3,
    BASEMENT = 4,
    SECRET_ROOM = 5,
    STORAGE = 6,
    NUM_ROOMS = 7
};

int main() {

    // Room names array
    string roomNames[NUM_ROOMS] = {
        "Entrance Hall",
        "Library",
        "Kitchen",
        "Garden",
        "Basement",
        "Secret Room",
        "Storage Room"
    };

    // Room descriptions array
    string roomDescriptions[NUM_ROOMS] = {
        "A grand entrance hall with a dusty chandelier hanging above.",
        "Walls lined with ancient books. The air smells of old paper.",
        "A spacious kitchen with an old stove and wooden counter.",
        "An overgrown garden with stone pathways and a small fountain.",
        "A dark, damp basement with cobwebs in the corners.",
        "A hidden room behind a bookshelf. It feels unnatural.",
        "A cluttered storage room filled with broken furniture."
    };

    // Adjacency list
    int connections[NUM_ROOMS][NUM_DIRECTIONS];

    // Initialize all to no connection
    for (int i = 0; i < NUM_ROOMS; i++) {
        for (int j = 0; j < NUM_DIRECTIONS; j++) {
            connections[i][j] = -1;
        }
    }

    // ================= MAP CONNECTIONS =================

    connections[ENTRANCE_HALL][NORTH] = LIBRARY;
    connections[LIBRARY][SOUTH] = ENTRANCE_HALL;

    connections[ENTRANCE_HALL][EAST] = KITCHEN;
    connections[KITCHEN][WEST] = ENTRANCE_HALL;

    connections[ENTRANCE_HALL][WEST] = GARDEN;
    connections[GARDEN][EAST] = ENTRANCE_HALL;

    connections[KITCHEN][SOUTH] = BASEMENT;
    connections[BASEMENT][NORTH] = KITCHEN;

    connections[LIBRARY][EAST] = SECRET_ROOM;
    connections[SECRET_ROOM][WEST] = LIBRARY;

    connections[KITCHEN][EAST] = STORAGE;
    connections[STORAGE][WEST] = KITCHEN;

    // ================= GAME STATE =================

    int currentRoom = ENTRANCE_HALL;
    bool gameRunning = true;

    while (gameRunning) {

        // Display room info
        cout << "\nYou are in the " << roomNames[currentRoom] << endl;
        cout << roomDescriptions[currentRoom] << endl;

        // Show exits
        cout << "Exits: ";
        bool hasExits = false;

        for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
            if (connections[currentRoom][dir] != -1) {
                cout << DIRECTION_NAMES[dir] << " ";
                hasExits = true;
            }
        }

        if (!hasExits) cout << "none";
        cout << endl;

        // Input
        string command;
        cout << "\nWhat do you do? ";
        cin >> command;

        if (command == "quit" || command == "q") {
            gameRunning = false;
        }
        else if (command == "north" || command == "n") {
            if (connections[currentRoom][NORTH] != -1)
                currentRoom = connections[currentRoom][NORTH];
            else
                cout << "You can't go that way.\n";
        }
        else if (command == "east" || command == "e") {
            if (connections[currentRoom][EAST] != -1)
                currentRoom = connections[currentRoom][EAST];
            else
                cout << "You can't go that way.\n";
        }
        else if (command == "south" || command == "s") {
            if (connections[currentRoom][SOUTH] != -1)
                currentRoom = connections[currentRoom][SOUTH];
            else
                cout << "You can't go that way.\n";
        }
        else if (command == "west" || command == "w") {
            if (connections[currentRoom][WEST] != -1)
                currentRoom = connections[currentRoom][WEST];
            else
                cout << "You can't go that way.\n";
        }
        else {
            cout << "Unknown command.\n";
        }
    }

    cout << "\nThanks for playing!\n";
    return 0;
}