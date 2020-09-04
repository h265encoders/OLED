#ifndef INPUT_H
#define INPUT_H
#include "mod.h"
#include "icon.h"

struct Mark
{
    Mark() {}
    double hScale = 1;
    int topDiff = 0;
    double sScale = 1;
    int interval = 0;

};

class ModINPUT : public Mods
{
public:
    explicit ModINPUT(Mods *parent = 0);
    bool init(const double &left,const double &top,const double &width,const double &height,QWidget *parent);

    void initMarkMap(const int &index,const double &hScale,const int &topDiff,const double &sScale,const int &interval);

private:
    QString hIcon = ":/icon/hdmi.png";
    QString sIcon = ":/icon/sdi.png";
    QString nIcon = ":/icon/hdmi2.png";

    QMap<int,InputIcon*> iconMap;
    QMap<int,Mark*> markMap;

};

#endif // INPUT_H
