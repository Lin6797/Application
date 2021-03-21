#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <content.h>
#include <fstream>

namespace Ui {
class AddWindow;
}

class AddWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddWindow(QWidget *parent = nullptr);
    ~AddWindow();
    void toFile(string path, Node* node, int num); //文件名
    int getAddNumber();//添加后记录数
    Node* getAddContent(); //得到添加后内容

private slots:
    void on_sure_button_clicked();

private:
    Ui::AddWindow *ui;
    int student_num; //添加后学生数目
    Node* head,* tail;  //链表指针
    string filename;  //通讯录文件
    content* students;  //content类
    bool ifExist(Student s); //判断s是否存在
};

#endif // ADDWINDOW_H
