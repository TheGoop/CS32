//
//  Map.h
//  proj2
//
//  Created by Akshay Gupta on 1/25/20.
//  Copyright © 2020 proj2. All rights reserved.
//


#ifndef Map_h
#define Map_h

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
    public:
        Map(); //DONE
        bool empty() const; //DONE
        int size() const; //DONE
        bool insert(const KeyType& key, const ValueType& value); //DONE
        bool update(const KeyType& key, const ValueType& value); //DONE
        bool insertOrUpdate(const KeyType& key, const ValueType& value); //DONE
        bool erase(const KeyType& key); //DONE
        bool contains(const KeyType& key) const; //DONE
        bool get(const KeyType& key, ValueType& value) const; //DONE
        bool get(int i, KeyType& key, ValueType& value) const; //DONE
        void swap(Map& other); //DONE
        //reassign - DONE
        //combine - DONE
        
        ~Map(); //DONE
        //Destructor
        //When a Map is destroyed, the nodes in the linked list must be deallocated.
        
        Map(const Map &other); //DONE
        //When a brand new Map is created as a copy of an existing Map, enough new nodes must be allocated to hold a duplicate of the original list.
        
        Map& operator = (const Map &other);
        //Assignment operator
        //When an existing Map (the left-hand side) is assigned the value of another Map (the right-hand side), the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).
    
    void dump() const;
    
    private:
        struct Node
        {
            KeyType key;
            ValueType value;
            Node* next;
            Node* prev;
        };
        
        Node* head;
        int m_size = 0;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);


#endif /* map_h */
