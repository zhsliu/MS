#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QWidget>

namespace Ui {
class searchResult;
}

class searchResult : public QWidget
{
    Q_OBJECT

public:
    explicit searchResult(QWidget *parent = nullptr);
    ~searchResult();

private:
    Ui::searchResult *ui;
};

#endif // SEARCHRESULT_H
