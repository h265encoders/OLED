
#include <QApplication>
#include "view.h"
#include "rpc.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Link::init(false);

    RPC::create()->initRPC();
    View::initView();
    //LinkUI::initOLED(View::initView(),"ZJY64128",1,true);
    //LinkUI::refreshOLED();
    return a.exec();
}
