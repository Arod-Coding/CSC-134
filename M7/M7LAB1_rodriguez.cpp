// M7T1
// Adrian Rodriguez
// 5/11/2026

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

/* ---------- Direction Enum ---------- */
enum Direction { NORTH, SOUTH, EAST, WEST };

/* Direction offsets (x, y) */
const std::pair<int, int> DIRECTION_OFFSETS[] = {
    {0, -1},  // NORTH
    {0, 1},   // SOUTH
    {1, 0},   // EAST
    {-1, 0}   // WEST
};

/* Opposite directions */
Direction opposite(Direction d) {
    if (d == NORTH) return SOUTH;
    if (d == SOUTH) return NORTH;
    if (d == EAST)  return WEST;
    return EAST;
}

/* ---------- Cell Class ---------- */
class Cell {
private:
    int row, col;
    std::unordered_map<Direction, bool> links;

public:
    Cell(int r = 0, int c = 0) : row(r), col(c) {}

    int getRow() const { return row; }
    int getCol() const { return col; }

    void link(Cell& other, Direction dir) {
        links[dir] = true;
        other.links[opposite(dir)] = true;
    }

    bool linked(Direction dir) const {
        return links.count(dir) && links.at(dir);
    }

    std::vector<Direction> getLinks() const {
        std::vector<Direction> result;
        for (auto& pair : links) {
            if (pair.second) result.push_back(pair.first);
        }
        return result;
    }
};

