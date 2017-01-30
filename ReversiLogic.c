#include <stdio.h>

typedef enum {
    None,
    Black,
    White
} Player;

void resetBoard(Player board[8][8]);
int onBoard(int a);
int play(Player board[8][8], char *move, Player p);
int viableMove(Player board[8][8], Player p, Player o, int a, int b);
void update(Player board[8][8], Player p, Player o, int a, int b);
int checkLine(Player board[8][8], Player p, Player o, int a, int b, int dirX, int dirY);
void turn(Player board[8][8], Player p, int a, int b, int dirX, int dirY);

void resetBoard(Player board[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = None;
        }
    }
    board[3][3] = board[4][4] = White;
    board[4][3] = board[3][4] = Black;
}

void printBoard(Player board[8][8]) {
    for (int i = 0; i < 8; i++) {
        printf("%c", '\n');
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
                case White:
                    printf("%c", 'W');
                    break;
                case Black:
                    printf("%c", 'B');
                    break;
                default:
                    printf("%c", '_');
                    break;
            }
        }
    }
}

int onBoard(int a) {return (a >= 0 && a < 8);}

int play(Player board[8][8], char *move, Player p) {
    int a = move[0] - '1';
    Player o = (p == White) ? Black : White; //opponent
    if (!onBoard(a)) {
        printf("Invalid move\n");
        return 0;
    }
    int b = move[1] - 'a';
    if (!onBoard(b)) {
        printf("Invalid move\n");
        return 0;
    }
    if(viableMove(board, p, o, a, b)) { //Troligen ineffektivt, jag gör nästan samma sak igen i update
        update(board, p, o, a, b);
        return 1;
    } else {
        printf("Invalid move\n");
        return 0;
    }
}

int viableMove(Player board[8][8], Player p, Player o, int a, int b) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (!(i == 0 && j == 0) && checkLine(board, p, o, a, b, i, j)) return 1;
        }
    }
    return 0;
}

void update(Player board[8][8], Player p, Player o, int a, int b) {
    board[a][b] = p;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if(checkLine(board, p, o, a, b, i, j)) {
                turn(board, p, a, b, i, j);
            }
        }
    }
}

int checkLine(Player board[8][8], Player p, Player o, int a, int b, int dirX, int dirY) {
    int x = a + dirX;
    int y = b + dirY;
    if(!(onBoard(x) && onBoard(y))) return 0;
    Player curr = board[x][y];
    if (curr == p) return 0;
    while (curr == o) {
        x += dirX;
        y += dirY;
        if(!(onBoard(x) && onBoard(y))) return 0;
        curr = board[x][y];
    }
    if (curr == p) return 1;
    else return 0;
}

void turn(Player board[8][8], Player p, int a, int b, int dirX, int dirY) {
    int x = a + dirX;
    int y = b + dirY;
    while (board[x][y] != p) {
        board[x][y] = p;
        x += dirX;
        y += dirY;
    }
}

int main(void) {
    Player board[8][8] = {None};
    board[3][3] = board[4][4] = White;
    board[4][3] = board[3][4] = Black;
    Player currentP = Black;
    printBoard(board);

    char input[2];
    while (1) {
        if (scanf("%s", input) != 1)
            break;
        if(play(board, input, currentP)) {
            currentP = (currentP == Black) ? White : Black;
        }
        printBoard(board);
   }

    return 0;
}
