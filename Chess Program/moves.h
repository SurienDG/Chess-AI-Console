//moves.h is a class part of the Chess Program project file and is a header for moves.cpp
//Program created by Farzam Karimi, Surien, Claudio
//This header is used to connect to moves
#ifndef MOVES_H
#define MOVES_H

#include <iostream>


using namespace std;

class moves
{
    public:
    // functions to render different moves the user enters
    bool Moves (char letter1, int num1, char letter2, int num2, string PrintRow[8][8], bool MateCheck, string player);
    void MovesWithoutLegal (char letter1, int num1, char letter2, int num2, string PrintRow[8][8]);
    // function to check which player should be allowed to move and only allows that player to move
    bool CheckForTurn (string player, string piece);
    // function for the promotion of chess pieces
    string promotion (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8], string player);
    bool castling (string position, string PrintRow[8][8],string player);
    protected:
    private:
};

#endif // MOVES_H
