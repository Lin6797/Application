#include "searchwindow.h"
#include "ui_searchwindow.h"

searchwindow::searchwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searchwindow)
{
    ui->setupUi(this);
}

searchwindow::~searchwindow()
{
    delete ui;
}

//准备设置表格
void searchwindow::setTable(Node* node){
    num=0;
    head=node;
    students=new content(head);
    //初始化
    Node* node_temp = new Node();
    node_temp->student.Name="";
    node_temp->student.Number="";
    node_temp->student.Grade="";
    node_temp->student.Acadamy="";
    node_temp->student.Major="";
    node_temp->student.Phone="";
    node_temp->link = NULL;
    goal_head=node_temp; goal_tail=goal_head;
    //设置表格
    ui->tableWidget->setColumnCount(6);
    //设置表头
    QStringList Head;
    Head<<"Number"<<"Name"<<"Grade"<<"Acadamy"<<"Majory"<<"Phone";
    ui->tableWidget->setHorizontalHeaderLabels(Head);
}

//按姓名查找
void searchwindow::on_name_button_clicked()
{
    Node* goal, *temp;
    QString Qname,Item;
    string sname;

    //得到查找条件
    Qname=ui->name_line->text();
    sname=Qname.toStdString();
    goal=students->SearchName(sname);

    //找不到
    if(goal==NULL) {
        QMessageBox::critical(this,"错误","没有符合条件的学生记录");
    }
    //找得到
    else{
        num++;
        goal_tail->link=goal;
        goal_tail=goal;
    }
    temp=goal_head->link;

    //显示表格
    ui->tableWidget->setRowCount(num);
    for(int i=0; i<num; i++){
        Item=QString::fromStdString(temp->student.Number); ui->tableWidget->setItem(i,0,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Name); ui->tableWidget->setItem(i,1,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Grade); ui->tableWidget->setItem(i,2,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Acadamy); ui->tableWidget->setItem(i,3,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Major); ui->tableWidget->setItem(i,4,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Phone); ui->tableWidget->setItem(i,5,new QTableWidgetItem(Item));
        temp=temp->link;
    }
}

//按学号查找
void searchwindow::on_number_button_clicked()
{
    Node* goal, *temp;
    QString Qnumber,Item;
    string snumber;

    //得到查找条件
    Qnumber=ui->number_line->text();
    snumber=Qnumber.toStdString();
    goal=students->SearchNumber(snumber);

    //找不到
    if(goal==NULL) {
        QMessageBox::critical(this,"错误","没有符合条件的学生记录");
    }
    //找得到
    else{
        num++;
        goal_tail->link=goal;
        goal_tail=goal;
    }
    temp=goal_head->link;

    //显示表格
    ui->tableWidget->setRowCount(num);
    for(int i=0; i<num; i++){
        Item=QString::fromStdString(temp->student.Number); ui->tableWidget->setItem(i,0,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Name); ui->tableWidget->setItem(i,1,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Grade); ui->tableWidget->setItem(i,2,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Acadamy); ui->tableWidget->setItem(i,3,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Major); ui->tableWidget->setItem(i,4,new QTableWidgetItem(Item));
        Item=QString::fromStdString(temp->student.Phone); ui->tableWidget->setItem(i,5,new QTableWidgetItem(Item));
        temp=temp->link;
    }
}
