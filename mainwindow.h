#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Data.h"
#include <QMainWindow>
#include <search.h>
#include <aboutdialog.h>
#include "result.h"
#include "searchresult.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int do_search( std::vector<std::string> Result ,Node *root);
    void read();
    Node *file2tree( FILE *fp );
    Node *root = new Node();



private slots:
    void on_action_8_triggered();

    void on_actionaction_4_triggered();

    void on_action_7_triggered();

    void on_do_search_btn_clicked();

    void on_actionaction_1_triggered();

    void on_actionaction_2_triggered();

    void on_action_6_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    search *do_search_btn ;
    AboutDialog *about;
    Result *res;
    searchResult *seres;


};

#endif // MAINWINDOW_H
