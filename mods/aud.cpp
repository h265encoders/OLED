#include "aud.h"

REGISTER_STATIC_CLASS(ModAUD)
ModAUD::ModAUD(Mods *parent) : Mods(parent){}
bool ModAUD::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    if(label == nullptr)
    {
        label = new QLabel(parent);
        QFont font;
        font.setPointSize(8);
        label->setGeometry(left,top,width,height);
        label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        label->setFont(font);
    }
    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("enc.getVolume");
    if (result->isSuccess()) {
        QVariantList list = result->result().toList();
        if(list.count()>0)
            label->setText("AUD:"+QString::number(list[0].toMap()["L"].toInt())+"db");
    }
    return importantChange;
}
