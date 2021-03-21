#include "SQLoperation.h"

#define MAXBUFLEN   255 
#define MaxNameLen  20

//���캯��
SQLopertaion::SQLopertaion(string Name, string Password) {
    name = Name;
    password = Password;
    connect(name.c_str(), password.c_str());
}

//�������ݿ�
void SQLopertaion::connect(const char* name, const char* password) {
    //��������
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);
    if (retcode < 0)//������
    {
        cout << "allocate ODBC Environment handle errors." << endl;
        getchar(); exit(1);
    }

    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
        (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if (retcode < 0) //������
    {
        cout << "the  ODBC is not version3.0 " << endl;
        getchar(); exit(1);
    }

    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);
    if (retcode < 0) //������
    {
        cout << "allocate ODBC connection handle errors." << endl;
        getchar(); exit(1);
    }

    retcode = SQLConnect(hdbc1, (SQLCHAR*)szDSN, (SWORD)strlen(szDSN),
        (SQLCHAR*)name,
        (SWORD)strlen(name),
        (SQLCHAR*)password,
        (SWORD)strlen(password));

    if (retcode < 0) //������
    {
        cout << "connect to  ODBC datasource errors." << endl;
        getchar(); exit(1);
    }
    else {
        cout << "connect successfully!" << endl;
    }

    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
    if (retcode < 0)
    {
        cout << "allocate ODBC statement handle errors." << endl;
        getchar(); exit(1);
    }

    //�ر�����
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);//�ͷ������ 
    SQLDisconnect(hdbc1);//�Ͽ������ݿ������
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);//�ͷ����Ӿ��  
    SQLFreeHandle(SQL_HANDLE_ENV, henv);//�ͷŻ������ 
}

//���־������
void SQLopertaion::Operation(int oper) {
    //��������
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);

    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
        (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);

    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);

    retcode = SQLConnect(hdbc1, (SQLCHAR*)szDSN, (SWORD)strlen(szDSN),
        (SQLCHAR*)name.c_str(),
        (SWORD)strlen(name.c_str()),
        (SQLCHAR*)password.c_str(),
        (SWORD)strlen(password.c_str()));

    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);

    //����ѡ��
    switch (oper) {
    case 1: {
        createTable();
        break;
    }
    case 2: {
        insertData();
        break;
    }
    case 3: {
        deleteData();
        break;
    }
    case 4: {
        updateData();
        break;
    }
    case 5: {
        dropTable();
        break;
    }
    case 6: {
        join();
        break;
    }
    case 7: {
        transaction();
        break;
    }
    case 8: {
        indexAdd();
        break;
    }
    case 9: {
        indexDelete();
        break;
    }
    default: {
        exit(1);
    }
    }


    //�Ͽ�����
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);//�ͷ������ 
    SQLDisconnect(hdbc1);//�Ͽ������ݿ������
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);//�ͷ����Ӿ��  
    SQLFreeHandle(SQL_HANDLE_ENV, henv);//�ͷŻ������ 
}

//��ô�������SQL���
string SQLopertaion::createTable_sql() {
    string temp;
    string sql = "create table `";

    cout << "�������½�������";
    cin >> temp;
    sql = sql + temp + "`(";

    while (1) {
        char Judge;

        cout << "������������";
        cin >> temp;
        sql = sql + "`" + temp + "`";
        cout << "�����������ͣ�";
        cin >> temp;
        sql = sql + temp + ", ";

        cout << "�Ƿ��Ѿ�������룿��Y/N����";
        rewind(stdin);  Judge = getchar();
        if (Judge == 'y' || Judge == 'Y') {
            sql = sql.replace(size(sql) - 2, size(sql), ");");
            break;
        }
        //û�й涨�����������
    }
    return sql;
}

//��ʼ�������
void SQLopertaion::createTable() {
    //�������
    string sql = createTable_sql();
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "Executing statement  throught ODBC  errors." << endl;
        exit(1);
    }
    else
    {
        cout << "create successfully!!" << endl;
    }
}

//ѡ��(�ǵ��޸����ݿ���)
string SQLopertaion::selectTable() {
    string temp;
    //ѡ��
    const char* fun1 = "select table_name from information_schema.tables where Table_schema='mylinuxsql';";
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)fun1, SQL_NTS);
    if (retcode < 0)
    {
        cout << "errors." << endl;
        exit(1);
    }
    SQLCHAR      runoob_title[MaxNameLen + 1];
    SQLLEN         columnLen = 0;

    retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, runoob_title, MaxNameLen, &columnLen);
    cout << "���ݿ����б����£�" << endl;
    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        cout << setw(20) << "Table_name:" << runoob_title << endl;
    }
    cout << "ѡ����Ҫ�ı��"; cin >> temp;

    return temp;
}

