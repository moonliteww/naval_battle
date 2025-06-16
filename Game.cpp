#include "Game.hpp"
#include <iostream>

Game::Game(Player* p1, Player* p2) : player1(p1), player2(p2), currentPlayer(p1), opponent(p2) {}

void Game::switchTurn() {
    std::swap(currentPlayer, opponent);
}

void Game::start() {
    player1->setupField();
    player2->setupField();

    while (true) {
        std::cout << "\nВаше поле:\n";
        currentPlayer->ownField.display();
        std::cout << "\nПоле противника:\n";
        currentPlayer->enemyField.display();

        auto [x, y] = currentPlayer->makeMove(*opponent->ownField);
        bool hit = opponent->ownField->receiveShot(x, y);

        std::cout << (hit ? "Попадание!" : "Промах.") << "\n";

        if (opponent->ownField.allShipsSunk()) {
            std::cout << "\n" << typeid(*currentPlayer).name() << " победил!\n";
            break;
        }

        if (!hit) switchTurn();
    }
}
