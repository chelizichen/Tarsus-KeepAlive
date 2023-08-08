#include<iostream>
#include "./logServer.cpp"

void initLogServer(){
    std::cout << "-------- Log_Server_Init --------- "<< std::endl;
    LogServerParams::logServerConfig serverConfig;
    serverConfig.serverName = "MyServer";
    serverConfig.dbConfig = LogServerParams::DbConfig();
    
    logServer* myServer = LogServerFactory(serverConfig);
    myServer->StartWatchPort(8083, 1);
    
    // 等待一段时间，以便观察定时任务输出
    std::this_thread::sleep_for(std::chrono::seconds(60));
    
    delete myServer;
}