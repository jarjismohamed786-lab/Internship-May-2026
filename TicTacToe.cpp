#include <iostream>

using namespace std;

char board[3][3] =
{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

char currentPlayer = 'X';

void displayBoard()
{
    cout << "\n";

    for (int i = 0; i < 3; i++)
    {
        cout << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            if (j < 2)
            {
                cout << " | ";
            }
        }

        cout << endl;

        if (i < 2)
        {
            cout << "---|---|---" << endl;
        }
    }

    cout << "\n";
}

bool placeMark(int position)
{
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O')
    {
        board[row][col] = currentPlayer;
        return true;
    }

    return false;
}

bool checkWin()
{
    // Rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
        {
            return true;
        }
    }

    // Columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
        {
            return true;
        }
    }

    // Diagonals
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
    {
        return true;
    }

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
    {
        return true;
    }

    return false;
}

bool checkDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                return false;
            }
        }
    }

    return true;
}

void switchPlayer()
{
    if (currentPlayer == 'X')
    {
        currentPlayer = 'O';
    }
    else
    {
        currentPlayer = 'X';
    }
}

void resetBoard()
{
    char value = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = value;
            value++;
        }
    }

    currentPlayer = 'X';
}

int main()
{
    char playAgain;

    do
    {
        resetBoard();

        int position;
        bool gameOver = false;

        while (!gameOver)
        {
            displayBoard();

            cout << "Player " << currentPlayer << ", enter position (1-9): ";
            cin >> position;

            if (position < 1 || position > 9)
            {
                cout << "\nInvalid Position!\n";
                continue;
            }

            bool success = placeMark(position);

            if (!success)
            {
                cout << "\nPosition Already Taken!\n";
                continue;
            }

            if (checkWin())
            {
                displayBoard();

                cout << "Player " << currentPlayer << " Wins!\n";

                gameOver = true;
            }
            else if (checkDraw())
            {
                displayBoard();

                cout << "Game Draw!\n";

                gameOver = true;
            }
            else
            {
                switchPlayer();
            }
        }

        cout << "\nDo You Want To Play Again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThanks For Playing!\n";

    return 0;
}