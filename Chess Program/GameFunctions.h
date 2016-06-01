//gamefunctions.h is a class part of the Chess Program project file and is a header for gamefunctions.cpp
//Program created by Farzam Karimi, Surien, Claudio Gonzalez
//This header is used to connect to gamefunctions
#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <iostream>

using namespace std;

class GameFunctions
{
public:
    // function to save the game
    void SaveGame(string PrintRow[8][8], string NameOfGameFile,  bool add);
// function to resume the game
    void ResumeGame(string PrintRow[8][8], string NameOfFile);
// function to reset the game
    void BoardSetup (string OriginalSetup [8][8], string PrintRow[8][8]);
    // log function
    void LoggingGames (string PrintRow[8][8], string NameOfGameFile, bool add,
                       string bools, int turns, string temps, string EnPassant, string LastMove );
protected:
private:
};

#endif // GAMEFUNCTIONS_H
