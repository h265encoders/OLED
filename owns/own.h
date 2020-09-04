#ifndef OWNS_H
#define OWNS_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include "object.h"
#include "rpc.h"
#include "Json.h"
#include <LinkUI.h>

class Owns : public QObject
{
    Q_OBJECT
public:
    static Owns *create(const QString &modName);
    virtual void init(const QVariantList &param = QVariantList());

protected:
    explicit Owns(QObject *parent = nullptr);

public slots:
    virtual void onGPIO(QString type, QVariant info);

};

#endif // OWNS_H
