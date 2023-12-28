#ifndef EDITCOURSE_H
#define EDITCOURSE_H

#include <QMainWindow>
#include <QItemSelection>
#include <QTableWidget>

namespace Ui {
class editCourse;
}

class editCourse : public QMainWindow
{
    Q_OBJECT

public:
    explicit editCourse(QWidget *parent = nullptr);
    ~editCourse();
    void setSelectedData(QTableWidget *selectedWidget);

private slots:
    void on_editButton_clicked();

private:
    Ui::editCourse *ui;
    int index;
    QString filePrefix = "c:/users/choim/documents";
};

#endif // EDITCOURSE_H
