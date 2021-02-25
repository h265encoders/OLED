#include "input.h"

REGISTER_STATIC_CLASS(ModINPUT)
ModINPUT::ModINPUT(Mods *parent) : Mods(parent)
{
    initPlaceMap(1,0.9,4,0);
    initPlaceMap(2,0.9,4,0);
    initPlaceMap(3,0.9,4,0);
    initPlaceMap(4,0.9,4,0);
    initPlaceMap(5,0.9,4,0);
    initPlaceMap(6,0.9,4,0);
    initPlaceMap(7,0.82,4,0);
    initPlaceMap(8,0.75,4,1);
    initPlaceMap(9,0.65,5,2);
}


bool ModINPUT::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{
    std::shared_ptr<jcon::JsonRpcResult> result = RPC::create()->rpcClient->call("enc.getInputState");
    if (result->isSuccess()) {

        if(iconBox == nullptr)
        {
            iconBox = new QWidget(parent);
            iconBox->setGeometry(left,top,width,height);
            iconBox->show();
        }
        //弹簧不起作用，为每个控件指定位置
        QVariantList res = result->result().toList();
        int count = res.count();
        Place *place = placeMap[count];
        for(int i=0;i<count;i++)
        {
            InputIcon *icon = getIconByIndex(i);
            int interval = (width - count*icon->width()*place->scale)/(count+1);
            if(count == 7)
                interval = 2;
            if(count > 7)
                interval =1;
            int marginLeft = interval * (i+1) + i*icon->width()*place->scale;
            QVariantMap map = res[i].toMap();
            if(map["avalible"].toBool())
            {
                QString protocol = map["protocol"].toString();
                if(protocol == "HDMI")
                {
                    icon->upDraw(hIcon,place->scale);
                    icon->move(marginLeft,place->h_top);
                }

                if(protocol == "SDI")
                {
                    icon->upDraw(sIcon,place->scale);
                    icon->move(marginLeft,place->s_top);
                }
            }
            else
            {
                icon->upDraw(nIcon,place->scale);
                icon->move(marginLeft,place->h_top+1);
            }
        }
    }
    return importantChange;
}

void ModINPUT::initPlaceMap(const int &index, const double &scale,const int &ht,const int &st)
{
    Place *place = new Place;
    place->scale = scale;
    place->h_top = ht;
    place->s_top = st;
    placeMap[index] = place;
}

InputIcon *ModINPUT::getIconByIndex(const int &index)
{
    if(iconList.count() > index)
        return iconList[index];

    InputIcon *icon = new InputIcon(iconBox);
    iconList << icon;
    return icon;
}


