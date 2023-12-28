#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QMainWindow>

namespace Ui {
class Account;
}

class Account : public QMainWindow
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr);
    ~Account();
    void createID();

private slots:
    void on_CreateButton_clicked();
private:
    Ui::Account *ui;
    QString filePrefix = "c:/users/choim/documents";
};

#endif // ACCOUNT_H
