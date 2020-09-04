#ifndef DISK_H
#define DISK_H
#include "mod.h"

class ModDISK : public Mods
{
public:
    explicit ModDISK(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

};

#endif // DISK_H
