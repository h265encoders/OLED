#ifndef TEMP_H
#define TEMP_H
#include "mod.h"

class ModTEMP : public Mods
{
public:
    explicit ModTEMP(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);
};

#endif // TEMP_H
