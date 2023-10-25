//
//  LinkedList.cpp
//  VerletModel
//
//  Created by Afroz Alam on 25/10/23.
//

#include <iostream>
using namespace std;
template<typename T>
class LinkedList{
    int length = 0;
    struct Node{
        T data;
        Node* next = nullptr;
    };
    Node* start = nullptr;
public:
    LinkedList(){
    }
    void pushFront(T data){
        Node* n = new Node{data, start};
        start = n;
        length++;
    }
    void insertAfter(Node* node, T data){
        Node* n = new Node{data, node->next};
        node->next = n;
        length++;
    }
    void pushBack(T data){
        Node* n = new Node{data};
        
        if (start == nullptr){
            // The start is null
            start = n;
            return;
        }
        Node* current = start;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = n;
        length++;
    }
    void popFront(){
        if (start){
            Node* current = start;
            start = start->next;
            delete current;
        }
        length--;
    }
    void popBack(){
        if (start){
            Node* pre = nullptr;
            Node* current = start;
            while(current->next){
                pre = current;
                current = current->next;
            }
            if(pre){
                pre->next = nullptr;
            }
            if (current == start) start = nullptr;
            delete current;
        }
        length--;
    }
    // The given node must exist in the linkedlist
    void popNode(Node* node){
        if (!node || !start) return; // Nothing to remove
        if (start == node) {
            // Remove the start node
            start = start->next;
            delete node;
            return;
        }
        Node* current = start;
        while(current && current->next != node){
            current = current->next;
        }
        if (current){
            current->next = node->next;
            delete node;
        }
        length--;
    }
    void display(){
        if (start == nullptr){
            // The start is null
            cout << "UnderFlow" << endl;
            return;
        }
        Node* current = start;
        int i = 0;
        while(current != nullptr){
            cout << "Element[" << i << "] = " << current->data << endl;
            current = current->next;
            i++;
        }
    }
    void foreach(function<bool(T&, int)> func){
        Node* current = start;
        int i = 0;
        while(current){
            bool result = func(current->data,i++);
            if (result) break;
            current = current->next;
        }
    }
    int getSize(){
        return length;
    }
};
