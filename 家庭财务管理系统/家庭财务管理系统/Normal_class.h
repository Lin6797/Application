//普通成员可以进行的操作类声明(包括写自己的账户，查看自己的账户，删除自己的账户)
#include<iostream>
#include<vector>
using namespace std;

class Nor{
	public:
		Nor(string id);//构造函数(将文件中的账户数据读取出来)
		bool View();//查看收支记录 
		bool Write();//写收支记录 
		bool Delete();//删除收支记录 
		bool Alter();//修改收支记录 
	private:
		int Num; //数组元素个数
		string ID; //存储用户名
		vector<string> finances;//定义容器类型和容器名字（用于存储本用户的财务信息）
		vector<string> other_finances;//定义容器类型和容器名字（用于存储其他用户的财务信息）
		bool New_vector(string id); //用于更新容器内数据 
		bool New_file();//用于更新文件信息
};

