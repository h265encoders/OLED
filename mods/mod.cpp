#include "mod.h"

Mods *Mods::create(const QString &modName)
{
    QString className = "Mod"+modName;
    return static_cast<Mods*>(CObjectFactory::createObject(className.toStdString()));
}

void Mods::init()
{

}

bool Mods::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    Q_UNUSED(left)
    Q_UNUSED(top)
    Q_UNUSED(width)
    Q_UNUSED(height)
    Q_UNUSED(parent)

    return importantChange;
}

Mods::Mods(QObject *parent) : QObject(parent)
{

}

void Mods::onGPIO(QString type, QVariant info)
{
    qDebug() << "12111";
}
