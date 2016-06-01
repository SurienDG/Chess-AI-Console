// main.cpp is the main class in The Chess Program Project File
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
// This class of The Chess Program Project File used to call the other classes so that the user can play one player or two player chess
//(c) Surien Das-Giwojno, Farzam, Claudio

// import libraries and classes
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <climits>
#include "PrintChess.h"
#include "moves.h"
#include "LegalMoves.h"
#include "ValidMoves.h"
#include "Conversion.h"
#include "ArtificialIintelligence.h"
#include "GameFunctions.h"





// state that namespace std is being used
using namespace std;


int main()
{
    // create class objects to so functions from other classes can be used
    PrintChess BoardPrint;
    moves MovesClass;
    LegalMoves legal;
    ValidMove valid;
    Conversion convert;
    ArtificialIntelligence ComputerPlayer;
    GameFunctions game;


    // set priority to high priority
    if(!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS))
    {
        return 0;
    }
    //  declare variables
    // variable to store which player is playing
    string player;
    // variable to count the number of turns in the game
    int  turns=2;
    // variables to check whether certain pieces have moved so that information can be used to determine
    // if a player is able to castle
    bool KingUpper=true;
    bool KingLower=true;
    bool RookUpperRight=true;
    bool RookUpperLeft=true;
    bool RookLowerRight=true;
    bool RookLowerLeft=true;
    // variable to store which player can do en passant
    string EnPassant="No";
    // variable to store whether a pawn was moved
    bool pawn=false;
    // variables temperily used to store the position pieces needed to be moved to for en passant to work
    int temp1=0;
    int temp2=0;
    char temp3=' ';
    // variable to store all the boolean variables for castling so that they can be saved to a text file or
    // easily imported into another function
    string bools;
    // variable to store the hightest
    int best =INT_MAX;
    // variable to store the value a move scores
    int val;
    // variable to store all the boolean variables for castling so that they can be saved to a text file or
    // easily imported into another function
    string temps;
    bool InvalidMove=false;
    bool GameLogging=true;
    string type="no";
    bool beginning=true;
    bool AI=false;
    // variable used to store copy of the board when the ai makes and unmakes moves
    string CopyBoard [8][8];
    // string to hold valid moves
    string ValidMove;
    // variables for counters for making different moves
    register int t=0;
    register int q=1;
    register int z=2;
    register int r=3;

    // string the hold values taken from text file (mostly used to hold the boolean values of the above variables)
    string InputValues;

    // string to hold the value of the last move
    string LastMove="";

    // declare streams
    ofstream outputFile;
    ifstream InputFile;

    //variable to store the set up of the board at the beginning so it can be used to start a new game
    string OriginalSetup[8][8];
    // declare array variables to hold values the chess board
    string PrintRow [8][8] {{" R "," N "," B "," K "," Q "," B "," N "," R "},
        {" P "," P "," P "," P "," P "," P "," P "," P " },{"   ","   ","   ","   ","   ","   ","   ","   "},
        {"   ","   ","   ","   ","   ","   ","   ","   "},{"   ","   ","   ","   ","   ","   ","   ","   "},
        {"   ","   ","   ","   ","   ","   ","   ","   "},{" p "," p "," p "," p "," p "," p "," p "," p ",},
        {" r "," n "," b "," k "," q "," b "," n "," r "}
    };
    // string to store the moves the user enters
    string moves="    ";


    // puts the starting values of the board in the array that stores the original setup
    game.BoardSetup(PrintRow, OriginalSetup);

    //deletes old log file so new one can be created
    remove ("GameLogging.txt");
     // variables to store boolean values
        bools=string(1,((char)(KingUpper+48))) +string(1,((char)(KingLower+48)))+string(1,((char)(RookUpperRight+48)))+
              string(1,((char)(RookUpperLeft+48)))+string(1,((char)(RookLowerRight+48)))+ string(1,((char)(RookLowerLeft+48)));

    // checks whether it is the beginning of the game or not and checks whether logging is on
                if (GameLogging==true and beginning==true)
                {
                    // stores all the castling bools in one string
                    bools=string(1,((char)(KingUpper+48))) +string(1,((char)(KingLower+48)))+string(1,((char)(RookUpperRight+48)))+
                          string(1,((char)(RookUpperLeft+48)))+string(1,((char)(RookLowerRight+48)))+ string(1,((char)(RookLowerLeft+48)));
                    // stores all the enpassant temporary variables in one string
                    temps=string(1,(char)(temp1+48))+string(1,(char)(temp2+48))+string(1,temp3);
                    // writes everything to a file inucluding the board state to a text file entitled GameLogging.txt
                    game.LoggingGames(PrintRow, "GameLogging.txt", true, bools, turns-1,  temps, EnPassant, LastMove );
                }
    // loop to keep the programing running
    while (true)
    {

        // variables to store boolean values
        bools=string(1,((char)(KingUpper+48))) +string(1,((char)(KingLower+48)))+string(1,((char)(RookUpperRight+48)))+
              string(1,((char)(RookUpperLeft+48)))+string(1,((char)(RookLowerRight+48)))+ string(1,((char)(RookLowerLeft+48)));

        // sets the colour of the background of the console
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );


        // checks to see if Enpassent was triggered
        if (EnPassant=="P" and InvalidMove==false)
        {
            //stores the value of the position the pawn was in if it was to have moved one space
            temp1=convert.CharToInt(moves[3])-1;
            temp2=convert.CharToInt(moves[3]);
            temp3=moves[0];
            // moves the pawn to the place the user intended for it to be
            MovesClass.Moves(moves[0],convert.CharToInt(moves[3])-1,moves[0],convert.CharToInt(moves[3]), PrintRow, false, player);
        }
        else if (EnPassant=="p" and InvalidMove==false)
        {
            //stores the value of the position the pawn was in if it was to have moved one space
            temp1=convert.CharToInt(moves[3])+1;
            temp2=convert.CharToInt(moves[3]);
            temp3=moves[0];
            // moves the pawn to the place the user intended for it to be
            MovesClass.Moves(moves[0],convert.CharToInt(moves[3])+1,moves[0],convert.CharToInt(moves[3]), PrintRow,false, player);
        }

        do
        {

            // assigns which player's turn it is depending on the value of turns
            if (turns%2!=0) player="lower";
            else player="upper";

            // clears the screen
            system("cls");
            // prints out the chess board
            // prints the orientation of of the board with a different header depending on who is playing
            if (player=="lower")
            {
                // States that the player playing the lowercase letters will now be playing
                cout<<"Player playing the LowerCase Letters Turn"<<endl<<endl;
                // outputs the board with a certain orientation
                BoardPrint.PrintChess1(PrintRow);
                cout<<"The last move made was: "<<LastMove<<endl;


            }
            else
            {
                // States that the player playing the uppercase letters will now be playing
                cout<<"Player playing the UpperCase Letters Turn"<<endl<<endl;
                // outputs the board with the opposite orientation of PrintChess1
                BoardPrint.PrintChess2(PrintRow);
                cout<<"The last move made was: "<<LastMove<<endl;

            }

            // checks to see if it is the ai's turn and whether the user wanted the ai to play or not
            if (player==type and AI==true)
            {
                // calls the openings function to read a text file with all the openings to see if
                //an opening can be used it and if it can it returns true and the stores the opening in a temp file
                if (ComputerPlayer.openings (PrintRow,KingUpper,KingLower,RookUpperRight,
                                             RookUpperLeft,RookLowerRight, RookLowerLeft, temp1, temp2,temp3,
                                             EnPassant, player)==true)
                {

                    // sets the next board state

                    // opens a text file by the name of temp.txt
                    InputFile.open("temp.txt");
                    // gets a line from the text file and stores it in InputValues
                    getline(InputFile,InputValues);
                    // assigns the value of InputValues to be nothing
                    InputValues="";
                    // reads the next line in the text file
                    getline(InputFile,InputValues);
                    // assigns the bool values to the following variables
                    KingUpper=convert.CharToBool(InputValues[0]);
                    KingLower=convert.CharToBool(InputValues[1]);
                    RookUpperRight=convert.CharToBool(InputValues[2]);
                    RookUpperLeft=convert.CharToBool(InputValues[3]);
                    RookLowerRight=convert.CharToBool(InputValues[4]);
                    RookLowerLeft=convert.CharToBool(InputValues[5]);
                    // gets the next line in the text file
                    getline(InputFile,InputValues);
                    // gets the next line in the text file
                    getline(InputFile,InputValues);
                    temp1=convert.CharToInt(InputValues[0]);
                    temp2=convert.CharToInt(InputValues[1]);
                    temp3=InputValues[2];
                    // gets the next line in the text file
                    getline(InputFile,InputValues);
                    // assigns Enpassant the value of InputValues
                    EnPassant=InputValues;
                    // gets the next line in the text file
                    getline(InputFile,InputValues);
                    // assigns LastMove the value of InputValues
                    LastMove=InputValues;
                    // closes the input file
                    InputFile.close();
                    // deletes the temp file
                    remove("temp.txt");
                    // logs the board state in a text file
                    if (GameLogging==true)
                    {
                        // stores all the boolean values for castling rights
                        bools=string(1,((char)(KingUpper+48))) +string(1,((char)(KingLower+48)))+string(1,((char)(RookUpperRight+48)))+
                              string(1,((char)(RookUpperLeft+48)))+string(1,((char)(RookLowerRight+48)))+ string(1,((char)(RookLowerLeft+48)));
                        // stores all the temp variables for en passent
                        temps=string(1,(char)(temp1+48))+string(1,(char)(temp2+48))+string(1,temp3);
                        // calls function to log the game
                        game.LoggingGames(PrintRow, "GameLogging.txt", true, bools, turns,  temps, EnPassant, LastMove );
                    }
                    // goes to the next turn
                    turns++;
                    // the value of moves back to null
                    moves="";
                    // continues in the loop
                    continue;
                }

                // resets the value of valid moves to null string
                ValidMove="";

                // calls function to get valid moves
                ValidMove=valid.ValidMoves(PrintRow, player, bools);

                // checks to see if ValidMove equals to a null string
                if (ValidMove=="")
                {
                    // If the ai is in checkmate tells the player that they won and what command they can type in
                    if (legal.ischeck(PrintRow,player)==type)
                        cout<<"You win. Type quit to quit type new game to restart"<<endl;
                    else
                        // If the ai is in stalemate tells the player that they won and what command they can type in
                        cout<<"It was a stalemate. Type quit to quit type new game to restart"<<endl;
                }
                else
                {
                    // calls function to get the top five best moves at depth one
                    ValidMove=ComputerPlayer.BestMoves(PrintRow,player,1, bools);

                    // resets values of the counters to the starting values for getting moves from the string
                    t=0;
                    q=1;
                    z=2;
                    r=3;


                    //sets the value of best to INT_MAX
                    best =INT_MAX;

                    // loop until end of string will be when r is equal to ValidMove.length()
                    while (r<ValidMove.length())
                    {
                        // calls function to make a copy of the current board state
                        game.BoardSetup(PrintRow,CopyBoard);
                        // calls function to render castling move and checks to see if the move was a castling move
                        if (MovesClass.castling(string (1,ValidMove[t])+string (1,ValidMove[q])+string (1,ValidMove[z])+string (1,ValidMove[r]),
                                                PrintRow,player)==false)
                        {
                            // if the move wasn't a castling move makes the move here
                            MovesClass.MovesWithoutLegal(ValidMove[t],convert.CharToInt(ValidMove[q]),ValidMove[z],convert.CharToInt(ValidMove[r]),PrintRow);
                        }
                        // gets the value of making that move by calling the function AlphaBeta to check moves up to depth 5
                        val = ComputerPlayer.AlphaBeta(5, INT_MIN, INT_MAX,PrintRow, player, turns+1, bools);
                        // unmakes the move
                        game.BoardSetup(CopyBoard,PrintRow);

                        // checks to see if the value of the move is less than best if it is adds it to moves and changes the value of best
                        if (val<=best )
                        {
                            //changes the value of best to val
                            best=val;
                            // makes moves equal to a null string
                            moves="";
                            // puts the move that was made into the variable moves
                            moves+=ValidMove[t];
                            moves+=ValidMove[q];
                            moves+=ValidMove[z];
                            moves+=ValidMove[r];
                        }

                        // increases the counters by one so that next move can be made
                        t+=4;
                        q+=4;
                        z+=4;
                        r+=4;

                    }

                    // once the best move has been found breaks out and renders the move
                    break;
                }
            }
            // checks whether a player is in check
            if (legal.ischeck(PrintRow,player)=="upper" or legal.ischeck(PrintRow,player)=="lower")
            {
                // if CheckForMate returns true then outputs the word checkmate
                if (valid.ValidMoves(PrintRow, player, bools)=="")cout<< "checkmate"<<endl;
                // just in check outputs the word check
                else cout<< "check"<<endl;
            }

            // outputs whether there is a stalemate or not based on returned value of ischeck function and whether ValidMoves found any moves
            if (legal.ischeck(PrintRow, player)=="No Check" and valid.ValidMoves(PrintRow,player, bools)=="")
            {
                // outputs statement "stalemate"
                cout<<"stalemate"<<endl;
            }

            // uncomment this line if you want to evaluation values of move scores
            //cout<< ComputerPlayer.evaluation(PrintRow,player, bools);

            // gets move from the user
            cout<<"Please enter your move"<<endl;
            getline(cin,moves);


            // if the user enters save then saves the game to a text file
            if(moves=="save")
            {
                // gets all the boolean values for castling stored in a single string
                bools=string(1,((char)(KingUpper+48))) +string(1,((char)(KingLower+48)))+string(1,((char)(RookUpperRight+48)))+
                      string(1,((char)(RookUpperLeft+48)))+string(1,((char)(RookLowerRight+48)))+ string(1,((char)(RookLowerLeft+48)));
                // stores all the temp files for en passant in a single string
                temps=string(1,(char)(temp1+48))+string(1,(char)(temp2+48))+string(1,temp3);
                // calls function LoggingGames to log the game
                game.LoggingGames(PrintRow, "SaveFile.txt", false, bools, turns,  temps, EnPassant, LastMove );
            }
            // if the user enters resume
            else if(moves=="resume")
            {
                // calls the function resume game and uses it assign values from a text file to the board array
                game.ResumeGame(PrintRow, "SaveFile.txt");
                // opens a text file by the name of SaveFile.txt
                InputFile.open("SaveFile.txt");
                // gets a line from the text file and stores it in InputValues
                getline(InputFile,InputValues);
                // assigns the value of InputValues to be nothing
                InputValues="";
                // reads the next line in the text file
                getline(InputFile,InputValues);
                // assigns the bool values to the following variables
                KingUpper=convert.CharToBool(InputValues[0]);
                KingLower=convert.CharToBool(InputValues[1]);
                RookUpperRight=convert.CharToBool(InputValues[2]);
                RookUpperLeft=convert.CharToBool(InputValues[3]);
                RookLowerRight=convert.CharToBool(InputValues[4]);
                RookLowerLeft=convert.CharToBool(InputValues[5]);
                // gets the next line in the text file
                getline(InputFile,InputValues);
                // converts the line of the text file to an integer and assigns it to the variable turns
                turns=convert.StringToInt(InputValues);
                // gets the next line in the text file
                getline(InputFile,InputValues);
                temp1=convert.CharToInt(InputValues[0]);
                temp2=convert.CharToInt(InputValues[1]);
                temp3=InputValues[2];
                // gets the next line in the text file
                getline(InputFile,InputValues);
                EnPassant=InputValues;
                // gets the next line in the text file
                getline(InputFile,InputValues);
                LastMove=InputValues;
                // closes the input file
                InputFile.close();

            }
            // if moves equals to new game then starts a new game
            else if(moves=="new game")
            {
                //removes logging file so it can start fresh
                remove ("GameLogging.txt");
                // resets values so the ai is not playing anymore
                AI=false;
                type="No";
                // resets the value
                LastMove="";
                // resets bool so it the program knows
                beginning=true;
                // resets the value of turns to 2
                turns=2;
                // calls the function to reset the board
                game.BoardSetup(OriginalSetup,PrintRow);
                // resets the boolean values back to true
                KingUpper=true;
                KingLower=true;
                RookUpperRight=true;
                RookUpperLeft=true;
                RookLowerRight=true;
                RookLowerLeft=true;
                // resets value of EnPAssant back to "No"
                EnPassant="No";
                pawn=false;
                temp1=0;
                temp2=0;
                temp3=' ';
                //  checks whether logging is on
                if (GameLogging==true)
                {
                    // stores all the castling bools in one string
                    bools=string(1,((char)(KingUpper+48))) +string(1,((char)(KingLower+48)))+string(1,((char)(RookUpperRight+48)))+
                          string(1,((char)(RookUpperLeft+48)))+string(1,((char)(RookLowerRight+48)))+ string(1,((char)(RookLowerLeft+48)));
                    // stores all the enpassant temporary variables in one string
                    temps=string(1,(char)(temp1+48))+string(1,(char)(temp2+48))+string(1,temp3);
                    // writes everything to a file inucluding the board state to a text file entitled GameLogging.txt
                    game.LoggingGames(PrintRow, "GameLogging.txt", true, bools, turns-1,  temps, EnPassant, LastMove );
                }

            }
            // this allows the user to skip a turn it was just used for testing if it is needed uncomment it
            /*else if(moves=="skip")
            {
                turns++;
                InvalidMove=false;
                if (turns<=10)
                    turns-=2;
            }*/
            // if moves equals quit, quits the game
            else if(moves=="quit")
            {
                return 0;
            }
            // if the user types in in ailower it tells the ai playing the lower pieces that it can start playing when it is its turn
            else if(moves=="ailower" and AI!=true)
            {
                type="lower";
                AI=true;
            }
            // if the user types in in ailower it tells the ai playing the upper pieces that it can start playing when it is its turn
            else if(moves=="aiupper" and AI!=true)
            {
                type="upper";
                AI=true;
            }
            // changes the letter the user enters so that all the letters are in the same case
            if (moves [0]>=97 and moves [0]<=122)
            {
                moves[0]-=32;
            }
            if (moves [2]>=97 and moves [2]<=122)
            {
                moves[2]-=32;
            }

        }
        // makes sure the user enters in valid move data
        while (!((moves [0]>=65 and moves [0]<=72) and (moves [0]>=65 and moves [0]<=72)
                 and (moves.length()==4) and (convert.CharToInt(moves[1])>0 and convert.CharToInt(moves[3])>0)
                 and (convert.CharToInt(moves[1])<=8 and convert.CharToInt(moves[3])<=8)));


        // checks to see if it is ai's turn if it is doesn't convert the moves
        if (player!=type)
        {
            // converts the letters so that they work properly with proper board labeling which we implemented at the end
            moves[0]=convert.ConvertingLetters(moves[0]);
            moves[2]=convert.ConvertingLetters(moves[2]);
        }


        // checks whether a pawn was moved
        if (PrintRow[convert.CharToInt(moves[1])-1][(int)moves[0]-65]==" P " or PrintRow[convert.CharToInt(moves[1])-1][(int)moves[0]-65]==" p ")pawn=true;
        else pawn=false;

        // checks whether user is trying to do enpassant when it is valid
        if (pawn==true and convert.CharToInt(moves[3])==temp1 and moves[2]==temp3  and ((int)moves[2]==(int)moves[0]+1 or (int)moves[2]==(int)moves[0]-1)
                and (convert.CharToInt(moves[3])==convert.CharToInt(moves[1])+1 or convert.CharToInt(moves[3])==convert.CharToInt(moves[1])-1 ) )
        {
            // if the user is trying to do en passant then checks whether en passant is possible and if it is moves pawn to the place
            // so it can be taken by the player
            if (EnPassant=="P" or EnPassant=="p")
            {
                MovesClass.MovesWithoutLegal(temp3,temp2,temp3,temp1, PrintRow);
            }

        }



        // checks to see if it legal for a move to be made normally, castling is not included as a normal move
        if (MovesClass.Moves(moves[0],convert.CharToInt(moves[1]),moves[2],convert.CharToInt(moves[3]),PrintRow, false, player)==false)
        {
            // if it couldn't be made noramlly checks to see if castling is legal
            if (legal.CastlingCheck (moves, PrintRow,player,KingUpper,KingLower, RookUpperRight, RookUpperLeft,
                                     RookLowerRight, RookLowerLeft, false))
            {
                // if castling is legal calls function to render castling move
                MovesClass.castling (moves,PrintRow, player);
            }
            else
            {
                // if both types of moves fails outputs that the move is invalid
                cout<<endl<<"Invalid move";
                Sleep(1000);
                // sets invalid move to be true
                InvalidMove=true;
                // and goes back through the loop and gets the move from the user again
                continue;
            }

        }
        LastMove=moves;

        // converts the letters so that show up as the move the user made or ai made on the new board labeling
        LastMove[0]=convert.ConvertingLetters( LastMove[0]);
        LastMove[2]=convert.ConvertingLetters(LastMove[2]);


        // sets invalid move to be false
        InvalidMove=false;

        //checks to see if a pawn was moved, if the pawn was moved checks to see if pawn was moved but was moved back due to en passant
        if ((pawn==true and ((convert.CharToInt(moves[3])-1==convert.CharToInt(moves[1])+1)
                             or convert.CharToInt(moves[3])-1==convert.CharToInt(moves[1])-3 ))
                and (PrintRow[convert.CharToInt(moves[3])-1][(int)moves[2]-65]!=" P "
                     and PrintRow[convert.CharToInt(moves[3])-1][(int)moves[2]-65]!=" p "))
        {
            //checks to see if en passant is true by seeing if the pawn was moved one move back because of the moves function which moves a pawn
            //back one to alert the program that en passant is possible
            if (PrintRow[convert.CharToInt(moves[3])-2][(int)moves[2]-65]==" P ")
                EnPassant="P";
            if (PrintRow[convert.CharToInt(moves[3])][(int)moves[2]-65]==" p ")
                EnPassant="p";
        }
        // if en passant is not possible sets value of EnPassant to false
        else EnPassant="No";


        // checks to see whether a king or rook was moved and records it with a boolean variable for the purpose of checking for to see if a
        // castle was is legal on other turns
        if (PrintRow[convert.CharToInt(moves[3])-1][(int)moves[2]-65]==" K " )
        {
            KingUpper=false;
        }
        else if (PrintRow[convert.CharToInt(moves[3])-1][(int)moves[2]-65]==" k " )
        {
            KingLower=false;
        }
        else if ((int)moves[0]-64==1 and convert.CharToInt(moves[1])==1 and PrintRow[convert.CharToInt(moves[3])-1][(int)moves[2]-65]==" R ")
        {
            RookUpperLeft=false;
        }
        else if ((int)moves[0]-64==8 and convert.CharToInt(moves[1])==1 and PrintRow[convert.CharToInt(moves[3])-1][(int)moves[2]-65]==" R ")
        {
            RookUpperRight=false;
        }
        else if ((int)moves[0]-64==1 and convert.CharToInt(moves[1])==8 and PrintRow[convert.CharToInt(moves[3])-1][(int)moves[2]-65]==" r ")
        {
            RookLowerLeft=false;
        }
        else if ((int)moves[0]-64==8 and convert.CharToInt(moves[1])==8 and PrintRow[convert.CharToInt(moves[3])-1][(int)moves[2]-65]==" r ")
        {
            RookLowerRight=false;
        }

            // increases the value of turns so it can move to the next turn
            turns++;

        // checks whether logging is on
        if (GameLogging==true)
        {
            // stores all the castling bools in one string
            bools=string(1,((char)(KingUpper+48))) +string(1,((char)(KingLower+48)))+string(1,((char)(RookUpperRight+48)))+
                  string(1,((char)(RookUpperLeft+48)))+string(1,((char)(RookLowerRight+48)))+ string(1,((char)(RookLowerLeft+48)));
            // stores all the enpassant temporary variables in one string
            temps=string(1,(char)(temp1+48))+string(1,(char)(temp2+48))+string(1,temp3);
            // writes everything to a file inucluding the board state to a text file entitled GameLogging.txt
            game.LoggingGames(PrintRow, "GameLogging.txt", true, bools, turns-1,  temps, EnPassant, LastMove );
        }





    }
    //returns a value of 0
    return 0;
}
