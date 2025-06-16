#include "Field.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

Field::Field(bool hide) : hideShips(hide) {
    grid.resize(SIZE, std::vector<Cell>(SIZE, EMPTY));
}

bool Field::isValidPosition(int x, int y, int size, bool horizontal) const {
    if (x < 0 || y < 0 || (horizontal ? x + size > SIZE : y + size > SIZE))
        return false;

    for (int i = 0; i < size; ++i) {
        int nx = horizontal ? x + i : x;
        int ny = horizontal ? y : y + i;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int tx = nx + dx;
                int ty = ny + dy;
                if (tx >= 0 && tx < SIZE && ty >= 0 && ty < SIZE) {
                    if (grid[ty][tx] == SHIP)
                        return false;
                }
            }
        }
    }

    return true;
}

void Field::placeShip(int x, int y, int size, bool horizontal) {
    if (!isValidPosition(x, y, size, horizontal)) {
        throw std::runtime_error("Неверное положение корабля");
    }

    for (int i = 0; i < size; ++i) {
        int nx = horizontal ? x + i : x;
        int ny = horizontal ? y : y + i;
        grid[ny][nx] = SHIP;
        shipPositions.emplace_back(nx, ny);
    }
}

void Field::autoPlaceShips() {
    srand(time(0));
    const int shipSizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    for (int size : shipSizes) {
        bool placed = false;
        while (!placed) {
            int x = rand() % SIZE;
            int y = rand() % SIZE;
            bool horiz = rand() % 2;

            try {
                placeShip(x, y, size, horiz);
                placed = true;
            } catch (...) {}
        }
    }
}

bool Field::receiveShot(int x, int y) {
    if (grid[y][x] == SHIP) {
        grid[y][x] = HIT;
        return true;
    } else if (grid[y][x] == EMPTY) {
        grid[y][x] = MISS;
    }
    return false;
}

bool Field::allShipsSunk() const {
    for (const auto& [x, y] : shipPositions) {
        if (grid[y][x] != HIT)
            return false;
    }
    return true;
}

void Field::display() const {
    std::cout << "   ";
    for (int i = 0; i < SIZE; ++i) std::cout << i+1 << " ";
    std::cout << "\n";

    for (int y = 0; y < SIZE; ++y) {
        std::cout << char('A' + y) << " |";
        for (int x = 0; x < SIZE; ++x) {
            switch (grid[y][x]) {
                case EMPTY: std::cout << "  "; break;
                case SHIP:  std::cout << (hideShips ? "  " : "■ "); break;
                case MISS:  std::cout << "• "; break;
                case HIT:   std::cout << "X "; break;
            }
        }
        std::cout << "|\n";
    }
}
