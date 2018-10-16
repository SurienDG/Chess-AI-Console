//gamefunctions.cpp is a class part of the Chess Program project file
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This Class of the chess program project file is used to hold the special game functions such as saving the game
//logging, and resume etc

#include "GameFunctions.h"
#include <fstream>

// state that namespace std is being used
using namespace std;

void GameFunctions::SaveGame(string PrintRow[8][8], string NameOfGameFile,  bool add)
{
    //function for save game
    ofstream outputFile;
    //output file
    if (add==false)
        outputFile.open(NameOfGameFile.c_str() );
    //if it cant add the file
    else
        outputFile.open(NameOfGameFile.c_str(),ios_base::out | ios_base::app);


    for (int col=0; col<=7; col++)
    {
        for (int row=0; row<=7; row++)
        {
            //outputs the save file like our board
            outputFile << PrintRow[col][row][1];
        }
    }
    //closes function
    outputFile.close();
}
//resume function
void GameFunctions::ResumeGame(string PrintRow[8][8], string NameOfFile)
{
    //function to resume the game
    ifstream inputFile;
    string line;
    //gets values fromm old files
    int i=0;

    inputFile.open(NameOfFile.c_str());
    //opens save file

    getline(inputFile,line);
    inputFile.close();

    for (int col=0; col<=7; col++)
    {
        for (int row=0; row<=7; row++)
        {
            PrintRow[col][row][1]=line[i];
            i++;
            //outputs values from save file
        }
    }

}

void GameFunctions::BoardSetup (string OriginalSetup [8][8], string PrintRow[8][8])
{
    for (int col=0; col<=7; col++)
    {
        for (int row=0; row<=7; row++)
        {
            PrintRow[col][row]=OriginalSetup [col][row];
        }
        //setups the board according to chess rules
    }
}
// log function
void GameFunctions::LoggingGames (string PrintRow[8][8], string NameOfGameFile, bool add,
                                  string bools, int turns, string temps, string EnPassant, string LastMove)
{
    ofstream outputFile;

    SaveGame(PrintRow, NameOfGameFile.c_str(), add);
    // opens the output file
    outputFile.open(NameOfGameFile.c_str(),ios_base::out | ios_base::app);
    // writes boolean values to text file on next line
    outputFile <<endl<<bools;
    // writes the number of turns to text file
    if (add==true)
        outputFile <<endl<<(turns+1);
    else
    outputFile <<endl<<turns;
    //outputs turns
    outputFile <<endl<<temps;
    //outputs temp
    outputFile <<endl<<EnPassant;
    //outputs enpassant
    outputFile <<endl<<LastMove<<endl;
    // closes the file the program is writing to
    outputFile.close();
}
