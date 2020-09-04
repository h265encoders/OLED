#include "br.h"

REGISTER_STATIC_CLASS(ModBR)
ModBR::ModBR(Mods *parent) : Mods(parent){}
bool ModBR::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
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
    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("push.getState");
    if (result->isSuccess()) {
        QVariantList list = result->result().toMap()["speed"].toList();
        if(list.count()>0)
            label->setText("BR:"+QString::number(list[0].toInt())+"k");
    }
    return importantChange;
}
