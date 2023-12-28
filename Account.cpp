#include "Account.h"
#include "ui_Account.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QRadioButton>

Account::Account(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);
}

Account::~Account()
{
    delete ui;
}

void Account::createID()
{
    try {
        QString userType = "";
        if(ui->radioStudent->isChecked()) {
            userType = "Student";
        } else if(ui->radioAdmin->isChecked()) {
            userType ="Administrator"; 
        } else {
            QMessageBox::warning(this, "check","You have to check userType");
        }
        QString iD =ui->lineID->text();
        QString password = ui->linePassword->text();
        QString userName = ui->lineName->text();
        QString gender = ui->lineGender->text();
        QString major = ui->lineMajor->text();
        QString email = ui->lineEmail->text();


        QFile fileId( filePrefix + "/collegeEnrollment/Sources/idAndPassword.txt");
        if(!fileId.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
        {
             throw QString("Could not open file");
        } else {
            fileId.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text);
        }
        QDataStream outId (&fileId);
        outId.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        outId << iD << password << userType;

        fileId.flush();
        fileId.close();


        QFile fileUser( filePrefix + "/collegeEnrollment/Sources/userData.txt");
        if(!fileUser.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
        {
             throw QString("Could not open file");
        } else {
            fileUser.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text);
        }
        QDataStream outUser (&fileUser);
        outUser.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        outUser << iD << userName << gender << major << email;

        fileUser.flush();
        fileUser.close();
    } catch(QString sErr) {
    QMessageBox::warning(this, "File",sErr);
    }catch(std::exception& e){
    QMessageBox::warning(this, "Error",e.what());
    }

}


void Account::on_CreateButton_clicked()
{
    createID();
    QMessageBox::information(this,"Success","Successfully Create Account!");
}

