#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


void test()
{
    Map m;
    assert(m.insert("Fred", 2.956));
    assert(m.insert("Ethel", 3.538));
    assert(m.size() == 2);
    ValueType v = 42;
    assert(!m.get("Lucy", v)  &&  v == 42);
    assert(m.get("Fred", v)  &&  v == 2.956);
    v = 42;
    KeyType x = "Lucy";
    assert(m.get(0, x, v)  &&
           ((x == "Fred"  &&  v == 2.956)  ||  (x == "Ethel"  &&  v == 3.538)));
    KeyType x2 = "Ricky";
    assert(m.get(1, x2, v)  &&
           ((x2 == "Fred"  &&  v == 2.956)  ||  (x2 == "Ethel"  &&  v == 3.538))  &&
           x != x2);
}
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
    
    test();
    cout << "Passed all tests" << endl;
}
 
