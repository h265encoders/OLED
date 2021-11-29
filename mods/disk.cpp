#include "disk.h"

REGISTER_STATIC_CLASS(ModDISK)
ModDISK::ModDISK(Mods *parent) : Mods(parent){}
bool ModDISK::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    if(label == nullptr)
    {
        label = new QLabel(parent);
        label->setGeometry(left,top,width,height);
        label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        QFont font;
        font.setPointSize(8);
        label->setFont(font);
        label->setText("DISK: -- / --");
    }

    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("rec.getState");
    if (result->isSuccess()) {
        QVariantMap res = result->result().toMap();
        QString used = res["used"].toString();
        QString total = res["total"].toString();
        label->setText("DISK: "+used+" / "+total);
        label->show();
    }

    return importantChange;
}
