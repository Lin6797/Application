#include "deletewindow.h"
#include "ui_deletewindow.h"

DeleteWindow::DeleteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeleteWindow)
{
    ui->setupUi(this);
}

DeleteWindow::~DeleteWindow()
{
    delete ui;
}

int DeleteWindow::getDelNumber(){
    return student_num;
}
//得到删除后内容
Node* DeleteWindow::getDelContent(){
    return head;
}

//得到文件
void DeleteWindow::toFile(string path, Node* node, int num){
    filename=path;
    head=node;
    student_num=num;
}

//按照姓名进行删除
void DeleteWindow::on_name_button_clicked()
{
    QString qstr;
    Node* node;
    students=new content(head);
    //得到姓名
    qstr=ui->name_line->text();
    node=students->SearchName(qstr.toStdString());
    if(node==NULL) QMessageBox::critical(this,"错误","没有符合条件的学生记录");
    else{
        head=students->DeleteName(qstr.toStdString());
        student_num--;
        QMessageBox::about(this,"关于","删除成功");
    }
    //写入文件
    fstream out;
    out.open(filename,ios::out);
    for(Node* temp=head->link; temp!=NULL; temp=temp->link){
        string total=temp->student.Total();
        out<<total<<endl;
    }
}

//按照学号进行删除
void DeleteWindow::on_number_button_clicked()
{
    QString qstr;
    Node* node;
    students=new content(head);
    //得到姓名
    qstr=ui->number_line->text();
    node=students->SearchNumber(qstr.toStdString());
    if(node==NULL) QMessageBox::critical(this,"错误","没有符合条件的学生记录");
    else{
        head=students->DeleteNumber(qstr.toStdString());
        student_num--;
        QMessageBox::about(this,"关于","删除成功");
    }
    //写入文件
    fstream out;
    out.open(filename,ios::out);
    for(Node* temp=head->link; temp!=NULL; temp=temp->link){
        string total=temp->student.Total();
        out<<total<<endl;
    }
}
