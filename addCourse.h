#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QMainWindow>

namespace Ui {
class addCourse;
}

class addCourse : public QMainWindow
{
    Q_OBJECT

public:
    explicit addCourse(QWidget *parent = nullptr);
    ~addCourse();

private slots:
    void on_updateButton_clicked();

private:
    Ui::addCourse *ui;
    QString filePrefix = "c:/users/choim/documents";
};

#endif // ADDCOURSE_H
