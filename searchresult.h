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

    int do_search( std::vector<std::string> Result);

private:
    Ui::searchResult *ui;
};

#endif // SEARCHRESULT_H
