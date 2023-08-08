#include <iostream>
#include "./src/logServer/logServer.cpp"
using namespace std;

int main(){
    cout<<"*********** start listening *********** "<<endl;
    logServer* myServer = new logServer();
    cout<<"***********    end   ****************** "<<endl;
}