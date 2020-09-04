#ifndef AUD_H
#define AUD_H
#include "mod.h"

class ModAUD : public Mods
{
public:
    explicit ModAUD(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

};

#endif // AUD_H
