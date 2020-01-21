//
//  testCarMap.cpp
//  map
//
//  Created by Akshay Gupta on 1/20/20.
//  Copyright © 2020 hw1. All rights reserved.
//

#include "CarMap.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    CarMap m;
    m.addCar("ak");
    m.addCar("br");
    m.addCar("hr");
    m.print();
    cout << "---" << endl;
    assert(m.fleetSize() == 3);
    
    assert(m.drive("ak",-5.0) == false);
    m.print();
    cout << "---" << endl;
    
    assert(m.drive("ak",5.2) == true);
    m.print();
    cout << "---" << endl;
    
    assert(m.drive("br",10.4) == true);
    m.print();
    cout << "---" << endl;
    
    assert(m.miles("na") == -1);
    assert(m.miles("br") == 10.4);
    assert(m.miles("hr") == 0);
    assert(m.miles("ak") == 5.2);
    
    m.print();
    cout << "---" << endl;
    
    cout << "Passes All Tests." << endl;
    
}
