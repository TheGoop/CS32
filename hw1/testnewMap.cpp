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
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int main()
{
     Map m;
     m.insert("A", 10);
     m.insert("B", 44);
     m.insert("C", 10);
     string all;
     double total = 0;
     for (int n = 0; n < m.size(); n++)
     {
         string k;
         double v;
         m.get(n, k, v);
         all += k;
         total += v;
     }
     
     Map gpas;
     gpas.insert("Fred", 2.956);
     gpas.insert("Ethel", 3.538);
     double v;
     string k1;
     assert(gpas.get(1,k1,v)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
     string k2;
     assert(gpas.get(1,k2,v)  &&  k2 == k1);
     
     Map gpa;
     gpa.insert("Fred", 2.956);
     assert(!gpa.contains(""));
     gpa.insert("Ethel", 3.538);
     gpa.insert("", 4.000);
     gpa.insert("Lucy", 2.956);
     assert(gpa.contains(""));
     gpa.erase("Fred");
     assert(gpa.size() == 3  &&  gpa.contains("Lucy")  &&  gpa.contains("Ethel")  &&
                 gpa.contains(""));
     
     Map m1;
     m1.insert("Fred", 2.956);
     Map m2;
     m2.insert("Ethel", 3.538);
     m2.insert("Lucy", 2.956);
     m1.swap(m2);
     
     m2.dump();
     m1.dump();
     
     assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  && m2.size() == 1  &&  m2.contains("Fred"));
     
     Map m9;  // maps strings to doubles
     assert(m9.empty());
     ValueType v9 = -1234.5;
     assert( !m.get("abc", v9)  &&  v9 == -1234.5); // v unchanged by get failure
     m9.insert("xyz", 9876.5);
     assert(m9.size() == 1);
     KeyType k9 = "hello";
     assert(m9.get(0, k9, v9)  &&  k9 == "xyz"  &&  v9 == 9876.5);
     
     Map t;
     assert(t.empty());
     assert(t.insert("ak", 9));
     assert(t.insert("Vi", 12));
     std::string k = ".";
     double val = 0;
     assert(t.get(0,k,val) && k=="ak" && val == 9);
     assert(t.contains("Vi"));
     assert(!t.contains("vi"));
     t.insert("al", 8);
     assert(!t.erase("vi"));
     assert(t.erase("Vi"));
     assert(t.get(1,k,val) && k=="al" && val == 8);
     assert(t.get(0,k,val) && k=="ak" && val == 9);
     assert(t.size()==2);
     assert(!t.empty());
     assert(!t.update("AK", 500));
     assert(t.update("ak", 500));
     assert(t.get(0,k,val) && k=="ak" && val == 500);
     assert(t.size()==2);
     assert(!t.empty());
     assert(t.insertOrUpdate("ak", 400));
     assert(t.get(0,k,val) && k=="ak" && val == 400);
     assert(t.size()==2);
     assert(!t.empty());
     assert(t.insertOrUpdate("Vi", 12));
     assert(t.size()==3);
     assert(!t.empty());
     
     
    
     assert(m9.get(0,k,val) && k=="xyz" && val == 9876.5);
     
     assert(t.get(0,k,val) && k=="ak" && val == 400);
     assert(t.get(1,k,val) && k=="al" && val == 8);
     assert(t.get(2,k,val) && k=="Vi" && val == 12);
     t.swap(m9);
     
     assert(m9.get(0,k,val) && k=="ak" && val == 400);
     assert(m9.get(1,k,val) && k=="al" && val == 8);
     assert(m9.get(2,k,val) && k=="Vi" && val == 12);
     
     assert(t.get(0,k,val) && k=="xyz" && val == 9876.5);
     
     m9.swap(t);
     
     assert(m9.get(0,k,val) && k=="xyz" && val == 9876.5);
     
     assert(t.get(0,k,val) && k=="ak" && val == 400);
     assert(t.get(1,k,val) && k=="al" && val == 8);
     assert(t.get(2,k,val) && k=="Vi" && val == 12);
     
     
     cout << "Passed all tests" << endl;
    
    Map m12;
    
    assert(m12.empty() == true);
    assert(m12.size() == 0);
    
    ValueType va = 5;
    m12.insert("ak", va);
    
    va = 900;
    
    assert ( m12.get("hr", va) == false && va == 900);
    
    assert(m12.size() == 1);
    
    m12.insert("xyz", 9876.5);
    assert (m12.size() == 2);
    
    KeyType keys = "hr";
    m12.dump();
    assert(m12.get(0, keys, va) && keys == "ak" && va == 5);
    
    Map g(m12);
    g.dump();
    assert (g.empty() != true);
    assert (g.size() == 2);
    
    Map n = g;
    n.dump();
    assert (n.empty() != true);
    assert (n.size() == 2);
    
    
    assert(n.contains("ak"));
    
    
    n.insertOrUpdate("small", 295.9);
    assert(n.get(2, keys, va) && keys == "small" && va == 295.9);
    
    
    n.insertOrUpdate("small", 813.7);
    assert(n.get(2, keys, va) && keys == "small" && va == 813.7);
    
    assert(n.contains("small"));
    
    Map z(n);
    n.dump();
    z.dump();
    
    Map x = z;
    x.dump();
    
    assert(x.size() == n.size() && x.size()== z.size());
    
    n.erase("xyz");
    assert(x.size() != n.size() && x.size()== z.size());
    
    x.erase("xyz");
    assert(x.size() == n.size() && x.size()!= z.size());
    
    
    cout << "Passed all tests" << endl;
    Map endProgem(-1);
}

