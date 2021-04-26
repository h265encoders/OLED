#include "rpc.h"
#include "Json.h"
#include "remote/remote.h"

RPC::RPC(QObject *parent) : QObject(parent)
{

}

RPC *RPC::create()
{
    static RPC rpc;
    return &rpc;
}

void RPC::initRPC()
{
    rpcServer=new jcon::JsonRpcTcpServer();
    jcon::JsonRpcServer::ServiceMap map;
    map[this]="oled";
#ifdef HI3521D
    map[Remote::initRemote()]="remote";
#endif
    rpcServer->registerServices(map, ".");
    rpcServer->listen(6004);

    rpcClient = new jcon::JsonRpcTcpClient();
}

bool RPC::updateRPC()
{
    if(!rpcClient->isConnected())
    {
        rpcClient->connectToServer("127.0.0.1", 6001);
        return false;
    }
    return true;
}

bool RPC::update(QString json)
{
    config=Json::decode(json).toList();
    Json::saveFile(config,"/link/config/button.json");

    return true;
}

void RPC::upDesignConfig(const QString &json)
{
    QVariantMap design=Json::decode(json).toMap();
    Json::saveFile(design,"/link/config/oled/oled.json");

    exit(0);
}
