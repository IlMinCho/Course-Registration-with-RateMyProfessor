#ifndef STUDENT_H
#define STUDENT_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

namespace Ui {
class Student;
}

class Student : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr);
    ~Student();
    void studentCourses();
    void createStudentFile(QString studentId);

private slots:
    void on_refreshButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

private:
    QString studentId;
    Ui::Student *ui;
    void coursesDisplay();
    QString filePrefix = "c:/users/choim/documents";

    enum Column
        {
           COURSE,INSTRUCTOR,RATE,MEETING,
               CREDITS,SEATS
        };
};

#endif // STUDENT_H
