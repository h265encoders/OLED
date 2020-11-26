#include "tipview.h"

REGISTER_CLASS(TipView)
TipView::TipView(BaseView *parent) : BaseView(parent){}
void TipView::initView(const QString &tip)
{
    BaseView::initView();
    if(label == nullptr)
    {
        label = new QLabel(this);
        label->setGeometry(0,0,this->width(),this->height());
        label->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(9);
        label->setFont(font);
        label->show();
    }
    label->setText(tip);
}
