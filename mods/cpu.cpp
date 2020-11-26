#include "cpu.h"

REGISTER_STATIC_CLASS(ModCPU)
ModCPU::ModCPU(Mods *parent) : Mods(parent){}
bool ModCPU::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("enc.getSysState");
    if (result->isSuccess()) {
        QVariantMap res = result->result().toMap();

        QFont font;
        font.setPointSize(8);
        if(label == nullptr)
        {
            label = new QLabel(parent);
            label->setGeometry(left,top,width,height);
            label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            label->setFont(font);
            label->show();
        }
        label->setText("CPU:"+QString::number(res["cpu"].toInt())+"%");
    }
    return importantChange;
}
