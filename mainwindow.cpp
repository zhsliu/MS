#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include "QAction"
#include "search.h"
#include "QWidget"
#include "aboutdialog.h"
#include "QStackedWidget"
#include "QMessageBox"
#include "result.h"
#include <iostream>
#include <string>
#include <vector>
#include "strSplit.cpp"
#include "gen_data.cpp"
#include "gen_tree.h"
#include "qdebug.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //状态栏添加文字
    read();
    QLabel *state_msg = new QLabel(this);
    state_msg->setMinimumSize(state_msg->sizeHint()); //设置label属性
    state_msg->setAlignment(Qt::AlignHCenter);        //设置label属性
    state_msg->setText("欢迎使用!!");                  //设置label内容
    this->statusBar()->addWidget(state_msg);          //将label添加至状态栏左侧

    //上传功能打开生成文件
    connect(ui->action_5,&QAction::triggered,this,[=](){
        do_search_btn = new search;
        do_search_btn->show();
    });

    ui->stackedWidget->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read(){
    FILE *fp;
    fp = fopen("../tree.txt", "r");
    root = file2tree(fp);
}

Node * MainWindow::file2tree( FILE *fp ) {
    int i, l, r;
    Node tn;

    if( feof(fp) != 0 ) return nullptr;//文件结束返回非0
    // ID
    fscanf(fp, "%d ", &tn.ID);
    // D
    for( i = 0; i < DICT_SIZE; i++ ) {
        fscanf(fp, "%lf ", &tn.D[0][i]);//将fp的内容读出
        fscanf(fp, "%lf ", &tn.D[1][i]);
    }
    // 指针
    fscanf(fp, "%d %d ", &l, &r);
    // FID
    fscanf(fp, "%d ", &tn.FID);
    // 递归调用
    if( l != -1 )//不是叶子节点
        tn.Pl = file2tree( fp );
    else
        tn.Pl = nullptr;
    if( r != -1 )
        tn.Pr = file2tree( fp );
    else
        tn.Pr = nullptr;
    // 检查左右孩子的身份
    if( (tn.Pl != nullptr && l != tn.Pl->ID)
            || (tn.Pr != nullptr && r != tn.Pr->ID ) ) {
        printf("Error at reading Node %3d from file\n", tn.ID);
    }

    return insert(&tn);
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
    QMessageBox::StandardButton return_btn;
    QString str_qt = ui->lineEdit->text();
    std::string str = str_qt.toStdString();
    //std::cout << str << "\n";
    if(str_qt == nullptr ){
        QMessageBox::warning(this,"警告" , "内容不能为空");
    }else{
        return_btn = QMessageBox::information(this,"提示","正在检索，请稍等。。",QMessageBox::Yes);
        std::string pattern(" ");

            std::vector<std::string> result = split(str,pattern);
            //std::cout << result[0] << " " << result[1] << std::endl;

//            if(do_search(result) == 2){
//                    QMessageBox::warning(this,"警告" , "格式错误");
//            }
            do_search(result,root);
    }
    ui->stackedWidget->setCurrentIndex(2);
//    if(return_btn == QMessageBox::Yes)
//    {
//        seres = new searchResult;
//        seres->show();
//    }
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
//    res = new Result;
//    res->show();
    ui->stackedWidget->setCurrentIndex(2);

}



void MainWindow::on_pushButton_clicked()
{
    QMessageBox::information(this,"提示","下载成功");
    ui->third_result->setRowCount(0);
}
