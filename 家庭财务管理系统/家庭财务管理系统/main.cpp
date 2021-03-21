#include "Commual_class.h"
#include "Normal_class.h"
#include "Administrate_class.h"
#include<vector>
#include<fstream>
#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int Length; 
//管理员获取全员用户名 
string* Get_ID(){
	string* ID;//存储用户名的数组
	int Num=0;//用户数量 
	ifstream in("Login_message.txt",ios::in);//打开Login_message文件（获取全部用户名） 
	if(!in){//打开失败时用 
		cerr<<"打开文件失败"<<endl;
		return NULL;
	}
	
	string Login;//定义读取类型为string 
	vector<string> Logins;//定义Login容器类型和容器名字 
	while(getline(in,Login)){
		Num++;//目前用户数目 
		Logins.push_back(Login);//全部登陆信息进入容器
	}
	in.close();//关闭Login_message文件
	
	ID = new string[Num]; 
	int num=0;//ID编号
	vector<string>::iterator it = Logins.begin();//定义it为容器logins的迭代器
	for(;it!=Logins.end();it++){//开始进行遍历 
		for(int i=0; i<(*it).length(); i++){
			if((*it)[i]==' '){
				ID[num] = (*it).substr(0,i);//截取第一个空格前的字符串,获得ID 
				break;
			}
		}
		num++; 
	}//得到所有用户的用户名
	extern int Length;
	Length=Num;
	return ID;//返回ID数组 
}

//管理员选择操作对象 
string Choice(){
	string *ID;//用户名数组 
	ID = Get_ID();//获得ID数组
	int no=0;//输出用户名的编号 
	int purpose;//目标用户名的编号 
	while(1){
		cout<<"    -------------------------------------------------------------"<<endl;
	    for(; no<Length; no++){//输出数组的用户名 
		     cout<<"    |                  "<<no+1<<"."<<ID[no]<<endl; 
	    }
	    cout<<"    |                  "<<no+1<<"."<<"退出操作"<<endl;
	    cout<<"    -------------------------------------------------------------"<<endl;
	    no=0;//初始化no 
	    cout<<"请选择你想要进行操作的用户："; cin>>purpose;cin.sync();
	    if(purpose>0 && purpose<=Length)
	    	return ID[purpose-1];//得到对应的用户名
	    else if(purpose==Length+1) exit(1);
	    else {system("cls"); cout<<"输入数据错误，请重新输入"<<endl;continue;}
	}
}


int main(int argc, char** argv) { 
	string id;//登陆的账号用户名
	string type;//登陆的账号类型 
	
	Commual c; //登陆/注册/修改密码操作 
	char operation;//选择的操作

	while(1){
	   string c_judge = "down";//直往下走
	   system("cls");
	   cout<< "\t\t|-------------------------------------------------------|\n";
       cout<< "\t\t|                       1.登陆                          |\n";
       cout<< "\t\t|                       2.注册                          |\n";
       cout<< "\t\t|                       3.退出系统                      |\n";
       cout<< "\t\t|-------------------------------------------------------|\n";
	   cout<<"请选择你要进行的操作："; cin>>operation; cin.sync();
	   switch (operation){
	   	   case '1':{//登陆 
	   	    	system("cls");
				cout<<"**********[登陆]**********"<<endl;
	   		    id = c.Login();
	   		    break;
	   	      }
	   	    case'2':{//注册 
	   	      	system("cls");
				cout<<"**********[注册]**********"<<endl;
	   	      	c.Resgin(); c_judge = "up";//往回走 
				break;
	   	      }
	   	    case'3':{
	   	    	system("cls");
				cout<<"*********[退出系统]*********"; 
	   	    	return 0;
	   	       }
	   	    default:{
	   	    	cout<<"输入错误"; 
                continue;	
	   	       } 
	   }
	   if(c_judge == "up") continue;
	   else break;
    }
    
	type = id.substr(id.length()-1,1);//账号类型 
    id = id.substr(0,id.length()-1);//登陆账号用户名
	
	if(type=="N"){//普通账户 
		Nor n(id); char nor_oper; char con_oper;//是否继续操作标志 
        while(1){
        	cout<< "\t\t|----------------------------------------------------------|\n";
            cout<< "\t\t|                       1.查看收支信息                     |\n";
            cout<< "\t\t|                       2.写入收支信息                     |\n";
            cout<< "\t\t|                       3.删除收支信息                     |\n";
            cout<< "\t\t|                       4.修改收支信息                     |\n";
            cout<< "\t\t|                       5.退出系统                         |\n";
            cout<< "\t\t|----------------------------------------------------------|\n";
        	cout<<"请选择你要进行的操作："; cin>>nor_oper; cin.sync();
		    switch(nor_oper){
			    case'1':{n.View();break;}
			    case'2':{n.Write();break;}
			    case'3':{n.Delete();break;}
			    case'4':{n.Alter();break;}
			    case'5':{return 0;}
			    default:{system("cls");cout<<"输入错误，请重新输入"<<endl; continue;}
		    }
		    cout<<endl;
		    while(1){
			    cout<<"是否继续进行操作？（Y/N）："; cin>>con_oper;cin.sync();system("cls");
		        if(con_oper == 'N' || con_oper == 'n') return 0;
		        else if(con_oper == 'Y' || con_oper == 'y') break;
		        else {cout<<"输入错误，请重新输入"<<endl;continue;}
		    }
        }
	}
	
	else{//管理员账户 
		system("cls"); 
		char con_oper;//是否继续操作标志 
        while(1){
        	string Pu_id = Choice();//获得操作对象ID 
        	if(Pu_id==id){//处理对象为管理员自己 
				Adm A(Pu_id, "Self");//将目标用户的用户名和标志"Self"传入管理员类中 
        	}
        	else{//处理对象为除了管理员之外的人 
        		Adm A(Pu_id, "Other");//将目标用户的用户名和标志"Other"传入管理员类中 
        	}
        	cout<<"是否选择其他家庭成员继续进行操作？（Y/N）：";
        	while(1){//判断是否选择其他成员进行操作
        		cin>>con_oper; cin.sync();
        		if(con_oper=='y' || con_oper=='Y'){
        			break;
        		}
        		else if(con_oper=='n' || con_oper=='N'){
        			return 0;
        		}
        		else{
        			cout<<"输入错误，请重新输入";
        			continue;
        		}
        	}//判断是否选择其他成员进行操作结束 
        }
	}
	 
	return 0;
}

