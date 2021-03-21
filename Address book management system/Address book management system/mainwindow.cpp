#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag=0;
    //初始化数
    student_number=0;
    //head
    Student stemp;
    stemp.Name="";
    stemp.Number="";
    stemp.Grade="";
    stemp.Acadamy="";
    stemp.Major="";
    stemp.Phone="";
    Node* node=new Node();
    node->student=stemp;
    node->link=NULL;
    head=node; tail=head;
    //建立窗口类
    students = new content(head);
    aw = new AddWindow();
    sw = new ShowWindow();
    searchw = new searchwindow();
    dw = new DeleteWindow();
    mw = new ModifyWindow();
    sortw = new SortWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//拆文件内容
Student MainWindow::apart(string s){
    Student Stemp; string s_get;
    //切
    Stemp.Number=s.substr(0,s.find(";"));
    s=s.substr(s.find(";")+1,s.length());

    Stemp.Name=s.substr(0,s.find(";"));
    s=s.substr(s.find(";")+1,s.length());

    Stemp.Phone=s.substr(0,s.find(";"));
    s=s.substr(s.find(";")+1,s.length());

    Stemp.Acadamy=s.substr(0,s.find(";"));
    s=s.substr(s.find(";")+1,s.length());

    Stemp.Grade=s.substr(0,s.find(";"));
    s=s.substr(s.find(";")+1,s.length());

    Stemp.Major=s.substr(0,s.find(";"));
    s=s.substr(s.find(";")+1,s.length());

    //返回
    return Stemp;
}


//创建通讯录
void MainWindow::on_createButton_clicked()
{
    bool ifok;
    QString Spath;
    ofstream out;
    Spath=QInputDialog::getText(NULL,"New Title","Please input new title",
                                   QLineEdit::Normal,"xxx\\xxx\\xxx.txt",&ifok);
    path=Spath.toStdString();

    if(ifok){
        aw->show();
        aw->toFile(path,head,student_number);
        flag=1;
    }
}

//打开通讯录
void MainWindow::on_openButton_clicked()
{
    QString Spath;
    char student_mail_char[500];
    fstream in;
    Student Stemp;
    string student_mail;

    //打开文件
    Spath=QFileDialog::getOpenFileName(NULL,"Chose mail list","F:","文本文件(*txt)");
    path=Spath.toStdString();
    in.open(path,ios::in);
    while(!in.eof()){
        in.getline(student_mail_char,500);
        student_mail=string(student_mail_char);
        if(student_mail.length()==0) break;
        Stemp=apart(student_mail);
        students->Add(Stemp);
        //计算记录数
        student_number++;
    }
    in.close();
    head=students->getFirst();
}

//展示
void MainWindow::on_showButton_clicked()
{
    //int total;
    if(flag==1){
        student_number=aw->getAddNumber();
        head=aw->getAddContent();
    }
    else if(flag==2){
        student_number=dw->getDelNumber();
        head=dw->getDelContent();
    }
    else if(flag==3){
        head=mw->getAddContent();
    }
    else if(flag==4){
        head=sortw->getAddContent();
    }
    sw->Show(head,student_number);
    //显示窗口
    sw->show();
}

//查找
void MainWindow::on_searchButton_clicked()
{
    searchw->setTable(head);
    searchw->show();
}

//添加
void MainWindow::on_addButton_clicked()
{
    aw->show();
    aw->toFile(path,head,student_number);
    flag=1;
}

//删除
void MainWindow::on_deleteButton_clicked()
{
    dw->show();
    dw->toFile(path,head,student_number);
    flag=2;
}

//修改
void MainWindow::on_modifyButton_clicked()
{
    mw->show();
    mw->toFile(path,head);
    flag=3;
}

//排序
void MainWindow::on_sortButton_clicked()
{
    sortw->show();
    sortw->toFile(path,head);
    flag=4;
}
