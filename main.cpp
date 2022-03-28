#include "mainwindow.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w; //主界面
    //bool re = false;
    Login l;    //登录界面
    l.show();
    //re = l.varifyPassword();
    if(Login:: == true ){
        w.show();
    }
    return a.exec();
}
