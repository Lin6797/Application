//普通成员可以进行的操作实现(包括写自己的账户，查看自己的账户，删除自己的账户)

#include"Normal_class.h"
#include<fstream>
#include<vector>
using namespace std;

Nor::Nor(string id){
	ID = id;
	Num = 0;//数组数量初始化（预测情况下：Num=num） 
	ifstream in("Finance_message.txt",ios::in);
	if(!in){
		cerr<<"目前未有收支信息"<<endl;
		return ;
	}
	
	string finance;//读取到的财务信息 
	while(getline(in,finance)){
		for(int i=0; i<finance.length(); i++){
			if(finance[i]==' '){
				if(finance.substr(0,i) == id){
					finances.push_back(finance);//该用户财务信息进入容器
					break;
				}
				else{
					other_finances.push_back(finance);//其他用户财务信息进入容器 
					break;
				}
			}
		}
	}
	in.close();//关闭 Finance_message文件
}
//更新容器内数据 
bool Nor::New_vector(string id){
	ID = id;
	Num = 0;//数组数量初始化（预测情况下：Num=num） 
	ifstream in("Finance_message.txt",ios::in);
	finances.clear();
	string finance;
	while(getline(in,finance)){
		for(int i=0; i<finance.length(); i++){
			if(finance[i]==' '){
				if(finance.substr(0,i) == id){
					finances.push_back(finance);//进入容器
					break;
				}
				else break;
			}
		}
	}
	in.close();//关闭 Finance_message文件
}

//更新文件内数据 
bool Nor::New_file(){
	ofstream out("Finance_message.txt",ios::out);//打开文件 
	vector<string>::iterator other = other_finances.begin();//定义迭代器类型以及迭代器指针
	while(other!=other_finances.end()){
		out<<*other<<endl;//将其他成员的信息写入文件
		other++; 
	}
	vector<string>::iterator it = finances.begin();//定义迭代器类型以及迭代器指针
	while(it!=finances.end()){
		out<<*it<<endl;//将该成员修改后的信息写入文件
		it++;
	}
	out.close();//关闭文件 
}
//查看收支信息 
bool Nor::View(){ 
	int i=1;//编号 
	vector<string>::iterator it = finances.begin();//定义迭代器类型和迭代器，同时给迭代器赋值 
	while(it!=finances.end()){
		cout<<i<<"  "<<*it<<endl;
		it++; i++;
	}
}

//书写收支信息 
bool Nor::Write(){
	int year,mouth,day;
	char Kind;string Type_symbol; char Type;
	float account;
	
	char Judge;//判断标志 
	ofstream out("Finance_message.txt",ios::app);//追加 

		out<<ID<<" ";
		cout<<"请输入交易进行时间(年 月 日)："; cin>>year;cin>>mouth;cin>>day; out<<"交易时间:"<<year<<" "<<mouth<<" "<<day<<" ";
		
		cout<< "\t\t|----------------------------------------------------------------|\n";
        cout<< "\t\t|                          1.收入                                |\n";
        cout<< "\t\t|                          2.支出                                |\n";
        cout<< "\t\t|----------------------------------------------------------------|\n";
		while(1){//选择收入或者支出 
            cout<<"请选择你要记录的种类："; cin>>Kind;cin.sync();
			switch(Kind){
				case'1':{Type_symbol="income";break;}
				case'2':{Type_symbol="expen";break;}
				default:{cout<<"输入错误，请重新输入"<<endl;continue;}
			}
			break;
		}
		
		if(Type_symbol == "expen"){//支出 
			cout<< "\t\t|-----------------------------------------------------------------|\n";
            cout<< "\t\t|                            1.食物                               |\n";
        	cout<< "\t\t|                            2.交通                               |\n";
        	cout<< "\t\t|                            3.购物                               |\n";
        	cout<< "\t\t|                            4.娱乐                               |\n";
        	cout<< "\t\t|                            5.学习                               |\n";
        	cout<< "\t\t|                            6.医疗                               |\n";
        	cout<< "\t\t|                            7.其他                               |\n";
        	cout<< "\t\t|-----------------------------------------------------------------|\n";
        	cout<<"请选择类型："; cin>>Type; cin.sync();
			while(1){
		 	 switch(Type){
        		case'1':{out<<"交易原因："<<"食物"<<" "; break;}
        		case'2':{out<<"交易原因："<<"交通"<<" "; break;}
        		case'3':{out<<"交易原因："<<"购物"<<" "; break;} 
        		case'4':{out<<"交易原因："<<"娱乐"<<" "; break;}
        		case'5':{out<<"交易原因："<<"学习"<<" "; break;} 
        		case'6':{out<<"交易原因："<<"医疗"<<" "; break;} 
        		case'7':{out<<"交易原因："<<"其他"<<" "; break;}
        		default:{cout<<"输入错误，请重新输入"<<endl; continue;} 
          	  }
          	  cout<<"请输入交易金额(元)：";
			  cin>>account; cin.sync();
			  out<<"交易金额："<<"-"<<account<<"元 "<<"\n";
          	  break;
        	}
		}
		
		else {//收入 
			cout<< "\t\t|------------------------------------------------------------------|\n";
            cout<< "\t\t|                           1.工资                                 |\n";
        	cout<< "\t\t|                           2.奖金                                 |\n";
        	cout<< "\t\t|------------------------------------------------------------------|\n";
        	cout<<"请选择类型："; cin>>Type; cin.sync();
        	while(1){
		 	 switch(Type){
        		case'1':{out<<"交易原因："<<"工资"<<" "; break;}
        		case'2':{out<<"交易原因："<<"奖金"<<" "; break;}
        		default:{cout<<"输入错误，请重新输入"<<endl; continue;} 
          	  }
          	  cout<<"请输入交易金额(元)：";
			  cin>>account; cin.sync();
			  out<<"交易金额："<<"+"<<account<<"元 "<<"\n";
          	  break;
        	}
		}
		out.close();
		
	New_vector(ID);//更新容器内数据（从文件内读出) 
}

bool Nor::Delete(){//删除数据 
	int purpose;
	View();
	cout<<"请输入你想要删除的收支信息编号：";
	while(1){
		cin>>purpose; cin.sync();
		if(purpose>finances.size()||purpose<=0){
			cout<<"输入错误，请重新输入：";
			continue;
		}
		break;
	}
	finances.erase(finances.begin()+purpose-1);
	New_file();//更新文件信息 
}

//修改收支记录 
bool Nor::Alter(){
	int purpose;
	View();
	cout<<"请输入你想要修改的收支信息编号：";
	while(1){
		cin>>purpose; cin.sync();
		if(purpose>finances.size()||purpose<=0){
			cout<<"输入错误，请重新输入：";
			continue;
		}
		break;
	}
	finances.erase(finances.begin()+purpose-1);
	New_file();
	cout<<"请输入修改后的收支信息："<<endl;
	Write();
}
