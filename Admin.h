#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "addCourse.h"
#include "editCourse.h"

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_refreshButton_clicked();

private:
    Ui::Admin *ui;
    QString filePrefix = "c:/users/choim/documents";
    addCourse *addCourse;
    editCourse *editCourse;

    void coursesDisplay();
    void rateDisplay();

    enum Column
        {
           COURSE,INSTRUCTOR,RATE,MEETING,
               CREDITS,SEATS
        };
};

#endif // ADMIN_H
