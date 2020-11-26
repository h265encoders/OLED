#ifndef TIPVIEW_H
#define TIPVIEW_H

#include "object.h"
#include "baseview.h"
#include <QLabel>

class TipView : public BaseView
{
    Q_OBJECT
public:
    explicit TipView(BaseView *parent = 0);
    void initView(const QString &tip = 0);
    QLabel *label = nullptr;
};

#endif // TIPVIEW_H
