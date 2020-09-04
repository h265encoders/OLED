#ifndef RPC_H
#define RPC_H

#include <QObject>
#include <jcon/json_rpc_tcp_server.h>
#include <jcon/json_rpc_tcp_client.h>

class RPC : public QObject
{
    Q_OBJECT
public:
    static RPC *create();
    void initRPC();

    QVariantList config;
    jcon::JsonRpcTcpServer *rpcServer;
    jcon::JsonRpcTcpClient *rpcClient;

    bool updateRPC();

protected:
    explicit RPC(QObject *parent = 0);

public slots:
    bool update(QString json);
    void upDesignConfig(const QString &json);
};

#endif // RPC_H
