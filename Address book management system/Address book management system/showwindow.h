#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H

#include <QMainWindow>
#include <content.h>

namespace Ui {
class ShowWindow;
}

class ShowWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowWindow(QWidget *parent = nullptr);
    ~ShowWindow();
    void Show(Node* node,int number); //展示

private:
    Ui::ShowWindow *ui;
};

#endif // SHOWWINDOW_H
