#include "Player.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

HumanPlayer::HumanPlayer() {
    ownField = Field(false);
    enemyField = Field(true);
}

void HumanPlayer::setupField() {
    std::cout << "Расставьте свои корабли вручную:\n";
    const int sizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    for (int size : sizes) {
        bool valid = false;
        while (!valid) {
            ownField.display();
            std::cout << "Введите координаты для корабля из " << size << " палуб (например: A3 H): ";
            std::string input;
            std::getline(std::cin, input);
            std::istringstream iss(input);
            char yChar;
            int x;
            char orientation;
            if (!(iss >> yChar >> x >> orientation)) {
                std::cout << "Ошибка ввода\n";
                continue;
            }
            int y = yChar - 'A';
            x -= 1;
            bool horizontal = (orientation == 'h' || orientation == 'H');
            try {
                ownField.placeShip(x, y, size, horizontal);
                valid = true;
            } catch (...) {
                std::cout << "Неверное расположение корабля. Попробуйте снова.\n";
            }
        }
    }
}

std::pair<int, int> HumanPlayer::makeMove(Field& enemyField) {
    while (true) {
        std::cout << "Введите координаты выстрела (например: A5): ";
        std::string input;
        std::getline(std::cin, input);
        if (input.length() < 2) continue;

        int x = input[1] - '1';
        int y = input[0] - 'A';

        if (x >= 0 && x < Field::SIZE && y >= 0 && y < Field::SIZE) {
            return {x, y};
        }
        std::cout << "Неверные координаты!\n";
    }
}

ComputerPlayer::ComputerPlayer(AIMode m) : mode(m) {
    ownField.autoPlaceShips();
    enemyField = Field(true);
}

void ComputerPlayer::setupField() {
    ownField.autoPlaceShips();
}

std::pair<int, int> ComputerPlayer::makeMove(Field& enemyField) {
    if (mode == RANDOM) {
        int x, y;
        do {
            x = rand() % Field::SIZE;
            y = rand() % Field::SIZE;
        } while (enemyField.receiveShot(x, y));
        return {x, y};
    } else {
        for (int y = 0; y < Field::SIZE; ++y) {
            for (int x = 0; x < Field::SIZE; ++x) {
                if (enemyField.enemyField.grid[y][x] == Field::HIT) {
                    for (auto [dx, dy] : std::vector<std::pair<int, int>>({{0,1},{1,0},{0,-1},{-1,0}})) {
                        int nx = x + dx, ny = y + dy;
                        if (nx >= 0 && nx < Field::SIZE && ny >= 0 && ny < Field::SIZE &&
                            enemyField.enemyField.grid[ny][nx] != Field::MISS &&
                            enemyField.enemyField.grid[ny][nx] != Field::HIT) {
                            return {nx, ny};
                        }
                    }
                }
            }
        }
        // Если не нашлось, то случайный
        return makeMove(enemyField); // рекурсия только для примера
    }
}