//��ò������ݵ�SQL���
string SQLopertaion::insertData_sql() {
    
    //��ñ�����������SQL���
    string table;
    string sql;

    //ѡ��
    table = selectTable();
    sql = "insert into " + table + " values(";

    //��øñ��е���ɲ�����SQL���
    sql = sql + insertData_getData(table);

    return sql;
}

//�����Ҫ����ĸ����Ԫ�ؾ���ֵ
string SQLopertaion::insertData_getData(string table) {
    string temp;
    string sql = "";
    //��øñ��е���ɲ�����SQL���
    string fun = "select Column_name,Data_type from information_schema.columns where table_name = '" + table + "'";
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(fun.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "errors." << endl;
        exit(1);
    }
    SQLCHAR      runoob_title1[MaxNameLen + 1];
    SQLCHAR      runoob_title2[MaxNameLen + 1];
    SQLLEN       columnLen = 0;

    retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, runoob_title1, MaxNameLen, &columnLen);
    retcode = SQLBindCol(hstmt1, 2, SQL_C_CHAR, runoob_title2, MaxNameLen, &columnLen);
    cout << "(��Ϊchar���ͣ�����ǰ����ӵ�����)" << endl;
    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        cout << setw(10) << "Column_name:" << runoob_title1 << "    ";
        cout << setw(10) << "Data_type:" << runoob_title2 << endl;
        cout << "����Ŀ��������ݣ�"; cin >> temp;
        sql = sql + temp + ",";
    }
    sql = sql.replace(size(sql) - 1, size(sql), ");");

    return sql;
}

//��������
void SQLopertaion::insertData() {
    string sql = insertData_sql();
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "insert error." << endl;
        exit(1);
    }
    else
    {
        cout << "insert successfully!!" << endl;
    }
}

//ɾ������
void SQLopertaion::deleteData() {
    string sql = deleteData_sql();
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "delete error." << endl;
        exit(1);
    }
    else
    {
        cout << "delete successfully!!" << endl;
    }
}

//���ɾ�����ݵ�SQL����
string SQLopertaion::deleteData_sql() {
    string table;
    string sql;

    table = selectTable();
    sql = deleteData_getData(table);

    return sql;
}

//ѡ��ɾ�����ݵ�����
string SQLopertaion::deleteData_getData(string table) {
    string temp;
    string sql = "delete from "+ table +" where ";
    //��øñ��е���ɲ�����SQL���
    string fun = "select Column_name,Data_type from information_schema.columns where table_name = '" + table + "'";
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(fun.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "errors." << endl;
        exit(1);
    }
    SQLCHAR      runoob_title1[MaxNameLen + 1];
    SQLCHAR      runoob_title2[MaxNameLen + 1];
    SQLLEN       columnLen = 0;

    retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, runoob_title1, MaxNameLen, &columnLen);
    retcode = SQLBindCol(hstmt1, 2, SQL_C_CHAR, runoob_title2, MaxNameLen, &columnLen);
    
    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        cout << setw(10) << "Column_name:" << runoob_title1 << "    ";
        cout << setw(10) << "Data_type:" << runoob_title2 << endl;
    }

    cout << "(��Ϊchar���ͣ�����ǰ����ӵ�����)" << endl;
    cout << "������ɾ��������" << endl; cin >> temp;
    sql = sql + temp + " ;";

    return sql;
}

//��������
void SQLopertaion::updateData() {
    string sql = updateData_sql();
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "updata error." << endl;
        exit(1);
    }
    else
    {
        cout << "update sucessfully!" << endl;
    }
}

//��ø������ݵ�SQL����
string SQLopertaion::updateData_sql() {
    string table;
    string sql;

    table = selectTable();
    sql = updateData_getData(table);

    return sql;
}

//ѡ���������
string SQLopertaion::updateData_getData(string table) {
    string temp;
    string sql = "update " + table + " set ";
    //��øñ��е���ɲ�����SQL���
    string fun = "select Column_name,Data_type from information_schema.columns where table_name = '" + table + "'";
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(fun.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "errors." << endl;
        exit(1);
    }
    SQLCHAR      runoob_title1[MaxNameLen + 1];
    SQLCHAR      runoob_title2[MaxNameLen + 1];
    SQLLEN       columnLen = 0;

    retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, runoob_title1, MaxNameLen, &columnLen);
    retcode = SQLBindCol(hstmt1, 2, SQL_C_CHAR, runoob_title2, MaxNameLen, &columnLen);

    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        cout << setw(10) << "Column_name:" << runoob_title1 << "    ";
        cout << setw(10) << "Data_type:" << runoob_title2 << endl;
    }

    cout << "(��Ϊchar���ͣ�����ǰ����ӵ�����)" << endl;
    cout << "��������º�����"; cin >> temp;
    sql = sql + temp + " where ";
    cout << "���������������"; cin >> temp;
    sql = sql + temp + ";";

    return sql;
}

