#include "declaration.hpp"
#include <iostream>
#include <string>

Heap::Heap(int sizeIN, int startNode, bool *containVertex){
    size = sizeIN;
    arrayOfVertex = new Pair*[size];
    cursize =0;
    int amtcontainVERTEX =0;
    for(int i =1;i<500001;i++){
        //if the vertex is in the graph:
        if(containVertex[i]){
            if(i == startNode){      //i E [1, 500k] in my code i doesn't repersent the vertex
                arrayOfVertex[cursize] = new Pair(i, 0);
            }
            else{
                arrayOfVertex[cursize] = new Pair(i, 1/0.0);
                //cout<<"current size"<< cursize<<endl;
            }
            heapifyUP(cursize);
   
            cursize++;
            amtcontainVERTEX++;
        }
    }
    //cout<<cursize<<endl;
   // cout<<"amount of true in containvertex "<< amtcontainVERTEX<<endl;
}
Heap::~Heap(){
    for(int i=0; i <size;i++){
        delete arrayOfVertex[i];
    }
    delete [] arrayOfVertex; 
}
//                              cost of u to v
bool Heap::relax(int u, int v, float Wuv){
    float uT = 0;
    float vT = 0;
    int indexOFv =0;
    // something I would like to change
    for(int i=0;i<cursize;i++){
       // cout<<" in total we have" << size<<" elements"<<endl;
        //cout<<"at "<<i<<" index of the array we have " <<arrayOfVertex[i]<<endl;
        if(arrayOfVertex[i]->getName() == u){
            uT = arrayOfVertex[i]->getT();
        }
        if(arrayOfVertex[i]->getName() == v){
            vT = arrayOfVertex[i]->getT();
            indexOFv =i;
        }
    }

    if(uT + Wuv < vT){
        arrayOfVertex[indexOFv]->setT(uT + Wuv);
        heapifyUP(indexOFv); 
        return true;
    }
    return false;
}
//implementing a min heap
void Heap::heapifyUP(int cursize){
    //we have the new element on the bottom, we see where it fits, bottom is 
    
    float newElementDistance = arrayOfVertex[cursize]->getT();
    //compare the newElementName with their parent. 
    int parentElementindex = (int)((cursize-1)/2);

    while(parentElementindex >=0 && newElementDistance < arrayOfVertex[parentElementindex]->getT() ){
       // cout<<newElementDistance<<" < "<<arrayOfVertex[parentElementindex]->getT()<<endl;
        Pair *temp = arrayOfVertex[parentElementindex];
        //put the new element in the place of the parent
        arrayOfVertex[parentElementindex] = arrayOfVertex[cursize];
        //put parent element in the new element's list
        arrayOfVertex [cursize] = temp;
        //shift the parenets element and current element
        cursize =parentElementindex;
        parentElementindex = (int)((parentElementindex-1)/2);
    }
}
//when we shift the element down
void Heap::heapifyDown(int sizer, int curElementIndex){
    //in the first iteration, curElement is 0
    int left = curElementIndex*2 +1;
    int right = curElementIndex*2 +2;
    int min = curElementIndex;
    if(left <sizer && arrayOfVertex[left]->getT()< arrayOfVertex[min]->getT() ){
        min = left;
    }
    if(right <sizer&& arrayOfVertex[right]->getT()< arrayOfVertex[min]->getT() ){
        min = right;
    }
    if(min != curElementIndex){
        Pair *temp = arrayOfVertex[curElementIndex];
        arrayOfVertex[curElementIndex] = arrayOfVertex[min];
        arrayOfVertex[min] = temp;
        heapifyDown(sizer,min);
    }
}
//copied this from ladan's slide
int Heap::ExtractMin(){
    //get the index 
    int k = arrayOfVertex[0] ->getName();
    //swap first element with the last element
    Pair * temp = arrayOfVertex[0];
    arrayOfVertex[0] = arrayOfVertex[cursize-1];
    arrayOfVertex[cursize -1] = temp;
    // decrease the size by 1
    cursize--;
    //call heapi
    heapifyDown(cursize,0);
    // for(int i=0;i<size;i++){
    //     cout<<"at array index "<<i<< " we have "<< arrayOfVertex[i]->getName()<<" with weight "<< arrayOfVertex[i]->getT()<<endl;
    // }
    return k;
}

int Heap::getSize()
{
    return cursize;
}
float Heap::returnT(int b){
     for(int i=0;i<size;i++){
        if(arrayOfVertex[i]->getName() == b){
            return arrayOfVertex[i]->getT();
        }
    }
    return 69420;
}