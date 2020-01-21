//
//  testnewMap.cpp
//  newMap
//
//  Created by Akshay Gupta on 1/20/20.
//  Copyright © 2020 hw1. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "newMap.h"
using namespace std;

int main()
{
    Map m;
    
    assert(m.empty() == true);
    assert(m.size() == 0);
    
    ValueType v = 5;
    m.insert("ak", v);
    
    v = 900;
    
    assert ( m.get("hr", v) == false && v == 900);
    
    assert(m.size() == 1);
    
    m.insert("xyz", 9876.5);
    assert (m.size() == 2);
    
    KeyType k = "hr";
    m.dump();
    assert(m.get(0, k, v) && k == "ak" && v == 5);
    
    Map g(m);
    g.dump();
    assert (g.empty() != true);
    assert (g.size() == 2);
    
    Map n = g;
    n.dump();
    assert (n.empty() != true);
    assert (n.size() == 2);
    
    
    assert(n.contains("ak"));
    
    
    n.insertOrUpdate("small", 613);
    assert(n.get(2, k, v) && k == "small" && v == 613);
    
    
    n.insertOrUpdate("small", 813);
    assert(n.get(2, k, v) && k == "small" && v == 813);
    
    assert(n.contains("small"));
    
    
    cout << "Passed all tests" << endl;
    Map endProgem(-1);



}
