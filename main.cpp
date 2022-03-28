#include "mainwindow.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w; //主界面
    Login l;    //登录界面
    l.show();
    if(l.exec() == QDialog::Accepted ){
        w.show();
        return a.exec();
    }
}