//ɾ�����
void SQLopertaion::dropTable() {
    string table;
    string sql = "drop table ";

    table = selectTable();
    sql = sql + table;

    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "drop error." << endl;
        exit(1);
    }
    else
    {
        cout << "drop sucessfully!" << endl;
    }
}

//���join
void SQLopertaion::join() {
    string sql = join_sql();
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "join error." << endl;
        exit(1);
    }
    else
    {
        cout << "join sucessfully!" << endl;
    }

    cout << "�õ����Ϊ��" << endl;
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "errors." << endl;
        exit(1);
    }
    SQLCHAR** runoob_title = new SQLCHAR * [total];
    SQLLEN       columnLen = 0;
    for (int i = 0; i < total; i++) {
        runoob_title[i] = new SQLCHAR[MaxNameLen + 1];
    }

    for (int i = 1; i <= total; i++) {
        retcode = SQLBindCol(hstmt1, i, SQL_C_CHAR, runoob_title[i-1], MaxNameLen, &columnLen);
    }
    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        for (int i = 0; i < total; i++) {
            cout << setw(9) << runoob_title[i] << "    ";
        }
        cout << endl;
    }
}

//��ÿ��join��SQL
string SQLopertaion::join_sql() {
    int getnum = 0;
    string sql, temp;
    string table1, table1_symbol, table1_show;
    string table2, table2_symbol, table2_show;
    table1 = selectTable();
    table2 = selectTable();
    if ( (table1.length() != table1.length()) || (table1 != table2) )
    {
        sql = "select * from ";
        string get_num = "select Column_name from information_schema.columns where table_name = '" + table1 + "' or table_name ='" + table2 + "';";
        //sql = "select ";

        //cout << "ѡ��ϣ��չʾ��Ԫ�أ�" << endl;
        //cout << "��" << table1 << "��ѡȡԪ�ظ�����"; cin >> getnum; cin.clear();
        //total = getnum; 
        //for (int i = 0; i < getnum; i++) {
        //    temp = joingetSymbol(table1);
        //    sql = sql + temp + ",";
        //}
        //cout << "��" << table2 << "��ѡȡԪ�ظ�����"; cin >> getnum; cin.clear();
        //total += getnum;
        //for (int i = 0; i < getnum; i++) {
        //    temp = joingetSymbol(table2);
        //    sql = sql + temp + ",";
        //}
        //sql = sql.replace(sql.length() - 1, sql.length() - 1, " from ");

        retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(get_num.c_str()), SQL_NTS);
        if (retcode < 0)
        {
            cout << "errors." << endl;
            getchar(); exit(1);
        }
        SQLCHAR      runoob_title[MaxNameLen + 1];
        SQLLEN         columnLen = 0;

        retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, runoob_title, MaxNameLen, &columnLen);
        while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
        {
           getnum++;
        }
        total = getnum;

        cout << "ѡ����Ϊ���ӵ�Ԫ�أ�" << endl;
        table1_symbol = joingetSymbol(table1);
        table2_symbol = joingetSymbol(table2);
        
        sql = sql + table1 + " inner join " + table2 + " on " + table1_symbol + " = " + table2_symbol + ";";
    }
    else
    {
        cout << "ѡ���񲻿���ͬ" << endl;
    }

    return sql;
}

//���Ŀ��Ԫ��
string  SQLopertaion::joingetSymbol(string table) {
    string temp;
    string sql = table + ".";
    //��øñ��е���ɲ�����SQL���
    string fun = "select Column_name,Data_type from information_schema.columns where table_name = '" + table + "'";
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(fun.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "errors." << endl;
        exit(1);
    }
    SQLCHAR      runoob_title1[MaxNameLen + 1];
    SQLCHAR      runoob_title2[MaxNameLen + 1];
    SQLLEN       columnLen = 0;

    retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, runoob_title1, MaxNameLen, &columnLen);
    retcode = SQLBindCol(hstmt1, 2, SQL_C_CHAR, runoob_title2, MaxNameLen, &columnLen);

    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        cout << setw(10) << "Column_name:" << runoob_title1 << "    ";
        cout << setw(10) << "Data_type:" << runoob_title2 << endl;
    }

    cout << "��ѡ��Ŀ��Ԫ�أ�"; cin >> temp;
    sql = sql + temp;

    return sql;
}

