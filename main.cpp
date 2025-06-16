#include "Game.hpp"
#include "Player.hpp"
#include <iostream>
#include <Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
  
    std::cout << "Выберите режим:\n1. Человек vs Компьютер\n2. Компьютер vs Компьютер\n";
    int choice;
    std::cin >> choice;

    Player* p1, *p2;

    if (choice == 1) {
        p1 = new HumanPlayer();
        p2 = new ComputerPlayer(Player::ComputerPlayer::SMART);
    } else {
        p1 = new ComputerPlayer(Player::ComputerPlayer::SMART);
        p2 = new ComputerPlayer(Player::ComputerPlayer::RANDOM);
    }

    Game game(p1, p2);
    game.start();

    delete p1;
    delete p2;

    return 0;
}
