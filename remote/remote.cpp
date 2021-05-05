#include "remote.h"
#include "Json.h"
#include "rpc.h"
#include <QProcess>
#include "router.h"


Remote *Remote::initRemote()
{
    static Remote remote;
    return &remote;
}

Remote::Remote(QObject *parent) : QObject(parent)
{

    if(!wtchRemote())
        return;

    dev=Link::create("Device");
    dev->start();
    dev->invoke("enableIR");
    connect(dev,SIGNAL(newEvent(QString,QVariant)),this,SLOT(onEvent(QString,QVariant)));


    webSocketServer = new QWebSocketServer(QStringLiteral("Notify Server"),QWebSocketServer::NonSecureMode,this);
    if(!webSocketServer->listen(QHostAddress::Any,7857))
    {
        qDebug() << "listen websocket error !!!";
        return;
    }

    connect(webSocketServer,SIGNAL(newConnection()),this,SLOT(onNewConnect()));

    pressTimer = new QTimer;
    connect(pressTimer,&QTimer::timeout,[=](){
            pressTimer->stop();
            this->controler(lastCode,"pressCH");
        });

    tipTimer = new QTimer;
    connect(tipTimer,&QTimer::timeout,[=](){
            Router::linkTo("/modView");
            tipTimer->stop();
        });

    definedLay = Json::loadFile("/link/config/defLays.json").toList();
    this->updateConfig();
}


void Remote::onEvent(QString type, QVariant msg)
{
    if(type == "IR")
    {
        if(sendType == "bind")
        {
            if(ws != nullptr)
                ws->sendTextMessage(Json::encode(msg));
        }
        if(sendType == "ctrl")
        {
            QVariantMap map = msg.toMap();
            qlonglong state = map["state"].toLongLong();
            qlonglong high = map["high"].toLongLong();
            qlonglong low = map["low"].toLongLong();
            qlonglong code = high+low;
            QString cc = QString::number(code);

            if(state == 0)
            {
                //判断是否长按
                if(lastCode == cc)
                    return;
                lastCode = cc;
                pressTimer->start(3000);
            }

            if(state == 1)
            {
                if(pressTimer->isActive())
                    this->controler(cc,"tapCH");
                pressTimer->stop();
                lastCode = "";

            }

        }

    }
}

void Remote::onNewConnect()
{
    QWebSocket *webSocket = webSocketServer->nextPendingConnection();
    connect(webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onReceivedMessage(QString)));
    connect(webSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}


void Remote::onReceivedMessage(const QString &message)
{
    sendType = message;
    ws = qobject_cast<QWebSocket *>(sender());
}


void Remote::onDisconnected()
{
    sendType = "ctrl";
    delete ws;
    ws = nullptr;
}

void Remote::controler(const QString &code, QString type)
{
    QVariantMap qv = Json::loadFile("/link/config/lang.json").toMap();
    QString lang = qv["lang"].toString();

    QVariantList btns = config["btns"].toList();
    for(int i=0;i<btns.count();i++)
    {
        QVariantMap btn = btns[i].toMap();
        QString cc = QString("%1").arg(btn["code"].toDouble(), 0, 'f', 0);
        if(cc == code)
        {
            if(btn[type].toString() == "开启Mix直播"){
                qDebug() << "start mix live";
                this->handleMixLive(true);
            }
            if(btn[type].toString() == "关闭Mix直播"){
                qDebug() << "stop mix live";
                this->handleMixLive(false);
            }
            if(btn[type].toString() == "开启录制"){
                qDebug() << "start record";
                this->handleRecord(true);
            }
            if(btn[type].toString() == "关闭录制"){
                qDebug() << "stop record";
                this->handleRecord(false);
            }
            if(btn[type].toString() == "开启Mix推流"){
                qDebug() << "start mix push";
                this->handleMixPush(true);
            }
            if(btn[type].toString() == "关闭Mix推流"){
                qDebug() << "stop mix push";
                this->handleMixPush(false);
            }
            if(btn[type].toString() == "开启全平台推流"){
                qDebug() << "start platform push";
                this->handlePlatformPush(true);
            }
            if(btn[type].toString() == "关闭全平台推流"){
                qDebug() << "stop platform push";
                this->handlePlatformPush(false);
            }
            if(btn[type].toString() == "开启 Hdmi/Vga"){
                qDebug() << "start hdmi/vga";
                this->handleVO(true);
            }
            if(btn[type].toString() == "关闭 Hdmi/Vga"){
                qDebug() << "stop hdmi/vga";
                this->handleVO(false);
            }
            if(btn[type].toString() == "开启 Dhcp"){
                qDebug() << "start dhcp";
                this->handleDhcp(true);
            }
            if(btn[type].toString() == "关闭 Dhcp"){
                qDebug() << "stop dhcp";
                this->handleDhcp(false);
            }
            if(btn[type].toString() == "恢复出厂设置"){
                qDebug() << "reset system";
                this->handleReset();
            }
            if(btn[type].toString() == "重启机器"){
                qDebug() << "restart";
                this->handleReboot();
            }

            //切换布局
            if(!definedLay.isEmpty())
            {
                for(int i=0;i<definedLay.count();i++)
                {
                    QVariantMap layMap = definedLay[i].toMap();
                    QString layName = layMap["layName"].toString();
                    if(btn[type].toString() == layName)
                        this->handleLayout(layMap);

                }
            }

            type = type.replace("CH","");
            type = type.replace("EN","");
            type += lang.toUpper();
            type = type.replace("CN","CH");

            Router::linkTo("/tipView",btn[type].toString());
            tipTimer->start(3000);
        }
    }
}

QVariantList Remote::handleConfig()
{
    return Json::loadFile("/link/config/config.json").toList();
}


