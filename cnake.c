#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
  int length;
  int width;
} Board;

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  Position *body;
  int size;
  int capacity;
  int score;
} Cnake;

int **createboard(Board *b) {
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

  Cnake cnake;
  cnake.size = 1;
  cnake.capacity = 1000; // giving the snake 1000 as an arbitrary value for now
  cnake.body = (Position *)malloc(cnake.capacity * sizeof(Position));
  cnake.body[0] = (Position){snake_x, snake_y};
  cnake.score = 0;

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

bool checkvalidmove(int new_x, int new_y, Board *b, int **board) {
  if (new_x < 0 || new_x >= b->width || new_y < 0 || new_y >= b->length) {
    return false;
  }
  if (board[new_y][new_x] == 1) {
    return false;
  }
  return true;
}

void movecnake(Cnake *s, int **board, Board *b) {
  char move;
  printf("Current score: %d. Input your next move (W, A, S, D): \n", s->score);
  scanf(" %c", &move);

  while (move != 'W' && move != 'A' && move != 'S' && move != 'D') {
    printf("Invalid input, please use W, A, S, or D to move!\n");
    scanf(" %c", &move);
  }

  int new_x = s->body[0].x;
  int new_y = s->body[0].y;

  switch (move) {
    case 'W': new_y--; break; // Move up
    case 'S': new_y++; break; // Move down
    case 'A': new_x--; break; // Move left
    case 'D': new_x++; break; // Move right
    case 'w': new_y--; break; // Move up
    case 's': new_y++; break; // Move down
    case 'a': new_x--; break; // Move left
    case 'd': new_x++; break; // Move right
  }

  if (!checkvalidmove(new_x, new_y, b, board)) {
    printf("Game over!\n");
    exit(0);
  }


  bool ate_food = board[new_y][new_x] == 2;
  if (ate_food) {
    s->score++;
    spawnfood(board, b);
  } else {

    Position tail = s->body[s->size - 1];
    board[tail.y][tail.x] = 0;
    s->size--;
  }


  for (int i = s->size; i > 0; i--) {
    s->body[i] = s->body[i - 1];
  }
  s->body[0] = (Position){new_x, new_y};
  s->size++;


  board[new_y][new_x] = 1;
}

int main() {
  srand(time(NULL));

  Board b = {20, 20};
  int **board = createboard(&b);

  Cnake cnake = spawncnake(board, &b);
  spawnfood(board, &b);

  displayboard(board, &b);

  while (true) {
    movecnake(&cnake, board, &b);

    system("clear");
    displayboard(board, &b);
  }


  free(cnake.body);
  for (int i = 0; i < b.length; i++) {
    free(board[i]);
  }
  free(board);

  return 0;
}
