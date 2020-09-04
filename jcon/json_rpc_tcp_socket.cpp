#include "json_rpc_tcp_socket.h"
#include "jcon_assert.h"

#include <QUrl>

namespace jcon {

JsonRpcTcpSocket::JsonRpcTcpSocket()
    : m_socket(new QTcpSocket(this))
{
    setupSocket();
    isHttp=false;
}

JsonRpcTcpSocket::JsonRpcTcpSocket(QTcpSocket* socket)
    : m_socket(socket)
{
    setupSocket();
    isHttp=false;
}

JsonRpcTcpSocket::~JsonRpcTcpSocket()
{
    m_socket->disconnect(this);
    m_socket->deleteLater();
}

void JsonRpcTcpSocket::setupSocket()
{
    m_socket->setSocketOption(QAbstractSocket::LowDelayOption, "1");
    m_socket->setSocketOption(QAbstractSocket::KeepAliveOption, "1");
    connect(m_socket, &QTcpSocket::connected, this, [this]() {
        emit socketConnected(m_socket);
    });

    connect(m_socket, &QTcpSocket::disconnected, this, [this]() {
        emit socketDisconnected(m_socket);
    });

    connect(m_socket, &QTcpSocket::readyRead,
            this, &JsonRpcTcpSocket::dataReady);

    void (QAbstractSocket::*errorFun)(QAbstractSocket::SocketError) =
        &QAbstractSocket::error;
    connect(m_socket, errorFun, this,
            [this](QAbstractSocket::SocketError error) {
                emit socketError(m_socket, error);
            });
}

void JsonRpcTcpSocket::connectToHost(const QString& host, int port)
{
    m_socket->connectToHost(host, port,
                            QIODevice::ReadWrite,
                            QAbstractSocket::IPv4Protocol);
}

void JsonRpcTcpSocket::connectToUrl(const QUrl& url)
{
    connectToHost(url.host(), url.port());
}

bool JsonRpcTcpSocket::waitForConnected(int msecs)
{
    return m_socket->waitForConnected(msecs);
}

void JsonRpcTcpSocket::disconnectFromHost()
{
    m_socket->disconnectFromHost();
    m_socket->close();
}

bool JsonRpcTcpSocket::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

size_t JsonRpcTcpSocket::send(const QByteArray& data)
{
    if(!isConnected())
    {
        disconnectFromHost();
        return 0;
    }

    int sz;
    if(isHttp)
    {
        QString str="HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: "+QString::number(data.length())+"\r\n\r\n";

        str+=data;
        sz=m_socket->write(str.toUtf8());
    }
    else
        sz= m_socket->write(data);

    if(sz<=0)
    {
        disconnectFromHost();
        return 0;
    }
    m_socket->flush();
    return sz;
}

QString JsonRpcTcpSocket::errorString() const
{
    return m_socket->errorString();
}

QHostAddress JsonRpcTcpSocket::localAddress() const
{
    return m_socket->localAddress();
}

int JsonRpcTcpSocket::localPort() const
{
    return m_socket->localPort();
}

QHostAddress JsonRpcTcpSocket::peerAddress() const
{
    return m_socket->peerAddress();
}

int JsonRpcTcpSocket::peerPort() const
{
    return m_socket->peerPort();
}

void JsonRpcTcpSocket::dataReady()
{
    JCON_ASSERT(m_socket->bytesAvailable() > 0);
    buf = m_socket->readAll();
    if(buf.contains("\r\n\r\n{"))
    {
        isHttp=true;
        int a=buf.indexOf("\r\n\r\n");
        buf=buf.mid(a+4);
    }
//    if(buf.startsWith("{"))
        emit dataReceived(buf.toUtf8(), m_socket);
}

}
