#include "searchresult.h"
#include "ui_searchresult.h"

searchResult::searchResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchResult)
{
    ui->setupUi(this);
    //设置列
    //ui->searchResult->setColumnCount(2);
    ui->search_result->setColumnCount(2);
    //设置水平表头
    ui->search_result->setHorizontalHeaderLabels(QStringList() << "文件名" << "文件目录");
    //设置行
    ui->search_result->setRowCount(4);
    //设置具体内容
    //设置文件名列表
    QList<QString> nameList;
    nameList << "File009" << "File092" << "File273" << "File432" ;

    QStringList pathList;
    pathList << "doc/File009.txt" << "doc/File092.txt" << "doc/File273.txt" << "doc/File432.txt" ;

    for (int i = 0; i < 4; i++) {
       int col = 0;
       ui->search_result->setItem(i,col++,new QTableWidgetItem( nameList[i] ));
       ui->search_result->setItem(i,col++,new QTableWidgetItem(pathList.at(i)));
    }

}

searchResult::~searchResult()
{
    delete ui;
}
