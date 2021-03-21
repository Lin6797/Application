#include <stdio.h>
#include <iostream>
#include "SQLoperation.h"

using namespace std;

int main() {
	string name;
	string password;
	char Judge = 'N';

	string allOPERATION = "1）创建数据表；\n2）插入数据；\n3）删除数据；\n4）修改数据；\n"
		"5）删除数据表；\n6） join操作;\n7）事务支持；\n8）添加索引\n9)删除索引\n10）退出\n";

	cout << "name:"; cin >> name;
	cout << "password:"; cin >> password;
	SQLopertaion* SQ = new SQLopertaion(name, password);
	while ( Judge!='y' && Judge!='Y')
	{
		cout << allOPERATION;
		int oper;
		cout << "请输入要执行的操作：";
		cin >> oper; cin.clear();
		SQ->Operation(oper);

		cout << "是否已完成所有操作（Y/N）：";
		cin >> Judge; cin.clear();

		if (Judge == 'y' || Judge == 'Y') { break; }
		system("cls");
	}
	
	return 0;
}