#include <iostream>
#include "src/logServer.h"

using namespace std;

int main(){
    cout<<"*********** start listening *********** "<<endl;
    auto* myServer = new logServer();
//    myServer->initDataBase();
    cout<<"***********    end   ****************** "<<endl;
}