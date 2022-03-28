#include "login.h"
#include "ui_login.h"
#include "QMessageBox"

Login::Login(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

//密码验证
void Login::on_LoginBtn_clicked()
{
    //验证密码
    if(ui->userLine->text() == "1" && ui->passwordLine->text() == "1"){
        Login::accept();
    }else {
        QMessageBox::warning(this,"警告","密码或用户名错误");
        ui->userLine->clear();
        ui->passwordLine->clear();
        ui->userLine->setFocus();
    }
}

void Login::on_SignBtn_clicked()
{
    close();
}
