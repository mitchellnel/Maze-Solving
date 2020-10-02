# Maze-Solving
This project involved creating two variations of maze solving algorithms, one using a Stack and one using a Queue.

## Stack-based pathExists()
The function pathExists() uses a stack to determine whether or not there's a path from the start to the finish point of a maze.

The prototype of the function is:
``` bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec); ```
The parameters are:
*	maze: a rectangular maze of Xs and dots that represent the maze. Each string of the array is a row of the maze. Each ‘X’ represents a wall, and each ‘.’ represents a walkway.
*	nRows: the number of rows in the maze.
*	nCols: the number of columns in the maze.
*	sr & sc: the starting coordinates in the maze; the row number is in the range 0 through nRows-1, and the column number is in the range 0 through nCols-1.
*	er & ec: the ending coordinates in the maze; the row number is in the range 0 through nRows-1, and the column number is in the range 0 through nCols-1.

The function uses a stack data structure, particularly, a stack of __Coords__, whose definition is:
```
class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};
```

The pseudocode for the function is:
```
Push the starting coordinate (sr,sc) onto the coordinate stack and
  update maze[sr][sc] to indicate that the algorithm has encountered
  it (i.e., set maze[sr][sc] to have a value other than '.').
While the stack is not empty,
{
  Pop the top coordinate off the stack. This gives you the current
  (r,c) location that your algorithm is exploring.
  
  If the current (r,c) coordinate is equal to the ending coordinate,
  then we've solved the maze so return true! 
  
  Else check each place you can move from the current cell as follows:
    If you can move EAST and haven't encountered that cell yet,
      then push the coordinate (r,c+1) onto the stack
      update maze[r][c+1] to indicate the algorithm has encountered it.
      
    If you can move SOUTH and haven't encountered that cell yet,
      then push the coordinate (r+1,c) onto the stack
      update maze[r+1][c] to indicate the algorithm has encountered it.
                
    If you can move WEST and haven't encountered that cell yet,
      then push the coordinate (r,c-1) onto the stack 
      update maze[r][c-1] to indicate the algorithm has encountered it.
                
    If you can move NORTH and haven't encountered that cell yet,
      then push the coordinate (r-1,c) onto the stack
      update maze[r-1][c] to indicate the algorithm has encountered it.
}
There was no solution, so return false
```

The function makes the following simplifying assumptions:
*	the maze array contains nRows rows (you couldn’t check for this anyway)
*	each string in the maze is of length nCols
*	the maze contains only Xs and dots when passed into the function
*	the top and bottom rows of the maze contain only Xs, as do the left and right columns
*	sr and er are between 0 and nRows*1. And sc and ec are between 0 and nCols*1
*	maze[sr][sc] and maze[er][ec] are ‘.’s, i.e. not walls

## Queue-based pathExists
This version of pathExists() uses a Queue to determine whether or not there's a part from the start to the end of the maze.

The prototype for the function is identical.

The implementation of this version of the function uses a queue, particulary, a queue of __Coords__ (with the same definition as above).

The pseudocode for the function is identical, apart from the terminology where:
* Pushing a Coord onto the stack == enqueuing a Coord
* Popping a Coord off the top of the stack == dequeuing a Coord

## Difference?
The main difference between the two algorithms is the way in which they explore the possible paths presented to them. The stack algorithm fully explores one pathway before it moves onto another, whereas the queue algorithm visits each of the possible pathways it sees in a circuit-like fashion.

The reason for this variance in algorithm is down to the nature of the data structure. Because a stack is a first-in-last-out algorithm: pushing a Coord onto it will lead to the algorithm exploring that same Coord moments later, and this is especially apparent when the algorithm is moving through a pathway in which you can only go one direction; i.e. it snakes all the way through the path first, before going back to another option. Because of this behaviour, it is a depth-first search, choosing to fully explore a solution to see if it will work, before moving on to an alternative.

On the other hand, a queue is a first-in-first-out algorithm: enqueueing a Coord into it will lead to the algorithm exploring that same Coord after it has also explored sections of the other possible options around it (i.e. the already queued coordinates, because that enqueued Coord will be at the back of the queue). This is most apparent in the way that the Coords it is analysing ‘jump around’ the maze between each of the possible pathways there are. Because of this behaviour, it is a breadth-first search, choosing to focus on exploring all possible options, albeit at a more surface level, at the same time.
