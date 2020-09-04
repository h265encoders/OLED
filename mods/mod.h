#ifndef MODS_H
#define MODS_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include "object.h"
#include "rpc.h"
#include "Json.h"

class Mods : public QObject
{
    Q_OBJECT
public:
    static Mods *create(const QString &modName);
    virtual void init();
    virtual bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);


protected:
    explicit Mods(QObject *parent = nullptr);
    bool importantChange = false;
    QLabel *label = nullptr;

public slots:
    virtual void onGPIO(QString type, QVariant info);

};

#endif // MODS_H
