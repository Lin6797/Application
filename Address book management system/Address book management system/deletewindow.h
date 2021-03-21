#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <content.h>
#include <string>
#include <QMessageBox>
#include <QMainWindow>
#include <fstream>

namespace Ui {
class DeleteWindow;
}

class DeleteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeleteWindow(QWidget *parent = nullptr);
    ~DeleteWindow();
    void toFile(string path, Node* node, int num); //文件名
    int getDelNumber(); //得到删除后数据总数
    Node* getDelContent(); //得到删除后内容

private slots:
    void on_name_button_clicked();
    void on_number_button_clicked();

private:
    Ui::DeleteWindow *ui;
    int student_num; //删除后学生数目
    Node* head,* tail; //链表指针
    string filename; //通讯录文件
    content* students; //content类
};

#endif // DELETEWINDOW_H
