#include "ipadr.h"

REGISTER_STATIC_CLASS(ModIP)
ModIP::ModIP(Mods *parent) : Mods(parent){}
bool ModIP::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    if(label == nullptr)
    {
        label = new QLabel(parent);
        label->setGeometry(left,top,width,height);
        label->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(9);
        label->setFont(font);
        label->setText("0.0.0.0");
        label->show();
    }

    QVariantMap net=Json::loadFile("/link/config/net.json").toMap();
    if(QFile::exists("/sys/class/net/wlan0/operstate"))
        net=Json::loadFile("/link/config/wifi.json").toMap();

    importantChange = false;
    if(label->text() != net["ip"].toString())
    {
        label->setText(net["ip"].toString());
        importantChange=true;
    }
    return importantChange;
}
