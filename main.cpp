#include<iostream>
#include "./src/logServer/index.cpp"
using namespace std;

int main(){
    cout<<"*********** start listening *********** "<<endl;
    initLogServer();
    cout<<"***********    end   ****************** "<<endl;
}