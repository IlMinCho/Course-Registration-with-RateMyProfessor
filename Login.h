#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "Admin.h"
#include "Account.h"
#include "Student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    void checkID();

private slots:
    void on_LogInButton_clicked();
    void on_CreateButton_clicked();
private:
    Ui::Login *ui;
    Admin *admin;
    Account *account;
    Student *student;
    QString filePrefix = "c:/users/choim/documents";
};
#endif // LOGIN_H
