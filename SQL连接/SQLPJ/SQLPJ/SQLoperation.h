//SQL数据库操作头文件
//数据库项目第一题

//1）创建数据表；2）插入数据；3）删除数据；4）修改数据；5）删除数据表；6 跨数据表操作（例如join）
//1）事务支持；2）索引支持
#include <Windows.h>
#include <iostream>
#include <string.h>
#include <iomanip>
#include <sql.h>
#include <odbcss.h>
#include <sqlext.h>

using namespace std;

class SQLopertaion {
public:
	SQLopertaion(string Name, string Password);
	void Operation(int oper);
private:
	RETCODE retcode;//错误返回码
	SQLHENV  henv = SQL_NULL_HENV;//定义环境句柄
	SQLHDBC  hdbc1 = SQL_NULL_HDBC;//定义数据库连接句柄     
	SQLHSTMT  hstmt1 = SQL_NULL_HSTMT;//定义语句句柄
	const char* szDSN = "myLinuxData";//添加数据源时，为其起的名字
	string name;
	string password;
	string allOPERATION = "1）创建数据表；\n2）插入数据；\n3）删除数据；\n4）修改数据；\n5）删除数据表；\n6 join操作;\n7）事务支持；\n8）索引支持\n";
	string OPERATION = "1）插入数据；\n2）删除数据；\n3）修改数据；";
	int total = 0;
	//事先确保连接
	void connect(const char* name, const char* password);
	//选取表格
	string selectTable();
	//选择除事务，索引之外的功能
	void selectoperation(int oper);
	//获得SQL语句
	string createTable_sql();
	string insertData_sql();
	string insertData_getData(string table);
	string deleteData_sql();
	string deleteData_getData(string table);
	string updateData_sql();
	string updateData_getData(string table);
	string join_sql();
	string joingetSymbol(string table);
	string indexAdd_sql();
	string indexAdd_Symbol(string table);
	string indexDelete_sql();
	string indexDelete_Index(string table);
	//操作
	void createTable();
	void insertData();
	void deleteData();
	void updateData();
	void dropTable();
	void join();
	void transaction();
	void indexAdd();
	void indexDelete();
};

