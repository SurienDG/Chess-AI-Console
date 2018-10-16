//conversion.h is a class part of the Chess Program project file and is a header for conversion.cpp
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This header is used to connect to conversion

#ifndef CONVERSION_H
#define CONVERSION_H

//library included
#include <iostream>


class Conversion
{
public:
// function to convert a chracter to an integer
    int CharToInt (char InputChar);
// fucntion to convert a string to an integer
    int StringToInt (std::string InputString);
// function to convert a character (1 or 0) to a bool
    bool CharToBool (char Character);
    // function to convert letters on the board so they are the correct way
    char ConvertingLetters(char MovesConvert);

protected:
private:
};

#endif // CONVERSION_H
