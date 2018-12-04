#include "ChessGame.h"
#include "CustomException.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

void ChessGame::printPlayers(std::string time)
{
    std::ofstream logFile;
    logFile.open("matches-players.txt", std::ios_base::app);
    logFile << "->" << nameA << " VS " << nameB << ", these opponents played on: " << time << '\n';
    logFile.close();
}

void ChessGame::enterNames()
{
    try
    {
        std::cout << "WELCOME:\nCastling, pawn promotion, en passant and pawn double-moves are not implemented (rules and exceptions)." << std::endl;
        std::cout << "The ingame exit code is 999 (while inputing movement coordinates)." << std::endl;
        std::cout << "White (1st) player is: ";
        std::cin >> nameA;
        std::cout << "Black (2nd) player is: ";
        std::cin >> nameB;
        
        if (nameA.size() < 3 || nameB.size() < 3)
            throw Mistake::CustomException("Little short for proper names, ey? OK, go on!");
    }
    catch (Mistake::CustomException & param)
    {
        std::cout << "Testing an exception: Woops! " << param.message << "\n" << std::endl;
    }
    std::cout << "Bugs, mistakes, code redundances and lack of implementations are expected.\nThis was my first C++ project." << std::endl;;
    std::cout << "\n\tHave a good match!\n___________________________________" << std::endl;
}

// main game loop
void ChessGame::start()
{
    time_t btime;
    struct tm* beginTime;
    time(&btime);
    beginTime = localtime(&btime);
    int beginHours = beginTime->tm_hour;
    int beginMinutes = beginTime->tm_min;
    int beginSeconds = beginTime->tm_sec;
    
    enterNames();
    exitCode = false;
    do
    {
        getNextMove(gameBoard.mqpaaBoard);
        alternateTurn();
        if (exitCode)
            break;
        // Xcode doesn't recognize this function 'sleep_for', perhaps it's OS dependent
        // #include <time.h>
        // #include <thread>
        // #include <chrono>
        // this_thread::sleep_for(2s);
        // I will use the Linux one -> #include <unistd.h> -> usleep(1000000) '1s'
        usleep(1000*1000);
        
    } while (!isGameOver());
    
    printPlayers(asctime(end));
    gameBoard.print();
}

void ChessGame::getNextMove(ChessPiece* qpaaBoard[8][8])
{
    bool bValidMove = false;
    do
    {
        gameBoard.print();
        
        // get input and convert to coordinates
        int iStartMove;
        int iStartRow;
        int iStartCol;
        
        int iEndMove;
        int iEndRow;
        int iEndCol;
        
        std::cout << turnOf << "'s Move: ";
        std::cin >> iStartMove;
        std::cout << "To: ";
        std::cin >> iEndMove;
        
        while (std::cin.fail() || iStartMove > 1000 || iStartMove < -1000 || iEndMove > 1000 || iEndMove < -1000)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid Input! Enter number coordinates (num of 2 digits):\n" << std::endl;
            std::cout << turnOf << "'s Move: ";
            std::cin >> iStartMove;
            std::cout << "To: ";
            std::cin >> iEndMove;
        }
        
        if (iStartMove == 999 || iEndMove == 999)
        {
            std::cout << "You've entered the exit game code 999.\nYour info is printed in matches-players.txt\nHave a nice day!" << std::endl;
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
                
                printPlayers(asctime(end));
            }
            // if the command below is not recognized, the term will show this sh: 'pause: command not found'
            system("pause");
            std::cout << "Maybe bash won't recognize the system('pause') command.\nIt's OK!" << std::endl;
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
            ChessPiece* qpCurrPiece = qpaaBoard[iStartRow][iStartCol];
            // check that the piece is the correct color
            if ((qpCurrPiece != 0) && (qpCurrPiece->getColor() == turnOf))
            {
                // check that the destination is a valid destination
                if (qpCurrPiece->isLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, qpaaBoard))
                {
                    // make the move
                    ChessPiece* qpTemp = qpaaBoard[iEndRow][iEndCol];
                    qpaaBoard[iEndRow][iEndCol] = qpaaBoard[iStartRow][iStartCol];
                    qpaaBoard[iStartRow][iStartCol] = 0;
                    // make sure that the current player is not in check
                    if (!gameBoard.isInCheck(turnOf))
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
            std::cout << "Invalid move!" << std::endl;
        }
    } while (!bValidMove);
}

void ChessGame::alternateTurn()
{
    turnOf = (turnOf == 'W') ? 'B' : 'W';
}

bool ChessGame::isGameOver()
{
    // check that the current player can move;
    // if not, we have a stalemate or checkmate
    bool bCanMove(false);
    bCanMove = gameBoard.canMove(turnOf);
    if (!bCanMove)
    {
        if (gameBoard.isInCheck(turnOf))
        {
            alternateTurn();
            std::cout << "Checkmate, " << turnOf << " Wins!" << std::endl;
            if (turnOf == 'W')
                std::cout << nameA << " is the winner!" << std::endl;
            else
                std::cout << nameB << " is the winner!" << std::endl;
        }
        else
        {
            std::cout << "Stalemate!" << std::endl;
        }
    }
    return !bCanMove;
}
