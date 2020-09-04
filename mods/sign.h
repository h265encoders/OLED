#ifndef SIGN_H
#define SIGN_H
#include "mod.h"

class ModHSIGN : public Mods
{
public:
    explicit ModHSIGN(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

private:
    QString fac = nullptr;
};


class ModSSIGN : public Mods
{
public:
    explicit ModSSIGN(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

private:
    QString fac = nullptr;
};

#endif // SIGN_H
