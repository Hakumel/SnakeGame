/*Program:
**    Classic Snake Game.
**
**Date        Author     Version
**2019/9/18   Hakumel    ver 0.1
**
**Possible problems:
**    If compilation "frame = new Wall(centralWidget);" fails，
**  replace it with the following code:
**  Wall* frame=Wall::getdata();
**  frame->setParent(centralWidget);
*/
#include "mainwindow.h"
#include <QApplication>
#include "wall.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
