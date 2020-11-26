#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QWidget>
#include "object.h"
#include <QTimer>
#include "LinkUI.h"
#include "unistd.h"
#include <QFile>
#include "Json.h"

class BaseView : public QWidget
{
    Q_OBJECT
public:
    static BaseView *create(const QString &className = 0);
    virtual void initView(const QString &tip = 0);


protected:
    explicit BaseView(QWidget *parent = 0);
    QVariantMap design,oledMods;
};

#endif // BASEVIEW_H
