//
//  history.h
//  proj1
//
//  Created by Akshay Gupta on 1/12/20.
//  Copyright © 2020 vampire. All rights reserved.
//

#ifndef history_h
#define history_h

#include "globals.h"
#include <stdio.h>

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
  private:
    int m_rows;
    int m_cols;
    char m_grid[MAXROWS][MAXCOLS];
};

#endif /* history_hpp */
