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
    
    std::cout << "Press any key to start ..." << std::endl;
    std::cin.get();
    
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
    gameBoard.printBoard();
    std::cout << std::endl;
}

void ChessGame::getNextMove(ChessPiece* boardMove[8][8])
{
    bool boolValidMove = false;
    do
    {
        gameBoard.printBoard();
        
        // get input and convert to coordinates
        int startMove;
        int startRow;
        int startCol;
        
        int endMove;
        int endRow;
        int endCol;
        
        std::cout << turnOf << "'s Move: ";
        std::cin >> startMove;
        std::cout << "To: ";
        std::cin >> endMove;
        
        while (std::cin.fail() || startMove > 1000 || startMove < -1000 || endMove > 1000 || endMove < -1000)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input! Enter number coordinates (num of 2 digits)." << std::endl;
            std::cout << turnOf << "'s Move: ";
            std::cin >> startMove;
            std::cout << "To: ";
            std::cin >> endMove;
        }
        
        if (startMove == 999 || endMove == 999)
        {
            std::cout << "You've entered the exit game code 999.\nHave a nice day!" << std::endl;
            exitCode = true;
            if (exitCode)
                printPlayers(getCurrentTime());

            exit(0);
        }
        
        startRow = (startMove / 10) - 1;
        startCol = (startMove % 10) - 1;
        endRow = (endMove / 10) - 1;
        endCol = (endMove % 10) - 1;
        
        // check that the indices are in range
        // and that the source and destination are different
        if ((startRow >= 0 && startRow <= 7) && (startCol >= 0 && startCol <= 7) && (endRow >= 0 && endRow <= 7) && (endCol >= 0 && endCol <= 7))
        {
            // additional checks in here
            ChessPiece* currentPiece = boardMove[startRow][startCol];
            // check that the piece is the correct color
            if ((currentPiece != 0) && (currentPiece->getColor() == turnOf))
            {
                // check that the destination is a valid destination
                if (currentPiece->isLegalMove(startRow, startCol, endRow, endCol, boardMove))
                {
                    // make the move
                    ChessPiece* temp = boardMove[endRow][endCol];
                    boardMove[endRow][endCol] = boardMove[startRow][startCol];
                    boardMove[startRow][startCol] = 0;
                    // make sure that the current player is not in check
                    if (!gameBoard.isInCheck(turnOf))
                    {
                        delete temp;
                        boolValidMove = true;
                    }
                    else
                    { // undo the last move
                        boardMove[startRow][startCol] = boardMove[endRow][endCol];
                        boardMove[endRow][endCol] = temp;
                    }
                }
            }
        }
        if (!boolValidMove)
        {
            std::cout << "Invalid move!" << std::endl;
        }
    } while (!boolValidMove);
}

void ChessGame::alternateTurn() { turnOf = (turnOf == 'W') ? 'B' : 'W'; }

bool ChessGame::isGameOver()
{
    // check that the current player can move;
    // if not, we have a stalemate or checkmate
    bool boolCanMove(false);
    boolCanMove = gameBoard.canMove(turnOf);
    if (!boolCanMove)
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
    
    return !boolCanMove;
}

std::string ChessGame::getCurrentTime()
{
    time_t timeVar;
    time(&timeVar);
    endTime = localtime(&timeVar);
    return asctime(endTime);
}
