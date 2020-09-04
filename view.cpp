#include "view.h"
#include <QFile>
#include "mods/mod.h"
#include "owns/own.h"

View *View::initView()
{
    static View view;
    return &view;
}

View::View(QWidget *parent) : QWidget(parent)
{
    this->resize(128,64);

    QVariantMap design = Json::loadFile("/link/config/oled.json").toMap();
    mods = design["mods"].toList();
    curBright=0xa0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    timer.start(2000);
    onTimer();

    QVariantList owns = design["own"].toList();

    for(QVariant own : owns)
    {
        QVariantMap ownMap = own.toMap();
        QString name = ownMap["name"].toString();
        QVariantList param = ownMap["param"].toList();

        if(name == "INIT")
            LinkUI::initOLED(this,param[0].toString(),param[1].toInt(),param[2].toBool());
        else
            Owns::create(name)->init(param);
    }

    RPC::create()->update(Json::encode(Json::loadFile("/link/config/button.json")));
}

int View::replacePX(QString value)
{
    return value.replace("px","").toInt();
}

void View::onTimer()
{
    if(!RPC::create()->updateRPC())
        return;
    static int count=0;
    count++;
    if(count==60)
    {
        count=0;
        if(curBright>0x0)
        {
            curBright-=0x10;
            LinkUI::setBrightness(curBright);
        }
    }
    importantChange = false;

    for(QVariant qv : mods)
    {
        QVariantMap map = qv.toMap();
        QString name = map["name"].toString();
        double top = (double)replacePX(map["top"].toString()) / scale;
        double left = (double)replacePX(map["left"].toString()) / scale;
        double width = (double)replacePX(map["width"].toString()) / scale;
        double height = (double)replacePX(map["height"].toString()) / scale;

        if(Mods::create(name)->init(left,top,width,height,this))
            importantChange = true;
    }

    if(importantChange)
    {
        curBright=0xa0;
        LinkUI::setBrightness(curBright);
    }
    LinkUI::refreshOLED();
}

