// Final Project
// Adrian Rodriguez
// 5/13/26

/*
 * =============================================================
 *   LAB ESCAPE
 * =============================================================
 *
 * A single mistake. One unlocked latch. Now the specimen roams the halls.
 * Your coworkers are gone. You barely escaped.
 * The monster knows you're here. It's toying with you.
 * But you have a plan: create a poison. Find the chemicals. Survive.
 * 
 * 
 * 
 *  Move room to room collecting chemicals.
 *  Reach the Mix Room with all 4 to attempt the formula.
 *  The monster is hunting you.
 *
 *  CONTROLS:
 *    n / s / e / w   Move
 *    p               Pick up chemical in this room
 *    q               Quit
 *
 *
 *  ENDINGS:
 *    1. Monster catches you        → DEAD
 *    2. Wrong mix order            → DEAD
 *    3. Correct mix order          → WIN
 * =============================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>

// ─────────────────────────────────────────
//  ROOM IDs
// ─────────────────────────────────────────
enum RoomID {
    STORAGE = 0,
    OFFICE,
    CHEM_BAY,
    LAB_BENCH,
    CONTAINMENT,
    MIX_ROOM,
    NUM_ROOMS
};

enum class GameState { PLAYING, WIN, DEAD_MONSTER, DEAD_MIX };

// ─────────────────────────────────────────
//  ROOM
// ─────────────────────────────────────────
struct Room {
    std::string          name;
    std::string          desc;
    std::map<char,RoomID> exits;   // 'n','s','e','w'
    std::string          chemical; // name of chemical here, "" if none / already taken
};

// ─────────────────────────────────────────
//  GAME
// ─────────────────────────────────────────
class Game {
public:
    Game();
    void run();

private:
    Room      rooms[NUM_ROOMS];
    RoomID    playerRoom;
    RoomID    monsterRoom;
    GameState state;

    // Inventory — just a list of chemical names collected
    std::vector<std::string> inventory;

    // Puzzle
    std::vector<std::string> chemNames;
    std::vector<int>         correctOrder; // indices into chemNames

    // Monster
    int monsterTick  = 0;
    int monsterSpeed = 2;

    // Messages (shown at bottom, cleared each turn)
    std::vector<std::string> msgs;

    void buildRooms();
    void generatePuzzle();

    void render();
    void drawCompass();
    void drawRoom();

    void handleInput(char cmd);
    void tryMove(char dir);
    void tryPickup();
    void doMixing();

    void moveMonster();
    RoomID bfsStep(RoomID from, RoomID to) const;

    void addMsg(const std::string& s);
    void showEnding();
    std::string repeat(char c, int n) const { return std::string(n, c); }
    std::string pad(const std::string& s, int w) const;
};

// ─────────────────────────────────────────
//  CONSTRUCTOR
// ─────────────────────────────────────────
Game::Game() : playerRoom(STORAGE), monsterRoom(CONTAINMENT), state(GameState::PLAYING) {
    srand(static_cast<unsigned>(time(nullptr)));
    chemNames = {"RedAcid", "BlueSolvent", "GreenBase", "YellowCatalyst"};
    generatePuzzle();
    buildRooms();
}

// ─────────────────────────────────────────
//  PUZZLE  — random mix order each run
// ─────────────────────────────────────────
void Game::generatePuzzle() {
    correctOrder = {0,1,2,3};
    for (int i = 3; i > 0; --i)
        std::swap(correctOrder[i], correctOrder[rand() % (i+1)]);
}

// ─────────────────────────────────────────
//  BUILD ROOMS
//
//  CIRCULAR LAYOUT (no dead ends, multiple paths):
//
//        STORAGE ──e── OFFICE ──e── CHEM_BAY
//           |                 |
//           s                 s
//           |                 |
//        CONTAINMENT       LAB_BENCH
//              \             /
//               \           /
//                ──e── MIX_ROOM
//
//  This creates multiple routes to every room!
// ─────────────────────────────────────────
void Game::buildRooms() {
    // STORAGE (0)
    rooms[STORAGE] = {
        "Storage Bay",
        "Overturned shelves. Red emergency lights. Exit south to Containment.",
        {{'e', OFFICE}, {'s', CONTAINMENT}},
        chemNames[correctOrder[0]]
    };
    
    // OFFICE (1)
    rooms[OFFICE] = {
        "Research Office",
        "Scattered papers. A half-erased whiteboard. Central hub.",
        {{'w', STORAGE}, {'e', CHEM_BAY}, {'s', LAB_BENCH}},
        chemNames[correctOrder[1]]
    };
    
    // CHEM_BAY (2)
    rooms[CHEM_BAY] = {
        "Chemical Storage",
        "Racks of labelled bottles. Sharp chemical smell.",
        {{'w', OFFICE}, {'s', LAB_BENCH}},
        chemNames[correctOrder[2]]
    };
    
    // LAB_BENCH (3)
    rooms[LAB_BENCH] = {
        "Lab Bench",
        "Steel workbenches. Burners still lit.",
        {{'n', OFFICE}, {'w', CHEM_BAY}, {'s', MIX_ROOM}},
        chemNames[correctOrder[3]]
    };
    
    // CONTAINMENT (4) - Monster starts here
    rooms[CONTAINMENT] = {
        "Containment Cell",
        "Blast glass scratched from the INSIDE. Lock shattered.",
        {{'n', STORAGE}, {'e', MIX_ROOM}},
        ""  // no chemical here
    };
    
    // MIX_ROOM (5)
    rooms[MIX_ROOM] = {
        "Mixing Lab",
        "Fume hoods and mixing equipment. This is where you end it.",
        {{'n', LAB_BENCH}, {'w', CONTAINMENT}},
        ""  // no chemical — this is where you mix
    };
}

// ─────────────────────────────────────────
//  HELPERS
// ─────────────────────────────────────────
std::string Game::pad(const std::string& s, int w) const {
    if ((int)s.size() >= w) return s.substr(0, w);
    int left = (w - (int)s.size()) / 2;
    int right = w - (int)s.size() - left;
    return std::string(left, ' ') + s + std::string(right, ' ');
}

void Game::addMsg(const std::string& s) { msgs.push_back(s); }

// ─────────────────────────────────────────
//  COMPASS
// ─────────────────────────────────────────
void Game::drawCompass() {
    Room& r = rooms[playerRoom];
    const int W = 46;

    auto info = [&](char dir) -> std::string {
        auto it = r.exits.find(dir);
        if (it == r.exits.end()) return "BLOCKED";
        RoomID nb = it->second;
        if (nb == monsterRoom)         return "MONSTER!";
        if (!rooms[nb].chemical.empty()) return "CHEM(!)";
        return " OPEN  ";
    };

    auto conn = [&](char dir, bool vertical) -> std::string {
        bool open = r.exits.count(dir) > 0;
        if (vertical) return open ? "|" : "X";
        return open ? "---" : "-X-";
    };

    std::string nI = info('n'), sI = info('s'), eI = info('e'), wI = info('w');
    std::string bar = "+" + repeat('-', W-2) + "+";

    std::cout << bar << "\n";
    // North
    std::cout << "|" << pad("[ N: " + nI + " ]", W-2) << "|\n";
    std::cout << "|" << pad(conn('n', true), W-2) << "|\n";
    // Mid
    std::string mid = "[ W: " + wI + " ]" + conn('w', false) + "[@]" + conn('e', false) + "[ E: " + eI + " ]";
    std::cout << "|" << pad(mid, W-2) << "|\n";
    // South
    std::cout << "|" << pad(conn('s', true), W-2) << "|\n";
    std::cout << "|" << pad("[ S: " + sI + " ]", W-2) << "|\n";
    std::cout << bar << "\n";
}

// ─────────────────────────────────────────
//  ROOM BOX
// ─────────────────────────────────────────
void Game::drawRoom() {
    Room& r = rooms[playerRoom];
    const int W = 46;
    std::string bar = "+" + repeat('-', W-2) + "+";

    std::cout << bar << "\n";
    std::cout << "|" << pad(r.name, W-2) << "|\n";
    std::cout << bar << "\n";
    std::cout << "|  " << std::left << std::setw(W-4) << r.desc << "  |\n";

    // Monster here?
    if (playerRoom == monsterRoom) {
        std::cout << "|" << pad("!! THE MONSTER IS HERE !!", W-2) << "|\n";
    }

    // Chemical here?
    if (!r.chemical.empty()) {
        std::cout << "|  " << std::left << std::setw(W-4)
                  << ("[!] " + r.chemical + " is here  --  press [p] to grab it") << "  |\n";
    }

    // Mix room special prompt
    if (playerRoom == MIX_ROOM) {
        int have = (int)inventory.size();
        if (have < 4) {
            std::cout << "|  " << std::left << std::setw(W-4)
                      << ("You have " + std::to_string(have) + "/4 chemicals. Keep searching.") << "  |\n";
        } else {
            std::cout << "|" << pad("You have all 4!  Press [m] to mix.", W-2) << "|\n";
        }
    }

    std::cout << bar << "\n";
}

// ─────────────────────────────────────────
//  INVENTORY BAR  (simple one-liner)
// ─────────────────────────────────────────
// ─────────────────────────────────────────
//  RENDER
// ─────────────────────────────────────────
void Game::render() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::cout << "+============================================+\n";
    std::cout << "|            L A B   E S C A P E            |\n";
    std::cout << "+============================================+\n\n";

    drawRoom();
    std::cout << "\n";
    drawCompass();

    // Inventory one-liner
    std::cout << "\nChemicals collected (" << inventory.size() << "/4): ";
    if (inventory.empty()) std::cout << "none";
    else for (auto& c : inventory) std::cout << c << "  ";
    std::cout << "\n";

    // Controls
    if (playerRoom == MIX_ROOM && (int)inventory.size() == 4)
        std::cout << "Controls: [n/s/e/w] Move   [m] Mix   [q] Quit\n";
    else
        std::cout << "Controls: [n/s/e/w] Move   [p] Pick up   [q] Quit\n";

    // Messages
    if (!msgs.empty()) {
        std::cout << "\n";
        for (auto& m : msgs) std::cout << "  > " << m << "\n";
    }
    std::cout << "\nCommand: ";
}

// ─────────────────────────────────────────
//  INPUT
// ─────────────────────────────────────────
void Game::handleInput(char cmd) {
    msgs.clear();
    switch (cmd) {
        case 'n': case 's': case 'e': case 'w': tryMove(cmd); break;
        case 'p': tryPickup(); break;
        case 'm': doMixing();  break;
        case 'q': state = GameState::DEAD_MONSTER; break;
        default:  addMsg("Use n/s/e/w to move, p to pick up, m to mix."); break;
    }
}

void Game::tryMove(char dir) {
    auto& exits = rooms[playerRoom].exits;
    auto it = exits.find(dir);
    if (it == exits.end()) { addMsg("Blocked — no exit that way."); return; }
    playerRoom = it->second;

    // Monster moves every N turns
    if (++monsterTick >= monsterSpeed) {
        monsterTick = 0;
        moveMonster();
    }
    if (playerRoom == monsterRoom) state = GameState::DEAD_MONSTER;
}

void Game::tryPickup() {
    Room& r = rooms[playerRoom];
    if (r.chemical.empty()) { addMsg("Nothing to pick up here."); return; }
    inventory.push_back(r.chemical);
    addMsg("Grabbed: " + r.chemical);
    r.chemical = "";
}

// ─────────────────────────────────────────
//  MIXING  — only accessible in MIX_ROOM
// ─────────────────────────────────────────
void Game::doMixing() {
    if (playerRoom != MIX_ROOM) { addMsg("You need to be in the Mixing Lab to mix."); return; }
    if ((int)inventory.size() < 4) {
        addMsg("You only have " + std::to_string(inventory.size()) + "/4 chemicals.");
        return;
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::cout << "+============================================+\n";
    std::cout << "|          M I X I N G   L A B              |\n";
    std::cout << "+============================================+\n\n";

    std::cout << "  Your chemicals:\n";
    for (int i = 0; i < 4; ++i)
        std::cout << "    " << (i+1) << ". " << inventory[i] << "\n";

    std::cout << "\n  The correct order is written on the plaques\n";
    std::cout << "  mounted above each flask on the bench.\n";
    std::cout << "  The plaques read (squinting through the haze):\n\n";

    // Show the correct order as found notes — player reads them here
    for (int step = 0; step < 4; ++step) {
        std::cout << "    Plaque " << (step+1) << ": \"Add " << chemNames[correctOrder[step]] << " here.\"\n";
    }

    std::cout << "\n  Enter your mix order — 4 numbers (1-4),\n";
    std::cout << "  matching each plaque step.\n";
    std::cout << "  Example: if plaque 1 says RedAcid and RedAcid\n";
    std::cout << "  is #2 in your list, enter 2 for step 1.\n\n";

    // Show numbered list again for reference
    std::cout << "  Your chemicals again:\n";
    for (int i = 0; i < 4; ++i)
        std::cout << "    " << (i+1) << ". " << inventory[i] << "\n";

    std::cout << "\n  Order (space-separated): ";

    std::vector<int> chosen(4);
    for (int i = 0; i < 4; ++i) { std::cin >> chosen[i]; chosen[i]--; }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Validate
    for (int v : chosen)
        if (v < 0 || v > 3) { addMsg("Invalid numbers — use 1 to 4."); return; }

    // Check: chosen[step] is which inventory slot → that slot's chem name
    // correctOrder[step] is the chem index that should go in step
    bool correct = true;
    for (int step = 0; step < 4; ++step) {
        // inventory[chosen[step]] should equal chemNames[correctOrder[step]]
        if (inventory[chosen[step]] != chemNames[correctOrder[step]]) {
            correct = false;
            break;
        }
    }

    state = correct ? GameState::WIN : GameState::DEAD_MIX;
}

// ─────────────────────────────────────────
//  MONSTER  (BFS over room graph)
// ─────────────────────────────────────────
RoomID Game::bfsStep(RoomID from, RoomID to) const {
    if (from == to) return from;
    std::map<RoomID,RoomID> prev;
    std::vector<RoomID> q = {from};
    std::set<RoomID> vis = {from};
    for (int qi = 0; qi < (int)q.size(); ++qi) {
        for (auto& [dir, nb] : rooms[q[qi]].exits) {
            if (vis.count(nb)) continue;
            vis.insert(nb); prev[nb] = q[qi]; q.push_back(nb);
            if (nb == to) goto done;
        }
    }
    return from;
    done:
    RoomID cur = to;
    while (prev[cur] != from) cur = prev[cur];
    return cur;
}

void Game::moveMonster() {
    monsterRoom = bfsStep(monsterRoom, playerRoom);
    if (monsterRoom == playerRoom) state = GameState::DEAD_MONSTER;
}

// ─────────────────────────────────────────
//  ENDINGS
// ─────────────────────────────────────────
void Game::showEnding() {
    std::cout << "\n\n";
    if (state == GameState::WIN) {
        std::cout << "+============================================+\n";
        std::cout << "|           Y O U   W I N !                 |\n";
        std::cout << "+============================================+\n";
        std::cout << "  The formula works. The creature convulses,\n";
        std::cout << "  collapses, and dissolves into the floor.\n";
        std::cout << "  You stagger out into the cold night air.\n\n";
    } else if (state == GameState::DEAD_MONSTER) {
        std::cout << "+============================================+\n";
        std::cout << "|           G A M E   O V E R               |\n";
        std::cout << "|        The monster caught you.             |\n";
        std::cout << "+============================================+\n";
        std::cout << "  Two pale eyes in the dark. Then nothing.\n\n";
    } else {
        std::cout << "+============================================+\n";
        std::cout << "|           G A M E   O V E R               |\n";
        std::cout << "|         Wrong mix order.                   |\n";
        std::cout << "+============================================+\n";
        std::cout << "  A billow of toxic gas erupts from the flask.\n";
        std::cout << "  You collapse before reaching the door.\n\n";
    }
    std::cout << "Play again? (y/n): ";
}

// ─────────────────────────────────────────
//  MAIN LOOP
// ─────────────────────────────────────────
void Game::run() {
    addMsg("CONTAINMENT BREACH. The creature is loose.");
    addMsg("Find all 4 chemicals, then reach the Mixing Lab.");
    while (state == GameState::PLAYING) {
        render();
        char cmd; std::cin >> cmd;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        handleInput(cmd);
    }
    render();
    showEnding();
}

int main() {
    char again = 'y';
    while (again == 'y' || again == 'Y') {
        Game g;
        g.run();
        std::cin >> again;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "\nThanks for playing Lab Escape!\n";
    return 0;
}