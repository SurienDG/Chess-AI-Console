//Printchess.cpp is a class part of the Chess Program project file
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This Class of the chess program project file is used print the chessboard

#include "PrintChess.h"
#include <iomanip>
#include <windows.h>
//includes header and libraries

void PrintChess::PrintChess1(string PrintRow[8][8])
{//print chess 1

    cout<<" ";
    for (char col=8; col>=1; col--)cout<<setw(5)<<(char)(col+64);
    cout<<endl;
    //prints out letters
    cout<<"  "<<"__________________________________________"<<endl;
    //prints lines to make it spacs
    for (int row=0; row<=7; row++)
    {

        cout<<row+1<<" |";
        //makes seperates chessboard into spaces
        for (int col=0; col<=7; col++)
        {
            //column goes up by 1 to 7
            if (row%2!=0)
            {
                //if row isn't even
                if (col%2!=0)
                    //if col number isn't even
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 47 );
                //sets console attribute to 47
                else
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 31 );
                       //sets console attribute to 31

            }
            else if  (row%2==0)
            {
                //if row is even
                if (col%2==0)
                    //and col is even
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 47 );
                  //sets console attribute to 47
                else
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 31 );
                      //sets console attribute to 31
            }

            cout<<"|"<<PrintRow[row][col]<<"|";
            //prints line seperatting it

        }
        cout<<"|";
        //seperate the board
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
        //sets console attribute to 15
        cout<<endl<<"  "<<"__________________________________________"<<endl;
         //seperate the board
    }

}
void PrintChess::PrintChess2(string PrintRow[8][8])
{
//prints the other board for other view
    cout<<" ";
    //outputs the space
    for (char col=1; col<=8; col++)cout<<setw(5)<<(char)(col+64);
    cout<<endl;
    //outputs the characters for the grid

    cout<<"  "<<"__________________________________________"<<endl;
    //outputs line for seperation
    for (int row=7; row>=0; row--)
    {
        //outputs row going down
        cout<<row+1<<" |";
        for (int col=7; col>=0; col--)
        {
            if (col%2!=0)
            {
                //if col is odd
                if (row%2!=0)
                     //if row number odd
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 47 );
                //sets to 47
                else
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 31 );
                    //sets to 31

            }
            else if  (col%2==0)
            {
                //if col is even
                if (row%2==0)
                    //if row is even
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 47 );
                //sets to 47
                else
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 31 );
                    //sets to 31
            }
            cout<<"|"<<PrintRow[row][col]<<"|";
            //outputs to seperate board

        }
        cout<<"|";
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
        //sets to 15
        cout<<endl<<"  "<<"__________________________________________"<<endl;
        //seperates board horizontally
    }

}

