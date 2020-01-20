//
//  history.cpp
//  proj1
//
//  Created by Akshay Gupta on 1/12/20.
//  Copyright © 2020 vampire. All rights reserved.
//

#include "History.h"
#include "globals.h"
#include <iostream>

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    //fill grid with empty .
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            m_grid[r][c] = '.';
        }
    }
}

bool History::record(int r, int c)
{
    //if r is out of bounds
    if (r <= 0 || r > MAXROWS)
    {
        return false;
    }
    //if c is out of bounds
    if (c <= 0 || c > MAXCOLS)
    {
        return false;
    }
    
    //if its a ., change to A
    if (m_grid[r-1][c-1] == '.')
    {
        m_grid[r-1][c-1] = 'A';
        return true;
    }
    //if its a z, can't increment anymore
    else if (m_grid[r-1][c-1] == 'Z')
    {
        return true;
    }
    //if its neither a ., or a Z, can be incremented
    //by adding 1 to ascii
    else
    {
        m_grid[r-1][c-1]=(char)(m_grid[r-1][c-1]+1);
    }

    return true;
}

void History::display() const
{
    //clear screen
    clearScreen();
    //output the grid
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            std::cout << m_grid[r][c];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
