#include "ChessGame.h"
#include "SomeException.h"
#include <fstream>
#include <time.h>
#include <thread>
#include <chrono>

void CChess::PrintPlayers(string time)
{
    ofstream fileF;
    fileF.open("ChessPlayers.txt", ios_base::app);
    fileF << " - " << nameA << " VS " << nameB << ", these opponents played on: " << time << endl;
    fileF.close();
}

void CChess::EnterNames()
{
    try
    {
        cout << "WELCOME:\nCastling, pawn promotion, en passant and pawn double-moves\nare not implemented (rules and exceptions);" << endl;
        cout << "The ingame exit code is 999 (while inputing movement coordinates);\nEntering it just once will exit the game; \nEnter your names and begin!" << endl;
        cout << "White (1st) player is: ";
        cin >> nameA;
        cout << "Black (2nd) player is: ";
        cin >> nameB;
        
        if (nameA.size() < 3 || nameB.size() < 3)
            throw Mistake::SomeException("Little short for proper names, lady/serah? OK, go on!");
    }
    catch (Mistake::SomeException & param)
    {
        cout << "Note -> Testing an exception: Woops! " << param.message << "\n" << endl;
    }
    cout << "Note -> Bugs, mistakes, code redundance & missed implementations are expected.\nThis was my first c++ project." << endl;
    cout << "\n\tHave a good match!\n___________________________________" << endl;
}

// main game loop
void CChess::Start()
{
    time_t btime;
    struct tm* beginTime;
    time(&btime);
    beginTime = localtime(&btime);
    int beginHours = beginTime->tm_hour;
    int beginMinutes = beginTime->tm_min;
    int beginSeconds = beginTime->tm_sec;
    
    EnterNames();
    exitCode = false;
    do
    {
        GetNextMove(mqGameBoard.mqpaaBoard);
        AlternateTurn();
        if (exitCode)
            break;
        this_thread::sleep_for(2s);
    } while (!IsGameOver());
    
    PrintPlayers(asctime(end));
    mqGameBoard.Print();
}

void CChess::GetNextMove(CAPiece* qpaaBoard[8][8])
{
    bool bValidMove = false;
    do
    {
        mqGameBoard.Print();
        
        // get input and convert to coordinates
        int iStartMove;
        int iStartRow;
        int iStartCol;
        //cin >> iStartMove;
        
        int iEndMove;
        int iEndRow;
        int iEndCol;
        //cin >> iEndMove;
        
        cout << mcPlayerTurn << "'s Move: ";
        cin >> iStartMove;
        cout << "To: ";
        cin >> iEndMove;
        
        while (cin.fail() || iStartMove > 1000 || iStartMove < -1000 || iEndMove > 1000 || iEndMove < -1000)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid Input! Enter number coordinates (num of 2 digits):\n" << endl;
            cout << mcPlayerTurn << "'s Move: ";
            cin >> iStartMove;
            cout << "To: ";
            cin >> iEndMove;
        }
        
        if (iStartMove == 999 || iEndMove == 999)
        {
            cout << "You've entered the exit game code 999.\nYour info is printed in ChessPlayers.txt\nHave a nice day!" << endl;
            exitCode = true;
            if (exitCode)
            {
                time_t etime;
                time(&etime);
                end = localtime(&etime);
                
                int endHours = end->tm_hour - beginHours;
                int endMinutes = end->tm_min - beginMinutes;
                int endSeconds = end->tm_sec - beginSeconds;
                
                if (endSeconds < 0)
                {
                    endMinutes--;
                    endSeconds = 60 + endSeconds;
                }
                
                PrintPlayers(asctime(end));
            }
            // if the command below is not recognized, the term will show this sh: 'pause: command not found'
            system("pause");
            cout << "Maybe bash won't recognize the system('pause') command.\nIt's OK, farewell!" << endl;
            exit(0);
        }
        
        iStartRow = (iStartMove / 10) - 1;
        iStartCol = (iStartMove % 10) - 1;
        iEndRow = (iEndMove / 10) - 1;
        iEndCol = (iEndMove % 10) - 1;
        
        // check that the indices are in range
        // and that the source and destination are different
        if ((iStartRow >= 0 && iStartRow <= 7) && (iStartCol >= 0 && iStartCol <= 7) && (iEndRow >= 0 && iEndRow <= 7) && (iEndCol >= 0 && iEndCol <= 7))
        {
            // additional checks in here
            CAPiece* qpCurrPiece = qpaaBoard[iStartRow][iStartCol];
            // check that the piece is the correct color
            if ((qpCurrPiece != 0) && (qpCurrPiece->GetColor() == mcPlayerTurn))
            {
                // check that the destination is a valid destination
                if (qpCurrPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, qpaaBoard))
                {
                    // make the move
                    CAPiece* qpTemp = qpaaBoard[iEndRow][iEndCol];
                    qpaaBoard[iEndRow][iEndCol] = qpaaBoard[iStartRow][iStartCol];
                    qpaaBoard[iStartRow][iStartCol] = 0;
                    // make sure that the current player is not in check
                    if (!mqGameBoard.IsInCheck(mcPlayerTurn))
                    {
                        delete qpTemp;
                        bValidMove = true;
                    }
                    else
                    { // undo the last move
                        qpaaBoard[iStartRow][iStartCol] = qpaaBoard[iEndRow][iEndCol];
                        qpaaBoard[iEndRow][iEndCol] = qpTemp;
                    }
                }
            }
        }
        if (!bValidMove)
        {
            cout << "Invalid move!" << endl;
        }
    } while (!bValidMove);
}

void CChess::AlternateTurn()
{
    mcPlayerTurn = (mcPlayerTurn == 'W') ? 'B' : 'W';
}

bool CChess::IsGameOver()
{
    // check that the current player can move;
    // if not, we have a stalemate or checkmate
    bool bCanMove(false);
    bCanMove = mqGameBoard.CanMove(mcPlayerTurn);
    if (!bCanMove)
    {
        if (mqGameBoard.IsInCheck(mcPlayerTurn))
        {
            AlternateTurn();
            cout << "Checkmate, " << mcPlayerTurn << " Wins!" << endl;
            if (mcPlayerTurn == 'W')
                cout << nameA << " is the winner!" << endl;
            else
                cout << nameB << " is the winner!" << endl;
        }
        else
        {
            cout << "Stalemate!" << endl;
        }
    }
    return !bCanMove;
}
