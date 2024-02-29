#include <iostream>
#include <string>
#include "declaration.hpp"
#include <fstream>
using namespace std;
int main(){
    Graph *Gpan = new Graph();
    string cmd;
    while(cin>>cmd){
        try{
            //check illegal argument
            if(cmd == "INSERT"){
                int a,b;
                cin>>a>>b;
                double d,s;
                cin>>d>>s;
                if(a<=0 || a>500000||b<=0 || b>500000|| s<=0){
                    throw ExceptionBad();
                }
                else{
                    Gpan->Insert(a,b,d,s);
                }
            }
            else if(cmd =="END"){
                break;
            }
            //check illegal argument
            else if(cmd =="PRINT"){
                int a;
                cin>>a;
                if(a<=0 || a>500000){
                    throw ExceptionBad();
                }
                else{
                    Gpan->Print(a);
                }
            }
            else if(cmd =="DELETE"){
                int a;
                cin>>a;
                if(a<=0 || a>500000){
                    throw ExceptionBad();
                }
                Gpan->Delete(a);
            }
            else if (cmd =="TRAFFIC"){
                int a,b;
                double A;
                cin>>a>>b>>A;
                if(a<=500000 && a>=0&& b<=500000 && b>=0){
                    Gpan->Traffic(a,b,A);
                }
                else{
                    throw ExceptionBad();
                }
            }
            else if(cmd == "UPDATE"){
                std::string fileName;
                std::cin>>fileName;
                std::fstream fin(fileName.c_str());
                Gpan->Readfile(fin,true);
            }
            else if(cmd == "LOAD"){
                std::string fileName;
                std::cin>>fileName;
                std::fstream fin(fileName.c_str());
                Gpan->Readfile(fin,false);
            }
            else if(cmd == "PATH"){
                int a,b;
                cin>>a>>b;
                if(a<=500000 && a>=0&& b <=500000 && b>=0){
                    Gpan->Path(a,b);
                }
                else{
                    throw ExceptionBad();
                }
            }
            else if(cmd == "LOWEST"){
                int a,b;
                cin>>a>>b;
                if(a<=500000 && a>=0 && b <=500000 && b>=0){
                    Gpan->Lowest(a,b);
                }
                else{
                    throw ExceptionBad();
                }
            }
        }
        catch(ExceptionBad l){
            cout<<l.msg()<<endl;
        }
    }
    delete Gpan;
}