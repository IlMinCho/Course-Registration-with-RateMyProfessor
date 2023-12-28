#include "Admin.h"
#include "ui_Admin.h"

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    coursesDisplay();
    rateDisplay();
}

Admin::~Admin()
{
    delete ui;
}

void Admin::coursesDisplay()
{
    try {
        QTableWidget *table = ui->tableWidget;
        QStringList tableHeader;

        tableHeader << "Course Name" << "Instructor" << "Prof Rate" << "Meeting information"
               << "Credits" << "Avail Seats";
        table->clear();
        table->setColumnCount(6);
        table->setRowCount(0);
        table->setHorizontalHeaderLabels(tableHeader);
        table->setSelectionMode(QAbstractItemView::ExtendedSelection);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setTextElideMode(Qt::ElideRight);

        QString courseName;
        QString instructor;
        QString profRate;
        QString meeting;
        QString credits;
        QString seats;

        QFile file(filePrefix + "/collegeEnrollment/Sources/courseData.txt");
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            file.open(QFile::ReadOnly|QFile::Text);
        }
        QTextStream in (&file);

        while(!in.atEnd()) {
            courseName = in.readLine();
            instructor = in.readLine();
            profRate = in.readLine();
            meeting = in.readLine();
            credits = in.readLine();
            seats = in.readLine();

            table->insertRow(ui->tableWidget->rowCount());
            int index = table->rowCount() - 1;
            table->setItem(index, COURSE, new QTableWidgetItem(courseName));
            table->setItem(index, INSTRUCTOR, new QTableWidgetItem(instructor));
            table->setItem(index, RATE, new QTableWidgetItem(profRate));
            table->setItem(index, MEETING, new QTableWidgetItem(meeting));
            table->setItem(index, CREDITS, new QTableWidgetItem(credits));
            table->setItem(index, SEATS, new QTableWidgetItem(seats));
        }
        file.close();

    }catch(QString sErr) {
        QMessageBox::warning(this, "File",sErr);
    }catch(std::exception& e){
        QMessageBox::warning(this, "Error",e.what());
    }

}

void Admin::rateDisplay()
{
    try {
        QFile file(filePrefix +"/collegeEnrollment/Sources/rateData.txt");
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            file.open(QFile::ReadOnly|QFile::Text);
        }
        QTextStream in (&file);
        ui->rateBrowser->setText(in.readAll());

        file.close();

    }catch(QString sErr) {
        QMessageBox::warning(this, "File",sErr);
    }catch(std::exception& e){
        QMessageBox::warning(this, "Error",e.what());
    }
}

void Admin::on_addButton_clicked()
{
    addCourse = new class addCourse(this);
    addCourse->show();
}

void Admin::on_editButton_clicked()
{
    editCourse = new class editCourse(this);
    editCourse->show();
    editCourse->setSelectedData(ui->tableWidget);
}

void Admin::on_deleteButton_clicked()
{
    try {
        int index = ui->tableWidget->currentRow();
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
        while(!in.atEnd()) {
            dataText.append(in.readLine()+"\n");
        }

        file.close();

        QFile writefile(filePrefix + "/collegeEnrollment/Sources/courseData.txt");
        if(!writefile.open(QFile::WriteOnly|QFile::Truncate|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            writefile.open(QFile::WriteOnly|QFile::Truncate|QFile::Text);
        }
        QTextStream out (&writefile);
        out << dataText;

        writefile.flush();
        writefile.close();

        QMessageBox::information(this,"Success","Successfully Deleted the Course! Click Refresh Button");

    } catch(QString sErr) {
    QMessageBox::warning(this, "File",sErr);
    } catch(std::exception& e){
    QMessageBox::warning(this, "Error",e.what());
    }

}

void Admin::on_refreshButton_clicked()
{
    coursesDisplay();
}
