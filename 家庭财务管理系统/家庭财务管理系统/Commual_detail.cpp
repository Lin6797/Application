//实现Commul类

#include"Commual_class.h"
#include<fstream>
#include<vector> 
using namespace std;

//构造函数 
Commual::Commual(){ 
	Num=0; //初始化给数组的元素个数

	ifstream in("Login_message.txt",ios::in);//打开Login_message文件 
	if(!in){//打开失败时用 
		cerr<<"此时系统为无用户,故请先进行注册"<<endl;
		Resgin();
		return ;
	}
	
	string login;//定义读取类型为string 
	while(getline(in,login)){
		Num++;
		logins.push_back(login);//进入容器 
	}
	in.close();//关闭Login_message文件 
	
	ID = new string[Num];
	Passcode = new string[Num];
	IsAdm = new string[Num];
	int num=0;//数组元素编号  
	string Judge="name";//判断获得的字符串类型 
	
	vector<string>::iterator it = logins.begin();//定义it为容器logins的迭代器
	for(;it!=logins.end();it++){//开始进行分割 
		int start=0;//遍历字符串的起始位置
		for(int i=0; i<(*it).length(); i++){
			if((*it)[i]==' ' && Judge=="name"){
				ID[num] = (*it).substr(start,i-start);
				start = i+1; Judge = "passcode";
			}
			else if((*it)[i]==' ' && Judge=="passcode"){
				Passcode[num] = (*it).substr(start,i-start);
				start = i+1; Judge = "IsAdm";
			}
			else if((*it)[i]==' ' && Judge=="IsAdm"){
				IsAdm[num] = (*it).substr(start,i-start);
				start = i; Judge = "name";
			}
		}
		num++;
	}
}

//更新函数
bool Commual::New(){ 
	Num=0; //初始化给数组的元素个数
	logins.clear();
	ifstream in("Login_message.txt",ios::in);//打开Login_message文件 
	if(!in){//打开失败时用 
		cerr<<"此时文件为空"<<endl;
		Resgin();
		return false;
	}
	
	string login;//定义读取类型为string 
	while(getline(in,login)){
		Num++;
		cout<<"Num:"<<Num<<endl;
		logins.push_back(login);//进入容器 
	}
	in.close();//关闭Login_message文件 
	
	ID = new string[Num];
	Passcode = new string[Num];
	IsAdm = new string[Num];
	int num=0;//数组元素编号  
	string Judge="name";//判断获得的字符串类型 
	
	vector<string>::iterator it = logins.begin();//定义it为容器logins的迭代器
	for(;it!=logins.end();it++){//开始进行分割 
		int start=0;//遍历字符串的起始位置
		for(int i=0; i<(*it).length(); i++){
			if((*it)[i]==' ' && Judge=="name"){
				ID[num] = (*it).substr(start,i-start);
				start = i+1; Judge = "passcode";
			}
			else if((*it)[i]==' ' && Judge=="passcode"){
				Passcode[num] = (*it).substr(start,i-start);
				start = i+1; Judge = "IsAdm";
			}
			else if((*it)[i]==' ' && Judge=="IsAdm"){
				IsAdm[num] = (*it).substr(start,i-start);
				start = i; Judge = "name";
			}
		}
		num++;
	}
	return true;
}

//注册
bool Commual::Resgin(){
	string in_ID, in_Pass1, in_Pass2; //输入的用户名、密码 
	char in_IsAdm; //输入的判断是否为管理员 
	
	string Judge;//作为某个板块的比较完成的标志
	ofstream out_login("Login_message.txt",ios::app);//打开文件，便于后面输入 
	while(1){ //判断用户名是否可以输入
		cout<<"请输入用户名：";cin>>in_ID; 
		Judge = "equal";
		for(int i=0; i<Num; i++){
			if(ID[i] == in_ID){ //不满足要求
				cout<<"该用户名已被使用，请重新输入"<<endl;
				Judge = "inequal"; break;
			}
		}
		if(Judge == "equal"){ //满足要求 
			out_login<<in_ID<<" "; break;
		}
	}
	
	while(1){ //判断密码是否可以输入 
		cout<<"请输入密码："; cin>>in_Pass1;
		cout<<"请再次输入密码："; cin>>in_Pass2;
		Judge = "equal";
		if(in_Pass1 != in_Pass2){
			cout<<"输入的密码不同，请重新输入"<<endl;
			Judge = "inequal";
		}
		if(Judge == "equal"){
			out_login<<in_Pass1<<" "; break; 
		}
	}
	
	//判断其输入的管理员判断标志 
	cout<<"该成员是否为管理员？（y/n）:"; cin>>in_IsAdm;
	if(in_IsAdm=='y' || in_IsAdm=='Y'){
		Judge="equal";
		for(int i=0; i<Num; i++){
			if(IsAdm[i] == "Y"){//已经存在管理员 
				cout<<"已经存在管理员，故不可成为管理员"<<endl;
				out_login<<"N"<<" "<<"\n"; Judge="inequal"; break;
			}
		}
		if(Judge == "equal")//不存在管理员 
		out_login<<"Y"<<" "<<"\n";
	}
	else if(in_IsAdm=='n' || in_IsAdm=='N'){
		out_login<<"N"<<" "<<"\n";
	}
	
	out_login.close();
	//向Login_message文件中添加消息完成
	 
	//开始向Member_messahe中添加成员信息
	string name,sex,age,weight,height;//各种个人信息
	int birth_year,birth_mouth,birth_day;//出生年月日 
	 
	ofstream out("Member_message.txt",ios::app);//打开文件
	out<<in_ID<<" "; 
	cout<<"请输入真实姓名："; cin>>name; out<<name<<" ";
	cout<<"请输入性别(男/女)："; cin>>sex; out<<sex<<" ";
	cout<<"请输入出生年月日（年 月 日）："; cin>>birth_year; cin>>birth_mouth; cin>>birth_day;  out<<birth_year<<" "<<birth_mouth<<" "<<birth_day<<" ";
	cout<<"请输入年龄："; cin>>age; out<<age<<" ";
	cout<<"请输入体重（kg）:"; cin>>weight; out<<weight<<" ";
	cout<<"请输入身高（m）："; cin>>height; out<<height<<" "<<"\n";
	out.close();
	
	New();
	return true; 
}

