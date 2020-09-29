//
//  mazequeue.cpp
//  Homework 2
//
//  Created by Mitchell McLinton on 29/1/20.
//  Copyright © 2020 Mitchell McLinton. All rights reserved.
//

#include <queue>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

/////////////////////////////////////////////
// CONSTANTS
/////////////////////////////////////////////
const char ENCOUNTERED = '@';
const char WALL = 'X';

/////////////////////////////////////////////////////
// pathExists PROTOTYPE
/////////////////////////////////////////////////////
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
  // Return true if there is a path from (sr,sc) to (er,ec)
  // through the maze; return false otherwise

/////////////////////////////////////////////
// Coord Class
/////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////
// pathExists Implementation (with queue)
/////////////////////////////////////////////////////////////////////////////////////////////////
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    queue<Coord> coordQueue;
    
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = ENCOUNTERED;
    
    Coord end(er, ec);
    
    while (!coordQueue.empty()) {
        Coord curr = coordQueue.front();
        coordQueue.pop();
        
        if (curr.r() == end.r() && curr.c() == end.c())
            return true;
        
        if (maze[curr.r()][curr.c()+1] != WALL && maze[curr.r()][curr.c()+1] != ENCOUNTERED) {
            coordQueue.push(Coord(curr.r(), curr.c()+1));
            maze[curr.r()][curr.c()+1] = ENCOUNTERED;
        }
        
        if (maze[curr.r()+1][curr.c()] != WALL && maze[curr.r()+1][curr.c()] != ENCOUNTERED) {
            coordQueue.push(Coord(curr.r()+1, curr.c()));
            maze[curr.r()+1][curr.c()] = ENCOUNTERED;
        }
        
        if (maze[curr.r()][curr.c()-1] != WALL && maze[curr.r()][curr.c()-1] != ENCOUNTERED) {
            coordQueue.push(Coord(curr.r(), curr.c()-1));
            maze[curr.r()][curr.c()-1] = ENCOUNTERED;
        }
        
        if (maze[curr.r()-1][curr.c()] != WALL && maze[curr.r()-1][curr.c()] != ENCOUNTERED) {
            coordQueue.push(Coord(curr.r()-1, curr.c()));
            maze[curr.r()-1][curr.c()] = ENCOUNTERED;
        }
    }
    return false;
}

/////////////////////////////////////////////
// main()
/////////////////////////////////////////////
int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X.XXX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 4,3, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
