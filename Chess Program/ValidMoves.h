//ValidMoves.h is a class part of the Chess Program project file and is a header for Artificiallintelligence.cpp
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This header is used to connect to ValidMoves
#ifndef VALIDMOVES_H
#define VALIDMOVES_H

#include <iostream>

class ValidMove
{
public:
    //Checks all valid moves for a piece
    std::string PieceValidMoves(int v, int q, int a, int b, bool (*function)(int,int,int,int,std::string[8][8]), std::string PrintRow[8][8],std::string player);
    // function to get all the valid moves for the rook
    std::string KingValidMoves (int v, int q, std::string PrintRow[8][8],std::string player);

    std::string ValidMoves (std::string PrintRow [8][8], std::string player, std::string bools);
// function to get all the valid moves for the bishop
    std::string BishopValidMoves (int IntLetterOne, int num1, std::string PrintRow[8][8], std::string player);
// function to get all the valid moves for the rook
    std::string PawnValidMoves (int v, int q, std::string PrintRow[8][8],std::string player);
// function to get all the valid moves for the rook
    std::string KnightValidMoves (int v, int q, std::string PrintRow[8][8],std::string player);
    // function to get all the valid moves for the rook
    std::string RookValidMoves (int IntLetterOne, int num1, std::string PrintRow[8][8],std::string player);
    //function to check for castling valid moves
    std::string CastlingValidMoves (int v, int q, std::string bools, std::string PrintRow[8][8], std::string player);
protected:
private:
};

#endif // VALIDMOVES_H
