#include "rotate.h"
#include <QMetaMethod>
#include "view.h"

REGISTER_STATIC_CLASS(OwnROTATE)
OwnROTATE::OwnROTATE(Owns *parent) : Owns(parent){}
void OwnROTATE::init(const QVariantList &param)
{
    LinkUI::setRotate(param[0].toInt());
}


