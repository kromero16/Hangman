/* 
 * File:   Node.h
 * Author: Kevin Romero
 *
 * Created on December 21, 2016, 5:18 PM
 */

#ifndef NODE_H
#define NODE_H

//System Libraries
#include <cstdlib>
#include <iostream>
using namespace std;

template<class T>
struct Node{
    T data;
    Node *ptr;
};



#endif /* NODE_H */