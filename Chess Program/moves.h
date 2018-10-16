//moves.h is a class part of the Chess Program project file and is a header for moves.cpp
//Program created by Farzam Karimi, Surien, Claudio
//This header is used to connect to moves
#ifndef MOVES_H
#define MOVES_H

#include <iostream>



class moves
{
    public:
    // functions to render different moves the user enters
    bool Moves (char letter1, int num1, char letter2, int num2, std::string PrintRow[8][8], bool MateCheck, std::string player);
    void MovesWithoutLegal (char letter1, int num1, char letter2, int num2, std::string PrintRow[8][8]);
    // function to check which player should be allowed to move and only allows that player to move
    bool CheckForTurn (std::string player, std::string piece);
    // function for the promotion of chess pieces
    std::string promotion (int IntLetterOne, int num1, int IntLetterTwo, int num2,std::string PrintRow[8][8], std::string player);
    bool castling (std::string position, std::string PrintRow[8][8],std::string player);
    protected:
    private:
};

#endif // MOVES_H
