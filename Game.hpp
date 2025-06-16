#pragma once
#include "Player.hpp"

class Game {
public:
    Game(Player* p1, Player* p2);
    void start();

private:
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    Player* opponent;

    void switchTurn();
};
