//Moves.cpp is a class part of the Chess Program project file
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This Class of the chess program project file is used determine moves for pieces


#include "moves.h"
#include "LegalMoves.h"
#include "PrintChess.h"
#include "Conversion.h"
#include <stdlib.h>
#include <windows.h>
//declares headers and libraries



bool moves::Moves (char letter1, int num1, char letter2, int num2, string PrintRow[8][8], bool MateCheck, string player)
{
    LegalMoves legal;
    // variable to temperarily store piece value
    string temp;
    // variable to hold number values of the letters
    int IntLetterOne=(int)letter1-64;
    int IntLetterTwo=(int)letter2-64;

    //temp holds the piece that needs to be moved
    temp=PrintRow [num1-1][IntLetterOne-1];
    // makes sure the user can't move a space
    if (temp=="   ")
    {
        //if empty returns false
        return false;
    }

    if (!(CheckForTurn(player,PrintRow [num1-1][IntLetterOne-1]))) return false;

    if (!(legal.PieceCheck(IntLetterOne,num1,IntLetterTwo,num2,PrintRow)))
    {
        return false;
        //returns f
    }

    // checks for valid moves for bishops
    if ((PrintRow [num1-1][IntLetterOne-1]==" b ") or (PrintRow [num1-1][IntLetterOne-1]==" B "))
    {
        if (!(legal.BishopCheck(IntLetterOne,num1,IntLetterTwo,num2,PrintRow)))
        {
            //valid move doesn't work for bishops
            return false;
        }
    }
    // checks for valid moves for queen
    if ((PrintRow [num1-1][IntLetterOne-1]==" q ") or (PrintRow [num1-1][IntLetterOne-1]==" Q "))
    {
        if (!(legal.QueenCheck(IntLetterOne,num1,IntLetterTwo,num2,PrintRow)))
        {
        //returns false if not true
            return false;
        }
    }


    // checks for valid moves for knights
    if ((PrintRow [num1-1][IntLetterOne-1]==" n ") or (PrintRow [num1-1][IntLetterOne-1]==" N "))
    {
        if (!(legal.KnightCheck(IntLetterOne,num1,IntLetterTwo,num2,PrintRow)))
        {
            return false;
        }
    }


    else if ((PrintRow [num1-1][IntLetterOne-1]==" p ") or (PrintRow [num1-1][IntLetterOne-1]==" P ") )
    {
        if (!(legal.PawnCheck(IntLetterOne,num1,IntLetterTwo,num2,PrintRow)))
        {
            return false;
            //returns false if pawncheck isn't true
        }
        if (num2==1 or num2==8)
        {
            temp=promotion (IntLetterOne,num1,IntLetterTwo,num2,PrintRow, player);
            //promotes pawn
        }
        //if pawn reaches other side of board it become another peice
        if (IntLetterTwo<=7 and (num2==num1+2 or num2==num1-2))
        {
            if (PrintRow [num1-1][IntLetterOne-1]==" p ")
            {
                if (PrintRow [num2-1][IntLetterTwo]==" P ")
                {
                    if (num2==num1+2) num2--;
                    else num2++;
                    //changes value where the pice moved two so it can alert the main program of the ability for en passant
                }
            }
            else
            {
                if (PrintRow [num2-1][IntLetterTwo]==" p ")
                {
                    if (num2==num1+2) num2--;
                    else num2++;
                    //changes value where the pice moved two so it can alert the main program of the ability for en passant
                }
            }
        }
        if (IntLetterTwo-2>=0 and (num2==num1+2 or num2==num1-2))
        {
            if (PrintRow [num1-1][IntLetterOne-1]==" p ")
            {
                //white
                if (PrintRow [num2-1][IntLetterTwo-2]==" P ")
                {
                    //Moves upper case pawn
                    if (num2==num1+2) num2--;
                    else num2++;
                }
            }
            else
            {
                if (PrintRow [num2-1][IntLetterTwo-2]==" p ")
                {
                    //for white
                    if (num2==num1+2) num2--;
                    else num2++;
                }
            }
        }

    }

    // checks for legal moves for the rook
    else if ((PrintRow [num1-1][IntLetterOne-1]==" R ") or (PrintRow [num1-1][IntLetterOne-1]==" r ") )
    {
        //uses a function to check if rook can move for both black and white
        if (!(legal.RookCheck(IntLetterOne,num1,IntLetterTwo,num2,PrintRow)))
        {
            //if not returns false
            return false;
        }
    }

    else if ((PrintRow [num1-1][IntLetterOne-1]==" K ") or (PrintRow [num1-1][IntLetterOne-1]==" k ") )
    {
        //uses a function to check if kinf can move for both Black and white
        if (!(legal.KingCheck(IntLetterOne,num1,IntLetterTwo,num2,PrintRow)))
        {
            //if not returns false
            return false;
        }
    }
    if (!(legal.CheckPrevention(IntLetterOne,num1,IntLetterTwo,num2,PrintRow, player)))
    {
        //refrences function to check for checkmate
        //if not returns an error
        if (MateCheck==false)cout<<"Can't move into check";
        return false;
    }

    // changes the value of the chess piece to a | so that the piece can be moved
    if (PrintRow [num2-1][IntLetterTwo-1]!="   ") PrintRow [num2-1][IntLetterTwo-1]="   ";
    //gives the old position the value of
    PrintRow [num1-1][IntLetterOne-1]=PrintRow [num2-1][IntLetterTwo-1];
    // gives the place where the piece is moved to the pieces new position
    PrintRow [num2-1][IntLetterTwo-1]=temp;
    // makes sure the user can't move a space

    return true;
}
void moves::MovesWithoutLegal (char letter1, int num1, char letter2, int num2, string PrintRow[8][8])
{
    LegalMoves legal;
    // variable to temperarily store piece value
    string temp;
    // variable to hold number values of the letters
    int IntLetterOne=(int)letter1-64;
    int IntLetterTwo=(int)letter2-64;

    //temp holds the piece that needs to be moved
    temp=PrintRow [num1-1][IntLetterOne-1];
    if (temp==" p " or temp==" P ")
    {
        if (num2==1)
            temp=" q ";
        else if (num2==8)
            temp=" Q ";
    }


    // changes the value of the chess piece to a | so that the piece can be moved
    if (PrintRow [num2-1][IntLetterTwo-1]!="   ") PrintRow [num2-1][IntLetterTwo-1]="   ";
    //gives the old position the value of
    PrintRow [num1-1][IntLetterOne-1]=PrintRow [num2-1][IntLetterTwo-1];
    // gives the place where the piece is moved to the pieces new position
    PrintRow [num2-1][IntLetterTwo-1]=temp;
    // makes sure the user can't move a space

    return;
}


