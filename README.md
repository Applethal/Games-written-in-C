# About the repo:

This is a small repo where I keep games that I wrote in C. All of these require a terminal emulator. No graphical library was used in the making.

## cnake


The game is turn based because I still have to figure out how to make it run at real time. The snake is represented by `1` while its food is represented by `2`. ~~I made it so that the game runs only on grids that are bigger than 2 x 2.~~ The game's board is set to 20 x 20 to avoid having users give a large custom number or inputting a `char` for the dimensions.  
~~Moving the snake extends its length even when not picking up the food, I have to find a way around fixing this piece of logic. For now I just marked every valid path with 1.~~ 

## Sudoku

The file will generate random Sudoku instances for the human to solve, the solution of which may be displayed, should the human choose to display it after generating the instance. Sadly generating and solving the sudoku use bruteforce methods, this is where I learned that almost every sudoku algorithm uses bruteforce checks. Heck I even found a paper on solving it using simulated annealing, which was interesting to read. I could not come up with the algorithms myself as I had to use some inspiration from the net.
