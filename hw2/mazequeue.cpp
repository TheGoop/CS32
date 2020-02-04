//
//  mazequeue.cpp
//  hw2
//
//  Created by Akshay Gupta on 2/4/20.
//  Copyright © 2020 hw2. All rights reserved.
//

#include <queue>
#include <iostream>

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


bool validCoords(int r, int c, int rows, int cols)
{
    if (r >= 0 && r < rows && c >= 0 && c < cols)
    {
        return true;
    }
    return false;
}

bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    std::queue<Coord> coordStack;
    Coord source(sr, sc);
    
    coordStack.push(source); //add the source to stack
    maze[sr][sc] = 'X'; //make source coord register as used
    
    while (!coordStack.empty())
    {
        //get the coord to go top
        Coord curr = coordStack.front();
        coordStack.pop();
        std::cout << curr.r() << ", " << curr.c() << std::endl;
        //if we are at the end point, return true
        if (curr.r() == er && curr.c() == ec)
        {
            return true;
        }
        
        //check East path
        if (validCoords(curr.r(), curr.c()+1, nRows, nCols))
        {
            //if we haven't been there
            if (maze[curr.r()][curr.c()+1] == '.')
            {
                Coord n(curr.r(), curr.c()+1);
                coordStack.push(n);
                maze[curr.r()][curr.c()+1] = 'X';
            }
        }
        
        //check South path
        if (validCoords(curr.r()+1, curr.c(), nRows, nCols))
        {
            //if we haven't been there
            if (maze[curr.r()+1][curr.c()] == '.')
            {
                Coord n(curr.r()+1, curr.c());
                coordStack.push(n);
                maze[curr.r()+1][curr.c()] = 'X';
            }
        }
        
        //check West path
        if (validCoords(curr.r(), curr.c()-1, nRows, nCols))
        {
            //if we haven't been there
            if (maze[curr.r()][curr.c()-1] == '.')
            {
                Coord n(curr.r(), curr.c()-1);
                coordStack.push(n);
                maze[curr.r()][curr.c()-1] = 'X';
            }
        }
        
        //check North path
        if (validCoords(curr.r()-1, curr.c(), nRows, nCols))
        {
            //if we haven't been there
            if (maze[curr.r()-1][curr.c()] == '.')
            {
                Coord n(curr.r()-1, curr.c());
                coordStack.push(n);
                maze[curr.r()-1][curr.c()] = 'X';
            }
        }
    }
    //if we can't find any path return false
    return false;
}

int main()
{
    std::string maze[10] = {
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
        std::cerr << "Solvable!" << std::endl;
    else
        std::cerr << "Out of luck!" << std::endl;
}