//����֧��
void SQLopertaion::transaction() {
    int oper; char Judge;
    string sql;

    sql = "begin;";
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "begin failed" << endl;
        exit(1);
    }
    else
    {
        cout << "begin transaction!" << endl;
    }

    while (1) {
        cout << OPERATION;
        cout << "������ϣ�����еĲ�����"; cin >> oper;
        selectoperation(oper);
        
        cout << "�Ƿ�ع�(Y/N)��"; cin >> Judge; cin.clear();
        if (Judge=='Y' || Judge=='y')
        {
            sql = "rollback;";
            retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
            if (retcode < 0)
            {
                cout << "rollback failed" << endl;
                exit(1);
            }
            else
            {
                cout << "rollback transaction successfully!" << endl;
            }
            break;
        }

        cout << "�Ƿ��ύ����(Y/N)��"; cin >> Judge; cin.clear();
        if (Judge == 'Y' || Judge == 'y')
        {
            sql = "commit;";
            retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
            if (retcode < 0)
            {
                cout << "commit failed" << endl;
                exit(1);
            }
            else
            {
                cout << "commit transaction successfully!" << endl;
            }
            break;
        }
    }
}

//ѡ������֧�֣�������Ĳ���
void SQLopertaion::selectoperation(int oper) {
    //����ѡ��
    switch (oper) {
    case 1: {
        insertData();
        break;
    }
    case 2: {
        deleteData();
        break;
    }
    case 3: {
        updateData();
        break;
    }
    default: {
        break;
    }
    }
}

//�������
void SQLopertaion::indexAdd() {
    string sql;
    sql = indexAdd_sql();
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "create index error." << endl;
        exit(1);
    }
    else
    {
        cout << "create index sucessfully!" << endl;
    }
}

//��ȡ�������SQL���
string SQLopertaion::indexAdd_sql() {
    int index_num;
    string sql = "create index ";
    string index_name, table;

    cout << "������������";
    cin >> index_name;
    sql = sql + index_name + " on ";

    table = selectTable();
    sql = sql + table + "(";

    cout << "������" << table << "���������Ԫ�ظ�����";
    cin >> index_num; cin.clear();
    for (int i = 0; i < index_num; i++) {
        sql = sql + indexAdd_Symbol(table) + ",";
    }
    sql = sql.replace(sql.length() - 1, sql.length() - 1, ");");

    return sql;
}

//����������Ԫ��
string SQLopertaion::indexAdd_Symbol(string table) {
    string temp;
    //��øñ��е���ɲ�����SQL���
    string fun = "select Column_name,Data_type from information_schema.columns where table_name = '" + table + "'";
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(fun.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "errors." << endl;
        exit(1);
    }
    SQLCHAR      runoob_title1[MaxNameLen + 1];
    SQLCHAR      runoob_title2[MaxNameLen + 1];
    SQLLEN       columnLen = 0;

    retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, runoob_title1, MaxNameLen, &columnLen);
    retcode = SQLBindCol(hstmt1, 2, SQL_C_CHAR, runoob_title2, MaxNameLen, &columnLen);

    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        cout << setw(10) << "Column_name:" << runoob_title1 << "    ";
        cout << setw(10) << "Data_type:" << runoob_title2 << endl;
    }

    cout << "��ѡ��Ŀ��Ԫ�أ�"; cin >> temp;

    return temp;
}

//ɾ������
void SQLopertaion::indexDelete() {
    string sql;
    sql = indexDelete_sql();

    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(sql.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "delete index error." << endl;
        exit(1);
    }
    else
    {
        cout << "delete index sucessfully!" << endl;
    }
}

//���ɾ��������SQL����
string SQLopertaion::indexDelete_sql() {
    string table;
    string sql = "drop index ";

    table = selectTable();
    sql = sql + indexDelete_Index(table) + " on " + table + ";";

    return sql;
}

//�����������
string SQLopertaion::indexDelete_Index(string table) {
    string temp;
    //��øñ��е���ɲ�����SQL���
    string fun = "SELECT column_name,index_name FROM INFORMATION_SCHEMA.STATISTICS WHERE TABLE_NAME='" + table + "';";
    retcode = SQLExecDirect(hstmt1, (SQLCHAR*)(fun.c_str()), SQL_NTS);
    if (retcode < 0)
    {
        cout << "errors." << endl;
        exit(1);
    }
    SQLCHAR      runoob_title1[MaxNameLen + 1];
    SQLCHAR      runoob_title2[MaxNameLen + 1];
    SQLLEN       columnLen = 0;

    retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, runoob_title1, MaxNameLen, &columnLen);
    retcode = SQLBindCol(hstmt1, 2, SQL_C_CHAR, runoob_title2, MaxNameLen, &columnLen);

    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        cout << setw(10) << "Column_name:" << runoob_title1 << "    ";
        cout << setw(10) << "Index_name:" << runoob_title2 << endl;
    }

    cout << "��ѡ��Ŀ���������֣�"; cin >> temp;

    return temp;
}