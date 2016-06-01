//ValidMoves.h is a class part of the Chess Program project file and is a header for Artificiallintelligence.cpp
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This header is used to connect to ValidMoves
#define VALIDMOVES_H
#include <iostream>

using namespace std;



class ValidMove
{
public:
    //Checks all valid moves for a piece
    string PieceValidMoves(int v, int q, int a, int b, bool (*function)(int,int,int,int,string[8][8]), string PrintRow[8][8],string player);
    // function to get all the valid moves for the rook
    string KingValidMoves (int v, int q, string PrintRow[8][8],string player);

    string ValidMoves (string PrintRow [8][8], string player, string bools);
// function to get all the valid moves for the bishop
    string BishopValidMoves (int IntLetterOne, int num1, string PrintRow[8][8], string player);
// function to get all the valid moves for the rook
    string PawnValidMoves (int v, int q, string PrintRow[8][8],string player);
// function to get all the valid moves for the rook
    string KnightValidMoves (int v, int q, string PrintRow[8][8],string player);
    // function to get all the valid moves for the rook
    string RookValidMoves (int IntLetterOne, int num1, string PrintRow[8][8],string player);
    //function to check for castling valid moves
    string CastlingValidMoves (int v, int q, string bools, string PrintRow[8][8], string player);
protected:
private:
};

#endif // VALIDMOVES_H
