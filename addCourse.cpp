#include "addCourse.h"
#include "ui_addCourse.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

addCourse::addCourse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addCourse)
{
    ui->setupUi(this);
}

addCourse::~addCourse()
{
    delete ui;
}

void addCourse::on_updateButton_clicked()
{
    try {
        QString courseName =ui->lineName->text();
        QString instructor = ui->lineInstructor->text();
        QString profRate = ui->lineRate->text();
        QString meeting = ui->lineMeeting->text();
        QString credits = ui->lineCredits->text();
        int seats = ui->lineSeats->text().toInt();

        QFile file(filePrefix + "/collegeEnrollment/Sources/courseData.txt");
        if(!file.open(QFile::WriteOnly|QFile::Append|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            file.open(QFile::WriteOnly|QFile::Append|QFile::Text);
        }
        QTextStream out (&file);
        out << courseName << "\n"<< instructor << "\n" << profRate << "\n"
            << meeting << "\n"<< credits << "\n"<< seats << "\n";

        file.flush();
        file.close();

        QMessageBox::information(this,"Success","Successfully Update Course! Click Refresh Button");

    } catch(QString sErr) {
        QMessageBox::warning(this, "File",sErr);
    } catch(std::exception& e){
        QMessageBox::warning(this, "Error",e.what());
    }

}
