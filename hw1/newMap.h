//
//  newMap.h
//  map
//
//  Created by Akshay Gupta on 1/20/20.
//  Copyright © 2020 hw1. All rights reserved.
//

#ifndef newMap_h
#define newMap_h

#include <stdio.h>
#include <string>

using KeyType = std::string;
using ValueType = double;
const int DEFAULT_MAX_ITEMS = 240;

class Map
{
  public:
    Map();   // Create an empty map (i.e., one with no key/value pairs)

    Map(int length);
    
    Map(const Map &other);
    
    Map& operator = (const Map &other);
    
    //DONE
    bool empty() const;  // Return true if *the map is empty, otherwise false.

    //DONE
    int size() const;    // Return the number of key/value pairs in the map.

    //DONE
    bool insert(const KeyType& key, const ValueType& value);
      // If key is not equal to any key currently in the map, and if the
      // key/value pair can be added to the map, then do so and return true.
    // Otherwise, m*ake no change to the map and return false (indicating
      // that either the key is already in the map, or the map has a fixed
      // capacity and is full).

    //DONE
    bool update(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // Otherwise, make no change to the map and return false.

    //DONE
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value that it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // If key is not equal to any key currently in the map and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that the key is not already in the map and the map has a fixed
      // capacity and is full).

    //DONE
    bool erase(const KeyType& key);
      // If key is equal to a key currently in the map, remove the key/value
      // pair with that key from the map and return true.  Otherwise, make
      // no change to the map and return false.
     
    //DONE
    bool contains(const KeyType& key) const;
      // Return true if key is equal to a key currently in the map, otherwise
      // false.
     
    //DONE
    bool get(const KeyType& key, ValueType& value) const;
      // If key is equal to a key currently in the map, set value to the
      // value in the map which that key maps to, and return true.  Otherwise,
      // make no change to the value parameter of this function and return
      // false.
     
    //DONE
    bool get(int i, KeyType& key, ValueType& value) const;
      // If 0 <= i < size(), copy into the key and value parameters the
      // key and value of one of the key/value pairs in the map and return
      // true.  Otherwise, leave the key and value parameters unchanged and
      // return false.  (See below for details about this function.)
    //DONE
    void swap(Map& other);
      // Exchange the contents of this map with the other one.
    
    void dump() const;
    
    void printAll();
    
    ~Map();
    
    private:
        struct Dict
        {
            KeyType key;
            ValueType val;
        };
        int m_size;
        int m_maxSize;
        Dict* m_array;
};


#endif /* newMap_hpp */
