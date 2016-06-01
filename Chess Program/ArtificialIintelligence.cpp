// ArtificialIintelligence.cpp is a class that is part of The Chess Program Project File
//Program created by Farzam Karimi, Surien Das-Giwojno, Claudio Gonzalez
// This class of The Chess Program Project File is used to to fuel the intelligence of the ai
//(c) Surien Das-Giwojno, Farzam, Claudio




//headers to link to different classes
#include "ArtificialIintelligence.h"
#include "ValidMoves.h"
#include "LegalMoves.h"
#include "moves.h"
#include "Conversion.h"
#include "GameFunctions.h"
// import libraries
#include <climits>
#include <vector>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstdlib>

// function to count the number of each type of piece a player has
int ArtificialIntelligence::NumberOfPieces (string PrintRow[8][8], string piece)
{
    // declare variable counter
    int counter=0;

    //loop to search through board array to count the number of times a piece appears on the board
    for (int col=7; col>=0; col--)
    {
        for (int row=7; row>=0; row--)
        {
            if (PrintRow[col][row]==piece)counter++; //counter
        }
    }
    return counter; //returns counter value
}

// function to return a move score at a certain depth
int  ArtificialIntelligence::evaluation (string PrintRow[8][8], string player, string bools)
{

    //declare variables hold the values of each piece and the weight of the piece
    const int mobilityWt =1;
    const int pawnWt = 10;
    const int bishopWt = 30;
    const int knightWt = 30;
    const int rookWt = 50;
    const int queenWt = 90;
    const int kingWt = 200;

    // declare variables to scores of materials and mobility and of who is moving
    int MaterialScore;
    int MobilityScore;
    int TotalScore;
    int Who2Move=0;
    // variables to store the number of moves for upper and lower pieces
    int LowerMovesNum;
    int UpperMovesNum;

    // create class objects
    LegalMoves legal;
    ValidMove valid;

    // decides whether to negate the score to change perspective because of the player
    if (player=="lower") Who2Move=1;
    else if (player=="upper") Who2Move=-1;

    // code implemented from https://chessprogramming.wikispaces.com/Evaluation
    MaterialScore = queenWt  *  (NumberOfPieces (PrintRow," q ")-NumberOfPieces (PrintRow," Q "))
                    + rookWt  * (NumberOfPieces (PrintRow," r ")-NumberOfPieces (PrintRow," R "))
                    + knightWt* (NumberOfPieces (PrintRow," n ")-NumberOfPieces (PrintRow," N "))
                    + bishopWt* (NumberOfPieces (PrintRow," b ")-NumberOfPieces (PrintRow," B "))
                    + pawnWt  * (NumberOfPieces (PrintRow," p ")-NumberOfPieces (PrintRow," P "));

    //
    LowerMovesNum=(valid.ValidMoves(PrintRow,"lower", bools).length())/4;
    UpperMovesNum=(valid.ValidMoves(PrintRow,"upper", bools).length())/4;

    MobilityScore = mobilityWt * ((LowerMovesNum)-(UpperMovesNum));

    TotalScore=(MobilityScore+MaterialScore)*Who2Move;
    // code implemented from https://chessprogramming.wikispaces.com/Evaluation

    // returns the score of the board position
    return TotalScore;

}
//Function to search depth for BestMoves function which is adapted from
//http://web.archive.org/web/20070604082157/http://www.brucemo.com/compchess/programming/alphabeta.htm
int ArtificialIntelligence::Negamax(int depth, int alpha, int beta, string PrintRow[8][8], string player, int turns, string bools)
{
    // create class objects
    Conversion convert;
    ValidMove valid;
    moves MovesClass;
    GameFunctions game;

    // variables declared as counters for making the different moves in a string array
    int t=0;
    int q=1;
    int z=2;
    int r=3;
    // variable to store value of a move
    int val;
    //variable to store a copy of the board
    string CopyBoard [8][8];
    // variable to store the valid moves
    string ValidMove="";
    // determines who is playing based on the turn number
    if (turns%2!=0) player="lower";
    else player="upper";


    // checks whether the depth is
    if (depth == 0)
    {
        // returns the evaluation for a specific board state
        return evaluation(PrintRow,player, bools);
    }
    //calls valid moves to give function
    ValidMove=valid.ValidMoves(PrintRow, player, bools);

    //if there are no ValidMoves to check just returns the evaluation
    if (ValidMove=="")
    {
        // returns evaluation
        return evaluation(PrintRow,player, bools);
    }

    // continues running through the loop while there are still moves to be tried
    while (r<ValidMove.length())
    {
        //Saves a copy a copy of the board
        game.BoardSetup(PrintRow, CopyBoard);

        // checks to see if the move is a castling move, if the move is a castling move castles
        if (MovesClass.castling(string (1,ValidMove[t])+string (1,ValidMove[q])+string (1,ValidMove[z])+string (1,ValidMove[r]),
                                PrintRow,player)==false)
        {
            //makes move noramlly if it isn't a castling move
            MovesClass.MovesWithoutLegal(ValidMove[t],convert.CharToInt(ValidMove[q]),ValidMove[z],convert.CharToInt(ValidMove[r]),PrintRow);
        }
        // returns the value Negamax gets when it recurses through itself
        val = -Negamax(depth - 1, -beta, -alpha,PrintRow, player, turns+1, bools);
        // resets the board to unmake the move
        game.BoardSetup(CopyBoard, PrintRow);

        //increase counters so it can move to the next move
        t+=4;
        q+=4;
        z+=4;
        r+=4;

        // if val>alpha assigns alpha the value of val
        if (val > alpha)
            alpha = val;
    }
    // returns alpha
    return alpha;
}
// main search function used in the program which is adapted from
//http://web.archive.org/web/20070605041203/http://www.brucemo.com/compchess/programming/pvs.htm
int ArtificialIntelligence::AlphaBeta(int depth, int alpha, int beta, string PrintRow[8][8], string player, int turns, string bools)
{
    //create class objects
    Conversion convert;
    ValidMove valid;
    moves MovesClass;
    GameFunctions game;

    // sets value of fFoundPv
    bool fFoundPv = false;

    // checks to see what player is playing based
    if (turns%2!=0) player="lower";
    else player="upper";
    // declare variables to act as counters in the loop so that new moves can be used
    int t=0;
    int q=1;
    int z=2;
    int r=3;
    // declare variable to store the value of the evaluation
    int val;
    // string to hold all the moves
    string ValidMove="";
    // array to hold copy of the board
    string CopyBoard [8][8];

    // assigns which player's turn it is depending on the value of turns
    if (depth == 0)
    {
        //checks to see whether turns is odd or even so evaluation can be returned in the perspective of the player
        if (turns&1)
        {
            return evaluation(PrintRow,player, bools);
        }
        else
            return -evaluation(PrintRow,player, bools);

    }
    // get top five best moves at depth 0
    ValidMove=BestMoves(PrintRow, player,0, bools);
    // check if there are no valid moves or not
    if (ValidMove=="")
    {
        //checks to see whether turns is odd or even so evaluation can be returned in the perspective of the player
        if (turns&1)
        {
            return evaluation(PrintRow,player, bools);
        }
        else
            return -evaluation(PrintRow,player, bools);
    }

    // makes the moves in the loop and exits when there are no moves left, it also gets value of the move
    while ((r<ValidMove.length()))
    {
        // creates a copy of the board
        game.BoardSetup(PrintRow, CopyBoard);


        // checks to see if the move is a castling move, if the move is a castling move castles
        if (MovesClass.castling(string (1,ValidMove[t])+string (1,ValidMove[q])+string (1,ValidMove[z])+string (1,ValidMove[r]),
                                PrintRow,player)==false)
        {
            //makes move noramlly if it isn't a castling move
            MovesClass.MovesWithoutLegal(ValidMove[t],convert.CharToInt(ValidMove[q]),ValidMove[z],convert.CharToInt(ValidMove[r]),PrintRow);
        }
        // checks to see if it returns score higher than a previous score
        if (fFoundPv)
        {
            // calls AlphaBeta function to get a val of move
            val = AlphaBeta(depth - 1, alpha, alpha+1,PrintRow, player, turns+1, bools);
            if ((val > alpha) && (val < beta)) // Check for failure.
                // calls AlphaBeta again with different parameters if it fails
                val = AlphaBeta(depth - 1, alpha, beta,PrintRow, player, turns+1, bools);
        }
        else
            //if Principal node wasn't found runs through the function as normal
            val = AlphaBeta(depth - 1, alpha, beta,PrintRow, player, turns+1, bools);

        // unmakes the move and resets board so it can make new move
        game.BoardSetup(CopyBoard,PrintRow );

        // increases value so new move can be made
        t+=4;
        q+=4;
        z+=4;
        r+=4;

        // checks to see if turn is odd
        if (turns&1)
        {
            // if odd runs it from the lower case player's perspective
            if( val >= beta )
                return beta;   // fail hard beta-cutoff
            if( val > alpha )
                alpha = val; // alpha acts like max in MiniMax
            // makes the pricipal node value true
            fFoundPv = true;
        }
        else
        {
            // if even runs it from the upper case player's perspective
            if( val <= alpha )
                return alpha; // fail hard alpha-cutoff
            if( val < beta )
                beta = val; // beta acts like min in MiniMax
            // makes the pricipal node value true
            fFoundPv = true;
        }


    }
    // returns different values based on the perspective of the player playing which
    if (turns&1)
    {
        return alpha;
    }
    else
    {
        return beta;
    }
}

