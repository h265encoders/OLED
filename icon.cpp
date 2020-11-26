#include "icon.h"

InputIcon::InputIcon(QWidget *parent) : QWidget(parent)
{
    this->resize(20,20);
}
void InputIcon::upDraw(QString iconPath, double scale)
{
    path = iconPath;
    scl = scale;

    this->update();
    this->show();
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
}
