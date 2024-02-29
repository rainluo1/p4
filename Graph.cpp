#include "declaration.hpp"
#include <iostream>
#include <string>
#include <cfloat>
#include <fstream>
using namespace std;
Graph::Graph(){
    containVertex = new bool [500001];
    vertex = new List*[500001];
    for(int i =0;i<500001;i++){
        vertex[i] = new List();
        containVertex [i] = false;
    }
    sizeOfGraph =0;
}
Graph::~Graph(){
    for(int i =0;i<500001;i++){
        delete vertex[i];
    }
    delete[] containVertex;
    delete[] vertex;
}
//prints the lowest weight path

void Graph::Lowest(int a, int b){
    //array keeping track of parents of each vertex.
    // the index is the vertex, the content stores the parent
    arrayParent = new int [500001]{0};
    //float distanceFromSource [500001];
    //i have implemented line 1 to 6
    Heap *minHeap = new Heap(sizeOfGraph,a, containVertex);
    while(minHeap->getSize()>0){    
        int u = minHeap->ExtractMin();
       // cout<<" extraMin result: "<< u<<endl;
        Node *walk = vertex[u]->getHead();
        while (walk){
            if(minHeap->relax(u, walk->getName(), walk->calcT())){
                //relax algorithm
                arrayParent[walk->getName()] = u;
               // cout<<"we are heapifying " << walk->getName()<<"  "<< u<<endl;
            }
            //int u, int v, float Wuv, float vT,float uT
            walk = walk ->getNext();
        }
    }
    if(arrayParent [b]!=0){
        cout<<"lowest is "<<minHeap->returnT(b)<<endl;
    }
    else{
        cout<<"failure"<<endl;
    }
    delete minHeap;
    delete []arrayParent;
}
void Graph::Path(int a, int b){
    //array keeping track of parents of each vertex.
    // the index is the vertex, the content stores the parent
    arrayParent = new int [500001]{0};
    //float distanceFromSource [500001];
    //i have implemented line 1 to 6
    Heap *minHeap = new Heap(sizeOfGraph,a, containVertex);
    while(minHeap->getSize()>0){    
        int u = minHeap->ExtractMin();
        //cout<<" extraMin result: "<< u<<endl;
        Node *walk = vertex[u]->getHead();
        while (walk){
            if(minHeap->relax(u, walk->getName(), walk->calcT())){
                //relax algorithm
                arrayParent[walk->getName()] = u;
               // cout<<"WOAH WOAH WOAH            parent of "<<walk->getName()<< " is "<<u<<endl;
               // cout<<"we are heapifying " << walk->getName()<<"  "<< u<<endl;
            }
            //int u, int v, float Wuv, float vT,float uT
            walk = walk ->getNext();
        }
    }
    //printing the stuff
    int printElement = b;
    bool ptSomeThing = false;
    while(arrayParent[printElement]!=0){
        ptSomeThing = true;
        cout<<printElement<<" ";
        printElement = arrayParent[printElement];
    }
    if(ptSomeThing) cout<<a<<endl;
    else cout<<"failure"<<endl;
    delete minHeap;
    delete []arrayParent;
}

