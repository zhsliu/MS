#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(ui->LoginBtn,&QPushButton::clicked,this,[=](){
//        bool re = varifyPassword();

    });
}

Login::~Login()
{
    delete ui;
}

//密码验证
void Login::on_LoginBtn_clicked()
{

}
