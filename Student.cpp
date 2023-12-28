#include "Student.h"
#include "ui_Student.h"

Student::Student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    coursesDisplay();
}

Student::~Student()
{
    delete ui;
}

void Student::coursesDisplay()
{
    try {
        QTableWidget *table = ui->tableCourses;
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

            if(seats != "0") {
                table->insertRow(ui->tableCourses->rowCount());
                int index = table->rowCount() - 1;
                table->setItem(index, COURSE, new QTableWidgetItem(courseName));
                table->setItem(index, INSTRUCTOR, new QTableWidgetItem(instructor));
                table->setItem(index, RATE, new QTableWidgetItem(profRate));
                table->setItem(index, MEETING, new QTableWidgetItem(meeting));
                table->setItem(index, CREDITS, new QTableWidgetItem(credits));
                table->setItem(index, SEATS, new QTableWidgetItem(seats));
            }

        }
        file.close();

    }catch(QString sErr) {
        QMessageBox::warning(this, "File",sErr);
    }catch(std::exception& e){
        QMessageBox::warning(this, "Error",e.what());
    }

}

void Student::studentCourses()
{
    try {
        QTableWidget *table = ui->tableStudent;
        QStringList tableHeader;

        tableHeader << "Course Name" << "Instructor" << "Prof Rate";
        table->clear();
        table->setColumnCount(3);
        table->setRowCount(0);
        table->setHorizontalHeaderLabels(tableHeader);
        table->setSelectionMode(QAbstractItemView::ExtendedSelection);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setTextElideMode(Qt::ElideRight);

        QString fileName = filePrefix + "/collegeEnrollment/Sources/";
        fileName.append(studentId);
        fileName.append("_Courses.txt");
        QString courseName;
        QString instructor;
        QString profRate;

        QFile file(fileName);
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

            table->insertRow(ui->tableStudent->rowCount());
            int index = table->rowCount() - 1;
            table->setItem(index, COURSE, new QTableWidgetItem(courseName));
            table->setItem(index, INSTRUCTOR, new QTableWidgetItem(instructor));
            table->setItem(index, RATE, new QTableWidgetItem(profRate));
        }
        file.close();

    }catch(QString sErr) {
        QMessageBox::warning(this, "File",sErr);
    }catch(std::exception& e){
        QMessageBox::warning(this, "Error",e.what());
    }
}

void Student::createStudentFile(QString studentId)
{
    this->studentId = studentId;
    ui->label_2->setText("BHCC_College Enrollment with RateMyProfessor  -- " + studentId);
    QString fileName = filePrefix + "/collegeEnrollment/Sources/";
    fileName.append(studentId);
    fileName.append("_Courses.txt");
    QFile fileStudent(fileName);
    if(!fileStudent.open(QFile::WriteOnly|QFile::Append|QFile::Text))
    {
         throw QString("Could not open file");
    } else {
        fileStudent.open(QFile::WriteOnly|QFile::Append|QFile::Text);
    }
    fileStudent.flush();
    fileStudent.close();
}

void Student::on_refreshButton_clicked()
{
    coursesDisplay();
    studentCourses();
}

void Student::on_addButton_clicked()
{
    try {
        int index = ui->tableCourses->currentRow();

        QString courseName, instructor, profRate, meeting, credits;
        int seats;

        QString dataText;
        QString dataStudent;

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
        courseName = in.readLine();
        instructor = in.readLine();
        profRate = in.readLine();
        meeting = in.readLine();
        credits = in.readLine();
        seats = in.readLine().toInt();
        seats--;

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
        if(!writefile.open(QFile::WriteOnly|QFile::Truncate|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            writefile.open(QFile::WriteOnly|QFile::Truncate|QFile::Text);
        }
        QTextStream out1 (&writefile);
        out1 << dataText;

        writefile.flush();
        writefile.close();



        dataStudent.append(courseName+"\n");
        dataStudent.append(instructor+"\n");
        dataStudent.append(profRate+"\n");

        QString fileName = filePrefix + "/collegeEnrollment/Sources/";
        fileName.append(studentId);
        fileName.append("_Courses.txt");
        QFile fileStudent(fileName);
        if(!fileStudent.open(QFile::WriteOnly|QFile::Append|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            fileStudent.open(QFile::WriteOnly|QFile::Append|QFile::Text);
        }

        QTextStream out2 (&fileStudent);
        out2 << dataStudent;

        fileStudent.flush();
        fileStudent.close();

        QMessageBox::information(this,"Success","Successfully Added the Course!");

    } catch(QString sErr) {
    QMessageBox::warning(this, "File",sErr);
    } catch(std::exception& e){
    QMessageBox::warning(this, "Error",e.what());
    }

    coursesDisplay();
    studentCourses();
}

void Student::on_deleteButton_clicked()
{
    try {
        int index = ui->tableStudent->currentRow();

        QString courseName1 ="", instructor1="", profRate1="", dataText1="";

        QString fileName = filePrefix + "/collegeEnrollment/Sources/";
        fileName.append(studentId);
        fileName.append("_Courses.txt");
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            file.open(QFile::ReadOnly|QFile::Text);
        }
        QTextStream in1 (&file);
        for (int i=0; i<index; i++) {
            dataText1.append(in1.readLine()+"\n");
            dataText1.append(in1.readLine()+"\n");
            dataText1.append(in1.readLine()+"\n");
        }
        courseName1 = in1.readLine();
        instructor1 = in1.readLine();
        profRate1 = in1.readLine();

        while(!in1.atEnd()) {
            dataText1.append(in1.readLine()+"\n");
        }

        file.close();

        QFile writefile1(fileName);
        if(!writefile1.open(QFile::WriteOnly|QFile::Truncate|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            writefile1.open(QFile::WriteOnly|QFile::Truncate|QFile::Text);
        }
        QTextStream out1 (&writefile1);
        out1 << dataText1;

        writefile1.flush();
        writefile1.close();



        QString courseName ="", instructor= "", profRate ="", meeting ="", credits ="", dataText;
        int seats;

        QFile fileCourse(filePrefix + "/collegeEnrollment/Sources/courseData.txt");
        if(!fileCourse.open(QFile::ReadOnly|QFile::Text))
        {
             throw QString("Could not open file");
        } else {
            fileCourse.open(QFile::ReadOnly|QFile::Text);
        }
        QTextStream in (&fileCourse);
        while(courseName != courseName1 && instructor != instructor1) {
            courseName = in.readLine();
            instructor = in.readLine();
            profRate = in.readLine();
            meeting = in.readLine();
            credits = in.readLine();
            seats = in.readLine().toInt();

            if ((courseName == courseName1 && instructor == instructor1)) {
                seats++;
            }
            dataText.append(courseName+"\n");
            dataText.append(instructor+"\n");
            dataText.append(profRate+"\n");
            dataText.append(meeting+"\n");
            dataText.append(credits+"\n");
            dataText.append(QString::number(seats)+"\n");
        }

        while(!in.atEnd()) {
            dataText.append(in.readLine()+"\n");
        }

        fileCourse.close();

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

        QMessageBox::information(this,"Success","Successfully Added the Course!");

    } catch(QString sErr) {
    QMessageBox::warning(this, "File",sErr);
    } catch(std::exception& e){
    QMessageBox::warning(this, "Error",e.what());
    }

    coursesDisplay();
    studentCourses();
}
