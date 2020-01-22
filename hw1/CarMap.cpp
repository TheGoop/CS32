//
//  CarMap.cpp
//  map
//
//  Created by Akshay Gupta on 1/20/20.
//  Copyright © 2020 hw1. All rights reserved.
//

#include "CarMap.h"
#include "Map.h"
#include <string>
#include <iostream>

bool CarMap::addCar(std::string license)
{
    //if license found, add the license
    if (!m_cars.contains(license))
    {
        return m_cars.insert(license, 0);
    }
    //if not found
    return false;
}

double CarMap::miles(std::string license) const
{
    double miles = -1;
    m_cars.get(license, miles);
    //if license is not found, get will keep miles as -1, otherwise will set miles = value
    return miles;
}

bool CarMap::drive(std::string license, double distance)
{
    //if distance is negative
    if (distance < 0)
    {
        return false;
    }
    //if there is no car with that license
    if (!m_cars.contains(license))
    {
        return false;
    }
    //calculate how many miles the car now has
    double m = miles(license) + distance;
    //update the value, if update fails returns false,
    //if update succeeds returns true
    return m_cars.update(license, m);;
}

//returns number of cars
int CarMap::fleetSize() const
{
    return m_cars.size();
}


void CarMap::print() const
{
    //iterate through all cars printing to cout every value
    for (int i = 0; i < m_cars.size(); i++)
    {
        ValueType v;
        KeyType k;
        m_cars.get(i, k, v);
        std::cout << k << " " << v << std::endl;
    }
}
