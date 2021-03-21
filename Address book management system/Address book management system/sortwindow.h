#ifndef SORTWINDOW_H
#define SORTWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <fstream>
#include <content.h>

namespace Ui {
class SortWindow;
}

class SortWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SortWindow(QWidget *parent = nullptr);
    ~SortWindow();
    void toFile(string path, Node* node); //文件名
    Node* getAddContent(); //得到修改后内容

private slots:
    void on_name_button_clicked();
    void on_number_button_clicked();

    void on_reNameButton_clicked();

    void on_reNumberButton_clicked();

private:
    Ui::SortWindow *ui;
    Node* head,* tail; //链表指针
    string filename; //文件名
    content* students; //content类
};

#endif // SORTWINDOW_H
