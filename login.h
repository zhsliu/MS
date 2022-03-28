#ifndef LOGIN_H
#define LOGIN_H

//#include <QWidget>
#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QDialog *parent = nullptr);
    ~Login();

private slots:
    void on_SignBtn_clicked();

    void on_LoginBtn_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
