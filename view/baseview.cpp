#include "baseview.h"
#include "owns/own.h"

BaseView *BaseView::create(const QString &className)
{
    return static_cast<BaseView*>(CObjectFactory::createObject(className.toStdString()));
}

BaseView::BaseView(QWidget *parent) : QWidget(parent)
{
    this->resize(128,64);
}

void BaseView::initView(const QString &tip)
{
    oledMods = Json::loadFile("/link/config/oled/oledMods.json").toMap();
    design = Json::loadFile("/link/config/oled/oled.json").toMap();
    QVariantList owns = oledMods["own"].toList();
    for(QVariant own : owns)
    {
        QVariantMap ownMap = own.toMap();
        QString name = ownMap["name"].toString();
        QVariantList param = ownMap["param"].toList();
        qDebug() << name << "###";
        if(name == "INIT")
            LinkUI::initOLED(this,param[0].toString(),param[1].toInt(),param[2].toBool());
        if(name == "ROTATE")
            Owns::create("ROTATE")->init(param);
    }
}