//program to limit the moves at each depth to 5 at a user defined depth
string ArtificialIntelligence::BestMoves (string PrintRow[8][8], string player, int depth, string bools)
{
    // create class objects
    Conversion convert;
    ValidMove valid;
    moves MovesClass;
    GameFunctions game;
    LegalMoves legal;

    // create variable types
    typedef vector <string> VectorString;
    typedef vector <int> VectorInt;

    VectorInt val; //vector for storing score
    VectorString BestMove; //vector for bestmove

    // variables for counters in the loop
    register int t=0;
    register int q=1;
    register int z=2;
    register int r=3;
    // counter for counting the number of best moves added to make it only the the top 5 best
    int counter=0;
    // temporary variable used in the sorting of moves
    int temp;
    // temp variable to temporially store current the best move
    string TempBestMove;
    // variable to hold the valid moves
    string ValidMove1="";
    // variable to store a copy of the board
    string CopyBoard[8][8];
    // variable to store the
    int turns;

    // variable to store the best valid moves
    string ValidBestMove="";
    // assigns a value for turns based
    if (player=="lower")
        turns=1;
    else
        turns=2;
    // calls function to get valid moves and store it in string ValidMove1
    ValidMove1=valid.ValidMoves(PrintRow, player, bools);

    // loops that check makes legal moves and exits loop when there are no more moves to be made
    while (r<ValidMove1.length())
    {

        // makes a copy of the board
        game.BoardSetup(PrintRow,CopyBoard);

        //checks to see if the move is a castling move, if it isn't makes the move normally
        if (MovesClass.castling(string (1,ValidMove1[t])+string (1,ValidMove1[q])+string (1,ValidMove1[z])+string (1,ValidMove1[r]),
                                PrintRow,player)==false)
        {
            // calls function to make the move normally
            MovesClass.MovesWithoutLegal(ValidMove1[t],convert.CharToInt(ValidMove1[q]),ValidMove1[z],convert.CharToInt(ValidMove1[r]),PrintRow);
        }
        //stores the score returned by Negamax in a vector array called val
        val.push_back (-Negamax(depth, INT_MIN, INT_MAX,PrintRow, player, turns+1, bools));
        //stores the move made to achieve the score in a vector array called BestMove
        BestMove.push_back (string (1,ValidMove1[t])+string (1,ValidMove1[q])+string (1,ValidMove1[z])+string (1,ValidMove1[r]));
        // resets the board back to the copy of the board
        game.BoardSetup(CopyBoard,PrintRow);

        // increases the counter by one is that it knows the number of elements sort later
        counter++;
        //increases the counters by 4 so the next move can be made
        t+=4;
        q+=4;
        z+=4;
        r+=4;
    }
    //loop used to sort the moves from best to worst
    for (int i=0; i<counter; i++)
    {
        for (int t=i; t>=0; t--)
        {
            // if statemate is used to switch moves and move scores accordingly
            if (val[i]>=val[i-t])
            {

                // variables switch position of moves changing their position in the array
                TempBestMove=BestMove[i-t];
                BestMove[i-t]=BestMove[i];
                BestMove[i]=TempBestMove;
                temp=val[i-t];
                val[i-t]=val[i];
                val[i]=temp;
            }
        }

    }

    // makes sure the number of moves stored for a given turn is never greater than 5
    if (counter>5)counter=5;
    // puts the ordered moves into a single string
    for (int i=0; i<counter; i++)
    {
        ValidBestMove+=BestMove[i];
    }

    return ValidBestMove; //returns the valid best moves
}

