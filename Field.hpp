#pragma once
#include <vector>
#include <utility>

class Field {
public:
    static const int SIZE = 10;

    enum Cell {
        EMPTY,
        SHIP,
        MISS,
        HIT
    };

    Field(bool hideShips = false);
    void placeShip(int x, int y, int size, bool horizontal);
    bool receiveShot(int x, int y);
    bool allShipsSunk() const;
    void display() const;
    void autoPlaceShips();

private:
    std::vector<std::vector<Cell>> grid;
    std::vector<std::pair<int, int>> shipPositions;
    bool hideShips;

    bool isValidPosition(int x, int y, int size, bool horizontal) const;
};