//登陆
string Commual::Login(){
	string id,passcode;//从外界获取的用户名和密码 
	
	while(1){
		string Judge="inexist";//判断输入的用户名是否存在的标志 
	    cout<<"请输入用户名：";cin>>id;
	    cout<<"请输入密码：";cin>>passcode;
		
		for(int i=0; i<Num; i++){
			if(ID[i]==id){
				Judge="exist";//存在有该用户名
				if(Passcode[i]==passcode){//登录成功 
					if(IsAdm[i]=="Y"){
						system("cls");
						cout<<"登陆管理员账号成功"<<endl;//看结果用的，后面记得删掉
						return id+IsAdm[i]; 
					}
					else{
						system("cls");
						cout<<"登陆普通成员账号成功"<<endl;
						return id+IsAdm[i];
					}
				}
				else{//密码输入错误 
					system("cls"); 
					cout<<"**********[登陆]**********"<<endl;
					cout<<"密码输入错误，请重新输入"<<endl;
					break;
				}
			}
		}//for循环结束 
		if(Judge=="inexist"){
			system("cls");
			cout<<"**********[登陆]**********"<<endl;
			cout<<"该用户名不存在，请重新输入"<<endl;
		}
	}
}

//修改密码
bool Commual::c_passcpde(){
	string pu_ID,new_Pass1,new_Pass2;//要修改密码的对象和新密码 
	string Judge; string origin_passcode;
	while(1){
		cout<<"请输入用户名："; cin>>pu_ID;
		Judge = "inexist";
		for(int i=0; i<Num; i++){
			if(ID[i] == pu_ID){//存在想要修改的 
			    Judge = "exist";
			    while(1){//判断输入的原密码正确与否 
			    	cout<<"请输入原密码:";cin>>origin_passcode;cin.sync();
			    	if(origin_passcode == Passcode[i]){//正确，可以开始准备修改密码 
					    while(1){//判断两个新密码相同与否 
					        cout<<"请输入新密码："; cin>>new_Pass1; cin.sync();
			    		    cout<<"请再一次输入新密码："; cin>>new_Pass2; cin.sync();
			    		    if(new_Pass1 == new_Pass2){ //相同则成功修改 
			    		    	Passcode[i]=new_Pass1;
			    		    	cout<<"******修改成功********"<<endl;
								return true;//跳出这个程序 
			    		    }
			    		    else{//不同则返回重新输入 
			    		    	system("cls");
			    		    	cout<<"修改对象为："<<pu_ID<<endl;
			    		    	cout<<"两次输入的新密码不一致，请重新输入"<<endl;
			    		    }
						}
						break;//里面修改出来，直接跳出判断输入原密码是否同的循环 
			    	}
			    	else{//不正确，返回重新输入密码 
			    	   system("cls");
			    	   cout<<"与原密码不一致，请重新输入"<<endl;
					}
			    }
			}
			//else (本会有的，但是没必要) 
		} 
		if(Judge == "inexist"){
			cout<<"该用户名不存在，请重新输入"<<endl;
			continue;
		}
	}
}
bool Commual::c_write(){
	ofstream out("Login_message.txt",ios::out);
	for(int i=0; i<Num; i++){
		out<<ID[i]<<" "<<Passcode[i]<<" "<<IsAdm[i]<<" "<<endl;
	}
	out.close();
}
