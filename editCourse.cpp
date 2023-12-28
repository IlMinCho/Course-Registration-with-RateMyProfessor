#include "editCourse.h"
#include "ui_editCourse.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

editCourse::editCourse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::editCourse)
{
    ui->setupUi(this);
}

editCourse::~editCourse()
{
    delete ui;
}

void editCourse::on_editButton_clicked()
{
    try {
        QString courseName =ui->lineName->text();
        QString instructor = ui->lineInstructor->text();
        QString profRate = ui->lineRate->text();
        QString meeting = ui->lineMeeting->text();
        QString credits = ui->lineCredits->text();
        int seats = ui->lineSeats->text().toInt();

        QString dataText;

        QFile file(filePrefix + "/collegeEnrollment/Sources/courseData.txt");
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            file.open(QFile::ReadOnly|QFile::Text);
        }
        QTextStream in (&file);
        for (int i=0; i<index; i++) {
            dataText.append(in.readLine()+"\n");
            dataText.append(in.readLine()+"\n");
            dataText.append(in.readLine()+"\n");
            dataText.append(in.readLine()+"\n");
            dataText.append(in.readLine()+"\n");
            dataText.append(in.readLine()+"\n");
        }
        for (int i=0; i<6; i++) {in.readLine();}
        dataText.append(courseName+"\n");
        dataText.append(instructor+"\n");
        dataText.append(profRate+"\n");
        dataText.append(meeting+"\n");
        dataText.append(credits+"\n");
        dataText.append(QString::number(seats)+"\n");

        while(!in.atEnd()) {
            dataText.append(in.readLine()+"\n");
        }

        file.close();

        QFile writefile(filePrefix + "/collegeEnrollment/Sources/courseData.txt");
        if(!file.open(QFile::WriteOnly|QFile::Truncate|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            file.open(QFile::WriteOnly|QFile::Truncate|QFile::Text);
        }
        QTextStream out (&file);
        out << dataText;

        writefile.flush();
        writefile.close();

        QMessageBox::information(this,"Success","Successfully Edited the Course! Click Refresh Button");

    } catch(QString sErr) {
    QMessageBox::warning(this, "File",sErr);
    } catch(std::exception& e){
    QMessageBox::warning(this, "Error",e.what());
    }
}

void editCourse::setSelectedData(QTableWidget *selectedWidget)
{
    index = selectedWidget->currentRow();
    QString courseName, instructor, profRate, meeting, credits, seats;

    try {
            QFile file(filePrefix + "/collegeEnrollment/Sources/courseData.txt");
            if(!file.open(QFile::ReadOnly|QFile::Text))
            {
                 throw QString("Could not open file");
            } else {
                file.open(QFile::ReadOnly|QFile::Text);
            }
            QTextStream in (&file);
            for ( int i=0; i<index+1; i++) {
                courseName = in.readLine();
                instructor = in.readLine();
                profRate = in.readLine();
                meeting = in.readLine();
                credits = in.readLine();
                seats = in.readLine();
            }
            file.flush();
            file.close();
        } catch(QString sErr) {
        QMessageBox::warning(this, "File",sErr);
        } catch(std::exception& e){
        QMessageBox::warning(this, "Error",e.what());
        }

     ui->lineName->setText(courseName);
     ui->lineInstructor->setText(instructor);
     ui->lineRate->setText(profRate);
     ui->lineMeeting->setText(meeting);
     ui->lineCredits->setText(credits);
     ui->lineSeats->setText(seats);

}