void Remote::updateConfig()
{
    qDebug() << "update config";
    QVariantList configs = Json::loadFile("/link/config/oled/remfea.json").toList();
    for(int i=0;i<configs.count();i++)
    {
        QVariantMap cfg = configs[i].toMap();
        if(cfg["used"].toBool())
            config = cfg;
    }
}

void Remote::handleMixLive(const bool &type)
{
    QVariantList configs = handleConfig();
    QVariantMap srcMap,mainMap,subMap;
    int indexMix = -1;
    for(int i=0;i<configs.count();i++) {
        QVariantMap map = configs[i].toMap();
        if(map["type"].toString() == "mix"){
            srcMap = map;
            indexMix = i;
        }
    }

    if(indexMix > -1)
    {
        mainMap = srcMap["stream"].toMap();
        subMap = srcMap["stream2"].toMap();
        mainMap["rtmp"] = type;
        subMap["rtmp"] = type;
        srcMap["stream"] = mainMap;
        srcMap["stream2"] = subMap;
        configs[indexMix] = srcMap;
        RPC::create()->rpcClient->call("enc.update",Json::encode(configs));
    }
}

void Remote::handleRecord(const bool &type)
{
    std::shared_ptr<jcon::JsonRpcResult> result;
    bool ret = true;
    if(type)
        result = RPC::create()->rpcClient->call("rec.start");
    else
        result = RPC::create()->rpcClient->call("rec.stop");

    if (result->isSuccess()) {
        QVariant re =  result->result();
        ret = re.toBool();
    }
    qDebug() << "record" << ret;
}

void Remote::handleMixPush(const bool &type)
{
    QVariantList configs = handleConfig();
    QVariantMap srcMap,mainMap,mainPushMap,subMap,subPushMap;
    int indexMix = -1;
    for(int i=0;i<configs.count();i++) {
        QVariantMap map = configs[i].toMap();
        if(map["type"].toString() == "mix"){
            srcMap = map;
            indexMix = i;
        }
    }

    if(indexMix > -1)
    {
        mainMap = srcMap["stream"].toMap();
        mainPushMap = mainMap["push"].toMap();
        mainPushMap["enable"] = type;

        subMap = srcMap["stream2"].toMap();
        subPushMap = mainMap["push"].toMap();
        subPushMap["enable"] = type;

        mainMap["push"] = mainPushMap;
        srcMap["stream"] = mainMap;
        subMap["push"] = subPushMap;
        srcMap["stream2"] = subMap;
        configs[indexMix] = srcMap;
        RPC::create()->rpcClient->call("enc.update",Json::encode(configs));
    }
}

void Remote::handlePlatformPush(const bool &type)
{
    if(type)
       RPC::create()->rpcClient->call("push.start");
    else
        RPC::create()->rpcClient->call("push.stop");
}

void Remote::handleVO(const bool &type)
{
    QVariantList configs = handleConfig();
    QVariantMap srcMap,hdmiMap,vgaMap;
    int indexMix = -1;
    for(int i=0;i<configs.count();i++) {
        QVariantMap map = configs[i].toMap();
        if(map["type"].toString() == "mix"){
            srcMap = map;
            indexMix = i;
        }
    }

    if(indexMix > -1)
    {
        hdmiMap = srcMap["output"].toMap();
        hdmiMap["enable"] = type;
        srcMap["output"] = hdmiMap;
        vgaMap = srcMap["output2"].toMap();
        vgaMap["enable"] = type;
        srcMap["output2"] = vgaMap;

        configs[indexMix] = srcMap;
        RPC::create()->rpcClient->call("enc.update",Json::encode(configs));
    }
}

void Remote::handleDhcp(const bool &type)
{
    RPC::create()->rpcClient->call("enc.setNetDhcp",type);
}

void Remote::handleReset()
{
    writeCom("/link/shell/reset.sh");
}

void Remote::handleReboot()
{
    writeCom("reboot");
}

void Remote::handleLayout(const QVariantMap &layMap)
{

    QVariantList layouts = layMap["layouts"].toList();

    QVariantList srcList;
    QVariantList layList;
    for(int i=0;i<layouts.count();i++)
    {

        QVariantMap map = layouts[i].toMap();
        QVariantMap pos = map["pos"].toMap();

        layList << pos;
        int id = map["id"].toString().toInt();
        if(id < 0)
            srcList << "-1";
        else
            srcList << map["id"].toString();
    }

    QVariantList configs = handleConfig();
    int indexMix = -1;
    QVariantMap srcMap;
    for(int i=0;i<configs.count();i++)
    {
        QVariantMap map = configs[i].toMap();
        if(map["type"].toString() == "mix"){
            indexMix = i;
            srcMap = map;
        }
    }

    if(index > 0 && !srcMap.isEmpty())
    {
        srcMap["srcV"] = srcList;
        srcMap["layout"] = layList;
        configs[indexMix] = srcMap;
        RPC::create()->rpcClient->call("enc.update",Json::encode(configs));
    }

}

bool Remote::wtchRemote()
{
    QString res = writeCom("cat /link/web/config.php");
    if(res.contains("remote"))
    {
        res = res.mid(res.indexOf("$remote"));
        res = res.replace(" ","");
        res = res.mid(res.indexOf("=")+1,4);
        if(res == "true")
            return true;
    }
    return false;
}


QString Remote::writeCom(const QString &com)
{
    QProcess proc;
    QStringList argList;
    argList << "-c" << com;
    proc.start("/bin/sh",argList);
    // 等待进程启动
    proc.waitForFinished();
    proc.waitForReadyRead();
    // 读取进程输出到控制台的数据
    QByteArray procOutput = proc.readAll();
    proc.close();
    return QString(procOutput);
}


