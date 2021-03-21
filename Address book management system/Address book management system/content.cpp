#include "content.h"

//带参构造函数
content::content(Node* node){
    head=node;
    tail=head;
    while(tail->link!=NULL){
        tail=tail->link;
    }
    total=0;
}

//析构函数
content::~content(){

}

//得到链表首部
Node* content::getFirst(){
    return head;
}

//末尾添加
Node* content::Add(Student s){
    //新建
    Node* addnode=new Node();
    addnode->student=s;
    addnode->link=NULL;
    //添加
    tail->link=addnode;
    tail = addnode;
    total++;
    //返回全部
    return head;
}

//链表内容排序(按照姓名)
Node* content::SortName(){
    Student stemp;
    //选择排序法
    for(Node* temp1=head->link; temp1->link!=NULL; temp1=temp1->link){
        for(Node* temp2=temp1->link; temp2!=NULL; temp2=temp2->link){
            if((temp1->student.Name)>(temp2->student.Name)){
                stemp=temp1->student;
                temp1->student=temp2->student;
                temp2->student=stemp;
            }
        }
    }
    return head;
}

//链表内容排序(按照学号)
Node* content::SortNumber(){
    Student stemp;
    //选择排序法
    for(Node* temp1=head->link; temp1->link!=NULL; temp1=temp1->link){
        for(Node* temp2=temp1->link; temp2!=NULL; temp2=temp2->link){
            if((temp1->student.Number)>(temp2->student.Number)){
                stemp=temp1->student;
                temp1->student=temp2->student;
                temp2->student=stemp;
            }
        }
    }
    return head;
}

//链表内容排序(按照姓名从大到小)
Node* content::reSortName(){
    Student stemp;
    //选择排序法
    for(Node* temp1=head->link; temp1->link!=NULL; temp1=temp1->link){
        for(Node* temp2=temp1->link; temp2!=NULL; temp2=temp2->link){
            if((temp1->student.Name)<(temp2->student.Name)){
                stemp=temp1->student;
                temp1->student=temp2->student;
                temp2->student=stemp;
            }
        }
    }
    return head;
}

//链表内容排序(按照学号从大到小)
Node* content::reSortNumber(){
    Student stemp;
    //选择排序法
    for(Node* temp1=head->link; temp1->link!=NULL; temp1=temp1->link){
        for(Node* temp2=temp1->link; temp2!=NULL; temp2=temp2->link){
            if((temp1->student.Number)<(temp2->student.Number)){
                stemp=temp1->student;
                temp1->student=temp2->student;
                temp2->student=stemp;
            }
        }
    }
    return head;
}

//链表内容删除(按照姓名)
Node* content::DeleteName(string name){
    Node* ntemp, *temp;
    for(temp=head; temp->link!=NULL; temp=temp->link){
        if(temp->link->student.Name == name){
            ntemp=temp->link;
            temp->link=ntemp->link;
            ntemp->link=NULL;
            delete ntemp;
            break;
        }
    }
    total--;
    return head;
}

//链表内容删除(按照学号)
Node* content::DeleteNumber(string number){
    Node* ntemp, *temp;
    for(temp=head; temp->link!=NULL; temp=temp->link){
        if(temp->link->student.Number == number){
            ntemp=temp->link;
            temp->link=ntemp->link;
            ntemp->link=NULL;
            delete ntemp;
            break;
        }
    }
    total--;
    return head;
}

//查找链表内容(按照姓名)
Node* content::SearchName(string name){
    for(Node* temp=head->link; temp!=NULL; temp=temp->link){
        if(temp->student.Name==name){
            return temp;
        }
    }
    return NULL;
}

//查找链表内容(按照学号)
Node* content::SearchNumber(string number){
    for(Node* temp=head->link; temp!=NULL; temp=temp->link){
        if(temp->student.Number == number){
            return temp;
        }
    }
    return NULL;
}

//链表内容修改
Node* content::Modify(Node* init, Student goal){
    init->student=goal;
    return head;
}

//返回记录数
int content::getTotalNum(){
    return total;
}
