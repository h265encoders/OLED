#ifndef MEM_H
#define MEM_H
#include "mod.h"

class ModMEM : public Mods
{
public:
    explicit ModMEM(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

};

#endif // MEM_H
