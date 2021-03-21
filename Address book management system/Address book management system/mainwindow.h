#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QFileDialog>
#include <fstream>
#include <showwindow.h>
#include <addwindow.h>
#include <searchwindow.h>
#include <deletewindow.h>
#include <modifywindow.h>
#include <sortwindow.h>
#include <content.h>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createButton_clicked();
    void on_openButton_clicked();
    void on_showButton_clicked();
    void on_searchButton_clicked();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_modifyButton_clicked();
    void on_sortButton_clicked();

private:
    Ui::MainWindow *ui;
    int student_number,flag; //记录数目、标志
    content* students;  //content类
    Node* head, *tail;  //链表指针
    string path; //打开文件路径
    //窗口类
    ShowWindow* sw;
    AddWindow* aw;
    searchwindow* searchw;
    DeleteWindow* dw;
    ModifyWindow* mw;
    SortWindow* sortw;
    Student apart(string s); //拆string
};

#endif // MAINWINDOW_H
