#include "icon.h"

InputIcon::InputIcon(QWidget *parent) : QWidget(parent){}
void InputIcon::upDraw(QString iconPath, int rotate, double scale)
{
    path = iconPath;
    rot = rotate;
    scl = scale;
    update();
}
void InputIcon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(path);

    if(path.contains("hdmi"))
    {
        pix = pix.scaled(20*scl,7*scl,Qt::KeepAspectRatio);
        painter.drawPixmap(0,0,20*scl,7*scl,pix);
    }
    else
    {
        pix = pix.scaled(18*scl,16*scl,Qt::KeepAspectRatio);
        painter.drawPixmap(0,0,18*scl,16*scl,pix);
    }

//    if(rot == 90)
//    {
//        painter.translate(10,0);
//        painter.rotate(90);
//    }
//    if(path.contains("sdi"))
//        painter.drawPixmap(0,0,18*0.8,16*0.8,pix);
//    else
//        painter.drawPixmap(0,0,20,7,pix);
}
