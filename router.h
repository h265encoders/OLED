#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QDebug>
#include <QMap>
#include "view/baseview.h"

static QMap<QString,QString> viewMap;

class Router : public QObject
{
    Q_OBJECT
public:

    static void init();
    static void linkTo(const QString &path = "/modView",const QString &param = 0);

private:
    explicit Router() = default;
    //static QList<BaseView*> viewList;

};

#endif // ROUTER_H
