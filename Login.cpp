#include "Login.h"
#include "ui_Login.h"
#include <QMessageBox>
#include <QMap>
#include <QString>
#include <QFile>
#include <QFlag>
#include <QListWidget>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->listWidget->setCurrentItem(ui->listWidget->item(0));
}

Login::~Login()
{
    delete ui;
}


void Login::checkID() {
    QString lineId = ui->lineUsername->text();
    QString linePassword = ui->linePassword->text();
    QString lineType = ui->listWidget->currentItem()->text();
    QString dataId = "";
    QString dataPassword = "";
    QString dataType = "";
    QString flag = "false";
    QFile file(filePrefix +"/collegeEnrollment/Sources/idAndPassword.txt");

    try{
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            throw QString("Could not open file");
        } else {
            file.open(QIODevice::ReadOnly|QIODevice::Text);
        }

        QDataStream in (&file);
        in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        while(!in.atEnd()){
            in >> dataId >> dataPassword >> dataType;

            if(dataId == lineId && dataPassword == linePassword && dataType == lineType) {
                flag = "true";
                if (lineType == "Administrator") {
                    admin = new Admin(this);
                    admin->show();
                    break;
                } else if (lineType == "Student"){
                    student = new Student(this);
                    student->show();
                    student->createStudentFile(lineId);
                    student->studentCourses();
                    break;
                }
            }
        }
        if(flag == "false") {
            QMessageBox::warning(this, "Login","Incorrect UserType, password or ID");
        }

    } catch(QString sErr) {
        QMessageBox::warning(this, "File",sErr);
    }
    catch(std::exception& e){
        QMessageBox::warning(this, "Error",e.what());
    }

    file.close();
};

void Login::on_LogInButton_clicked()
{
    checkID();
}

void Login::on_CreateButton_clicked()
{
    account = new Account(this);
    account->show();
}

