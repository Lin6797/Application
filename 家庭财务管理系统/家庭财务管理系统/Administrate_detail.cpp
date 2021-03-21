//管理员类的实现
#include"Administrate_class.h"
#include"Normal_class.h"
#include<vector>
#include<fstream>
using namespace std;

//构造函数
Adm::Adm(string ID, string object){
	Pu_id=ID; Object=object;
	cout<<"Object:"<<Object<<endl;
	if(Object=="Self"){
		Choice_opera_self();//选择操作 
	}
	else{
		Choice_opera_other();//选择操作 
	}
}

//选择操作（对象为管理员本身时）
bool Adm::Choice_opera_self(){
	char nor_oper;//操作标志 
	char con_oper;//是否继续操作标志
	Nor s(Pu_id); 
	while(1){
        cout<< "\t\t|----------------------------------------------------------|\n";
        cout<< "\t\t|                       1.查看收支信息                     |\n";
        cout<< "\t\t|                       2.写入收支信息                     |\n";
        cout<< "\t\t|                       3.删除收支信息                     |\n";
        cout<< "\t\t|                       4.修改收支信息                     |\n";
        cout<< "\t\t|                       5.退出操作                         |\n";
        cout<< "\t\t|----------------------------------------------------------|\n";
        cout<<"请选择你要进行的操作："; cin>>nor_oper; cin.sync();
		switch(nor_oper){
			case'1':{s.View();break;}
			case'2':{s.Write();break;}
			case'3':{s.Delete();break;}
			case'4':{s.Alter();break;}
			case'5':{return 0;}
			default:{system("cls");cout<<"输入错误，请重新输入"<<endl; continue;}
		}
		cout<<endl;
		while(1){
			cout<<"是否继续对该成员进行操作？（Y/N）："; cin>>con_oper;cin.sync();system("cls");
		    if(con_oper == 'N' || con_oper == 'n') return 0;
		    else if(con_oper == 'Y' || con_oper == 'y') break;
		    else {cout<<"输入错误，请重新输入"<<endl;continue;}
		}
    }
}

//选择操作（对象为除管理员外的其他家庭成员时）
bool Adm::Choice_opera_other(){
	char nor_oper;//操作标志 
	char con_oper;//是否继续操作标志
	Nor t(Pu_id); 
	while(1){
        cout<< "\t\t|----------------------------------------------------------|\n";
        cout<< "\t\t|                       1.查看收支信息                     |\n";
        cout<< "\t\t|                       2.写入收支信息                     |\n";
        cout<< "\t\t|                       3.删除收支信息                     |\n";
        cout<< "\t\t|                       4.修改收支信息                     |\n";
        cout<< "\t\t|                       5.删除该成员信息                   |\n";
        cout<< "\t\t|                       6.退出操作                         |\n";
        cout<< "\t\t|----------------------------------------------------------|\n";
        cout<<"请选择你要进行的操作："; cin>>nor_oper; cin.sync();
		switch(nor_oper){
			case'1':{t.View();break;}
			case'2':{t.Write();break;}
			case'3':{t.Delete();break;}
			case'4':{t.Alter();break;}
			case'5':{Delete_all();return true;}
			case'6':{return 0;}
			default:{system("cls");cout<<"输入错误，请重新输入"<<endl; continue;}
		}
		cout<<endl;
		while(1){
			cout<<"是否继续对该成员进行操作？（Y/N）："; cin>>con_oper;cin.sync();system("cls");
		    if(con_oper == 'N' || con_oper == 'n') return 0;
		    else if(con_oper == 'Y' || con_oper == 'y') break;
		    else {cout<<"输入错误，请重新输入"<<endl;continue;}
		}
    }
}

//删除家庭成员的全部资料 
bool Adm::Delete_all(){
	Delete_login();//删除Login_message文件中的对应数据 
	Delete_member();//删除Member_message文件中的对应数据 
	Delete_finance();//删除Finance_message文件中的对应数据 
}

//删除登陆信息 
bool Adm::Delete_login(){
	ifstream in("Login_message.txt",ios::in);
	string login;
	vector<string> logins;//定义容器类型和容器名字 
	while(getline(in,login)){
		for(int i=0; i<login.length(); i++){
			if(login[i]==' '){//截取第一个空格前面的字符串 
				if(login.substr(0,i) != Pu_id)
				 logins.push_back(login);//进入容器logins.push_back(login);//进入容器
				break;
			}
		} 
	}
	in.close();
	//读取，挑选除了Pu_id外的存放在容器中
	 
	ofstream out("Login_message.txt",ios::out);
	vector<string>::iterator it = logins.begin();//定义迭代器类型和迭代器，同时给迭代器赋值 
	while(it!=logins.end()){
		out<<*it<<endl;
		it++;
	}
	out.close();
	//写入，清空原文件，将容器保存的写入文件中 
}

//删除成员信息 
bool Adm::Delete_member(){
	ifstream in("Member_message.txt",ios::in);
	string member;
	vector<string> members;//定义容器类型和容器名字 
	while(getline(in,member)){
		for(int i=0; i<member.length(); i++){
			if(member[i]==' '){//截取第一个空格前面的字符串 
				if(member.substr(0,i) != Pu_id)
				 members.push_back(member);//进入容器logins.push_back(login);//进入容器
				break;
			}
		} 
	}
	in.close();
	//读取，挑选除了Pu_id外的存放在容器中
	 
	ofstream out("Member_message.txt",ios::out);
	vector<string>::iterator it = members.begin();//定义迭代器类型和迭代器，同时给迭代器赋值 
	while(it!=members.end()){
		out<<*it<<endl;
		it++;
	}
	out.close(); 
	//写入，清空原文件，将容器保存的写入文件中 
}

//删除财务信息 
bool Adm::Delete_finance(){
	ifstream in("Finance_message.txt",ios::in);
	string finance;
	vector<string> finances;//定义容器类型和容器名字 
	while(getline(in,finance)){
		for(int i=0; i<finance.length(); i++){
			if(finance[i]==' '){//截取第一个空格前面的字符串 
				if(finance.substr(0,i) != Pu_id)
				 finances.push_back(finance);//进入容器logins.push_back(login);//进入容器
				break;
			}
		} 
	}
	in.close();
	//读取，挑选除了Pu_id外的存放在容器中
	 
	ofstream out("Finance_message.txt",ios::out);
	vector<string>::iterator it = finances.begin();//定义迭代器类型和迭代器，同时给迭代器赋值 
	while(it!=finances.end()){
		out<<*it<<endl;
		it++;
	}
	out.close();
	//写入，清空原文件，将容器保存的写入文件中 
} 
