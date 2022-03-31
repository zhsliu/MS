#include "result.h"
#include "ui_result.h"

Result::Result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
    //设置列
    ui->tableWidget->setColumnCount(2);
    //设置水平表头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "文件名" << "文件目录");
    //设置行
    ui->tableWidget->setRowCount(4);
    //设置具体内容
    //设置文件名列表
    QList<QString> nameList;
    nameList << "File009" << "File092" << "File273" << "File432" ;

    QStringList pathList;
    pathList << "doc/File009.txt" << "doc/File092.txt" << "doc/File273.txt" << "doc/File432.txt" ;

    for (int i = 0; i < 4; i++) {
       int col = 0;
       ui->tableWidget->setItem(i,col++,new QTableWidgetItem( nameList[i] ));
       ui->tableWidget->setItem(i,col++,new QTableWidgetItem(pathList.at(i)));
    }

}

Result::~Result()
{
    delete ui;
}
