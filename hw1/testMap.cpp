#include "Map.h"
#include <iostream>
#include <cassert>
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
    cout << all << total;
    
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
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
           m2.size() == 1  &&  m2.contains("Fred"));
    
    Map m9;  // maps strings to doubles
    assert(m9.empty());
    ValueType v9 = -1234.5;
    assert( !m.get("abc", v9)  &&  v9 == -1234.5); // v unchanged by get failure
    m9.insert("xyz", 9876.5);
    assert(m9.size() == 1);
    KeyType k9 = "hello";
    assert(m9.get(0, k9, v9)  &&  k9 == "xyz"  &&  v9 == 9876.5);
    
    cout << "Passed all tests" << endl;
}
 
