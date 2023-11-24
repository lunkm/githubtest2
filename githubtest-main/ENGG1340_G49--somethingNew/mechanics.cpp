#include "display.h"
#include "mechanics.h"
#include <iostream>
#include <string>
#define reset "\033[1;0m"
#define red "\033[1;31m"
#define green "\033[1;32m"
#define yellow "\033[1;33m"
#define blue "\033[1;34m"
#define magenta "\033[1;35m"
#define cyan "\033[1;36m"
#define white "\033[1;37m"
#define blueBackground "\033[44m"
using namespace std;


void Board::setBoardSize() {
    cout << "CUSTOMIZE YOUR OWN BOARD, OWN GAME!!" << endl;
    cout << "ENTER NUMBER BETWEEN 8-16 FOR row : ";
    cin >> row;
    cout << "ENTER NUMBER BETWEEN 8-30 FOR column : ";
    cin >> column;
    
    while ( row<8 || row>16)
    {
        cout << "Please enter the row again : ";
        cin >> row;
    }
    
    while ( column<8 || column >30 )
    {
        cout << "Please enter the col again : ";
        cin >> column;
    }
}


void Board::setBoard() {
    mineBoard = new char*[row];
    for(int i=0; i<row; i++) {
        mineBoard[i] = new char[column];
    }
    
    // make player board
    playerBoard = new char*[row];
    for(int i=0; i<row; i++) {
        playerBoard[i] = new char[column];
    }
    
    for(int i=0; i<row; i++)
    {
        for(int j = 0; j < column; ++j) {
            playerBoard[i][j] = ' ';
            mineBoard[i][j] = '.';
        }
    }
}


void Board::placeMines(int x, int y)
{
    mineBoard[x][y]='H';
    
    numberOfMines = (row*column) * 0.2;
    numberOfFlags = numberOfMines;
    currentScore = 5000;
    
    int rnd_r, rnd_c;   // random input for row and column
    
    srand(time(NULL));
    for (int i=0; i<numberOfMines; i++)
    {
        rnd_r = rand() % row;
        rnd_c = rand() % column;
        
        while (rnd_r>=x-1 && rnd_r<=x+1)
            rnd_r = rand() % row;
        
        while (rnd_c>=y-1 && rnd_c<=y+1)
            rnd_c = rand() % column;
        
        if (mineBoard[rnd_r][rnd_c] == 'B')
        {
            i--; continue;
        }
        else
            mineBoard[rnd_r][rnd_c] = 'B';
    }
}


void Board::delDynamic()
{
    for(int i=0; i<row; i++)
        delete[] mineBoard[i];
    delete[] mineBoard;
    
    mineBoard = nullptr;
}
     

// needs to be edited to highlight or point to where the cursor is currently located
void Board::printBoard() {
    system("clear");
    displayBanner();

    string corners[9] = {"┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"};
    int l = 0;

    for (int i = 0; i < row; ++i) {
        if (i != 0) {
            l = 3;
        }

        cout << corners[l] << "─────";

        for (int j = 1; j < column; ++j) {
            cout << corners[l+1] << "─────";
        }

        cout << corners[l+2] << '\n';

        for (int j = 0; j < column; ++j) {
            if (i == yLocation && j == xLocation){
                cout << "│  " << blueBackground << playerBoard[i][j] << reset << "  ";
                continue;
            }
            cout << "│  " << playerBoard[i][j] << "  ";
        }
        cout << "│" << '\n';
    }

    cout << corners[6] << "─────";
    for (int j = 1; j < column; ++j) {
            cout << corners[7] << "─────";
        }
    cout << corners[8];
    displayControls();
}


char Board::getPlayerInput(bool IsFirstTimePlaying) {
    char playerInput;
    printBoard();
    cout << "input the direction you want to head. "
            "if you put in multiple characters, "
            "only the first one will be considered.\n";

    bool validInput = false;
    do {
        cin >> playerInput;

        switch (playerInput) {
        case 's':
        case 'S':
            if (yLocation + 1 < row) {
                ++yLocation;
                validInput = true;
            }
            break;

        case 'a':
        case 'A':
            if (xLocation - 1 >= 0) {
                --xLocation;
                validInput = true;
            }
            break;

        case 'w':
        case 'W':
            if (yLocation - 1 >= 0) {
                --yLocation;
                validInput = true;
            }
            break;

        case 'd':
        case 'D':
            if (xLocation + 1 < column) {
                ++xLocation;
                validInput = true;
            }
            break;

        case 'o':
        case 'O':
            if (IsFirstTimePlaying == true) {
                return 'o';
            }
            uncover(xLocation, yLocation);
            validInput = true;
            break;

        case 'p':
        case 'P':
            if (IsFirstTimePlaying == true) {
                break;
            }
            flagging();
            validInput = true;
            break;

        case 'm':
        case 'M':
            validInput = true;
            return 'm';

        default:
            break;
        }
        
        if (!validInput) {
            printBoard();
            cout << "invalid input. please enter again.\n";
        }

    } while (!validInput);

    return '.';

}


void Board::uncover(int x, int y) {
    if (mineBoard[y][x] == 'B') {
        numberOfFlags -= 1;
        numFlagMines += 1;
        currentScore -= 100;
        playerBoard[y][x] = '@';
        cout << "You uncovered a mine!\n";
        // not final. need to figure out a way to format this message below the board.
        return;
        if(numFlagMines == numberOfMines){
        cout << "You have uncovered all the mines!\n"
        };
    }
    
    playerBoard[y][x] = '.';
    int surroundingMineCount = 48;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            if (i == 0 && j == 0) {
                continue;
            }

            int neighborX = x + i;
            int neighborY = y + j;

            bool cellOutOfRange = (neighborX < 0 || neighborX >= column || neighborY < 0 || neighborY >= row);
            if (cellOutOfRange) {
                continue;
            }

            if (mineBoard[neighborY][neighborX] == 'B') {
                surroundingMineCount++;
            }
        }
    }

    if (surroundingMineCount != 48) {
        playerBoard[y][x] = char(surroundingMineCount);
        return;
    }

    // recursively uncover the neighboring cells if surroundingMineCount is 0.
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            if (i == 0 && j == 0) {
                continue;
            }

            int neighborX = x + i;
            int neighborY = y + j;

            bool cellOutOfRange = (neighborX < 0 || neighborX >= column || neighborY < 0 || neighborY >= row);
            if (cellOutOfRange) {
                continue;
            }

            if (playerBoard[neighborY][neighborX] == '.') {
                continue;
            }

            uncover(neighborX, neighborY);
        }
    }
}


// 'F' for flags? not final. Also, the scores need to be adjusted.
void Board::flagging() {
    numberOfFlags = numberOfMines;
    currentScore = 5000;
    //이 위에 두개 중간에 끼워넣어야 할듯 여기다 넣으면 계속 초기화될거 같아
    if (playerBoard[yLocation][xLocation] == 'F') {
        playerBoard[yLocation][xLocation] = ' ';
        numberOfFlags -= 1;
        if(mineboard[yLocation][xLocation] == 'B'){
        numFlagMines -= 1;
        return;
        }
        return;
    }

    playerBoard[yLocation][xLocation] = 'F';
    numberOfFlags += 1
    if(mineboard[yLocation][xLocation] == 'B'){
        numFlagMines += 1;
        return;
    }

    if(numFlagMines == numberOfMines){
        cout << "You have uncovered all the mines!\n"
        }
}
