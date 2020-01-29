//
//  map.cpp
//  proj2
//
//  Created by Akshay Gupta on 1/25/20.
//  Copyright © 2020 proj2. All rights reserved.
//

#include <iostream>
#include "Map.h"
 

Map::Map()
{
    //dummy head
    head = new Node;
    head->next = head;
    head->prev = head;
    m_size = 0;
}

Map::~Map()
{
    //if there are no elements, just delete dummy node
    if (m_size == 0)
    {
        delete head;
        return;
    }
    
    //if there are elements, we have to iterate and delete
    Node *curr = head;
    for (int i = 0; i < size(); i++)
    {
        Node *nxt = curr->next;
        delete curr;
        curr = nxt;
    }
    delete curr;
}

Map::Map(const Map &other)
{
    
    //create dummy head variable
    head = new Node;
    head->prev = head;
    head->next = head;
    
    //if other is empty, can just return here
    if (other.empty())
    {
        return;
    }
    
    //iterate through every other element, and insert it into new Map
    for (Node* curr = other.head->next; curr != other.head; curr = curr->next)
    {
        insert(curr->key, curr->value);
    }
}



Map& Map::operator=(const Map &other)
{
    Map temp(other);
    swap(temp);
    return *this;
}


bool Map::empty() const
{
    return (m_size == 0);
}

int Map::size() const
{
    return m_size;
}


bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (!contains(key))
    {
        Node* newValue = new Node;
        newValue->key = key;
        newValue->value = value;
        //if is empty
        if (size() == 0)
        {
            head->next = newValue;
            head->next->prev = head;
            head->next->next = head;
            m_size++;
            return true;
        }
    
    //AT THIS POINT IN CODE, LIST SIZE > 0
    
    //Checks to see if key is in list
    
        //Inserts value between dummy head and first value
        
        //copies original first value
        Node* firstElement = head->next;
        //sets the value behind original value for orig to newValue
        firstElement->prev = newValue;
        //sets value in front of head to newValue
        head->next = newValue;
        //links the chain by setting value in front of newValue to original first value
        newValue->next = firstElement;
        newValue->prev = head;
        m_size++;
        return true;
    }
    return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    //if there is no key in list to update or list is empty
    if (!contains(key))
    {
        return false;
    }
    
    for (Node* curr = head->next; curr != head; curr = curr->next)
    {
        if (curr->key == key)
        {
            curr->value = value;
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

bool Map::erase(const KeyType& key)
{
    //if it doens't have the key, or the size is 0 this will exit
    if (!contains(key))
    {
        return false;
    }
    
    //iterate through list
    for (Node* curr = head->next; curr != head; curr = curr->next)
    {
        //if the current value has the key
        if (curr->key == key)
        {
            //if something in front of current value
            if (curr->next != nullptr)
            {
                //set the value behind current value's next variable to the variable in front of current value
                curr->prev->next = curr->next;
                delete curr;
                m_size--;
                return true;
            }
            //if nothing in front of current value
            else
            {
                //set the value in front of previous to nullptr
                curr->prev->next = nullptr;
                delete curr;
                m_size--;
                return true;
            }
        }
    }
    return false;
}

bool Map::contains(const KeyType& key) const
{
    //if its empty, can't contain key
    if (empty())
    {
        return false;
    }
    
    //iterate through list looking for key
    for (Node* i = head->next; i != head; i=i->next)
    {
        //if key found return true
        if (i->key == key)
        {
            return true;
        }
    }
    return false;
}


bool Map::get(const KeyType& key, ValueType& value) const
{
    //if list is empty or doesn't have key
    if (!contains(key))
    {
        return false;
    }
    
    //iterate through linked list
    for (Node* curr = head->next; curr != head; curr = curr->next)
    {
        //if node has correct key, update value param
        if (curr->key == key)
        {
            value = curr->value;
            return true;
        }
    }
    
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    //if i is not in bounds
    if (i < 0 || i >= size())
    {
        return false;
    }
    //if list is empty
    if (empty())
    {
        return false;
    }
    
    int tempIndex = 0;
    
    //iterate through list
    for (Node* curr = head->next; curr != head; curr = curr->next)
    {
        //if we reach the index we want
        if (tempIndex == i)
        {
            //update key and value params
            key = curr->key;
            value = curr->value;
            return true;
        }
        tempIndex++;
    }
    return false;
}

void Map::swap(Map& other)
{
    //since first element of linked list is dummy node, if there are no actual elements after can just return
    
    int tmp = m_size;
    m_size = other.size();
    other.m_size = tmp;
    
    
    
    //if both point to variables at this point in code, then swap the first values using a temp
    Node* temp = head;
    head = other.head;
    other.head = temp;
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
    //merging the 2 maps into 1 map
    //if the same key value pair is in both, only add 1
    //if the same key is in both but different values don't add
    //    - must return false at end instead of true
    //if key value pair is in one, but not the other add it
    bool r = true;
    Map copy(m1);
    for (int i = 0; i < m2.size(); i++)
    {
        //iterate through m2
        KeyType m2IndexedKey;
        ValueType m2IndexedVal;
        m2.get(i,m2IndexedKey,m2IndexedVal);
        
        //if same key is already there
        if (copy.contains(m2IndexedKey))
        {
            ValueType m1Value;
            copy.get(m2IndexedKey, m1Value);
            //if same key, but diff values get rid of key
            if (m1Value!=m2IndexedVal)
            {
                copy.erase(m2IndexedKey);
                r=false;
            }
        }
        //if it wasn't there, add it to copy
        else
        {
            copy.insert(m2IndexedKey, m2IndexedVal);
        }
    }
    result = copy;
    return r;
}

void reassign(const Map& m, Map& result)
{
    //if theres only 1 or no pairs, no way to reassign
    if (m.size() <= 1)
    {
        result = m;
        return;
    }
    
    result = m;
    
    //if the number of items is odd, then theres at least 3 items swap the first and last, then proceed with regular even implementation
    if (result.size() % 2 == 1)
    {
        KeyType tempKey1;
        ValueType tempVal1;
        result.get(1, tempKey1, tempVal1);
        
        //we have to use size() + 1, because size() counts from 0, but get counts' index starts at 1
        KeyType tempKey3;
        ValueType tempVal3;
        result.get(result.size()-1, tempKey3, tempVal3);
        
        result.update(tempKey3, tempVal1);
        result.update(tempKey1, tempVal3);
    }
    
    //swap 1st and 2nd, 3rd and 4th, and so on
    for (int i = 0; i+1 < result.size(); i=i+2)
    {
        KeyType tmpKey1, tmpKey2;
        ValueType tmpVal1, tmpVal2;
        result.get(i,tmpKey1, tmpVal1);
        result.get(i+1, tmpKey2, tmpVal2);
        
        result.update(tmpKey1, tmpVal2);
        result.update(tmpKey2, tmpVal1);
    }
}

void Map::dump() const
{
    std::cerr << std::endl;
    std::cerr << "------" << std::endl;
    if (empty())
    {
        std::cerr << "empty" << std::endl;
        std::cerr << "------" << std::endl;
        return;
    }
    for (Node* curr = head->next; curr != head; curr = curr->next)
    {
        std::cerr << curr->key << "   " << curr->value << std::endl;
    }
    
    std::cerr << "------" << std::endl;
}
