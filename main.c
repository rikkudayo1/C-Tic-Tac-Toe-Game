#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void CheckWin(const char board[3][3], bool *winningCheck, char *currentWinner) {
    const char players[2] = {'X', 'O'};

    for (int p = 0; p < 2; p++) {
        char c = players[p];
        // แนวนอน
        for (int r = 0; r < 3; r++) {
            if (board[r][0] == c && board[r][1] == c && board[r][2] == c) {
                *winningCheck = true;
                *currentWinner = c;
                return;
            }
        }
        // แนวตั้ง
        for (int col = 0; col < 3; col++) {
            if (board[0][col] == c && board[1][col] == c && board[2][col] == c) {
                *winningCheck = true;
                *currentWinner = c;
                return;
            }
        }
        // เฉียง
        if ((board[0][0] == c && board[1][1] == c && board[2][2] == c) ||
            (board[0][2] == c && board[1][1] == c && board[2][0] == c)) {
            *winningCheck = true;
            *currentWinner = c;
            return;
        }

        if ((board[0][0] != '.' && board[0][1] != '.' && board[0][2] != '.') &&
            (board[1][0] != '.' && board[1][1] != '.' && board[1][2] != '.') &&
            (board[2][0] != '.' && board[2][1] != '.' && board[2][2] != '.')) {
            *winningCheck = true;
            *currentWinner = 'T';
            return;
        }
    }
}

void ShowCurrentBoard(const char *currentPlayer, const char currentBoard[3][3]) {
        printf("\n\n<===================================================>");
        printf("\n\n< %c's turn >", *currentPlayer);
        printf("\n\n ");
        printf("   0   1   2\n");
        printf("A : %c | %c | %c \n", currentBoard[0][0], currentBoard[0][1], currentBoard[0][2]);
        printf("    __________ \n");
        printf("B : %c | %c | %c \n", currentBoard[1][0], currentBoard[1][1], currentBoard[1][2]);
        printf("    __________ \n");
        printf("C : %c | %c | %c \n", currentBoard[2][0], currentBoard[2][1], currentBoard[2][2]);
        printf("\n\n ");
}

bool CheckMoveString(char answer[999]) {
    if (strlen(answer) != 2) return false;

    if (answer[0] != 'A' && answer[0] != 'B' && answer[0] != 'C') {
        return false;
    }
    if (answer[1] != '0' && answer[1] != '1' && answer[1] != '2') {
        return false;
    }

    return true;
}

void ChangePlayer(char *p) {
    if (*p == 'X') {
        *p = 'O';
    } else {
        *p = 'X';
    }
}

void CheckBox(char board[3][3], const char answer[], bool *dupeCheck, char currentPlayer) {
    int row = answer[0] - 'A';
    int col = answer[1] - '0';

    *dupeCheck = false;

    if (board[row][col] != '.') {
        *dupeCheck = true;
        return;
    }

    board[row][col] = currentPlayer;
}

int main() {
    char start[999];

    printf("\n\n");
    printf("<============ Welcome to XO So Good kub! =============>");
    printf("\n ");
    printf("\n<====================== Rules ======================>");
    printf("\n ");
    printf("\n   1) Same rules as XO");
    printf("\n   2) Dont play alone you'll be lonely");
    printf("\n ");
    printf("\n<============== How to play this game ===============>");
    printf("\n ");
    printf("\n   - The board is 9x9 size, there is a marker for each rows and column (A,B,C 0,1,2) when you answer you just type A0 A1 B2 C2");
    printf("\n ");
    printf("\n<===================================================>");
    printf("\n\n ");
    printf("Enter anything to start the game: ");

    scanf("%s", &start);

    while (true) {
        int rematch = 0;
        char currentBoard[3][3] = {
            { '.', '.', '.' },
            { '.', '.', '.' },
            { '.', '.', '.' },
        };

        char currentPlayer = 'X';
        char currentWinner = '\0';
        char currentAnswer[999];

        bool isWon = false;
        bool answerCheckStatus = false;
        bool DuplicateCheck = false;

        while (!isWon) {
            ShowCurrentBoard(&currentPlayer, currentBoard);

            do {
                printf("player %c, make a move : ", currentPlayer);
                scanf("%s", currentAnswer);

                answerCheckStatus = CheckMoveString(currentAnswer);
                if (!answerCheckStatus) {
                    printf("\nWrong move! only A0-A2, B0-B2 and C0-C2 is allowed!\n");
                    continue;
                }

                CheckBox(currentBoard, currentAnswer, &DuplicateCheck, currentPlayer);
                if (DuplicateCheck) {
                    printf("\nSomeone already took that box!\n");
                }

            } while (!answerCheckStatus || DuplicateCheck);

            CheckWin(currentBoard, &isWon, &currentWinner);
            if (isWon) break;

            ChangePlayer(&currentPlayer);
        }

        ShowCurrentBoard(&currentPlayer, currentBoard);

        if (currentWinner == 'T') {
            printf("\nTie! Good game!");
            printf("\n\n<===================================================>");
        } else {
            printf("\n%c wins! good game!", currentWinner);
            printf("\n\n<===================================================>");
        }
        printf("\n\n Enter '1' to rematch, '0' to quit game : ");
        scanf("%i", &rematch);

        if (rematch == 0) {
            break;
        }
    }

    return 0;
}
