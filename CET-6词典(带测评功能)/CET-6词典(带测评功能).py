from tkinter import *
from tkinter import ttk
import tkinter.messagebox as MB
import random

#查询操作
def search():
    f=open("英语词典.txt","r")
    Words=f.readlines()
    f.close()

    def Search():
        purpose=purpose_input.get()
        Judge=[]
        Purpose=[]
        for word in Words:
           if purpose in word:
               Purpose.append(word)
               Judge.append("exist")
           else:
               Judge.append("no exist")
        if Judge.count("exist")==0:
            MB.showerror(title="查询失败",message="词典未收录目标单词或翻译")
        else:
            winsearch=Tk()
            winsearch.title("查询结果")
            Tip=Text(winsearch,width=30,height=10)
            Tip.pack()
            Tip.insert(INSERT, "查询结果为:\n")
            for line in Purpose:
                Tip.insert(INSERT,line)

    wins = Toplevel()
    wins.title("查询")

    purpose_input_tip=Label(wins,text="请输入你要查询的对象")
    purpose_input_tip.grid(row=0, column=1, padx=5, pady=(15, 5), sticky="e")
    purpose_input= Entry(wins, width=15)
    purpose_input.grid(row=0,column=2,padx=5,pady=(15, 5),sticky="w")

    purpose_get=Button(wins,text="查询",command=Search)
    purpose_get.grid(row=2,column=1,columnspan=2,pady=5)
#添加操作
def add():
    def Add():
        Judge="no exist"
        Epurpose=Eadd_input.get()
        Cpurpose=Cadd_input.get()

        f=open("英语词典.txt","r")
        word=f.readline()
        while word:
            if Epurpose in word and Cpurpose in word:
                Judge="exist"
                break
            word=f.readline()
        f.close()

        if Judge=="exist":
            MB.showerror(title="添加错误",message="词典中已存在改单词及对应翻译")
        else:
            f=open("英语词典.txt","a")
            f.write(Epurpose+":"+Cpurpose+"\n")
            f.close()
            MB.showwarning(title="添加成功",message="已经成功添加单词及相应翻译")

    wina=Toplevel()
    wina.title("添加")
    Add_input_tip=Label(wina,text="请输入你要添加的对象",font=("SimSun",13))
    Add_input_tip.grid(row=0,column=0,padx=(10,10),pady=(10,5),columnspan=2)

    Eadd_input_tip=Label(wina,text="英文单词")
    Eadd_input_tip.grid(row=1,column=0,padx=(10,0),pady=(10,0))
    Eadd_input=Entry(wina,width=15)
    Eadd_input.grid(row=1,column=1,padx=(0,10),pady=(10,0))
    Cadd_input_tip=Label(wina,text="中文翻译")
    Cadd_input_tip.grid(row=2,column=0,padx=(10,0),pady=(5,10))
    Cadd_input=Entry(wina,width=15)
    Cadd_input.grid(row=2,column=1,padx=(0,10),pady=(7,10))

    P_get=Button(wina,text="添加",command=Add)
    P_get.grid(row=3,column=0,padx=(10,10),pady=(0,15),columnspan=2)
#删除操作
def delet():

    def Delet():
        Epurpose=Edelet_input.get()
        Cpurpose=Cdelet_input.get()

        f=open("英语词典.txt","r")
        Words=f.readlines()
        de_nu=0
        for word in Words:
            if Epurpose in word and Cpurpose in word:
                Words.remove(word)
                de_nu+=1
        f.close()

        if de_nu==0:
            MB.showerror(title="删除错误",message="词典中不存在该单词及相应翻译")
        else:
            f=open("英语词典.txt","w")
            for word in Words:
                f.write(word)
            f.close()
            MB.showwarning(title="删除结果",message="已经成功删除%s个单词"%de_nu)

    wind=Toplevel()
    wind.title("删除")
    Delet_input_tip=Label(wind,text="请输入你想删除的对象",font=("SimSun",13))
    Delet_input_tip.grid(row=0,column=0,padx=(10,10),pady=(10,5),columnspan=2)

    Edelet_input_tip=Label(wind,text="英文单词")
    Edelet_input_tip.grid(row=1,column=0,padx=(10,0),pady=(10,0))
    Edelet_input=Entry(wind,width=15)
    Edelet_input.grid(row=1,column=1,padx=(0,10),pady=(10,0))
    Cdelet_input_tip=Label(wind,text="中文翻译")
    Cdelet_input_tip.grid(row=2,column=0,padx=(10,0),pady=(5,10))
    Cdelet_input=Entry(wind,width=15)
    Cdelet_input.grid(row=2,column=1,padx=(0,10),pady=(7,10))

    P_get=Button(wind,text="删除",command=Delet)
    P_get.grid(row=3,column=0,padx=(10,10),pady=(0,15),columnspan=2)
#测试
def test():
    f=open("英语词典.txt","r")
    Words=f.readlines()
    English=[]
    Chinese=[]
    for word in Words:
        i=0
        for symbol in word:
           if symbol != ":":
               i+=1
           else: break
        English.append(word[:i])
        Chinese.append(word[i+1:-1])
    nu=len(Chinese)
    Nu=random.randint(0,nu-1)

    def detection():
        Einput=ETest_input.get()
        if Einput==English[Nu]:
            MB.showwarning(title="结果显示",message="恭喜你答对了！\n重新点击‘记忆测验’可以进行下一轮")
        else:
            MB.showerror(title="结果显示",message="很抱歉，回答错误\n可以在页面重新进行回答")

    #窗口
    Test=Toplevel()
    Test.title("记忆测试")
    Test_input_tip=Label(Test,text="请按照中文翻译输入对应的英文单词", font=("Arial", 13))
    Test_input_tip.grid(row=0,column=0,columnspan=2,pady=5)

    CTest_appear_tip=Label(Test,text=Chinese[Nu])
    CTest_appear_tip.grid(row=1,column=0,padx=(2,10),pady=(15,5),sticky="e")
    ETest_input=Entry(Test,width=15)
    ETest_input.grid(row=1,column=1,padx=(10,2),pady=(15,5))

    BT_get=Button(Test,text="确定",command=detection)
    BT_get.grid(row=2,column=0,columnspan=2,pady=(5,30))

#初始窗口
win=Tk()
win.title("英语词典")
Tip=Label(text="请选择你要进行的操作",font=("Arial",13))
Tip.grid(row=0,column=2,padx=(10,10),pady=(10,10))

BS=Button(win,text="查询",command=search)
BS.grid(row=1,column=2,padx=10,pady=(5,5))
BA=Button(win,text="添加",command=add)
BA.grid(row=2,column=2,padx=10,pady=(0,0))
BD=Button(win,text="删除",command=delet)
BD.grid(row=3,column=2,padx=10,pady=(5,20))

Tip=Label(text="进行记忆测验",font=("Arial",10))
Tip.grid(row=4,column=2,padx=(10,10),pady=(10,5))
BT=Button(win,text="记忆测验",command=test)
BT.grid(row=5,column=2,pady=(5,40))

win.mainloop()
