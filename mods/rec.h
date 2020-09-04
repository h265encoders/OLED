#ifndef REC_H
#define REC_H
#include "mod.h"

class ModREC : public Mods
{
public:
    explicit ModREC(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

};

#endif // REC_H
