// ValidMoves.cpp is a class that is part of The Chess Program Project File
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
// This class of The Chess Program Project File is used to check all possible moves by pieces on board
//(c) Surien Das-Giwojno, Farzam, Claudio Gonzalez
#include "ValidMoves.h"
#include "LegalMoves.h"
#include "Conversion.h"
#include <windows.h>




// function to get all the valid moves for the rook
string ValidMove::KingValidMoves (int v, int q, string PrintRow[8][8],string player)
{//call up classes and create moves string
    string moves="";
    LegalMoves legal;
//calls up PieceValidMOves function to check all valid moves for that piece and if valid adds it to moves
    moves+=PieceValidMoves(v, q, -1, 1,legal.KingCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 1, 1,legal.KingCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, -1, -1,legal.KingCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 1, -1,legal.KingCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 0, 1,legal.KingCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 0, -1,legal.KingCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 1, 0,legal.KingCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, -1, 0,legal.KingCheck, PrintRow,player);
//when done checking moves it return the string
    return moves;
}
string ValidMove::PieceValidMoves(int v, int q, int a, int b, bool (*function)(int,int,int,int,string[8][8]), string PrintRow[8][8],string player)
{//call up classes and create moves string
    string moves="";
    LegalMoves legal;
//if statement that check if the move is in the board and if the move is valid by whichever LegalMove's fucntion is called
    if ((((q+b)<=8 and (q+b)>=1) and (v+a)<=8 and (v+a)>=1) and function(v,q,v+a,q+b,PrintRow) and legal.PieceCheck(v,q,v+a,q+b, PrintRow) and legal.CheckPrevention(v,q,v+a,q+b, PrintRow,player))
    {//original position
        moves+=(char)(v+64);
        moves+=(char)(q+48);
    //ending position
        moves+=(char)((v+a)+64);
        moves+=(char)((q+b)+48);
    }
//return the move if valid
    return moves;
}
string ValidMove::ValidMoves (string PrintRow [8][8], string player, string bools)
{//creates variable to hold valid strings
    string moves="";
//check if pieces are lower or higher and get peices accordingly
    string pieces;
    if (player=="upper")
    {
        pieces="BQKRPN";
    }
    else if (player=="lower")
    {
        pieces= "bqkrpn";
    }
//loop to check through entire board
    for (int v=1; v<=8; v++ )
    {
        for (int q=1; q<=8; q++ )
        {//all if statements to check all possible valid moves by pieces on board. Adds it to moves string if valid
            //bishop
            if (PrintRow [q-1][v-1][1]==pieces[0])
            {
                moves+=BishopValidMoves(v,q,PrintRow,player);
            }
            //queen
            else if (PrintRow [q-1][v-1][1]==pieces[1])
            {
                moves+=BishopValidMoves(v,q,PrintRow,player);
                moves+=RookValidMoves(v,q,PrintRow,player);
            }
            //king
            else if (PrintRow [q-1][v-1][1]==pieces[2])
            {
                moves+=CastlingValidMoves(v, q, bools, PrintRow, player);
                moves+=KingValidMoves(v, q, PrintRow,player);
            }
            //rook
            else if (PrintRow [q-1][v-1][1]==pieces[3])
            {
                moves+=RookValidMoves (v, q, PrintRow,player);
            }
            //pawn
            else if (PrintRow [q-1][v-1][1]==pieces[4])
            {
                moves+=PawnValidMoves(v,q,PrintRow,player);
            }
            //knight
            else if (PrintRow [q-1][v-1][1]==pieces[5])
            {
                moves+=KnightValidMoves(v,q,PrintRow,player);
            }

        }
    }



//when done checking moves it return the string
    return moves;
}
// function to get all the valid moves for the bishop
string ValidMove::BishopValidMoves (int v, int q, string PrintRow[8][8], string player)
{//call up classes and create moves string
    string moves;
    LegalMoves legal;

//calls up PieceValidMOves function to check all valid moves for that piece and if valid adds it to moves
//looping to check all spaces
    for (int i=1; (q-1)+i<8 and (v-1)-i>=0 ; i++)
    {
        moves+=PieceValidMoves(v, q, -i, i, legal.BishopCheck, PrintRow,player);
    }
    for (int i=1; (v-1)+i<8 and (q-1)-i>=0 ; i++)
    {
        moves+=PieceValidMoves(v, q, i, -i, legal.BishopCheck, PrintRow,player);
    }
    for (int i=1; (v-1)+i<8 and (q-1)+i<8 ; i++)
    {
        moves+=PieceValidMoves(v, q, i, i, legal.BishopCheck, PrintRow,player);
    }
    for (int i=1; (v-1)-i>=0 and (q-1)-i>=0 ; i++)
    {
        moves+=PieceValidMoves(v, q, -i, -i, legal.BishopCheck, PrintRow,player);
    }
//when done checking moves it return the string
    return moves;
}

