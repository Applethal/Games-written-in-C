#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
  int length;
  int width;
} Board;

typedef struct {
  int cnake_x;
  int cnake_y;
  int score;
} Cnake;

int **createboard(Board *b) {
  if (b->length < 2 && b->width < 2) {
    while (b->length < 2 && b->width < 2) {
      printf("Invalid insertion. Enter length and width values that are higher than 2: ");
      scanf("%d", &b->length);
      scanf("%d", &b->width);
    }
  }

  int **board = (int **)malloc(b->length * sizeof(int *));
  for (int i = 0; i < b->length; i++) {
    board[i] = (int *)malloc(b->width * sizeof(int));
  }

  for (int i = 0; i < b->length; i++) {
    for (int j = 0; j < b->width; j++) {
      board[i][j] = 0;
    }
  }

  return board;
}

void displayboard(int **board, Board *b) {
  for (int i = 0; i < b->length; i++) {
    for (int j = 0; j < b->width; j++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }
}

Cnake spawncnake(int **board, Board *b) {
  int snake_y = rand() % b->length;
  int snake_x = rand() % b->width;

  Cnake cnake = {snake_x, snake_y,0};
  board[snake_y][snake_x] = 1;
  return cnake;
}

void spawnfood(int **board, Board *b) {
  int food_y, food_x;

  do {
    food_y = rand() % b->length;
    food_x = rand() % b->width;
  } while (board[food_y][food_x] != 0);

  board[food_y][food_x] = 2;
}

bool checkvalidmove(int new_x, int new_y, Board *b, int **board, Cnake *s) {
  if (new_x < 0 || new_x >= b->width || new_y < 0 || new_y >= b->length) {
    return false;
  }
  if (board[new_y][new_x] == 1) {
    return false;
  }
  if (board[new_y][new_x] == 2){
    spawnfood(board, b);
    s->score ++;
    return true;
  }
  return true;
}


void movecnake(Cnake *s, int **board, Board *b) {
  char move;
  printf("Current score: %d .Input your next move (W, A, S, D): \n", s->score);
  scanf(" %c", &move);

  if (move != 'W' && move != 'A' && move != 'S' && move != 'D') {
    printf("Invalid input, please use W, A, S, or D to move!\n");
    return;
  }

  int new_x = s->cnake_x;
  int new_y = s->cnake_y;

  switch (move) {
    case 'W': new_y--; break; // Move up
    case 'S': new_y++; break; // Move down
    case 'A': new_x--; break; // Move left
    case 'D': new_x++; break; // Move right
  }

  if (checkvalidmove(new_x, new_y, b, board, s)) {

    s->cnake_x = new_x;
    s->cnake_y = new_y;
    board[s->cnake_y][s->cnake_x] = 1; // new position

  } else {
    printf("Game over!\n");
    exit(0);
  }
}



int main() {
  int w, l;
  srand(time(NULL));

  printf("Enter width of the board: \n");
  scanf("%d", &w);
  printf("Enter length of the board: \n");
  scanf("%d", &l);

  Board b = {w, l};
  int **board = createboard(&b);

  Cnake cnake = spawncnake(board, &b);
  spawnfood(board, &b);

  displayboard(board, &b);

  while (true) {
    movecnake(&cnake, board, &b);


    system("clear");
    displayboard(board, &b);
  }

  for (int i = 0; i < b.length; i++) {
    free(board[i]);
  }
  free(board);

  return 0;
}
