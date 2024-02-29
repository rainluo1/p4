#include "declaration.hpp"
#include <iostream>
#include <string>
#include <cfloat>
using namespace std;
Node::Node(double speed, double dis, int num){
    d =dis;
    S = speed;
    name = num;
    nextNode_ = nullptr;
    A =1;
    
}

void Node:: setNext(Node * N){
    nextNode_ = N;
}
void Node:: setA(double A2){
    A = A2;
}
double Node::getA(){
    return A;
}
Node * Node::getNext(){
    return nextNode_;
}

int Node::getName(){
    return name;
}
double Node::getD(){
    return d;
}
void Node::setD(double d2){
    d =d2;
}
double Node::getS(){
    return S;
}
void Node::setS(double s2){
    S =s2;
}
float Node::calcT(){
    // if(A ==0){
    //     cout<<"the distance should be infinity"<<endl;
    // }
    return d/(S*A);
}