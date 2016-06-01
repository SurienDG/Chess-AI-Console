//conversion.cpp is a class part of the Chess Program project file
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This Class of the chess program project file is used to convert different inputs to other types

#include "Conversion.h"
//includes header as well

// function to convert a chracter to an integer
int Conversion::CharToInt (char InputChar) //converts the char into int
{
       int number=(int(InputChar)-48);
    //changes char values to int then returns values
    return number; //returns the int values
}
// fucntion to convert a string to an integer
int Conversion::StringToInt (string InputString) //converts string values into integer
{
    int number=0;
    int TimesTen=1; //declares variables number and timesten

    for (int i=InputString.length()-1; i>=0; i--)
    {
        char character=InputString[i]; //the character equals a space going down in inputstring
        number+=(int(character)-48)*TimesTen;  //multiply int character by 10 to convert to number
        TimesTen*=10; //times ten turns to 10
    }
    return number;
}
// function to convert a character (1 or 0) to a bool
bool Conversion::CharToBool (char Character)
{
    if (Character=='1')return true; //if it's 1 then it's true
    else return false; //if it''s not 1 then it's false
}

// function to convert letters on the board so they are the correct way
char Conversion::ConvertingLetters(char MovesConvert)
{
    if (MovesConvert=='A') MovesConvert='H'; //converts a-h to represent board value
    else if (MovesConvert=='H') MovesConvert='A';
    else if (MovesConvert=='B') MovesConvert='G';
    else if (MovesConvert=='G') MovesConvert='B';
    else if (MovesConvert=='C') MovesConvert='F';
    else if (MovesConvert=='F') MovesConvert='C';
    else if (MovesConvert=='D') MovesConvert='E';
    else if (MovesConvert=='E') MovesConvert='D';

    return MovesConvert; //returns coverted moves
}