// function to check which player should be allowed to move and only allows that player to move
bool moves:: CheckForTurn (string player, string piece)
{
    if (player=="lower")
    {
        if (piece==" K " or piece==" R " or piece==" P " or piece==" B " or piece==" N " or piece==" Q ")
        {
            return false;
            //if it's not its turn it cant go
        }
        else
        {
            return true;
            //if it is you can go
        }
    }
    else
    {
        if (piece==" k " or piece==" r " or piece==" p " or piece==" b " or piece==" n " or piece==" q ")
        {
            return false;
            //if it's not its turn it cant go
        }
        else
        {
            return true;
            //if it is you can go
        }
    }
}

string moves::promotion (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8], string player)
{
    PrintChess BoardPrint;
    //gets board vals
    string letter;
    string FullPieceString=" ";

    while (true)
    {
        cout<<endl<<"Please enter in letter for the piece you want to change the pawn into?"<<endl;
        cin>>letter;
        //gets letter to promote pawn into
        if ((PrintRow [num1-1][IntLetterOne-1][1]>=97 and PrintRow [num1-1][IntLetterOne-1][1]<=122))
        {
            if ((letter [0]=='q' or letter[0]=='b' or letter[0]=='r' or letter[0]=='n'))
            {
                //lets the user change into queen bishop rook or knight LOWERCASE
                break;
            }
        }

        else if ((PrintRow [num1-1][IntLetterOne-1][1]>=65 and PrintRow [num1-1][IntLetterOne-1][1]<=90))
        {

            if ((letter [0]=='Q' or letter[0]=='B' or letter[0]=='R' or letter[0]=='N'))
            {
                //lets the user change into queen bishop rook or knight UPPERCASE
                break;
            }
        }
        cout<<endl<<"Not a valid piece for you to pick"<<endl;
        //outputs invalid statement if you pick pawn of king to change into
        Sleep(1000);
        system("cls");
        //clears screen
        if (player=="lower")
        {
            cout<<"Player playing the LowerCase Letters Turn"<<endl<<endl;
            //outsputs which player's move it is
            BoardPrint.PrintChess1(PrintRow);
        }

        else
        {
            cout<<"Player playing the UpperCase Letters Turn"<<endl<<endl;
            //outsputs which player's move it is
            BoardPrint.PrintChess2(PrintRow);
        }
    }


    FullPieceString+=letter;
    FullPieceString+=" ";
    // adds the letter to FullPieceString


    return FullPieceString;
    // returns what the user changed the piece to
}

bool moves::castling (string position, string PrintRow[8][8],string player)
{
    Conversion convert;
    //gets conversion vals from other class
    if (PrintRow[convert.CharToInt(position[1])-1][(int)position[0]-65]==" K " and convert.CharToInt(position[3])==1 and (int)position[2]-64==2)
    {
        //converts castling to work for board for UPPer rooks
        MovesWithoutLegal('D',1,'B',1,PrintRow);
        PrintRow[0][0]="   ";
        PrintRow[0][2]=" R ";
        return true;
    }

    else if (PrintRow[convert.CharToInt(position[1])-1][(int)position[0]-65]==" K " and convert.CharToInt(position[3])==1 and (int)position[2]-64==6)
    {
         //converts castling to work for board for UPPer rooks
        MovesWithoutLegal('D',1,'F',1,PrintRow);
        PrintRow[0][7]="   ";
        PrintRow[0][4]=" R ";
        return true;
    }
    else if (PrintRow[convert.CharToInt(position[1])-1][(int)position[0]-65]==" k " and convert.CharToInt(position[3])==8 and (int)position[2]-64==2)
    {
         //converts castling to work for board for lower rooks side 1
        MovesWithoutLegal('D',8,'B',8,PrintRow);
        PrintRow[7][0]="   ";
        PrintRow[7][2]=" r ";
        return true;
    }

    else if (PrintRow[convert.CharToInt(position[1])-1][(int)position[0]-65]==" k " and convert.CharToInt(position[3])==8 and (int)position[2]-64==6)
    {
     //converts castling to work for board for lower rooks side 2
        MovesWithoutLegal('D',8,'F',8,PrintRow);
        PrintRow[7][7]="   ";
        PrintRow[7][4]=" r ";
        return true;
    }

    //if not returns false to castle
    return false;
}
