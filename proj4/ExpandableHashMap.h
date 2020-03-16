// ExpandableHashMap.h

// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.

#ifndef EXPANDABLEHASHMAP_INCLUDED
#define EXPANDABLEHASHMAP_INCLUDED
#include "provided.h"
#include <iterator>
#include <list>

template<typename KeyType, typename ValueType>
class ExpandableHashMap
{
public:
	ExpandableHashMap(double maximumLoadFactor = 0.5);
	~ExpandableHashMap();
	void reset();
	int size() const;
	void associate(const KeyType& key, const ValueType& value);

	  // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
	}

	  // C++11 syntax for preventing copying and assignment
	ExpandableHashMap(const ExpandableHashMap&) = delete;
	ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

private:
    struct Node
    {
        Node(KeyType k, ValueType v):m_key(k), m_value(v){}
        KeyType m_key;
        ValueType m_value;
    };
    
    void rehash();
    
    std::vector<std::list<Node*>> m_hashMap;
    double m_loadFactorMax;
    int m_items = 0;
};

template<typename KeyType, typename ValueType>
ExpandableHashMap< KeyType, ValueType>::ExpandableHashMap(double maximumLoadFactor)
{
    m_hashMap.resize(8);
    m_loadFactorMax = maximumLoadFactor;
//    for (int i = 0; i < m_hashMap.size(); i++)
//    {
//        m_hashMap[i] = nullptr;
//    }
}

template<typename KeyType, typename ValueType>
ExpandableHashMap< KeyType, ValueType>::~ExpandableHashMap()
{
    //no dynamically allocated objects, so nothing to delete
    reset();
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap< KeyType, ValueType>::reset()
{
    
    for (int bucket = 0; bucket < m_hashMap.size(); bucket++)
    {
        for (auto j = (m_hashMap[bucket]).begin(); j != (m_hashMap[bucket]).end(); j++)
        {
            Node* temp = *j;
            j = m_hashMap[bucket].erase(j);
            if (temp!=nullptr)
            {
                delete temp;
            }
        }
        m_hashMap[bucket].clear();
    }
    
    for (int bucket = 0; bucket < m_hashMap.size(); bucket++)
    {
        m_hashMap[bucket].resize(8);
    }
//    for (int i = 0; i < m_hashMap.size(); i++)
//    {
//        m_hashMap[i] = nullptr;
//    }
    m_items = 0;
    m_loadFactorMax = 0.5;
}

template<typename KeyType, typename ValueType>
int ExpandableHashMap< KeyType,  ValueType>::size() const
{
    return m_items;
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap< KeyType,  ValueType>::rehash()
{
        //create new map of 2x time of previous
        int nSize = m_hashMap.size()*2;
        std::vector<std::list<Node*>> hashExpanded;
        hashExpanded.resize(nSize);
    //    for (int i = 0; i < nSize; i++)
    //    {
    //        hashExpanded[i] = nullptr;
    //    }

        //hashing function
        unsigned int hasher(const KeyType& g);


        int usedItems = 0;
        //iterate through all of the buckets
        for (auto bucket = m_hashMap.begin(); bucket != m_hashMap.end(); bucket++)
        {
            //iterate through list in bucket
            for (auto j = (bucket)->begin(); j != (bucket)->end(); j++)
            {
                //get hash value for node
                unsigned int bucket = hasher((*j)->m_key) % nSize;
                //check that bucket in new map

                //if empty
                if (hashExpanded[bucket].size() == 0)
                {
                    //create new list, and put list in new map
                    std::list<Node*> temp;
                    temp.push_back((*j));
                    //add t and place in new hashmap
                    hashExpanded[bucket] = temp;
                    usedItems++;
                }
                //if not empty
                else
                {
                    //iterate through list, looking for same key
                    typename std::list<Node*>::iterator it;
                    for (it = hashExpanded[bucket].begin(); it != hashExpanded[bucket].end(); it++)
                    {
                        //if same key, then update that keys value to j's value
                        if ( (*it) == (*j))
                        {
                            (*it)->m_value = (*j)->m_value;
                            break;
                        }

                    }
                    //if nothing matched, just add the key value pair
                    hashExpanded[bucket].push_back(*j);
                    usedItems++;
                }

            }
        }

        std::swap(m_hashMap, hashExpanded);
        m_items = usedItems;
    

}
    
template<typename KeyType, typename ValueType>
void ExpandableHashMap< KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    //rehash map if we need to now
    double futureItemCount = m_items+1;
    double hashFactor = (futureItemCount)/m_hashMap.size();
    if(  hashFactor > m_loadFactorMax)
    {
        rehash();
    }
    
    //now we know that map is correctly sized, we can try adding new value
    
    
    //get the bucket value
    unsigned int hasher(const KeyType& g);
    unsigned int bucket = hasher(key) % m_hashMap.size();
    
    //if there is nothing in the bucket
    int bucketSize = m_hashMap[bucket].size();
    if (bucketSize == 0)
    {
        std::list<Node*> temp;
        m_hashMap[bucket] = temp;
        m_hashMap[bucket].push_back(new Node(key, value));
        m_items++;
        return;
    }
    
    //if there is stuff in the bucket, search for a matching key
    for (auto listPos = m_hashMap[bucket].begin(); listPos != m_hashMap[bucket].end(); listPos++)
    {
        //if theres a matching key, update its value
        if ( (*listPos)->m_key == key)
        {
            (*listPos)->m_value = value;
            return;
        }
    }
    
    //if we make it here, nothing matched in the list. Add a new node to the bucket
    m_hashMap[bucket].push_back(new Node(key, value));
    m_items++;
}



template<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap< KeyType,  ValueType>::find(const KeyType& key) const
{
    //gets the hash value for the key
    unsigned int hasher(const KeyType& g);
    unsigned int bucket = hasher(key) % m_hashMap.size();
    
    //iterate through list
    for (auto it = m_hashMap[bucket].begin(); it != m_hashMap[bucket].end(); it++)
    {
        //if key matches a key in the list, return that keys value
        if ( (*it)->m_key == key)
        {
            return &((*it)->m_value);
        }
    }
    return nullptr;
}









////check if a rehash is necessary to add the key value pair, if so rehash
//double futureItemCount = m_items+1;
//double hashFactor = (futureItemCount)/m_hashMap.size();
//std::cout << hashFactor << " : " << m_loadFactorMax << std::endl;
//if(  hashFactor > m_loadFactorMax)
//{
//    rehash();
//}
//
//
//Node *t = new Node(key,value);
//
//unsigned int hasher(const KeyType& g);
//unsigned int bucket = hasher(key) % m_hashMap.size();
//
////if the bucket is empty
//if (m_hashMap[bucket].size() == 0)
//{
//    //create a temp list, and load it with the node
//    std::list<Node*> temp;
//    temp.push_back(t);
//    //add t and place in hashmap
//    m_hashMap[bucket] = temp;
//    m_items++;
//    return;
//}
//else
//{
//
//    //iterate through list
//    for (auto it = m_hashMap[bucket].begin(); it != m_hashMap[bucket].end(); it++)
//    {
//        //if key matches a key in the list, update that keys value
//        if ( (*it)->m_key == t->m_key)
//        {
//            //m_hashMap[bucket].push_back(t);
//            (*it)->m_value = t->m_value;
//            m_items++;
//            return;
//        }
//    }
//    //if nothing matched in list, add to list
//    m_hashMap[bucket].push_back(t);
//    m_items++;
//
//
//}
#endif
