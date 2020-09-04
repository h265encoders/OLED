#include "sign.h"
#include <QProcess>

static QString handleFac()
{
    QString com = "cat /link/config/fac";
    QProcess proc;
    QStringList argList;
    argList << "-c" << com;
    proc.start("/bin/sh",argList);
    proc.waitForFinished();
    proc.waitForReadyRead();
    QByteArray procOutput = proc.readAll();
    proc.close();
    return QString(procOutput);
}


REGISTER_STATIC_CLASS(ModHSIGN)
ModHSIGN::ModHSIGN(Mods *parent) : Mods(parent){}
bool ModHSIGN::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    if(label == nullptr)
    {
        label = new QLabel(parent);
        QFont font;
        font.setPointSize(8);
        label->setGeometry(left,top,width,height);
        label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        label->setFont(font);
        label->setText("HDMI: No input");
        fac = handleFac().replace("\n","");
    }
    importantChange = false;
    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("enc.getInputState");
    if (result->isSuccess()) {
        QVariantList res = result->result().toList();

        for(int i=0;i<res.count();i++)
        {
            QVariantMap map = res[i].toMap();
            QString protocol = map["protocol"].toString();
            if(protocol == "HDMI")
            {
                if(map["avalible"].toBool())
                {
                    QString str;
                    str=str.sprintf("HDMI:%dx%d@%d",map["width"].toInt(),map["height"].toInt(),map["framerate"].toInt());
                    str=str+(map["interlace"].toBool()?"I":"P");
                    if(label->text()!=str)
                    {
                        importantChange=true;
                        label->setText(str);
                    }
                }
                else
                {
                    if(label->text()!="HDMI: No input")
                    {
                        importantChange=true;
                        label->setText("HDMI: No input");
                    }
                }
                break;
            }
        }
    }
    return importantChange;
}


REGISTER_STATIC_CLASS(ModSSIGN)
ModSSIGN::ModSSIGN(Mods *parent) : Mods(parent){}
bool ModSSIGN::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    if(label == nullptr)
    {
        label = new QLabel(parent);
        QFont font;
        font.setPointSize(8);
        label->setGeometry(left,top,width,height);
        label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        label->setFont(font);
        label->setText("SDI: No Input");
        fac = handleFac().replace("\n","");
    }
    importantChange = false;
    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("enc.getInputState");
    if (result->isSuccess()) {
        QVariantList res = result->result().toList();
        for(int i=0;i<res.count();i++)
        {
            QVariantMap map = res[i].toMap();
            QString protocol = map["protocol"].toString();
            if(protocol == "SDI")
            {
                if(map["avalible"].toBool())
                {
                    QString str;
                    str=str.sprintf("SDI:%dx%d@%d",map["width"].toInt(),map["height"].toInt(),map["framerate"].toInt());
                    str=str+(map["interlace"].toBool()?"I":"P");
                    if(label->text()!=str)
                    {
                        importantChange=true;
                        label->setText(str);
                    }
                }
                else
                {
                    if(label->text()!="SDI: No input")
                    {
                        importantChange=true;
                        label->setText("SDI: No input");
                    }
                }
                break;
            }
        }
    }
    return importantChange;
}

