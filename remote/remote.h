#ifndef REMOTE_H
#define REMOTE_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QTimer>
#include "Link.h"


class Remote : public QObject
{
    Q_OBJECT
public:
    static Remote *initRemote();

protected:
    explicit Remote(QObject *parent = nullptr);
    LinkObject *dev = nullptr;
    QWebSocketServer *webSocketServer = nullptr;
    QWebSocket *ws = nullptr;
    QString sendType = "ctrl";
    QVariantMap config;
    QTimer *pressTimer = nullptr;
    QString lastCode;
    QTimer *tipTimer = nullptr;
    QVariantList definedLay;

    void controler(const QString &code,QString type = "tap");
    QVariantList handleConfig();
    void handleMixLive(const bool &type = 1);
    void handleRecord(const bool &type = 1);
    void handleMixPush(const bool &type = 1);
    void handlePlatformPush(const bool &type = 1);
    void handleVO(const bool &type = 1);
    void handleDhcp(const bool &type = 1);
    void handleReset();
    void handleReboot();
    void handleLayout(const QVariantMap &layMap);
    bool wtchRemote();


    QString writeCom(const QString &com);



public slots:
    void onEvent(QString type,QVariant msg);
    void onNewConnect();
    void onReceivedMessage(const QString &message);
    void onDisconnected();
    void updateConfig();
};

#endif // REMOTE_H
