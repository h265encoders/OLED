#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QTimer>
#include "LinkUI.h"
#include "unistd.h"
#include <QPainter>
#include <QFile>
#include "Json.h"
#include <jcon/json_rpc_tcp_server.h>

class View : public QWidget
{
    Q_OBJECT
public:
    static View *initView();

protected:
    explicit View(QWidget *parent = nullptr);
    int replacePX(QString value);

    QTimer timer;
    uchar curBright;
    QVariantList mods;

    bool importantChange=false;
    int scale = 2;


public slots:
    void onTimer();

};

#endif // VIEW_H
