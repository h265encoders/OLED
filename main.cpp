
#include <QApplication>
#include "view.h"
#include "rpc.h"
#include "router.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Link::init(false);

    RPC::create()->initRPC();

    Router::init();
    Router::linkTo("/modView");
    return a.exec();
}
