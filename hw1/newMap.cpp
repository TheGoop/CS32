//
//  newMap.cpp
//  map
//
//  Created by Akshay Gupta on 1/20/20.
//  Copyright © 2020 hw1. All rights reserved.
//

#include "newMap.h"
#include <string>
#include <iostream>
using namespace std;


Map::Map()
{
    m_size = 0;
    m_maxSize = DEFAULT_MAX_ITEMS;
    m_array = new Dict[m_maxSize];
}

Map::Map(int length)
{
    if (length < 0)
    {
        exit(0);
    }
    m_size = 0;
    m_maxSize = length;
    m_array = new Dict[m_maxSize];
}

Map::Map(const Map &other)
{
    this->m_size = other.m_size;
    this->m_maxSize = other.m_maxSize;
    for (int i = 0; i < m_size; i++)
    {
        this->m_array[i] = other.m_array[i];
    }
}

/**Map& Map::operator=(const Map &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->m_size = other.m_size;
    this->m_maxSize = other.m_maxSize;
    this->~Map();
    m_array = new Dict[m_maxSize];
    for (int i = 0; i < m_maxSize; i++)
    {
        this->m_array[i] = other.m_array[i];
    }
    return *this;
    
}*/



bool Map::empty() const
{
    //returns if map is empty
    return (m_size == 0);
}


int Map::size() const
{
    //returns number of contents in map
    return m_size;
}

bool Map::contains(const KeyType& key) const
{
    //iterates through map looking for key
    for (int i = 0; i < m_size; i++)
    {
        if (m_array[i].key == key)
        {
            //if found, returns true
            return true;
        }
    }
    //if not found, returns false
    return false;
}

bool Map::insert(const KeyType& key, const ValueType& val)
{
    //if there are already too many items
    if (m_size >= DEFAULT_MAX_ITEMS)
    {
        return false;
    }
    //if it already has the key
    if (contains(key))
    {
        return false;
    }
    
    //if conditions are valid, append key and val
    m_array[m_size].key = key;
    m_array[m_size].val = val;
    m_size++; //increment size counter
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    //if i is a valid index
    if (i >= 0 && i < size())
    {
        //update key and value to what user wants
        key = m_array[i].key;
        value = m_array[i].val;
        return true;
    }
    
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    //iterates through looking for key
    for (int i = 0; i < m_size; i++)
    {
        if (m_array[i].key == key)
        {
            //if matching key found, update value and quit
            value = m_array[i].val;
            return true;
        }
    }
    //if no matching key found, quit function
    return false;
}

bool Map::erase(const KeyType& key)
{
    //iterate through map looking for matching key
    for (int i = 0; i < m_size; i++)
    {
        //if matching key
        if (key == m_array[i].key)
        {
            //move all values in front of matching key back one,
            //thereby overwriting/deleting the key to erase
            for (int j = i; j < m_size-1; j++)
            {
                m_array[j] = m_array[j+1];
            }
            //update the size counter
            m_size--;
            return true;
        }
    }
    return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    //iterate through map looking for key
    for (int i = 0; i < m_size; i++)
    {
        //if key found, change its value to desired and quit
        if (key == m_array[i].key)
        {
            m_array[i].val = value;
            return true;
        }
    }
    
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    //if we can update, update key's value
    if (update(key, value))
    {
        return true;
    }
    //if can't update, then try inserting
    return insert(key, value);
}

void Map::swap(Map& other)
{
    int max = this->m_size > other.m_size  ?  this->m_size : other.m_size;
    for (int i = 0; i < max; i++)
    {
        Dict tmp = this->m_array[i];
        this->m_array[i] = other.m_array[i];
        other.m_array[i] = tmp;
    }
    
    int tmpSize = this->m_size;
    this->m_size = other.m_size;
    other.m_size = tmpSize;
}

Map::~Map()
{
    delete [] m_array;
}

int main()
{
    Map m;
    std::cout << "done";
}
