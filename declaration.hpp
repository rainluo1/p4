#ifndef DECLARATION_HPP
#define DECLARATION_HPP
#include <string>
#include <cfloat>
#include <fstream>
#include <exception>
using namespace std;
class ExceptionBad : public std::exception{
    public:
        std::string msg() const { return "illegal argument";}
};

class Node{
public: 
    Node * getNext();
    void setNext(Node * N);
    Node(double S, double d, int num);
    int getName();
    void setA(double A2);
    double getD();
    void setD(double d2);
    double getS();
    void setS(double s2);
    float calcT();
private: 
    double d,S,A;
    int name;
    Node *nextNode_;
    
};
class Pair{
    public: 
    Pair();
    Pair(int in, float distanceIn){
        i = in;
        distance = distanceIn;
    }
    float getDistance(){
        return distance;
    }
    int getName(){
        return i;
    }
    private:
    int i;
    float distance;
    
};

class Heap{
    public: 
    void insert();
    int ExtractMin(); // return the numebr of element
    Heap(bool containVertex[], Node vertex[], int startNode);
    ~Heap();
    int getSize();
    


    private:
    void heapifyUP(int cursize);
    Pair ** arrayOfVertex;
    int size;
    int cursize;
    void heapifyDown(int size, int curElement);
};

class List{
public:
    List();
    ~List();
    Node* getHead();
    void setHead(Node *N);
    void insert(Node *N);
    void walk();
    void RemoveElement(int a);
    
private:
    Node *listHead_;

};

//I'll be implementing an adjacentcy matrix here
class Graph{
private:
    List ** vertex;
    bool *containVertex;// if the node doesn't have a graph
    int sizeOfGraph;
public:
    Graph();
    ~Graph(); // literate through and delete
    void Insert(int a, int b, double d, double s);
    void Print(int a);
    void Delete(int a);
    void Traffic(int a, int b, double A);
    bool isInGraph(int a);
    void Readfile(fstream &fin, bool whichcmd);
};

#endif