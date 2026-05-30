#pragma once

class Attacker
{
public:
    virtual Position makeMove(Board& enemyBoard) = 0;
    virtual void processResult(Board& board, Position pos, AttackResult result) {}
};