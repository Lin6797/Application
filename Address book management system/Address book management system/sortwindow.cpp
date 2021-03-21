#include "sortwindow.h"
#include "ui_sortwindow.h"

SortWindow::SortWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SortWindow)
{
    ui->setupUi(this);
}

SortWindow::~SortWindow()
{
    delete ui;
}

//传文件名
void SortWindow::toFile(string path, Node* node){
    filename=path;
    head=node;
}

//得到排序后内容
Node* SortWindow::getAddContent(){
    return head;
}

//按姓名进行排序
void SortWindow::on_name_button_clicked()
{
    //排序
    students=new content(head);
    head=students->SortName();
    delete students;
    //写入文件
    fstream out;
    out.open(filename,ios::out);
    for(Node* temp=head->link; temp!=NULL; temp=temp->link){
        string total=temp->student.Total();
        out<<total<<endl;
    }
    QMessageBox::about(this,"关于","排序完成");
}

//按学号进行排序
void SortWindow::on_number_button_clicked()
{
    //排序
    students=new content(head);
    head=students->SortNumber();
    delete students;
    //写入文件
    fstream out;
    out.open(filename,ios::out);
    for(Node* temp=head->link; temp!=NULL; temp=temp->link){
        string total=temp->student.Total();
        out<<total<<endl;
    }
    QMessageBox::about(this,"关于","排序完成");
}

//按姓名进行逆排序
void SortWindow::on_reNameButton_clicked()
{
    //排序
    students=new content(head);
    head=students->reSortName();
    delete students;
    //写入文件
    fstream out;
    out.open(filename,ios::out);
    for(Node* temp=head->link; temp!=NULL; temp=temp->link){
        string total=temp->student.Total();
        out<<total<<endl;
    }
    QMessageBox::about(this,"关于","排序完成");
}

//按学号进行逆排序
void SortWindow::on_reNumberButton_clicked()
{
    //排序
    students=new content(head);
    head=students->reSortNumber();
    delete students;
    //写入文件
    fstream out;
    out.open(filename,ios::out);
    for(Node* temp=head->link; temp!=NULL; temp=temp->link){
        string total=temp->student.Total();
        out<<total<<endl;
    }
    QMessageBox::about(this,"关于","排序完成");
}
