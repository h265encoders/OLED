#ifndef IP_H
#define IP_H
#include "mod.h"

class ModIP : public Mods
{
public:
    explicit ModIP(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

};

#endif // IP_H
