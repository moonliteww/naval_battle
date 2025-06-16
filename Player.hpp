#pragma once
#include "Field.hpp"

class Player {
public:
    virtual ~Player() = default;
    virtual std::pair<int, int> makeMove(Field& enemyField) = 0;
    virtual void setupField() = 0;

    Field ownField;
    Field enemyField;
};

class HumanPlayer : public Player {
public:
    HumanPlayer();
    std::pair<int, int> makeMove(Field& enemyField) override;
    void setupField() override;
};

class ComputerPlayer : public Player {
public:
    enum AIMode { RANDOM, SMART };
    ComputerPlayer(AIMode mode);
    std::pair<int, int> makeMove(Field& enemyField) override;
    void setupField() override;

private:
    AIMode mode;
    std::vector<std::pair<int, int>> hitStack;
};
