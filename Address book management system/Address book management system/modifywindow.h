#ifndef MODIFYWINDOW_H
#define MODIFYWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <content.h>

namespace Ui {
class ModifyWindow;
}

class ModifyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyWindow(QWidget *parent = nullptr);
    ~ModifyWindow();
    void toFile(string path, Node* node); //文件名
    Node* getAddContent(); //得到修改后内容

private slots:
    void on_surebutton_clicked();
    void on_name_button_clicked();
    void on_number_button_clicked();

private:
    Ui::ModifyWindow *ui;
    Node* init; //目标修改Node的内容
    Node* head,* tail; //链表指针
    string filename; //文件名
    content* students; //content类
};

#endif // MODIFYWINDOW_H
