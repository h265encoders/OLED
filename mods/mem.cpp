#include "mem.h"

REGISTER_STATIC_CLASS(ModMEM)
ModMEM::ModMEM(Mods *parent) : Mods(parent){}
bool ModMEM::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    if(label == nullptr)
    {
        label = new QLabel(parent);
        label->setGeometry(left,top,width,height);
        label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        QFont font;
        font.setPointSize(8);
        label->setFont(font);
        label->setText("MEM:0%");
        label->show();
    }

    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("enc.getSysState");
    if (result->isSuccess()) {
        QVariantMap res = result->result().toMap();
        label->setText("MEM:"+QString::number(res["mem"].toInt())+"%");
    }
    return importantChange;
}
