//
//  testMap.cpp
//  proj2
//
//  Created by Akshay Gupta on 1/28/20.
//  Copyright © 2020 proj2. All rights reserved.
//

#include <iostream>
using namespace std;
#include "Map.h"
#include <cassert>



int main() {
    // insert code here...
    Map m;
    assert(m.size()==0);
    assert(m.empty());
    
    
    KeyType key = "this";
    ValueType value = 99.2;
    assert(!m.get(key, value) && value == 99.2);
    assert(!m.erase(key));
    assert(!m.contains(key));
    assert(!m.get(5, key, value));
    assert(!m.update(key, value));
    assert(m.size()==0);
    assert(m.empty());
    //all empty cases pass by this point
    
    m.insert("ab", 5.4);
    assert(!m.empty());
    assert(m.size()==1);
    
    assert(m.contains("ab"));
    
    
    m.insert("ab", 5.4);
    assert(!m.empty());
    assert(m.size()==1);
    
    
    assert(m.get(0, key, value));
    assert(key == "ab" && value == 5.4);
    
    assert(!m.get("not in the list", value));
    assert(value == 5.4);
    
    key = "ba";
    value = 6.4;
    assert(m.insertOrUpdate( key, value));
    
    assert(m.size() == 2);
    
    assert(m.update(key, 7.4));
    assert(m.contains("ba"));
    
    KeyType k;
    ValueType v;
    assert(m.get(key, v) && v == 7.4);
    
    
    
    assert(m.erase("ab"));
    assert(m.size() == 1);
    assert(!m.empty());
    
    assert(m.insert("te", 9.8));
    assert(m.contains("te"));
    assert(m.contains("ba"));
    assert(m.get(0, key, value));
    assert(key == "te" && value == 9.8);
    assert(m.get(1, key, value));
    assert(key == "ba" && value == 7.4);
    assert (m.size() == 2);
    assert(!m.empty());
    assert(m.update("ba", 10.4));
    assert(m.get(1, key, value));
    assert(key == "ba" && value == 10.4);
    
    
    Map n;
    
    Map result;
    
    
    Map f(m);
    
    
    m.insert("fu", 9000);
    n = m;
    n.update("ba", 500);
    assert(!combine(m,n,m));
    
    
    m = n;
    m.insert("bi", 90);
    
    m.insert("ne", 12);
    
    reassign(m, result);
    
    Map g;
    
    reassign(g, result);
    
    assert(result.empty());
    assert(result.size() == 0);
    
    assert(m.size() == 5 && n.size() == 3);
    m.swap(n);
    assert(m.size() == 3 && n.size() == 5);
    
    
    assert(m.size() == 3 && g.size() == 0);
    m.swap(g);
    assert(m.size() == 0 && g.size() == 3);
    
    Map h, i;
    assert(h.size() == 0 && i.size()==0);
    assert(combine(i,i,i));
    assert(i.size() == 0);
    
    assert(combine(h,i, result));
    assert(result.size()==0);
    
    h.insert("bo", 480);
    h.insert("shelly", 990);
    assert(h.size() == 2);
    assert(combine(h,h,h));
    assert(h.size() == 2);
    
    g = h;
    assert(g.size() == 2);
    g.update("bo", 550);
    assert(!combine(g,h,result));
    assert(result.size() == 1);
    
    assert(!combine(g,h,g));
    assert(g.size() == 1);
    
    assert(m.size() == 0);
    g.insertOrUpdate("brock", 550);
    assert(combine(g,g,m));
    assert(m.size() == 2);
    
    

}
