//
//  MyMap.hpp
//  CS_32_Proj4_MYMAP
//
//  Created by harry yee on 3/8/17.
//  Copyright © 2017 harry yee. All rights reserved.
//

#ifndef MyMap_hpp
#define MyMap_hpp

#include <stdio.h>
#include "support.h"
// MyMap.h===================================

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

template<typename KeyType, typename ValueType>
class MyMap
{
public:
    MyMap();
    ~MyMap();
    void clear();
    int size() const;
    // The associate method associates one item (key) with another (value). // If no association currently exists with that key, this method inserts // a new association into the tree with that key/value pair. If there is // already an association with that key in the tree, then the item
    // associated with that key is replaced by the second parameter (value). // Thus, the tree contains no duplicate keys.
    void associate(const KeyType& key, const ValueType& value);
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;
    //================================UP
    
    
    
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    
private:
    struct Node
    {
        Node(KeyType a, ValueType b)// constructor
        :key(a), value(b){}
        
        KeyType key;
        ValueType value;
        Node* right = nullptr;
        Node* left = nullptr;
        
        
    };
    void clear(Node* r);
    Node* pinPoint(const KeyType& key);
    Node *root = nullptr;
    int ass_num = 0;
};

//=======================================================.cpp
template<typename KeyType, typename ValueType>
MyMap<KeyType,ValueType>::MyMap()
{
    //Constructor that basically does nothing
}
template<typename KeyType, typename ValueType>
MyMap<KeyType,ValueType>::~MyMap()
{
    //destructor that calls clear();
    clear();
}
template<typename KeyType, typename ValueType>
void MyMap<KeyType,ValueType>::clear()
{
    //uses some recursion post delete
    if(root == nullptr)
        return;
    else clear(root);
    
}
template<typename KeyType, typename ValueType>
void MyMap<KeyType,ValueType>::clear(Node* r)
{
   //helper function for clear;
    if(r == nullptr)
        return;
    else
    {
        clear(r->right);
        clear(r->left);
        delete r;
    }
    
    
}
template<typename KeyType, typename ValueType>
int MyMap<KeyType,ValueType>::size() const
{
    return ass_num;
}
template<typename KeyType, typename ValueType>
void MyMap<KeyType,ValueType>::associate(const KeyType &key, const ValueType &value)
{
    //inserts this into the binary search tree
    if(root == nullptr)//for null pointer
    {
        root = new Node(key,value);
        ass_num++;
        return;
    }
    // loops through until logn times to find key
    Node* r = root;
    while(r != nullptr)
    {
        if(r->key == key)
        {
            r->value = value;
            return;
        }
        if(r->key > key)
        {
           if(r->left == nullptr)
           {
               r->left = new Node(key,value);
               ass_num++;
               return;
           }
            r = r->left;
        }
        else
        {
            if(r->right == nullptr)
            {
                r->right = new Node(key,value);
                ass_num++;
                return;
            }
            r = r->right;
        }
    }
    
}
template<typename KeyType, typename ValueType>
const ValueType* MyMap<KeyType,ValueType>::find(const KeyType &key) const
{
    Node* r = root;
    while(r != nullptr)
    {
        if(r->key == key || key == r->key)
            return &r->value;
        if(r->key > key)
            r = r->left;
        else r = r->right;
    }
    return nullptr;
}
#endif /* MyMap_hpp */
