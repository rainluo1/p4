#include "declaration.hpp"
#include <iostream>
#include <string>

Heap::Heap(bool containVertex[], Node vertex[], int startNode){
    for(int i =0;i<50001;i++){
        if(containVertex[i]){
            size++;
        }
    }
    arrayOfVertex = new Pair*[size];
    cursize =0;
    for(int i =0;i<50001;i++){
        if(i == startNode){
            arrayOfVertex[cursize] = new Pair(i, 0);
            //everytimes we insert we must heapifly
            heapifyUP(cursize);
            cursize++;
        }
        if(containVertex[i]){
            //arrayOfVertex[cursize] = new Pair(i, 1/0);
            //everytimes we insert we must heapifly
            heapifyUP(cursize);
            cursize++;
        }
    }
}
Heap::~Heap(){
    for(int i=0; i <size;i++){
        delete arrayOfVertex[i];
    }
    delete [] arrayOfVertex; 
}
//implementing a min heap
void Heap::heapifyUP(int cursize){
    //we have the new element on the bottom, we see where it fits, bottom is 
    int newElementDistance = arrayOfVertex[cursize]->getDistance();
    //compare the newElementName with their parent. 
    int parentElementindex = (int)((cursize-1)/2);
    while(newElementDistance <arrayOfVertex[parentElementindex]->getDistance()){
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
void Heap::heapifyDown(int size, int curElementIndex){
    //in the first iteration, curElement is 0
    int left = curElementIndex*2 +1;
    int right = curElementIndex*2 +2;
    int min;
    if(left <size){
        int curVal = arrayOfVertex[curElementIndex]->getDistance();
        int leftVal = arrayOfVertex[left]->getDistance();
        if(curVal <leftVal){
            min = curElementIndex;
        }
        else{
            min = left;
        }
    }
    else if(right <size){
        int curVal = arrayOfVertex[curElementIndex]->getDistance();
        int rightVal = arrayOfVertex[right]->getDistance();
        if(curVal <rightVal){
            min = curElementIndex;
        }
        else{
            min = right;
        }
    }
    if(min != curElementIndex){
        heapifyDown(size,min);
    }
}
//copied this from ladan's slide
int Heap::ExtractMin(){
    //get the index 
    int k = arrayOfVertex[0] ->getName();
    //swap first element with the last element
    Pair *temp = arrayOfVertex[0];
    arrayOfVertex[0] = arrayOfVertex[cursize];
    // decrease the size by 1
    cursize--;
    //call heapi
    heapifyDown(cursize,1);
    return k;
}
int Heap::getSize(){
    return cursize;
}