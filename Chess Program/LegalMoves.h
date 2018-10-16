//LegalMoves.h is a class part of the Chess Program project file and is a header for LegalMoves.cpp
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio
//This header is used to connect to LegalMoves

#ifndef LEGALMOVES_H
#define LEGALMOVES_H

#include <iostream>


class LegalMoves
{
public:
    // function to prevent a player from taking there own pieces. It also checks that pawns can only take pieces diagonally
    bool PieceCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,std::string PrintRow[8][8]);
// function to check to see if the user made a valid move for the pawn
    static bool PawnCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,std::string PrintRow[8][8]);
// function to check to see if the user made a valid move for the knight
    static bool KnightCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,std::string PrintRow[8][8]);
// function to check to see if the user made a valid move for the King
    static bool KingCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,std::string PrintRow[8][8]);
// function to check to see if the user made a valid move for the Rook
    static bool RookCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,std::string PrintRow[8][8]);
// function to check to see if the user made a valid move for the Bishop
    static bool BishopCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,std::string PrintRow[8][8]);
// function to check to see if the user made a valid move for the queen
    static bool QueenCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,std::string PrintRow[8][8]);
//check if check can be prevented
    bool CheckPrevention (int IntLetterOne, int num1, int IntLetterTwo, int num2,std::string PrintRow[8][8], std::string player);
//checks if king is in check
    std::string ischeck (std::string PrintRow[8][8], std::string player);
//check for valid castling
    bool CastlingCheck (std::string position, std::string PrintRow[8][8],std::string player,bool KingUpper,bool KingLower, bool RookUpperRight, bool RookUpperLeft,
                           bool RookLowerRight, bool RookLowerLeft,bool message);

protected:
private:
};

#endif // LEGALMOVES_H
