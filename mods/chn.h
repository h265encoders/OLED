#ifndef MODCHN_H
#define MODCHN_H
#include "mod.h"

class ModCHN : public Mods
{
public:
    explicit ModCHN(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);
};

#endif // MODCHN_H
