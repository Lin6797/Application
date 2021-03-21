#include "addwindow.h"
#include "ui_addwindow.h"

AddWindow::AddWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddWindow)
{
    ui->setupUi(this);
    student_num=0;
}

AddWindow::~AddWindow()
{
    delete ui;
}

//得到最终的node
Node* AddWindow::getAddContent(){
    return head;
}

//得到最终的记录数
int AddWindow::getAddNumber(){
    return student_num;
}

//判断是否存在
bool AddWindow::ifExist(Student s){
    Node* node;
    students=new content(head);
    node=students->SearchName(s.Name);
    if(node!=NULL){
        delete students;
        return true;
    }
    node=students->SearchNumber(s.Number);
    if(node!=NULL){
        delete students;
        return true;
    }
    return false;
}

//得到文件名
void AddWindow::toFile(string path, Node* node, int num){
    filename=path;
    head=node;
    student_num=num;
}

//确认添加
void AddWindow::on_sure_button_clicked()
{
    Student stemp;
    QString qstr;
    string total;
    bool ifexist;
    //得到添加内容
    qstr=ui->number_edit->text(); stemp.Number = qstr.toStdString();
    qstr=ui->name_edit->text(); stemp.Name = qstr.toStdString();
    qstr=ui->grade_edit->text(); stemp.Grade = qstr.toStdString();
    qstr=ui->acadamy_edit->text(); stemp.Acadamy = qstr.toStdString();
    qstr=ui->majory_edit->text(); stemp.Major = qstr.toStdString();
    qstr=ui->phone_edit->text(); stemp.Phone = qstr.toStdString();
    total = stemp.Total();
    //判断是否已有
    ifexist=ifExist(stemp);
    if(ifexist){
        QMessageBox::critical(this,"错误","此记录已存在于数据库中");
    }
    else{
        //写入文件
        fstream out;
        out.open(filename,ios::app|ios::out);
        out<<total<<endl;
        out.close();
        //添加
        students=new content(head);
        head=students->Add(stemp);
        student_num++;
        delete students;
        //提示
        QMessageBox::about(this,"关于","添加成功");
    }
}
