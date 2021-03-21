#include "SQLoperation.h"

#define MAXBUFLEN   255 
#define MaxNameLen  20

//构造函数
SQLopertaion::SQLopertaion(string Name, string Password) {
    name = Name;
    password = Password;
    connect(name.c_str(), password.c_str());
}

//连接数据库
void SQLopertaion::connect(const char* name, const char* password) {
    //进行连接
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);
    if (retcode < 0)//错误处理
    {
        cout << "allocate ODBC Environment handle errors." << endl;
        getchar(); exit(1);
    }

    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
        (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if (retcode < 0) //错误处理
    {
        cout << "the  ODBC is not version3.0 " << endl;
        getchar(); exit(1);
    }

    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);
    if (retcode < 0) //错误处理
    {
        cout << "allocate ODBC connection handle errors." << endl;
        getchar(); exit(1);
    }

    retcode = SQLConnect(hdbc1, (SQLCHAR*)szDSN, (SWORD)strlen(szDSN),
        (SQLCHAR*)name,
        (SWORD)strlen(name),
        (SQLCHAR*)password,
        (SWORD)strlen(password));

    if (retcode < 0) //错误处理
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

    //关闭连接
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);//释放语句句柄 
    SQLDisconnect(hdbc1);//断开与数据库的连接
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);//释放连接句柄  
    SQLFreeHandle(SQL_HANDLE_ENV, henv);//释放环境句柄 
}

//各种具体操作
void SQLopertaion::Operation(int oper) {
    //进行连接
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

    //操作选择
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


    //断开连接
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);//释放语句句柄 
    SQLDisconnect(hdbc1);//断开与数据库的连接
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);//释放连接句柄  
    SQLFreeHandle(SQL_HANDLE_ENV, henv);//释放环境句柄 
}

//获得创建表格的SQL语句
string SQLopertaion::createTable_sql() {
    string temp;
    string sql = "create table `";

    cout << "请输入新建表名：";
    cin >> temp;
    sql = sql + temp + "`(";

    while (1) {
        char Judge;

        cout << "输入表格列名：";
        cin >> temp;
        sql = sql + "`" + temp + "`";
        cout << "输入数据类型：";
        cin >> temp;
        sql = sql + temp + ", ";

        cout << "是否已经完成输入？（Y/N）：";
        rewind(stdin);  Judge = getchar();
        if (Judge == 'y' || Judge == 'Y') {
            sql = sql.replace(size(sql) - 2, size(sql), ");");
            break;
        }
        //没有规定输入错误的情况
    }
    return sql;
}

//开始创建表格
void SQLopertaion::createTable() {
    //创建表格
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

//选表(记得修改数据库名)
string SQLopertaion::selectTable() {
    string temp;
    //选表
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
    cout << "数据库中有表如下：" << endl;
    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        cout << setw(20) << "Table_name:" << runoob_title << endl;
    }
    cout << "选择需要的表格："; cin >> temp;

    return temp;
}

//获得插入数据的SQL语句
string SQLopertaion::insertData_sql() {
    
    //获得表的列名并获得SQL语句
    string table;
    string sql;

    //选表
    table = selectTable();
    sql = "insert into " + table + " values(";

    //获得该表中的组成并生成SQL语句
    sql = sql + insertData_getData(table);

    return sql;
}

//获得需要插入的各组成元素具体值
string SQLopertaion::insertData_getData(string table) {
    string temp;
    string sql = "";
    //获得该表中的组成并生成SQL语句
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
    cout << "(若为char类型，请在前后添加单引号)" << endl;
    while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
    {
        cout << setw(10) << "Column_name:" << runoob_title1 << "    ";
        cout << setw(10) << "Data_type:" << runoob_title2 << endl;
        cout << "输入目标插入数据："; cin >> temp;
        sql = sql + temp + ",";
    }
    sql = sql.replace(size(sql) - 1, size(sql), ");");

    return sql;
}

//插入数据
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

//删除数据
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

//获得删除数据的SQL语言
string SQLopertaion::deleteData_sql() {
    string table;
    string sql;

    table = selectTable();
    sql = deleteData_getData(table);

    return sql;
}

