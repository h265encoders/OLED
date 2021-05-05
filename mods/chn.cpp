#include "chn.h"


REGISTER_STATIC_CLASS(ModCHN)
ModCHN::ModCHN(Mods *parent) : Mods(parent){}

bool ModCHN::init(const double &left, const double &top, const double &width, const double &height, QWidget *parent)
{

    if(label == nullptr)
    {
        label = new QLabel(parent);
        label->setGeometry(left,top,width,height);
        label->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(30);
        label->setFont(font);
        label->setText("01");
        QString qss="QLabel{background-color:white;color:black;}";
        label->setStyleSheet(qss);
        label->show();
    }


    return false;
}
