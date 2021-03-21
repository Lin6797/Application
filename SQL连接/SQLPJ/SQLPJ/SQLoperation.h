//SQL���ݿ����ͷ�ļ�
//���ݿ���Ŀ��һ��

//1���������ݱ�2���������ݣ�3��ɾ�����ݣ�4���޸����ݣ�5��ɾ�����ݱ�6 �����ݱ����������join��
//1������֧�֣�2������֧��
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
	RETCODE retcode;//���󷵻���
	SQLHENV  henv = SQL_NULL_HENV;//���廷�����
	SQLHDBC  hdbc1 = SQL_NULL_HDBC;//�������ݿ����Ӿ��     
	SQLHSTMT  hstmt1 = SQL_NULL_HSTMT;//���������
	const char* szDSN = "myLinuxData";//�������Դʱ��Ϊ���������
	string name;
	string password;
	string allOPERATION = "1���������ݱ�\n2���������ݣ�\n3��ɾ�����ݣ�\n4���޸����ݣ�\n5��ɾ�����ݱ�\n6 join����;\n7������֧�֣�\n8������֧��\n";
	string OPERATION = "1���������ݣ�\n2��ɾ�����ݣ�\n3���޸����ݣ�";
	int total = 0;
	//����ȷ������
	void connect(const char* name, const char* password);
	//ѡȡ���
	string selectTable();
	//ѡ�����������֮��Ĺ���
	void selectoperation(int oper);
	//���SQL���
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
	//����
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