//选择删除数据的条件
string SQLopertaion::deleteData_getData(string table) {
    string temp;
    string sql = "delete from "+ table +" where ";
    //获得该表中的组成并生成SQL语句
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

    cout << "(若为char类型，请在前后添加单引号)" << endl;
    cout << "请输入删除条件：" << endl; cin >> temp;
    sql = sql + temp + " ;";

    return sql;
}

//更新数据
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

//获得更新数据的SQL语言
string SQLopertaion::updateData_sql() {
    string table;
    string sql;

    table = selectTable();
    sql = updateData_getData(table);

    return sql;
}

//选择更新条件
string SQLopertaion::updateData_getData(string table) {
    string temp;
    string sql = "update " + table + " set ";
    //获得该表中的组成并生成SQL语句
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

    cout << "(若为char类型，请在前后添加单引号)" << endl;
    cout << "请输入更新后结果："; cin >> temp;
    sql = sql + temp + " where ";
    cout << "请输入更新条件："; cin >> temp;
    sql = sql + temp + ";";

    return sql;
}

//删除表格
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

//跨表join
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

    cout << "得到结果为：" << endl;
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

//获得跨表join的SQL
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

        //cout << "选择希望展示的元素：" << endl;
        //cout << "从" << table1 << "中选取元素个数："; cin >> getnum; cin.clear();
        //total = getnum; 
        //for (int i = 0; i < getnum; i++) {
        //    temp = joingetSymbol(table1);
        //    sql = sql + temp + ",";
        //}
        //cout << "从" << table2 << "中选取元素个数："; cin >> getnum; cin.clear();
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

        cout << "选择作为连接的元素：" << endl;
        table1_symbol = joingetSymbol(table1);
        table2_symbol = joingetSymbol(table2);
        
        sql = sql + table1 + " inner join " + table2 + " on " + table1_symbol + " = " + table2_symbol + ";";
    }
    else
    {
        cout << "选择表格不可相同" << endl;
    }

    return sql;
}

//获得目标元素
string  SQLopertaion::joingetSymbol(string table) {
    string temp;
    string sql = table + ".";
    //获得该表中的组成并生成SQL语句
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

    cout << "请选择目标元素："; cin >> temp;
    sql = sql + temp;

    return sql;
}

//事务支持
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
        cout << "请输入希望进行的操作："; cin >> oper;
        selectoperation(oper);
        
        cout << "是否回滚(Y/N)："; cin >> Judge; cin.clear();
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

        cout << "是否提交事务(Y/N)："; cin >> Judge; cin.clear();
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

//选择处事务支持，索引外的操作
void SQLopertaion::selectoperation(int oper) {
    //操作选择
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

//添加索引
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

//获取添加索引SQL语句
string SQLopertaion::indexAdd_sql() {
    int index_num;
    string sql = "create index ";
    string index_name, table;

    cout << "输入索引名：";
    cin >> index_name;
    sql = sql + index_name + " on ";

    table = selectTable();
    sql = sql + table + "(";

    cout << "请输入" << table << "组成索引的元素个数：";
    cin >> index_num; cin.clear();
    for (int i = 0; i < index_num; i++) {
        sql = sql + indexAdd_Symbol(table) + ",";
    }
    sql = sql.replace(sql.length() - 1, sql.length() - 1, ");");

    return sql;
}

//获得索引组成元素
string SQLopertaion::indexAdd_Symbol(string table) {
    string temp;
    //获得该表中的组成并生成SQL语句
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

    cout << "请选择目标元素："; cin >> temp;

    return temp;
}

//删除索引
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

//获得删除索引的SQL语言
string SQLopertaion::indexDelete_sql() {
    string table;
    string sql = "drop index ";

    table = selectTable();
    sql = sql + indexDelete_Index(table) + " on " + table + ";";

    return sql;
}

//获得索引名字
string SQLopertaion::indexDelete_Index(string table) {
    string temp;
    //获得该表中的组成并生成SQL语句
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

    cout << "请选择目标索引名字："; cin >> temp;

    return temp;
}