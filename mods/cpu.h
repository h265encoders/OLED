#ifndef CPU_H
#define CPU_H
#include "mod.h"

class ModCPU : public Mods
{
public:
    explicit ModCPU(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

};

#endif // CPU_H
