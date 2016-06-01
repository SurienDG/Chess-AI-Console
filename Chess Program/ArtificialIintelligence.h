//Artificiallintelligence.h is a class part of the Chess Program project file and is a header for Artificiallintelligence.cpp
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This header is used to connect to ArtificialIntelligence

// class definition
#ifndef ARTIFICIALIINTELLIGENCE_H
#define ARTIFICIALIINTELLIGENCE_H

//libarary included
#include <iostream>

using namespace std;


class ArtificialIntelligence
{
public:
    //Function to count the number of pieces
    int NumberOfPieces (string PrintRow[8][8], string piece);
    // function to evaluation a board position
    int  evaluation (string PrintRow[8][8], string player, string bools);
    // function to search many moves deep and return a score
    int AlphaBeta(int depth, int alpha, int beta, string PrintRow[8][8], string player, int turns, string bools);
    // function to get the top five best moves determined at a certain depth
    string BestMoves (string PrintRow[8][8], string player, int depth, string bools);
    // function to read text file with moves of an opening and to allow the main program along with this function to render
    // the move
    bool openings (string PrintRow[8][8], bool NormalKingUpper, bool NormalKingLower, bool NormalRookUpperRight,
                   bool NormalRookUpperLeft, bool NormalRookLowerRight, bool NormalRookLowerLeft, int NormalTemp1,  int NormalTemp2,char NormalTemp3,
                   string NormalEnPassant, string NormalPlayer);
    // function used in BestMoves to search depth
    int Negamax(int depth, int alpha, int beta, string PrintRow[8][8], string player, int turns, string bools);
protected:
private:
};

#endif // ARTIFICIALIINTELLIGENCE_H
