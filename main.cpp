#include <iostream>
#include <string>

using namespace std;

char board[7][7];

int turns;
int map;

int playerRow;
int playerCol;

bool gameOver = false;
bool winGame = false;

void make_board() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = ' ';
        }
    }

    if (map == 1) {

        for (int i = 0; i < 7; i++) {
            board[0][i] = '#';
            board[6][i] = '#';
            board[i][6] = '#';
        }

        for (int i = 0; i < 5; i++) {
            board[i][0] = '#';
        }

        board[2][2] = '#';
        board[2][4] = '#';
        board[4][3] = '#';
        board[4][5] = '#';

        board[5][0] = '@';
        playerRow = 5;
        playerCol = 0;

        board[2][5] = '$';

        board[1][3] = 'v';
        board[3][5] = '<';
        board[5][2] = '^';
    }

    if (map == 2) {

        for (int i = 0; i < 7; i++) {
            board[0][i] = '#';
            board[6][i] = '#';
            board[i][0] = '#';
            board[i][6] = '#';
        }

        board[2][2] = '#';
        board[3][2] = '#';
        board[4][4] = '#';

        board[1][1] = '@';
        playerRow = 1;
        playerCol = 1;

        board[5][5] = '$';

        board[2][5] = 'v';
        board[5][2] = '>';
    }

    if (map == 3) {

        for (int i = 0; i < 7; i++) {
            board[0][i] = '#';
            board[6][i] = '#';
            board[i][0] = '#';
            board[i][6] = '#';
        }

        board[2][2] = '#';
        board[2][3] = '#';

        board[4][2] = '#';
        board[4][4] = '#';

        board[1][1] = '@';
        playerRow = 1;
        playerCol = 1;

        board[5][5] = '$';

        board[2][4] = 'v';
        board[5][1] = '>';
    }
}

void print_board() {

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

bool isGuard(char c) {
    return (c == '^' || c == 'v' || c == '<' || c == '>');
}

void move_player(char move) {

    int newRow = playerRow;
    int newCol = playerCol;

    if (move == 'w') {
        newRow--;
    }
    else if (move == 's') {
        newRow++;
    }
    else if (move == 'a') {
        newCol--;
    }
    else if (move == 'd') {
        newCol++;
    }
    char target = board[newRow][newCol];

    if (target == '#') {
        cout << "You cant move through a wall! Try again." << endl;
        return;
    }

    if (isGuard(target)) {
        gameOver = true;
        return;
    }

    if (target == '$') {
        winGame = true;
    }

    board[playerRow][playerCol] = ' ';
    board[newRow][newCol] = '@';

    playerRow = newRow;
    playerCol = newCol;
}

char opposite(char guard) {

    if (guard == '^') {
        return 'v';
    }
    if (guard == 'v') {
        return '^';
    }
    if (guard == '<') {
        return '>';
    }
    return '<';
}

void move_guards() {

    char temp[7][7];

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            temp[i][j] = board[i][j];
        }
    }

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {

            if (!isGuard(board[r][c])) {
                continue;
            }
            char guard = board[r][c];

            int dr = 0;
            int dc = 0;

            if (guard == '^') {
                dr = -1;
            }
            if (guard == 'v') {
                dr = 1;
            }
            if (guard == '<') {
                dc = -1;
            }
            if (guard == '>') {
                dc = 1;
            }

            int nr = r + dr;
            int nc = c + dc;

            if (board[nr][nc] != ' ') {

                guard = opposite(guard);

                dr = 0;
                dc = 0;

                if (guard == '^') {
                    dr = -1;
                }
                if (guard == 'v') {
                    dr = 1;
                }
                if (guard == '<') {
                    dc = -1;
                }
                if (guard == '>') {
                    dc = 1;
                }

                nr = r + dr;
                nc = c + dc;
            }

            temp[r][c] = ' ';

            if (nr == playerRow && nc == playerCol) {
                gameOver = true;
            }

            temp[nr][nc] = guard;
        }
    }

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = temp[i][j];
        }
    }
}

void check_vision() {

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {

            if (!isGuard(board[r][c])) {
                continue;
            }

            char guard = board[r][c];

            int dr = 0;
            int dc = 0;

            if (guard == '^') {
                dr = -1;
            }
            if (guard == 'v') {
                dr = 1;
            }
            if (guard == '<') {
                dc = -1;
            }
            if (guard == '>') {
                dc = 1;
            }

            int row = r + dr;
            int col = c + dc;

            while (row >= 0 && row < 7 &&
                col >= 0 && col < 7) {

                if (row == playerRow &&
                    col == playerCol) {

                    gameOver = true;
                    return;
                }

                if (board[row][col] != ' ') {
                    break;
                }

                row += dr;
                col += dc;
            }
        }
    }
}

void check_turns() {

    cout << "Moves Remaining: " << turns << endl;

    if (turns <= 0) {
        cout << endl << "Out of moves!" << endl;
        gameOver = true;
    }
}


int main() {

    bool playAgain = true;

    while (playAgain) {

        gameOver = false;
        winGame = false;

        cout << "Welcome to Generic Spy Game!" << endl;
        cout << "Choose a map:" << endl;
        cout << "1) Beginner" << endl;
        cout << "2) Intermediate" << endl;
        cout << "3) Advanced" << endl << endl;

        string response;
        getline(cin, response);

        for (char& c : response)
            c = tolower(c);

        if (response == "1" || response == "beginner") {
            map = 1;
            turns = 15;
        }

        if (response == "2" || response == "intermediate") {
            map = 2;
            turns = 12;
        }

        if (response == "3" || response == "advanced") {
            map = 3;
            turns = 18;
        }

        make_board();

        while (!gameOver && !winGame) {

            print_board();

            check_turns();

            check_vision();

            if (gameOver) {
                break;
            }

            cout << endl << "Move (WASD): ";

            string move;
            cin >> move;

            move[0] = tolower(move[0]);

            move_player(move[0]);

            turns--;

            if (winGame || gameOver) {
                break;
            }

            move_guards();

            check_vision();
        }

        print_board();

        if (winGame) {
            cout << endl << "MISSION SUCCESS!" << endl;
        }
        else {
            cout << endl << "MISSION FAILED!" << endl;
        }

        string again;

        cout << endl << "Play another level? (y/n): ";
        cin >> again;

        for (char& c : again) {
            c = tolower(c);
        }

        if (again != "y" && again != "yes") {
            playAgain = false;
        }
    }
}