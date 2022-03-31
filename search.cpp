#include "search.h"
#include "ui_search.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QFile"

search::search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
    //按钮相应
    connect(ui->openFile,&QPushButton::clicked,this,[=](){
        //文件路径获取
       QString filePath = QFileDialog::getOpenFileName(this,"选择文件","./","(*.txt)");
       //路径空判断
       if( filePath.isEmpty() ){
           QMessageBox::warning(this,"打开失败","文件路径不能为空");
           return ;
       }else{
       ui->fileLine->setText(filePath); //文件路径显示
       }
       //文件内容展示
       QFile file(filePath) ;
       file.open(QIODevice::ReadOnly);
       QByteArray arr;
       arr = file.readAll();
       ui->fileContent->setText(arr);

    });
}

search::~search()
{
    delete ui;
}

void search::on_upload_btn_clicked()
{
    QMessageBox::warning(this,"提示","上传完成");
}
