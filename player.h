//
//  player.h
//  proj1
//
//  Created by Akshay Gupta on 1/12/20.
//  Copyright © 2020 vampire. All rights reserved.
//

#ifndef player_h
#define player_h

#include <stdio.h>

class Arena;
#include <string>
using namespace std;

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string dropPoisonVial();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};




#endif /* player_hpp */
