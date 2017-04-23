#include "App.h"
#include <QCoreApplication>
#include "DBConnPool.h"
#include "time.h"

int main(int argc, char * argv[])
{
    QCoreApplication app(argc, argv);
    srand((int)time(0));
    new App;

    DBConnPool::release();
    return app.exec();
}