//
void Graph::Readfile(fstream &fin, bool update){
    int a,b;
    double A,d,s;
    if(update){
        bool success = false;
        while(fin>>a>>b>>A){
            bool w1 = false;
            bool w2 = false;
            if(containVertex[a]&&containVertex[b]){
                Node* walk = vertex[a]->getHead();
                while(walk){
                    if (walk->getName()==b){
                            if(walk ->getA() != A){
                                walk->setA(A);
                                success = true;
                                w1 = true;
                                break;
                            }
                    }
                    walk = walk->getNext();
                }
                walk = vertex[b]->getHead();
                while(walk){
                    if (walk->getName()==a){
                        if(walk ->getA() != A){
                            walk->setA(A);
                            w2 = true;
                            break;
                        }
                    }
                    walk = walk->getNext();
                }
                if(w1 && w2){
                    success = true;
                }
            }
            else{
                success = false;
            }
        }
        if(success)
            cout<<"success"<<endl;
        else{
            cout<<"failure"<<endl;
        }
    }
    if(!update){
        bool success = false;
        while(fin>>a>>b>>d>>s){
            if(!containVertex[a] ||!containVertex[b]){
                    //a isn't created but b is
                    if(!containVertex[a] && containVertex[b]){ //add the vertex
                        containVertex[a] = true;
                        vertex[a]->setHead(new Node(s,d,b));
                        vertex[b]->insert(new Node(s,d,a));
                        sizeOfGraph++;
                    }
                    else if(!containVertex[b]&& containVertex[a]){//add the vertex since its a undirected graph
                        containVertex[b] = true;
                        vertex[b]->setHead(new Node(s,d,a));
                        vertex[a]->insert(new Node(s,d,b));
                        sizeOfGraph++;

                    }
                    //missing case 3
                    //a and b are both not within the list
                    else{
                        containVertex[a] = true;
                        containVertex[b] = true;
                        vertex[b]->setHead(new Node(s,d,a));
                        vertex[a]->setHead(new Node(s,d,b));
                        sizeOfGraph+=2;
                    }
                }
                //regular insert
            else{
                vertex[a]->insert(new Node(s,d,b));
                vertex[b]->insert(new Node(s,d,a));
            }
        }
        cout<<"success"<<endl;
    }
}


bool Graph::isInGraph(int a){
    return containVertex[a];
}
//assume the input is vaild.
void Graph::Traffic(int a, int b, double A){
    bool w1 = false;
    bool w2 = false;
    if(A >1 || A<0){
        cout<<"failure"<<endl;
        return;
    }
    if(containVertex[a]&&containVertex[b]){
        //gotta change both directions
        Node* walk = vertex[a]->getHead();
        while(walk){
            if (walk->getName()==b){
                walk->setA(A);
                //cout<<walk->getA()<<" new value between" <<a <<" and "<<b<<endl;
                //cout<<"success"<<endl;
                w1 = true;
                break;
            }
            walk = walk->getNext();
        }
        walk = vertex[b]->getHead();
        while(walk){
            if (walk->getName()==a){
                walk->setA(A);
                w2 = true;
                break;
            }
            walk = walk->getNext();
        }
        if(!w1 || !w2){
            cout<<"failure"<<endl;
        }
        else{
            cout<<"success"<<endl;
        }

    }
    else{
        cout<<"failure"<<endl;
    }
}
void Graph::Delete(int a){
    if(containVertex[a]){
        Node *walk = vertex[a]->getHead();
        while(walk){
           // cout<<"we are going to "<<walk->getName()<<" to delete"<<a<<endl;
            vertex[walk->getName()]->RemoveElement(a);
            walk = walk->getNext();
        }
        //checks all the element that a have and remove a from their list
        containVertex[a]= false;
        sizeOfGraph--;
        cout<<"success"<<endl;
        //very important
        delete vertex[a];
        vertex[a] = new List();
    }else{
        cout<<"failure"<<endl;
    }
}


// goal: intialize 
void Graph::Insert(int a, int b, double d, double s){
    if(!containVertex[a] ||!containVertex[b]){
        //a isn't created but b is
        if(!containVertex[a] && containVertex[b]){ //add the vertex
            containVertex[a] = true;
            vertex[a]->setHead(new Node(s,d,b));
            vertex[b]->insert(new Node(s,d,a));
            sizeOfGraph++;
        }
        else if(!containVertex[b]&& containVertex[a]){//add the vertex since its a undirected graph
            containVertex[b] = true;
            vertex[b]->setHead(new Node(s,d,a));
            vertex[a]->insert(new Node(s,d,b));
            sizeOfGraph++;
        }
        //missing case 3
        //a and b are both not within the list
        else if(!containVertex[b]&& !containVertex[a]){
            containVertex[a] = true;
            containVertex[b] = true;
            vertex[b]->setHead(new Node(s,d,a));
            vertex[a]->setHead(new Node(s,d,b));
            sizeOfGraph+=2;
        }
        
    }
    //regular insert
    else{
        vertex[a]->insert(new Node(s,d,b));
        vertex[b]->insert(new Node(s,d,a));
    }
    cout<<"success"<<endl;
}
void Graph::Print(int a){
    if(containVertex[a]){
        vertex[a]->walk();
    }
    else{
        cout<<"failure"<<endl;
    }
}

