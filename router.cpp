#include "router.h"

void Router::init()
{
    viewMap["/modView"] = "ModView";
    viewMap["/tipView"] = "TipView";
}

void Router::linkTo(const QString &path, const QString &param)
{
    QMap<QString, QString>::const_iterator it;
    for(it = viewMap.constBegin(); it != viewMap.constEnd(); it++)
    {
        QString className = it.value();
        BaseView *view = BaseView::create(className);
        if(path != it.key())
        {
            view->hide();
            continue;
        }
        view->initView(param);
        view->show();
    }
}

