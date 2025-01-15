#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void print_board(int board[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }
}


bool unUsedInRow(int board[9][9], int row, int num) {
  for (int i = 0; i < 9; i++) {
    if (board[row][i] == num) {
      return false;
    }
  }
  return true;
}


bool unUsedInCol(int board[9][9], int col, int num) {
  for (int i = 0; i < 9; i++) {
    if (board[i][col] == num) {
      return false;
    }
  }
  return true;
}


bool unUsedInBox(int board[9][9], int rowStart, int colStart, int num) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[rowStart + i][colStart + j] == num) {
        return false;
      }
    }
  }
  return true;
}


bool checkIfSafe(int board[9][9], int row, int col, int num) {
  return unUsedInRow(board, row, num) &&
  unUsedInCol(board, col, num) &&
  unUsedInBox(board, row - row % 3, col - col % 3, num);
}


bool findEmptyLocation(int board[9][9], int l[2]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == 0) {
        l[0] = i;
        l[1] = j;
        return true;
      }
    }
  }
  return false;
}


bool solveSudoku(int board[9][9]) {
  int l[2];

  if (!findEmptyLocation(board, l)) {
    return true;
  }

  int row = l[0];
  int col = l[1];


  for (int num = 1; num <= 9; num++) {
    if (checkIfSafe(board, row, col, num)) {
      board[row][col] = num;  // Make the move


      if (solveSudoku(board)) {
        return true;
      }


      board[row][col] = 0;
    }
  }
  return false; // Trigger backtracking
}

// Logic to generate random boards


void FillBox(int board[9][9], int row, int col) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int num;
      do {
        num = rand() % 9 + 1;
      } while (!unUsedInBox(board, row, col, num));
      board[row + i][col + j] = num;
    }
  }
}


void fillDiagonal(int board[9][9]) {
  for (int i = 0; i < 9; i += 3) {
    FillBox(board, i, i);
  }
}


void removeKDigits(int board[9][9], int k) {
  while (k > 0) {
    int cellId = rand() % 81;
    int i = cellId / 9;
    int j = cellId % 9;

    if (board[i][j] != 0) {
      board[i][j] = 0;
      k--;
    }
  }
}

int main() {
  srand(time(NULL));
  char yes;
  int k;
  printf("Input the amount of hints (Up to 17 hints):\n");
  scanf("%d", &k);

  while (k < 0 || k > 17) {
    printf("Invalid number, input a value between 0 and 17\n");
    scanf("%d", &k);
  }

  int board[9][9] = {0};

  fillDiagonal(board);
  solveSudoku(board);
  removeKDigits(board, 81 - k);

  print_board(board);   // Print the solved board
  printf("do you want the solution? Y - N\n");
  scanf("%c",&yes);

  while (yes != 'Y' && yes != 'N') {
    printf("Invalid response, use Y or N please: ");
    scanf("%c", &yes);
  }

  if (yes == 'Y') {
    solveSudoku(board);
    print_board(board);
  } else {
    exit(0);
  }



  return 0;
}