string ValidMove::RookValidMoves (int v, int q, string PrintRow[8][8], string player)
{//call up classes and create moves string
    string moves="";
    LegalMoves legal;

//calls up PieceValidMOves function to check all valid moves for that piece and if valid adds it to moves
//looping to check all spaces
    for (int i=1; (q-1)+i<8 ; i++)
    {
        moves+=PieceValidMoves(v, q, 0, i, legal.RookCheck, PrintRow,player);
    }
    for (int i=1; (q-1)-i>=0 ; i++)
    {
        moves+=PieceValidMoves(v, q, 0, -i, legal.RookCheck, PrintRow,player);
    }
    for (int i=1; (v-1)+i<8 ; i++)
    {
        moves+=PieceValidMoves(v, q, i, 0, legal.RookCheck, PrintRow,player);
    }
    for (int i=1; (v-1)-i>=0 ; i++)
    {
        moves+=PieceValidMoves(v, q, -i, 0, legal.RookCheck, PrintRow,player);
    }
//when done checking moves it return the string
    return moves;
}

// function to get all the valid moves for the rook
string ValidMove::PawnValidMoves (int v, int q, string PrintRow[8][8],string player)
{//call up classes and create moves string
    string moves="";
    LegalMoves legal;
//calls up PieceValidMOves function to check all valid moves for that piece and if valid adds it to moves
    moves+=PieceValidMoves(v, q, -1, 1, legal.PawnCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, -1, 1, legal.PawnCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 1, 1, legal.PawnCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 1, 1, legal.PawnCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, -1, -1, legal.PawnCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, +1, -1, legal.PawnCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 0, 1, legal.PawnCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 0, -1, legal.PawnCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 0, 2, legal.PawnCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 0, -2, legal.PawnCheck, PrintRow,player);
//when done checking moves it return the string
    return moves;
}

// function to get all the valid moves for the rook
string ValidMove::KnightValidMoves (int v, int q, string PrintRow[8][8],string player)
{
//call up classes and create moves string
    string moves="";
    LegalMoves legal;
//calls up PieceValidMOves function to check all valid moves for that piece and if valid adds it to moves
    moves+=PieceValidMoves(v, q, -1, 2, legal.KnightCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 1, 2, legal.KnightCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, -1, -2, legal.KnightCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 1, -2, legal.KnightCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, -2, 1, legal.KnightCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 2, 1, legal.KnightCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, -2, -1, legal.KnightCheck, PrintRow,player);
    moves+=PieceValidMoves(v, q, 2, -1, legal.KnightCheck, PrintRow,player);
//when done checking moves it reutnr the string
    return moves;

}
//fucntion to call up possible caslting moves
string ValidMove::CastlingValidMoves (int v, int q, string bools, string PrintRow[8][8], string player)
{//calls up classes required
    LegalMoves legal;
    Conversion convert;
//creates variables to check pieces required for move on the board
    bool KingUpper=convert.CharToBool(bools[0]);
    bool KingLower=convert.CharToBool(bools[1]);
    bool RookUpperRight=convert.CharToBool(bools[2]);
    bool RookUpperLeft=convert.CharToBool(bools[3]);
    bool RookLowerRight=convert.CharToBool(bools[4]);
    bool RookLowerLeft=convert.CharToBool(bools[5]);
    string moves;
    string position [4];

//check all possible calls to castle
    position[0]+=(char)(v+64);
    position[0]+=(char)(q+48);
    position[0]+='F';
    position[0]+='8';
    position[1]+=(char)(v+64);
    position[1]+=(char)(q+48);
    position[1]+='B';
    position[1]+='8';
    position[2]+=(char)(v+64);
    position[2]+=(char)(q+48);
    position[2]+='B';
    position[2]+='1';
    position[3]+=(char)(v+64);
    position[3]+=(char)(q+48);
    position[3]+='F';
    position[3]+='1';
//loop to chekc through castling calls
    for (int i=0; i<4; i++)
    {//check if that call is valid for castling through the check castling funtion
        if (legal.CastlingCheck(position [i], PrintRow, player, KingUpper, KingLower, RookLowerRight, RookLowerLeft, RookUpperRight, RookLowerLeft, true))
        {//add that castling move to moves string if valid
            moves+=position[i];
        }
    }
//return all possible moves
    return moves;

}


