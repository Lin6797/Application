#include <stdio.h>
#include <string>
using namespace std;

#ifndef CONTENT_H
#define CONTENT_H

//学生通讯录内容
struct Student{
    string Number; //学号
    string Name; //姓名
    string Phone;  //电话
    string Acadamy;  //学院
    string Grade;  //年级
    string Major;  //专业
    //写入文件内容
    string Total(){
        string total;
        total = Number+";"+Name+";"+Phone+";"+Acadamy+";"+Grade+";"+Major+";";
        return total;
    }
};

//链表节点
struct Node{
    Student student;
    Node* link;
};

class content
{
public:
    content(Node* node); //构造函数
    ~content();  //析构函数
    Node* getFirst(); //返回头指针
    Node* Add(Student s); //链表末尾插入s
    Node* SortName(); //链表内容排序(按照姓名)
    Node* SortNumber(); //链表内容排序(按照学号)
    Node* reSortName(); //链表内容排序(按照姓名从大到小)
    Node* reSortNumber(); //链表内容排序(按照学号从大到小)
    Node* DeleteName(string name); //链表内容删除(按照姓名)
    Node* DeleteNumber(string number); //链表内容删除(按照学号)
    Node* SearchName(string name); //查找链表内容(按照姓名)
    Node* SearchNumber(string number); //查找链表内容(按照学号)
    Node* Modify(Node* init, Student goal); //链表内容修改
    int getTotalNum(); //得到总记录数
private:
    int total; //总记录数
    Node* head; //链表头
    Node* tail; //链表尾
};

#endif // CONTENT_H

