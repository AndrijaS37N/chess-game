#include "ChessGame.h"
#include "CustomException.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

void ChessGame::printPlayers(std::string time)
{
    std::string fileName = "game-date-history.txt";
    std::ofstream logFile(fileName, std::ios_base::app);
    logFile << "-> " << nameA << " VS " << nameB << ", these opponents finished playing on: " << time << std::endl;
    logFile.close();
    
    if(logFile)
        std::cout << "Your info is printed in " << fileName << std::endl;
    else
        std::cout << "Something went wrong with the fstream." << std::endl;
}

void ChessGame::enterNames()
{
    try
    {
        std::cout << "\n\t\tWelcome:\n\n* Castling, pawn promotion, en passant and pawn double-moves are not implemented (rules and exceptions)." << std::endl;
        std::cout << "* The ingame exit code is 999 (enter it while inputing movement coordinates)." << std::endl;
        std::cout << "* White (1st) player is: ";
        getline(std::cin, nameA);
        std::cout << "* Black (2nd) player is: ";
        getline(std::cin, nameB);
        
        if (nameA.length() < 3 || nameB.length() < 3)
            throw Mistake::CustomException("One of those names is a short one ... OK, go on!");
        
        if (nameA == nameB)
            throw Mistake::CustomException("Those names are the same ... but OK, go on!");
    }
    catch (Mistake::CustomException & arg)
    {
        std::cout << "\n* Woops! " << arg.message << "\n" << std::endl;
    }
    std::cout << "* Bugs, mistakes, code redundances and lack of implementations are expected.\n* This was my first C++ project." << std::endl;;
    std::cout << "\n\t\tHave a good match!\n___________________________________" << std::endl;
}

// main game loop
void ChessGame::start()
{
    enterNames();
    exitCode = false;
    do
    {
        if (exitCode)
            break;
        
        getNextMove(gameBoard.boardMove);
        alternateTurn();
        
        // Xcode doesn't recognize this function 'sleep_for', perhaps it's OS dependent
        // #include <time.h>
        // #include <thread>
        // #include <chrono>
        // this_thread::sleep_for(2s);
        
        // I will use this one -> #include <unistd.h> -> usleep(1000000) '1s'
        usleep(1000*1000);
        
    } while (!isGameOver());
    
    std::cout << "Here is the view of the last move:" << std::endl;
    gameBoard.print();
}

void ChessGame::getNextMove(ChessPiece* boardMove[8][8])
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
            std::cout << "\nInvalid input! Enter number coordinates (num of 2 digits)." << std::endl;
            std::cout << turnOf << "'s Move: ";
            std::cin >> iStartMove;
            std::cout << "To: ";
            std::cin >> iEndMove;
        }
        
        if (iStartMove == 999 || iEndMove == 999)
        {
            std::cout << "You've entered the exit game code 999.\nHave a nice day!" << std::endl;
            exitCode = true;
            if (exitCode)
                printPlayers(getCurrentTime());

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
            ChessPiece* currentPiece = boardMove[iStartRow][iStartCol];
            // check that the piece is the correct color
            if ((currentPiece != 0) && (currentPiece->getColor() == turnOf))
            {
                // check that the destination is a valid destination
                if (currentPiece->isLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, boardMove))
                {
                    // make the move
                    ChessPiece* temp = boardMove[iEndRow][iEndCol];
                    boardMove[iEndRow][iEndCol] = boardMove[iStartRow][iStartCol];
                    boardMove[iStartRow][iStartCol] = 0;
                    // make sure that the current player is not in check
                    if (!gameBoard.isInCheck(turnOf))
                    {
                        delete temp;
                        bValidMove = true;
                    }
                    else
                    { // undo the last move
                        boardMove[iStartRow][iStartCol] = boardMove[iEndRow][iEndCol];
                        boardMove[iEndRow][iEndCol] = temp;
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
            std::cout << "Checkmate!" << std::endl;
            if (turnOf == 'W')
                std::cout << nameA << " is the winner!" << std::endl;
            else
                std::cout << nameB << " is the winner!" << std::endl;
        }
        else
        {
            std::cout << "Stalemate!" << std::endl;
        }
        
        printPlayers(getCurrentTime());
    }
    
    return !bCanMove;
}

std::string ChessGame::getCurrentTime()
{
    time_t timeVar;
    time(&timeVar);
    endTime = localtime(&timeVar);
    return asctime(endTime);
}
