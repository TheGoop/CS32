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
    if (m_cars.contains(license))
    {
        return false;
    }
    m_cars.insert(license, 0);
    return true;
}

double CarMap::miles(std::string license) const
{
    double miles = -1;
    m_cars.get(license, miles);
    return miles;
}

bool CarMap::drive(std::string license, double distance)
{
    if (distance < 0)
    {
        return false;
    }
    double m = miles(license) + distance;
    return m_cars.update(license, m);;
}

int CarMap::fleetSize() const
{
    return m_cars.size();
}

void CarMap::print() const
{
    for (int i = 0; i < m_cars.size(); i++)
    {
        ValueType v;
        KeyType k;
        m_cars.get( i, k, v);
        std::cout << k << " " << v << std::endl;
    }
}
