/* 
 * File:   LinkedList.h
 * Author: Kevin Romero
 * Purpose: Singly Linked List
 * Created on December 21, 2016, 5:18 PM
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//System Libraries
#include <cstdlib>
#include <iostream>
using namespace std;

//User Libraries
#include "Node.h"

template<class T>
class LinkedList{
private:
    Node<T> *front;         //Front of Linked List
    
public:
    //Constructor
    LinkedList(){
        front=NULL;
    }
    
    //Sort 
    void sort(){
    if (front != 0){
        Node<T> *current = front;
        Node<T> *prev = 0;
        Node<T> *tempNode = 0;
        int changeFlag = 0;
        int s=getNumNodes();
        
        //Find end
        Node<T> *end=front;
        while(end->ptr!=NULL){
            end=end->ptr;
        }
        
        for (int i = 0; i < s; i++) {
            while (current->ptr != 0){
                tempNode = current->ptr;
                
                if (current->ptr > tempNode->ptr) {
                    changeFlag = 1;
                    current->ptr = tempNode->ptr;
                    tempNode->ptr = current;
                    if (prev != 0)
                        prev->ptr = tempNode;
                    prev = tempNode;
                    if (front == current)
                        front = tempNode;
                    if (current->ptr == 0)
                        end = current;
                }
                else
                {
                    prev = current;
                    current = current->ptr;
                }
            }
            if (changeFlag == 0)
                break;
            else
            {
                prev = 0;
                current = front;
                changeFlag = 0;
            }
        }
    }
}
    
    
    //Reverse a linked list using iteration
    void reverseList(){    
        Node<T> *prev,*current,*next;
        current=front;
        prev=NULL;
        
        if(front==NULL){
            cout<<"The Linked List is Empty\n\n";
            return;
        }
        else{
        while(current!=NULL){
            next=current->ptr;
            current->ptr=prev;
            prev=current;
            current=next;
        } 
        front=prev;
        
        }
    }
    
    //Push Node at Position
    void pushAt(int n, int pos){     
        Node<T> *next=fillNode(n);
        
        if(pos<=0||pos>getNumNodes()+1){
            cout<<"Position out of List Range.\n\n";
            return;
        }
        else if(pos==1){
            front=fillNode(n);
        }
        else{
            Node<T> *temp=front;
            for(int i=0;i<pos-2;i++){
                temp=temp->ptr;
            }
            next->ptr=temp->ptr;
            temp->ptr=next;
            
        }
        
    }
    
    //Remove given node
    void removeNthNode(int n){
        Node<T> *next=front;
        Node<T> *prev=NULL;
        
        if(n<=0||n>getNumNodes()){
            cout<<"The Nth Node is not Within Range.\n\n";
            return;
        } 
        else if(n==1){
            front=next->ptr;
            delete next;
        }
        else{
            for(int i=0;i<n-2;i++){
                next=next->ptr;
            }
            prev=next->ptr;
            next->ptr=prev->ptr;
            delete prev;
        }
    }
    
    //Count number of nodes
    int getNumNodes(){
        int cnt=0;
        Node<T> *tmp=front;
        while(tmp!=NULL){
            cnt++;
            tmp=tmp->ptr;
        }
        return cnt;
    }
    
    //Push to front
    void push_front(T n){
        if(front==NULL)
            front=fillNode(n);
        else{
            Node<T> *temp=fillNode(n);
            temp->ptr=front;
            front=temp;
        }
    }
    
    //Push Data
    void push_back(T n){
        //Create node with data
        Node<T> *next=fillNode(n);
        
        //Traverse list if not empty
        if(front!=NULL){
            //Find end
            Node<T> *end=front;
            while(end->ptr!=NULL){
                end=end->ptr;
            }
            //Add node to end
            end->ptr=next;
        }else{
            //If empty add to front
            front=next;
        }
    }
    
    //Returns filled node
    Node<T> *fillNode(T n){
        Node<T> *next=new Node<T>;
        next->data=n;
        next->ptr=NULL;
        return next;
    }
    
    //Print List
    void printList(){
        Node<T> *tmp=front;
        
        while(tmp!=NULL){
            cout<<tmp->data<<"-> ";
            tmp=tmp->ptr;
        }cout<<"NULL \n";
    }
    
    //Destructor
    ~LinkedList(){
        while(front!=NULL){
            Node<T> *temp=front;
            front=front->ptr;
            delete temp;
        }
        delete front;
    }
    
};



#endif /* LINKEDLIST_H */