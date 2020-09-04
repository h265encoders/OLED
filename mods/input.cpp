#include "input.h"

REGISTER_STATIC_CLASS(ModINPUT)
ModINPUT::ModINPUT(Mods *parent) : Mods(parent)
{
    initMarkMap(9,0.65,4,0.65,14);
    initMarkMap(8,0.75,4,0.75,16);
    initMarkMap(7,0.85,4,0.85,18);
    initMarkMap(6,0.9,4,0.9,20);
}


bool ModINPUT::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("enc.getInputState");
    if (result->isSuccess()) {
        QVariantList res = result->result().toList();
        int count = res.count();
//        count=9;
        if(count <= 6 )
            count = 6;
        Mark *mark = markMap[count];
        for(int i=0;i<res.count();i++)
        {
            QVariantMap map = res[i].toMap();
//            QVariantMap map;
            QString protocol = map["protocol"].toString();

            InputIcon *icon = nullptr;
            if(iconMap.contains(i))
                icon = iconMap[i];
            else
            {
                icon = new InputIcon(parent);
                iconMap[i] = icon;
            }

            if(map["avalible"].toBool())
            {
                if(protocol == "HDMI")
                {
                    icon->upDraw(hIcon,0,mark->hScale);
                    icon->move(left + i*mark->interval,top+mark->topDiff);
                }

                if(protocol == "SDI")
                {
                    icon->upDraw(sIcon,0,mark->sScale);
                    icon->move(left + i*mark->interval,top);
                }
            }
            else
            {
//                if(i>2)
//                {
//                    icon->upDraw(hIcon,0,mark->hScale);
//                    icon->move(left + i*mark->interval,top+mark->topDiff);
//                }
//                else
//                {
//                    icon->upDraw(sIcon,0,mark->hScale);
//                    icon->move(left + i*mark->interval,top);
//                }
                icon->upDraw(nIcon,0,mark->hScale);
                icon->move(left + i*mark->interval,top+mark->topDiff);
            }

            icon->show();
        }
    }
    return importantChange;
}

void ModINPUT::initMarkMap(const int &index, const double &hScale, const int &topDiff, const double &sScale, const int &interval)
{
    Mark *mark = new Mark;
    mark->hScale = hScale;
    mark->sScale = sScale;
    mark->topDiff = topDiff;
    mark->interval = interval;
    markMap[index] = mark;
}

