#ifndef MODVIEW_H
#define MODVIEW_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QTimer>
#include "LinkUI.h"
#include "unistd.h"
#include <QPainter>
#include <QFile>
#include "Json.h"
#include "baseview.h"
#include <jcon/json_rpc_tcp_server.h>

class ModView : public BaseView
{
    Q_OBJECT
public:
    explicit ModView(QWidget *parent = nullptr);
    void initView(const QString &tip = 0);

protected:
    int replacePX(QString value);

    QTimer timer;
    uchar curBright;
    QVariantList mods;

    bool importantChange=false;
    int scale = 2;
    bool initMark = false;


public slots:
    void onTimer();

};

#endif // MODVIEW_H
