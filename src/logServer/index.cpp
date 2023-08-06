#include<iostream>

#include "./logServer.cpp"

void initLogServer(){
    dbConfig getDbConfig = dbConfig();
    logServerConfig serverConfig = logServerConfig();
    serverConfig.dbConfig = getDbConfig;
    serverConfig.serverName = "keep_alive";
    new logServer(serverConfig);
}