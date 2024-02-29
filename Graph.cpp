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
//
void Graph::Readfile(fstream &fin, bool update){
    int a,b;
    double A,d,s;
    if(update){
        bool success = false;
        while(fin>>a>>b>>A){
            bool w = false;
            if(containVertex[a]&&containVertex[b]){
                Node* walk = vertex[a]->getHead();
                while(walk){
                    if (walk->getName()==b){
                        walk->setA(A);
                        success = true;
                        w = true;
                        break;
                    }
                    walk = walk->getNext();
                }
                if(!w){
                    success = false;
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
    bool w = false;
    if(containVertex[a]&&containVertex[b]){
        Node* walk = vertex[a]->getHead();
        while(walk){
            if (walk->getName()==b){
                walk->setA(A);
                cout<<"success"<<endl;
                w = true;
                break;
            }
            walk = walk->getNext();
        }
        if(!w){
            cout<<"failure"<<endl;
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
        cout<<"success"<<endl;
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

