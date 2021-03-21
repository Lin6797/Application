//通用类声明（内部包括注册、登录、修改密码） 

#include<iostream>
#include<vector>
using namespace std;

class Commual{
	public:
		Commual();//构造函数（给Num赋值，获得Login_message的元素）
		bool Resgin();//注册 
		string Login();//登录
		bool c_passcpde();//修改密码
		bool c_write();//修改密码后写入文件 
	private:
		string* ID;//Login_message中的用户名 
		string* Passcode;//Login_message中的密码 
		string* IsAdm;//Login_message中的是否为管理员的标志
		int Num;//数组元素个数
		vector<string> logins;//定义login容器类型和容器名字 
		bool New();
};