/* ---------- Grid Class ---------- */
class Grid {
private:
    int rows, cols;
    std::vector<std::vector<Cell>> grid;

public:
    Grid(int r, int c) : rows(r), cols(c) {
        for (int i = 0; i < rows; i++) {
            std::vector<Cell> row;
            for (int j = 0; j < cols; j++) {
                row.emplace_back(i, j);
            }
            grid.push_back(row);
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    bool isValid(int r, int c) const {
        return r >= 0 && r < rows && c >= 0 && c < cols;
    }

    Cell& at(int r, int c) {
        return grid[r][c];
    }

    const Cell& at(int r, int c) const {
        return grid[r][c];
    }

    void display() const {
        std::cout << "+";
        for (int c = 0; c < cols; c++) std::cout << "---+";
        std::cout << "\n";

        for (int r = 0; r < rows; r++) {
            std::cout << "|";
            for (int c = 0; c < cols; c++) {
                std::cout << "   ";
                if (at(r, c).linked(EAST)) std::cout << " ";
                else std::cout << "|";
            }
            std::cout << "\n+";
            for (int c = 0; c < cols; c++) {
                if (at(r, c).linked(SOUTH)) std::cout << "   +";
                else std::cout << "---+";
            }
            std::cout << "\n";
        }
    }
};

/* ---------- Binary Tree Maze Generator ---------- */
class BinaryTreeMaze {
public:
    static void on(Grid& grid) {
        std::srand((unsigned)std::time(nullptr));

        for (int r = 0; r < grid.getRows(); r++) {
            for (int c = 0; c < grid.getCols(); c++) {
                std::vector<Direction> neighbors;

                if (grid.isValid(r - 1, c)) neighbors.push_back(NORTH);
                if (grid.isValid(r, c + 1)) neighbors.push_back(EAST);

                if (!neighbors.empty()) {
                    Direction dir = neighbors[std::rand() % neighbors.size()];
                    int nr = r + DIRECTION_OFFSETS[dir].second;
                    int nc = c + DIRECTION_OFFSETS[dir].first;
                    grid.at(r, c).link(grid.at(nr, nc), dir);
                }
            }
        }
    }
};

/* ---------- Distances Class ---------- */
class Distances {
private:
    std::unordered_map<std::string, int> cells;
    Cell* root;

    std::string key(int r, int c) const {
        return std::to_string(r) + "," + std::to_string(c);
    }

public:
    Distances(Cell& start) : root(&start) {
        cells[key(start.getRow(), start.getCol())] = 0;
    }

    int getDistance(const Cell& cell) const {
        auto k = key(cell.getRow(), cell.getCol());
        if (cells.count(k)) return cells.at(k);
        return std::numeric_limits<int>::max();
    }

    void setDistance(const Cell& cell, int d) {
        cells[key(cell.getRow(), cell.getCol())] = d;
    }

    Cell* getMaxCell(Grid& grid) const {
        int max = 0;
        Cell* result = root;

        for (auto& pair : cells) {
            if (pair.second > max) {
                int comma = pair.first.find(',');
                int r = std::stoi(pair.first.substr(0, comma));
                int c = std::stoi(pair.first.substr(comma + 1));
                if (grid.isValid(r, c)) {
                    max = pair.second;
                    result = &grid.at(r, c);
                }
            }
        }
        return result;
    }
};

/* ---------- Dijkstra Algorithm ---------- */
class Dijkstra {
public:
    static Distances calculate(Grid& grid, Cell& start) {
        Distances distances(start);

        auto key = [](Cell& c) {
            return std::to_string(c.getRow()) + "," + std::to_string(c.getCol());
        };

        std::priority_queue<
            std::pair<int, std::string>,
            std::vector<std::pair<int, std::string>>,
            std::greater<>
        > frontier;

        frontier.push({0, key(start)});

        while (!frontier.empty()) {
            auto [dist, k] = frontier.top();
            frontier.pop();

            int comma = k.find(',');
            int r = std::stoi(k.substr(0, comma));
            int c = std::stoi(k.substr(comma + 1));

            Cell& cell = grid.at(r, c);

            for (Direction dir : cell.getLinks()) {
                int nr = r + DIRECTION_OFFSETS[dir].second;
                int nc = c + DIRECTION_OFFSETS[dir].first;
                if (!grid.isValid(nr, nc)) continue;

                Cell& neighbor = grid.at(nr, nc);
                int newDist = dist + 1;

                if (newDist < distances.getDistance(neighbor)) {
                    distances.setDistance(neighbor, newDist);
                    frontier.push({newDist, key(neighbor)});
                }
            }
        }
        return distances;
    }

    static std::vector<Cell*> longestPath(Grid& grid) {
        Cell& start = grid.at(0, 0);
        Distances d1 = calculate(grid, start);
        Cell* mid = d1.getMaxCell(grid);
        Distances d2 = calculate(grid, *mid);
        Cell* end = d2.getMaxCell(grid);
        return { mid, end };
    }
};

/* ---------- Path Display ---------- */
void displayWithPath(const Grid& grid, const std::vector<Cell*>& path) {
    auto onPath = [&](const Cell& cell) {
        for (auto* c : path) {
            if (c->getRow() == cell.getRow() && c->getCol() == cell.getCol())
                return true;
        }
        return false;
    };

    std::cout << "+";
    for (int c = 0; c < grid.getCols(); c++) std::cout << "---+";
    std::cout << "\n";

    for (int r = 0; r < grid.getRows(); r++) {
        std::cout << "|";
        for (int c = 0; c < grid.getCols(); c++) {
            if (onPath(grid.at(r, c))) std::cout << " X ";
            else std::cout << "   ";
            if (grid.at(r, c).linked(EAST)) std::cout << " ";
            else std::cout << "|";
        }
        std::cout << "\n+";
        for (int c = 0; c < grid.getCols(); c++) {
            if (grid.at(r, c).linked(SOUTH)) std::cout << "   +";
            else std::cout << "---+";
        }
        std::cout << "\n";
    }
}

/* ---------- Main ---------- */
int main() {
    Grid grid(10, 10);
    BinaryTreeMaze::on(grid);

    std::cout << "Generated Maze:\n";
    grid.display();

    std::cout << "\nMaze Path:\n";
    auto path = Dijkstra::longestPath(grid);
    displayWithPath(grid, path);

    return 0;
}