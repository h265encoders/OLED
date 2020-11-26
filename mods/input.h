#ifndef INPUT_H
#define INPUT_H

#include <QHBoxLayout>
#include "mod.h"
#include "icon.h"

struct Place
{
    Place() {}
    double scale = 1;
    int h_top = 0;
    int s_top = 0;
};

class ModINPUT : public Mods
{
public:
    explicit ModINPUT(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

    void initPlaceMap(const int &index,const double &scale,const int &ht,const int &st);

private:
    QString hIcon = ":/icon/hdmi.png";
    QString sIcon = ":/icon/sdi.png";
    QString nIcon = ":/icon/hdmi2.png";

    QWidget *iconBox = nullptr;
    QHBoxLayout *layout = nullptr;
    QMap<int,Place*> placeMap;

};

#endif // INPUT_H
