//LegalMoves.cpp is a class part of the Chess Program project file
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
//This Class of the chess program project file is used to ceheck if moves are valid
#include "LegalMoves.h"
#include <cmath>
#include "moves.h"
#include "Conversion.h"
#include "GameFunctions.h"
#include "windows.h"

// function to prevent a player from taking there own pieces. It also checks that pawns can only take pieces diagonally
bool LegalMoves::PieceCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8])
{
// makes it so you can't take your own pieces
    if  (PrintRow [num1-1][IntLetterOne-1][1]>=65 and PrintRow [num1-1][IntLetterOne-1][1]<=90)
    {
        if (!(PrintRow [num2-1][IntLetterTwo-1][1]>=97 and PrintRow [num2-1][IntLetterTwo-1][1]<=122
                or PrintRow [num2-1][IntLetterTwo-1]=="   " ))
        {
            //if you do and it does not meet these conditions it returns false
            return false;
        }
    }

    else if ((PrintRow [num1-1][IntLetterOne-1][1]>=97 and PrintRow [num1-1][IntLetterOne-1][1]<=122))
    {
        if (!(PrintRow [num2-1][IntLetterTwo-1][1]>=65 and PrintRow [num2-1][IntLetterTwo-1][1]<=90
                or PrintRow [num2-1][IntLetterTwo-1]=="   " ))
        {
            //if you do and it does not meet these conditions it returns false
            return false;
        }
    }
    if (PrintRow [num1-1][IntLetterOne-1]==" p " or PrintRow [num1-1][IntLetterOne-1]==" P ")
    {
        if ((IntLetterOne==IntLetterTwo+1 or IntLetterOne==IntLetterTwo-1))
        {
            if (!(PrintRow [num2-1][IntLetterTwo-1][1]>=65 and PrintRow [num2-1][IntLetterTwo-1][1]<=122))
            {
                //if you do and it does not meet these conditions it returns false, for black and white
                return false;
            }
        }
        else if (IntLetterOne==IntLetterTwo and (num2==num1+1 or num2==num1-1 or num2==num1+2 or num2==num1-2 ))
        {
            if (PrintRow [num2-1][IntLetterTwo-1]!="   ")
            {
                //if you do and it does not meet these conditions it returns false
                return false;
            }
        }
    }
    return true;
}
// function to check to see if the user made a valid move for the pawn
bool LegalMoves::PawnCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8])
{
//Checks for moves for pawn that are white
    if ((PrintRow [num1-1][IntLetterOne-1]==" p ") ) //row 7
    {
        if (num1==7)
        {
            if (!(( num1==num2+1 ) and (((IntLetterOne==IntLetterTwo+1 or IntLetterOne==IntLetterTwo-1)
                                         or IntLetterOne==IntLetterTwo)) or ((num1==num2+2) and (IntLetterOne==IntLetterTwo))))
            {

                //if this isn't true returns false
                return false ;
            }
            if ((num1==num2+2) and (IntLetterOne==IntLetterTwo))
                {
                    if (PrintRow [num1-2][IntLetterOne-1]!="   ")
                        return false;
                }
        }

        else
        {

            if (!(( num1==num2+1)and (IntLetterOne==IntLetterTwo+1 or IntLetterOne==IntLetterTwo-1
                                      or IntLetterOne==IntLetterTwo)))
            {
                //if this isn't true it returns false
                return false ;
            }
        }
    }

//for pawns that are black
    else if ((PrintRow [num1-1][IntLetterOne-1]==" P ") )
    {
        if (num1==2)
        {
            if (!((( num1==num2-1 ) and (IntLetterOne==IntLetterTwo+1 or IntLetterOne==IntLetterTwo-1
                                         or IntLetterOne==IntLetterTwo)) or ((num1==num2-2) and (IntLetterOne==IntLetterTwo))))
            {

                //if this isn't true it returns false
                return false ;
            }
            if ((num1==num2-2) and (IntLetterOne==IntLetterTwo))
                {
                    if (PrintRow [num1][IntLetterOne-1]!="   ")
                        return false;
                }
        }
        else
        {
            if (!(( num1==num2-1)and (IntLetterOne==IntLetterTwo+1 or IntLetterOne==IntLetterTwo-1
                                      or IntLetterOne==IntLetterTwo)))
            {
                //if this isn't true it returns false
                return false ;
            }
        }
    }
    return true;
}
// function to check to see if the user made a valid move for the knight
bool LegalMoves::KnightCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8])
{
//lets it jump over peices in an l shape by moving 2 and 1
    if (!(((num1==num2+2 or num1==num2-2)  and (IntLetterOne==IntLetterTwo+1 or IntLetterOne==IntLetterTwo-1))
            or ((num1==num2-1 or num1==num2+1) and (IntLetterOne==IntLetterTwo+2 or IntLetterOne==IntLetterTwo-2))))
    {
        return false;
    }

    return true;
}

