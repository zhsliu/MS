#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include "QAction"
#include "search.h"
#include "QWidget"
#include "aboutdialog.h"
#include "QStackedWidget"
#include "QMessageBox"
#include "gen_data.cpp"
#include "gen_tree.cpp"
#include "do_search.cpp"
#include "result.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->setFixedSize(600,500);

    //状态栏添加文字
    QLabel *state_msg = new QLabel(this);
    state_msg->setMinimumSize(state_msg->sizeHint()); //设置label属性
    state_msg->setAlignment(Qt::AlignHCenter);        //设置label属性
    state_msg->setText("欢迎使用!!");                  //设置label内容
    this->statusBar()->addWidget(state_msg);          //将label添加至状态栏左侧

    //上传功能打开生成文件
    connect(ui->action_5,&QAction::triggered,this,[=](){
        searchbtn = new search;
        searchbtn->show();
    });

    ui->stackedWidget->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}



//帮助
void MainWindow::on_action_8_triggered()
{
    about = new AboutDialog;
    about->show();
}

//退出
void MainWindow::on_actionaction_4_triggered()
{
    close();
}

//检索功能
void MainWindow::on_action_7_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_do_search_btn_clicked()
{
    QMessageBox::StandardButton return_btn = QMessageBox::information(this,"提示","正在检索，请稍等。。",QMessageBox::Yes);
//    do_search();
    if(return_btn == QMessageBox::Yes)
    {
        seres = new searchResult;
        seres->show();
    }
}

//生成数据
void MainWindow::on_actionaction_1_triggered()
{
    gen_data();
    QMessageBox::information(nullptr,"提示","数据生成完成",QMessageBox::Yes);

}

//生成树
void MainWindow::on_actionaction_2_triggered()
{
    gen_tree();
    QMessageBox::information(this,"提示","密钥生成成功");
}

void MainWindow::on_action_6_triggered()
{
    res = new Result;
    res->show();

}
