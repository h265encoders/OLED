#include "gpio.h"
#include <QMetaMethod>

REGISTER_STATIC_CLASS(OwnGPIO)
OwnGPIO::OwnGPIO(Owns *parent) : Owns(parent){}
void OwnGPIO::init(const QVariantList &param)
{
    gpio=Link::create("GPIO");
    gpio->start();
    gpio->invoke("registEvent","GPIO0_0").toBool();
    gpio->invoke("registEvent","GPIO0_1").toBool();
    connect(gpio,SIGNAL(newEvent(QString,QVariant)),this,SLOT(onGPIO(QString,QVariant)));

    pressTimer = new QTimer;
    connect(pressTimer,&QTimer::timeout,[=](){

            pressTimer->stop();
            QVariantList config = RPC::create()->config;
            for(int i=0;i<config.count();i++)
            {
                QVariantMap cfg=config[i].toMap();
                if(btnName==cfg["gpio"].toString())
                {
                    if(!cfg["press"].toString().isEmpty())
                        RPC::create()->rpcClient->call(cfg["press"].toString());
                    break;
                }
            }

        });
}


void OwnGPIO::onGPIO(QString type, QVariant info)
{
//    if(btnName == nullptr)
    btnName = info.toString();

    if(type == "down")
        pressTimer->start(5000);

    if(type == "up")
    {
        QVariantList config = RPC::create()->config;
        if(pressTimer->isActive())
        {
            pressTimer->stop();
            for(int i=0;i<config.count();i++)
            {
                QVariantMap cfg=config[i].toMap();
                if(btnName==cfg["gpio"].toString())
                {
                    if(!cfg["click"].toString().isEmpty())
                        RPC::create()->rpcClient->call(cfg["click"].toString());
                    break;
                }
            }
        }
    }
}

