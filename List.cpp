#include "declaration.hpp"
#include <iostream>
#include <string>
//adjacentcy list

using namespace std;

List::List(){
    listHead_  = nullptr;
    //cout<<"here"<<listHead_->getName()<<endl;
}
List::~List(){
    Node *walk = listHead_;
    //deactive all the information
    while(walk != nullptr){
        Node *child {walk};
        walk = walk->getNext();
        delete child;
        child = nullptr;
    }
}
void List::RemoveElement(int a){
    Node* temp = listHead_;
    Node * vertexRemove;
    while(temp){
        //case where the first element is not the removed element
        if(temp->getName()== a){
            vertexRemove = temp;
            listHead_ = temp->getNext();
            delete vertexRemove;
            return;
        }
        else if(temp->getNext()->getName() == a){
            vertexRemove = temp->getNext();
            temp->setNext(temp->getNext()->getNext());
            delete vertexRemove;
            return;
        }
    }
}

void List::walk(){
    Node *walkNode = listHead_;
    while(walkNode){
        cout<<walkNode->getName()<<" ";
        walkNode = walkNode->getNext();
    }
    cout<<endl;
}

Node * List::getHead(){
    return listHead_;
}

void List::setHead(Node *N){
    listHead_ = N;
}
//insert the element in the front of the linked-list
void List::insert(Node *N){
    Node * temp = listHead_;
    while(temp){
        //update the element
        if(temp->getName()== N->getName()){
            temp->setD(N->getD());
            temp->setS(N->getS());
        }
        return;
    }
    temp = listHead_;
    listHead_ = N;
    N->setNext(temp);
}