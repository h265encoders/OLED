#ifndef BR_H
#define BR_H
#include "mod.h"

class ModBR : public Mods
{
public:
    explicit ModBR(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);
};

#endif // BR_H
