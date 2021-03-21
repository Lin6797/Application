#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <content.h>

namespace Ui {
class searchwindow;
}

class searchwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchwindow(QWidget *parent = nullptr);
    void setTable(Node* node);
    ~searchwindow();

private slots:
    void on_name_button_clicked();
    void on_number_button_clicked();

private:
    Ui::searchwindow *ui;
    int num; //追加显示查找内容
    Node* head, *goal_head, *goal_tail; //链表指针
    content* students; //content类
};

#endif // SEARCHWINDOW_H
