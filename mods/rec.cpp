#include "rec.h"

REGISTER_STATIC_CLASS(ModREC)
ModREC::ModREC(Mods *parent) : Mods(parent){}
bool ModREC::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    if(label == nullptr)
    {
        label = new QLabel(parent);
        label->setGeometry(left,top,width,height);
        label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        QFont font;
        font.setPointSize(8);
        label->setFont(font);
        label->setText("REC: OFF");
        label->show();
    }

    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("rec.isRecordState");
    if (result->isSuccess()) {
        //QVariantMap res = result->result().toMap();
        bool res = result->result().toBool();
        if(res)
            label->setText("REC: ON");
        else
            label->setText("REC: OFF");
    }

    return importantChange;
}