// function to check to see if the user made a valid move for the King
bool LegalMoves::KingCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8])
{
    if (!(( num1==num2+1 or num2==num1 + 1 or num1==num2-1 or num2==num1 - 1 or (num1==num2))and (IntLetterOne==IntLetterTwo+1 or IntLetterOne==IntLetterTwo-1
            or IntLetterOne==IntLetterTwo or IntLetterTwo==IntLetterOne+1 or IntLetterTwo==IntLetterOne-1)  ))
    {
        return false;
    }


    return true;

}
// function to check to see if the user made a valid move for the Rook
bool LegalMoves::RookCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8])
{//check if the rook is moving in straight vertically
    if (IntLetterOne==IntLetterTwo)
    {//check if its moving up or down the board
        if (num1<num2)//moving down
        {//loop to check spaces between start and finish
            for (int i=1; (num2-1)>(num1-1)+i; i++)//loop checking down the board
            {//check if the value stored in that position in the array is blank
                if (PrintRow [(num1-1)+i][IntLetterTwo-1]!="   ")
                {//if its not blank/open return a false move. Piece in the way
                    return false;
                }
            }
        }
        else//moving up
        {
            for (int i=1; (num1-1)-i>(num2-1); i++)
            {
                if (PrintRow [(num1-1)-i][IntLetterTwo-1]!="   ")
                {
                    return false;
                }
            }
        }


    }
    // check if rook is moving straight horizantally
    else if (num1==num2)
    {//check if its moving left or right on board
        if (IntLetterOne<IntLetterTwo)//moving left
        {
            for (int i=1; (IntLetterTwo-1)>(IntLetterOne-1)+i; i++)//loop up the board going left
            {
                if (PrintRow [num1-1][(IntLetterOne-1)+i]!="   ")
                {
                    return false;
                }
            }
        }
        else//moving right
        {
            for (int i=1; (IntLetterOne-1)-i>(IntLetterTwo-1); i++)//loop down the board going right
            {
                if (PrintRow [(num1-1)][(IntLetterOne-1)-i]!="   ")
                {
                    return false;
                }
            }
        }
    }

    else//if movement is not straight return false
    {
        return false;
    }
    //if no conditions are trigered return as valid move
    return true;
}
// function to check to see if the user made a valid move for the Bishop
bool LegalMoves::BishopCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8])
{
    //variable to hold the vertical and horizantel difference between the origianl and new position
    int LetterDifference = abs(IntLetterOne-IntLetterTwo);
    int NumberDifference = abs(num1-num2);

//check if the vertical
    if(LetterDifference==NumberDifference)
    {//check if its moving up or down
        if (num1<num2 and IntLetterOne>IntLetterTwo)
        {//loop to check spaces bewteen start and finish
            for (int i=1; (num2-1)>(num1-1)+i ; i++)//loop going up
            {//check if position in the array is blank
                if (PrintRow [(num1-1)+i][(IntLetterOne-1)-i]!="   ")
                {//if not blank/open return false move. Piece in the way
                    return false;
                }
            }
        }
        else if (num1>num2 and IntLetterOne<IntLetterTwo)//going down
        {
            for (int i=1; (num1-1)-i>(num2-1); i++)//loop going down
            {
                if (PrintRow [(num1-1)-i][(IntLetterOne-1)+i]!="   ")
                {
                    return false;
                }
            }
        }
        //check if bishop is moving left or right
        else if (num1<num2 and IntLetterOne<IntLetterTwo)
        {
            for (int i=1; (IntLetterTwo-1)>(IntLetterOne-1)+i; i++)//loop going right
            {
                if (PrintRow [(num1-1)+i][(IntLetterOne-1)+i]!="   ")
                {
                    return false;
                }
            }
        }
        else if (num1>num2 and IntLetterOne>IntLetterTwo)
        {
            for (int i=1; (IntLetterOne-1)-i>(IntLetterTwo-1); i++)//loop going left
            {
                if (PrintRow [(num1-1)-i][(IntLetterOne-1)-i]!="   ")
                {
                    return false;
                }
            }
        }
    }
    else//if not moving diagnolly return false move
    {
        return false;
    }
//if not conditions are triggered retunr valid move
    return true;
}
// function to check to see if the user made a valid move for the queen
bool LegalMoves::QueenCheck (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8])
{//use finstions of bishop check and rook check to vearify move is valid
    if (BishopCheck (IntLetterOne, num1, IntLetterTwo, num2, PrintRow)==true or RookCheck (IntLetterOne, num1, IntLetterTwo, num2, PrintRow)==true)
    {//reutnr true if valid
        return true;
    }
    else
    {//false if not valid
        return false;
    }
}
// function to prevent the user from moving into check
bool LegalMoves::CheckPrevention (int IntLetterOne, int num1, int IntLetterTwo, int num2,string PrintRow[8][8], string player)
{//create varibles to temporarily hold positions for original and destination
    string temp1= PrintRow [num2-1][IntLetterTwo-1];
    string temp2= PrintRow [num1-1][IntLetterOne-1];

//check if you can move out of the way
    PrintRow [num2-1][IntLetterTwo-1]=PrintRow [num1-1][IntLetterOne-1];
    PrintRow [num1-1][IntLetterOne-1]="   ";
//check if the piece is higher or lower
    if ((temp2[1]>=97 and temp2[1]<=122 and ischeck(PrintRow, player)=="lower") or
            (temp2[1]>=65 and temp2[1]<=90 and ischeck(PrintRow,player)=="upper"))

    {//if you cant prevent i5 return false. reutnr pieces to original positions
        PrintRow [num2-1][IntLetterTwo-1]=temp1;
        PrintRow [num1-1][IntLetterOne-1]=temp2;
        return false;
    }

//return values to original position
    PrintRow [num2-1][IntLetterTwo-1]=temp1;
    PrintRow [num1-1][IntLetterOne-1]=temp2;
//if you can prevent it return true
    return true;
}
string  LegalMoves::ischeck (string PrintRow[8][8], string player)
{

    string KingLevel;
    string pieces;

//loop to check the whole board
    for (int i=1; i<=8; i++ )
    {
        for (int t=1; t<=8; t++ )
        {
            //determine if its higher or lower case
            if (player=="upper" and PrintRow [i-1][t-1]==" k ")
            {
                continue;
            }
            else if (player=="lower" and PrintRow [i-1][t-1]==" K ")
            {
                continue;
            }
            //get pieces determined on the case
            if (PrintRow [i-1][t-1]==" k ")
            {
                pieces="BQKRPN";
                KingLevel="lower";

            }
            else if (PrintRow [i-1][t-1]==" K ")
            {
                pieces="bqkrpn";
                KingLevel="upper";
            }
            //check where king is
            if (PrintRow [i-1][t-1]==" k " or PrintRow [i-1][t-1]==" K " )
            {
                //loop through whole board
                for (int q=1; q<=8; q++ )
                {
                    for (int v=1; v<=8; v++ )
                    {
                    //calls to check if any of the pieces have the king in check
                    //bishop
                        if (PrintRow [q-1][v-1][1]==pieces[0])
                        {
                            if (BishopCheck (v, q, t, i,PrintRow))
                            {
                                return KingLevel;
                            }
                        }
                    //queen
                        else if (PrintRow [q-1][v-1][1]==pieces[1])
                        {
                            if (QueenCheck (v, q, t, i,PrintRow))
                            {
                                return KingLevel;
                            }
                        }
                    //king
                        else if (PrintRow [q-1][v-1][1]==pieces[2])
                        {
                            if (KingCheck (v, q, t, i,PrintRow))
                            {
                                return KingLevel;
                            }
                        }
                    //rook
                        else if (PrintRow [q-1][v-1][1]==pieces[3])
                        {
                            if (RookCheck (v, q, t, i, PrintRow))
                            {
                                return KingLevel;
                            }
                        }
                    //pawn
                        else if (PrintRow [q-1][v-1][1]==pieces[4])
                        {
                            if (PawnCheck (v, q, t, i,PrintRow) and PieceCheck (v, q, t, i, PrintRow)  )
                            {
                                return KingLevel;
                            }
                        }
                    //knight
                        else if (PrintRow [q-1][v-1][1]==pieces[5])
                        {
                            if (KnightCheck (v, q, t, i, PrintRow))
                            {
                                return KingLevel;
                            }

                        }
                    }
                }
            }
        }
    }

//if no condittion is triggered reutnr no check
    KingLevel="No Check";
    return KingLevel;
}
bool LegalMoves::CastlingCheck (string position, string PrintRow[8][8],string player, bool KingUpper,bool KingLower,
                           bool RookUpperRight, bool RookUpperLeft, bool RookLowerRight, bool RookLowerLeft, bool message)
{//call up classes
    Conversion convert;
    moves MovesClass;


//use king check to check is player is in check
   if (ischeck(PrintRow, player)=="No Check")
            {//check if king is capital or lower case
                if (PrintRow[convert.CharToInt(position[1])-1][(int)position[0]-65]==" K " and convert.CharToInt(position[3])==1 and (int)position[2]-64==2
                        and KingUpper==true and RookUpperLeft==true)
                {//check for pieces between king and rook
                    for (int i=2; i>=1; i-- )
                    {
                        if (PrintRow [0][i]!="   ")return false;
                    }
                    //specific calls to castle going left with capital
                    if (MovesClass.Moves('D',1,'C',1,PrintRow, message, player)==false)
                    {
                        return false;

                    }
                    else
                    {
                        if (MovesClass.Moves('C',1,'B',1,PrintRow, message, player)==false)
                        {
                            MovesClass.MovesWithoutLegal('C',1,'D',1,PrintRow);
                            return false;
                        }
                        else
                        {
                            MovesClass.MovesWithoutLegal('B',1,'D',1,PrintRow);
                            return true;
                        }
                    }

                }
                //check higher or lower
                else if (PrintRow[convert.CharToInt(position[1])-1][(int)position[0]-65]==" K " and convert.CharToInt(position[3])==1 and (int)position[2]-64==6
                         and KingUpper==true and RookUpperRight==true)
                {//check for pieces in between
                    for (int i=4; i<=6; i++ )
                    {
                        if (PrintRow [0][i]!="   ")return false;
                    }
                    //check for castling capital going left
                    if (MovesClass.Moves('D',1,'E',1,PrintRow, message, player)==false)
                    {
                       return false;

                    }
                    else
                    {
                        if (MovesClass.Moves('E',1,'F',1,PrintRow, message, player)==false)
                        {
                            MovesClass.MovesWithoutLegal('E',1,'D',1,PrintRow);
                            return false;
                        }
                        else
                        {

                            if (MovesClass.Moves('F',1,'G',1,PrintRow, message, player)==false)
                            {
                                MovesClass.MovesWithoutLegal('F',1,'D',1,PrintRow);
                                return false;
                            }
                            else
                            {
                                MovesClass.MovesWithoutLegal('G',1,'D',1,PrintRow);
                                return true;
                            }
                        }

                    }
                }
                //check if higher or lower
                else if (PrintRow[convert.CharToInt(position[1])-1][(int)position[0]-65]==" k " and convert.CharToInt(position[3])==8 and (int)position[2]-64==2
                         and KingLower==true and RookLowerLeft==true)
                {//loop to check pieces in the way
                    for (int i=2; i>=1; i-- )
                    {
                        if (PrintRow [7][i]!="   ")return false;
                    }
                    //calls to castle going right with lower
                    if (MovesClass.Moves('D',8,'C',8,PrintRow, message, player)==false)
                    {
                        return false;
                    }
                    else
                    {
                        if (MovesClass.Moves('C',8,'B',8,PrintRow, message, player)==false)
                        {
                            MovesClass.MovesWithoutLegal('C',8,'D',8,PrintRow);
                            return false;
                        }
                        else
                        {
                            MovesClass.MovesWithoutLegal('B',8,'D',8,PrintRow);
                            return true;
                        }
                    }

                }

                else if (PrintRow[convert.CharToInt(position[1])-1][(int)position[0]-65]==" k " and convert.CharToInt(position[3])==8 and (int)position[2]-64==6
                         and KingLower==true and RookLowerRight==true)
                {
                //loop to check pieces
                    for (int i=4; i<=6; i++ )
                    {
                        if (PrintRow [7][i]!="   ")return false;
                    }
                    //calls to castle going left with lower
                    if (MovesClass.Moves('D',8,'E',8,PrintRow, message, player)==false)
                    {
                       return false;

                    }
                    else
                    {
                        if (MovesClass.Moves('E',8,'F',8,PrintRow, message, player)==false)
                        {
                            MovesClass.MovesWithoutLegal('E',8,'D',8,PrintRow);
                            return false;
                        }
                        else
                        {

                            if (MovesClass.Moves('F',8,'G',8,PrintRow, message, player)==false)
                            {
                                MovesClass.MovesWithoutLegal('F',8,'D',8,PrintRow);
                                return false;
                            }
                            else
                            {
                                MovesClass.MovesWithoutLegal('G',8,'D',8,PrintRow);
                                return true;
                            }
                        }
                    }
                }
        }

        return false;


}



