//Artificiallintelligence.h is a class part of the Chess Program project file and is a header for Artificiallintelligence.cpp
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This header is used to connect to ArtificialIntelligence

// class definition
#ifndef ARTIFICIALIINTELLIGENCE_H
#define ARTIFICIALIINTELLIGENCE_H

#include <iostream>

class ArtificialIntelligence
{
public:
    //Function to count the number of pieces
    int NumberOfPieces (std::string PrintRow[8][8], std::string piece);
    // function to evaluation a board position
    int  evaluation (std::string PrintRow[8][8], std::string player, std::string bools);
    // function to search many moves deep and return a score
    int AlphaBeta(int depth, int alpha, int beta, std::string PrintRow[8][8], std::string player, int turns, std::string bools);
    // function to get the top five best moves determined at a certain depth
    std::string BestMoves (std::string PrintRow[8][8], std::string player, int depth, std::string bools);
    // function to read text file with moves of an opening and to allow the main program along with this function to render
    // the move
    bool openings (std::string PrintRow[8][8], bool NormalKingUpper, bool NormalKingLower, bool NormalRookUpperRight,
                   bool NormalRookUpperLeft, bool NormalRookLowerRight, bool NormalRookLowerLeft, int NormalTemp1,  int NormalTemp2,char NormalTemp3,
                   std::string NormalEnPassant, std::string NormalPlayer);
    // function used in BestMoves to search depth
    int Negamax(int depth, int alpha, int beta, std::string PrintRow[8][8], std::string player, int turns, std::string bools);
protected:
private:
};

#endif // ARTIFICIALIINTELLIGENCE_H