// function to read the ai move files in order perform openings such as the queen's gambit
bool ArtificialIntelligence::openings (string PrintRow[8][8], bool NormalKingUpper, bool NormalKingLower, bool NormalRookUpperRight,
                                       bool NormalRookUpperLeft, bool NormalRookLowerRight, bool NormalRookLowerLeft, int NormalTemp1,  int NormalTemp2,char NormalTemp3,
                                       string NormalEnPassant, string NormalPlayer)
{
    //declare variable to store the original board
    string OriginalBoard [8][8] {{" R "," N "," B "," K "," Q "," B "," N "," R "},
        {" P "," P "," P "," P "," P "," P "," P "," P " },{"   ","   ","   ","   ","   ","   ","   ","   "},
        {"   ","   ","   ","   ","   ","   ","   ","   "},{"   ","   ","   ","   ","   ","   ","   ","   "},
        {"   ","   ","   ","   ","   ","   ","   ","   "},{" p "," p "," p "," p "," p "," p "," p "," p ",},
        {" r "," n "," b "," k "," q "," b "," n "," r "}
    };
    //create class objects
    Conversion convert;
    GameFunctions game;

    // create vector variable types
    typedef vector <int> VectorInt;
    typedef vector <bool> VectorBool;
    typedef vector <string> VectorString;
    typedef vector <char> VectorChar;
    // declare variables for holding the board states from the text file
    VectorString BoardStates [8][8];
    VectorBool KingUpper;
    VectorBool KingLower;
    VectorBool RookUpperRight;
    VectorBool RookUpperLeft;
    VectorBool RookLowerRight;
    VectorBool RookLowerLeft;
    VectorInt  turns;
    VectorInt  temp1;
    VectorInt temp2;
    VectorChar temp3;
    VectorString EnPassant;
    VectorString LastTurn;
    // variable to hold the player who is playing based on the turn number in the text file
    string player;
    //variables to store vectors that were converted to normal
    string LastTurnString;
    string EnPassantString;
    // variable used to get input from the text file
    string InputValues;
    // variables to store the turn number based
    int NormalTurns;
    int MatchNum=0;
    int MatchCount=0;
    int i=0;
    // variable used as a counter to tell the program how many elements the vector array has
    int t=0;
    // variable used to return whether it is the end of an opening or not
    bool EndOfOpening=true;
    //boolean variable used to check to see if there is a match
    bool match=false;
    // number to give the ai an idea of which match it should use so it isn't allows playing the same opening
    int FinishedMatching;
    // variable for
    int BoardNum;


    // gets random number to chose opening
    int max;
    max = 92;
    srand(time(0)); //gets randomnum num using time
    FinishedMatching= (rand () % max) + 1;

    // assigns a value for normal turns based on whether the player is upper of lowercase letters
    if (NormalPlayer=="lower")
        NormalTurns=1;
    else
        NormalTurns=2;

    //declares input stream
    ifstream InputFile;

    //decides which file to open based on which player is playing
    if (NormalPlayer=="lower")
    {
        //tries to open the text file
        ifstream ifile("LowerMoves.txt");
        // check to see if it could open it if it can' returns false
        if (!(ifile)) return false;
        // if it can opens the text file
        InputFile.open("LowerMoves.txt"); //gets the text for lowermoves
    }
    else if  (NormalPlayer=="upper")
    {
        //tries to open the text file
        ifstream ifile("UpperMoves.txt");
        // check to see if it could open it if it can' returns false
        if (!(ifile)) return false;
        // if it can opens the text file
        InputFile.open("UpperMoves.txt"); //gets the text file for uppermoves
    }
    // reads the text file till it hits the word blank
    while (InputValues!="BLANK")
    {
        //resets the value of the input file to a null string
        InputValues="";
        // reads the next line in the text file
        getline(InputFile,InputValues);
        // checks to see if it equals BLANK and if it does exits
        if (InputValues=="BLANK") break;
        // resets the value of i to 0 so it can read the board
        i=0;

        // loop to read the board from the text file and store it in the BoardStates vector array
        for (int col=0; col<=7; col++)
        {
            for (int row=0; row<=7; row++)
            {
                BoardStates[col][row].push_back(" "+string(1,InputValues[i])+" ");
                i++;
            } //loads the board states
        }

        // assigns the value of InputValues to be nothing
        InputValues="";
        // reads the next line in the text file
        getline(InputFile,InputValues);
        // assigns the bool values to the following variables
        KingUpper.push_back(convert.CharToBool(InputValues[0]));
        KingLower.push_back(convert.CharToBool(InputValues[1]));
        RookUpperRight.push_back(convert.CharToBool(InputValues[2]));
        RookUpperLeft.push_back(convert.CharToBool(InputValues[3]));
        RookLowerRight.push_back(convert.CharToBool(InputValues[4]));
        RookLowerLeft.push_back(convert.CharToBool(InputValues[5]));
        // assigns the value of InputValues to be a null string
        InputValues="";
        // gets the next line in the text file
        getline(InputFile,InputValues);
        // converts the line of the text file to an integer and assigns it to the variable turns
        turns.push_back(convert.StringToInt(InputValues));
        // assigns the value of InputValues to be a null string
        InputValues="";
        // gets the next line in the text file
        getline(InputFile,InputValues);
        temp1.push_back(convert.CharToInt(InputValues[0]));
        temp2.push_back(convert.CharToInt(InputValues[1]));
        temp3.push_back(InputValues[2]);
        // assigns the value of InputValues to be a null string
        InputValues="";
        // gets the next line in the text file
        getline(InputFile,InputValues);
        //adds the value of en passant to the variable EnPassant
        EnPassant.push_back(InputValues);
        // gets the next line in the text file
        getline(InputFile,InputValues);
        //adds the value of LastTurn to the variable LastTurn
        LastTurn.push_back(InputValues);
        t++;
    }
    // closes the input file
    InputFile.close();

    // sets the value of BoardNum to t (number of elements in the array) so it can serve boundary for the loop
    BoardNum=t;

    // loop to check for matches in board states
    for (t=0; t<BoardNum; t++)
    {

        //checks to see if the end of the array has been reached without finding a match at the desired number value
        // thus sets the value to use the last match
        if (t==BoardNum-1 and MatchCount!=0)
        {
            MatchCount=FinishedMatching-1;
            t=MatchNum;
        }
        //assigns which player's turn it is depending on the value of turns
        if (turns[t]%2!=0) player="lower";
        else player="upper";

        // checks to see if all conditions found in the text file match the game conditions
        if ((KingUpper[t]==NormalKingUpper and KingLower[t]==NormalKingLower and RookUpperRight[t]==NormalRookUpperRight and
                RookUpperLeft[t]==NormalRookUpperLeft and RookLowerRight[t]==NormalRookLowerRight and RookLowerLeft[t]==NormalRookLowerLeft
                and temp1[t]==NormalTemp1  and temp2[t]==NormalTemp2 and temp3[t]==NormalTemp3 and EnPassant[t]==NormalEnPassant
                and player==NormalPlayer))

        {
            // sets match equal to true
            match=true;

            // checks the board to make sure the game board matches the board in the text file
            // if it matches then leaves match equal to true
            for (int col=0; col<=7; col++)
            {
                for (int row=0; row<=7; row++)
                {
                     // if something doesn't match sets the boolean variable match to false and breaks out of the loop
                    if ((BoardStates[col][row][t])!=PrintRow[col][row])
                    {
                        match=false;
                        break;
                    }
                }
                // checks to see if match was set to false and breaks out of this loop too
                if (match==false)
                    break;
            }

            //checks to see if match is equal to true
            if (match==true)
            {
                // if the match is true sets match number to t
                MatchNum=t;
                //imccreases match
                MatchCount++;
            }


            // if MatchCount is equal to finish matching which means it found the latest match closest to number it goes to moving the to next board
            // to the console
            if (MatchCount==FinishedMatching)
            {
                // makes sure it is not going into the next opening by comparing the original board to the new board it was going to change to
                for (int col=0; col<=7; col++)
                {
                    for (int row=0; row<=7; row++)
                    {
                        if ((BoardStates[col][row][MatchNum+1])!=OriginalBoard[col][row])

                        {
                            //if they don't match then EndOfOpening is assigned a value of false
                            EndOfOpening=false;
                            // then breaks out of the loop
                            break;
                        }
                    }
                }
                // breaks out of the function if it is the end of the opening
                if (EndOfOpening==true)
                {
                    return false;
                }
                //stores the new board in the variable of the old board
                for (int col=0; col<=7; col++)
                {
                    for (int row=0; row<=7; row++)
                    {
                        PrintRow[col][row]=(BoardStates[col][row][MatchNum+1]);
                    }
                }
                // stores new bools for castling in a single variable entitled bools
                string bools= string(1,((char)(KingUpper[MatchNum+1]+48))) +string(1,((char)(KingLower[MatchNum+1]+48)))+
                string(1,((char)(RookUpperRight[MatchNum+1]+48)))+ string(1,((char)(RookUpperLeft[MatchNum+1]+48)))
                +string(1,((char)(RookLowerRight[MatchNum+1]+48))) + string(1,((char)(RookLowerLeft[MatchNum+1]+48)));
                // stores new temporary variables for enpassant in a string entitled temps
                string temps=string(1,(char)(temp1[MatchNum+1]+48))+string(1,(char)(temp2[MatchNum+1]+48))+string(1,temp3[MatchNum+1]);
                // converts the vector string value to a normal string
                EnPassantString=EnPassant[MatchNum+1];
                // converts the vector string value to a normal string
                LastTurnString=LastTurn[MatchNum+1];
                //logs games very quickly into a temp text then deletes it later
                game.LoggingGames(PrintRow, "temp.txt", false, bools, NormalTurns+1,  temps, EnPassantString, LastTurnString );
                // returns a true value
                return true;
            }


        }
    }
    // returns false if the other conditions were not matched and therefore a matching board state was not found
    return false;
}


