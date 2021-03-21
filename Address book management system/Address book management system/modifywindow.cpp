#include "modifywindow.h"
#include "ui_modifywindow.h"

ModifyWindow::ModifyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModifyWindow)
{
    ui->setupUi(this);
}

ModifyWindow::~ModifyWindow()
{
    delete ui;
}

//传文件名
void ModifyWindow::toFile(string path, Node* node){
    filename=path;
    head=node;
}

//得到修改后内容
Node* ModifyWindow::getAddContent(){
    return head;
}

//按姓名进行查找
void ModifyWindow::on_name_button_clicked()
{
    QString qstr;
    //得到姓名
    students=new content(head);
    qstr=ui->name_search->text();
    init=students->SearchName(qstr.toStdString());
    delete students;
    //显示
    if(init==NULL) QMessageBox::critical(this,"错误","没有符合条件的学生记录");
    else{
        ui->number_edit->setText(QString::fromStdString(init->student.Number));
        ui->name_edit->setText(QString::fromStdString(init->student.Name));
        ui->grade_edit->setText(QString::fromStdString(init->student.Grade));
        ui->acadamy_edit->setText(QString::fromStdString(init->student.Acadamy));
        ui->majory_edit->setText(QString::fromStdString(init->student.Major));
        ui->phone_edit->setText(QString::fromStdString(init->student.Phone));
    }
}

//按学号进行查找
void ModifyWindow::on_number_button_clicked()
{
    QString qstr;
    //得到学号
    students=new content(head);
    qstr=ui->number_search->text();
    init=students->SearchNumber(qstr.toStdString());
    delete students;
    //显示
    if(init==NULL) QMessageBox::critical(this,"错误","没有符合条件的学生记录");
    else{
        ui->number_edit->setText(QString::fromStdString(init->student.Number));
        ui->name_edit->setText(QString::fromStdString(init->student.Name));
        ui->grade_edit->setText(QString::fromStdString(init->student.Grade));
        ui->acadamy_edit->setText(QString::fromStdString(init->student.Acadamy));
        ui->majory_edit->setText(QString::fromStdString(init->student.Major));
        ui->phone_edit->setText(QString::fromStdString(init->student.Phone));
    }
}


//确认修改
void ModifyWindow::on_surebutton_clicked()
{
    Student stemp;
    QString qstr;
    string total;
    //得到修改后数据
    students=new content(head);
    qstr=ui->number_edit->text(); stemp.Number = qstr.toStdString();
    qstr=ui->name_edit->text(); stemp.Name = qstr.toStdString();
    qstr=ui->grade_edit->text(); stemp.Grade = qstr.toStdString();
    qstr=ui->acadamy_edit->text(); stemp.Acadamy = qstr.toStdString();
    qstr=ui->majory_edit->text(); stemp.Major = qstr.toStdString();
    qstr=ui->phone_edit->text(); stemp.Phone = qstr.toStdString();
    total = stemp.Total();
    //修改
    head=students->Modify(init,stemp);
    delete students;
    //提示
    QMessageBox::about(this,"关于","修改成功");
}

