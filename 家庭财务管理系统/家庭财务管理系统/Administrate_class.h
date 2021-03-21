//管理员类 

#include<iostream>
using namespace std;

class Adm{
	public:
		Adm(string ID, string object);//构造函数
		bool Delete_all();//删除家庭成员 
		bool View();//查看成员收支信息
		bool Edit_finance();//编辑成员收支信息
	private:
		string Pu_id;//操作对象ID
		string Object;//判断操作对象为管理员自己或者他人
		bool Choice_opera_self();//选择操作（对象为管理员自己时）
		bool Choice_opera_other();//选择操作(对象为出管理员外的家庭成员时)
		bool Delete_login();//删除Login_message文件中的对应数据 
	    bool Delete_member();//删除Member_message文件中的对应数据
	    bool Delete_finance();//删除Finance_message文件中的对应数据
};
