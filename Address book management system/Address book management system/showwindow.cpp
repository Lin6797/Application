#include "showwindow.h"
#include "ui_showwindow.h"

ShowWindow::ShowWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowWindow)
{
    ui->setupUi(this);
}

ShowWindow::~ShowWindow()
{
    delete ui;
}

//展示
void ShowWindow::Show(Node* node, int number){
    int i=0;
    //设置表格
    ui->tableWidget->setRowCount(number+1);
    ui->tableWidget->setColumnCount(6);
    //设置表头
    QStringList Head;
    Head<<"Number"<<"Name"<<"Grade"<<"Acadamy"<<"Majory"<<"Phone";
    ui->tableWidget->setHorizontalHeaderLabels(Head);
    //写入内容
    for(Node* temp=node->link; temp!=NULL; temp=temp->link){
        int j; QString Item;
        j=0; Item = QString::fromStdString(temp->student.Number); ui->tableWidget->setItem(i,j,new QTableWidgetItem(Item));
        j++; Item = QString::fromStdString(temp->student.Name); ui->tableWidget->setItem(i,j,new QTableWidgetItem(Item));
        j++; Item = QString::fromStdString(temp->student.Grade); ui->tableWidget->setItem(i,j,new QTableWidgetItem(Item));
        j++; Item = QString::fromStdString(temp->student.Acadamy); ui->tableWidget->setItem(i,j,new QTableWidgetItem(Item));
        j++; Item = QString::fromStdString(temp->student.Major); ui->tableWidget->setItem(i,j,new QTableWidgetItem(Item));
        j++; Item = QString::fromStdString(temp->student.Phone); ui->tableWidget->setItem(i,j,new QTableWidgetItem(Item));
        i++;
    }
}
