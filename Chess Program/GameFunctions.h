//gamefunctions.h is a class part of the Chess Program project file and is a header for gamefunctions.cpp
//Program created by Farzam Karimi, Surien, Claudio Gonzalez
//This header is used to connect to gamefunctions
#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <iostream>

class GameFunctions
{
public:
    // function to save the game
    void SaveGame(std::string PrintRow[8][8], std::string NameOfGameFile,  bool add);
// function to resume the game
    void ResumeGame(std::string PrintRow[8][8], std::string NameOfFile);
// function to reset the game
    void BoardSetup (std::string OriginalSetup [8][8], std::string PrintRow[8][8]);
    // log function
    void LoggingGames (std::string PrintRow[8][8], std::string NameOfGameFile, bool add,
                       std::string bools, int turns, std::string temps, std::string EnPassant, std::string LastMove );
protected:
private:
};

#endif // GAMEFUNCTIONS_H
