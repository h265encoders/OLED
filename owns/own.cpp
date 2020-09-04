#include "own.h"

Owns *Owns::create(const QString &modName)
{
    QString className = "Own"+modName;
    return static_cast<Owns*>(CObjectFactory::createObject(className.toStdString()));
}

void Owns::init(const QVariantList &param)
{

}


Owns::Owns(QObject *parent) : QObject(parent)
{

}

void Owns::onGPIO(QString type, QVariant info)
{
    qDebug() << "12111";
}
