/**
 * @author Clark
 * @email haixuanwo_clark@hotmail.com
 * @date 2020-09-01
 * @brief sqlite3数据库中间层接口
 */

#include <stdio.h>
#include "sqlite.h"

int CSqlite::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   for(int i=0; i<argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


CSqlite::CSqlite(const char *db_name)
{
    db = NULL;
    int rc = sqlite3_open(db_name, &db);
    if (rc)
    {
        fprintf(stderr, "can't open database:%s\n", sqlite3_errmsg(db));
    }
}


// 创建表
int CSqlite::sql_create_table()
{
    char *zErrMsg = 0;
    const char *sql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";

    if (NULL == db)
    {
        return -1;
    }

    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    return 0;
}


// 增加
int CSqlite::sql_insert()
{
    char *zErrMsg = 0;
    const char *sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    int rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    return 0;
}


// 插入数据
int CSqlite::sql_insert_ID(int ID)
{
    char *zErrMsg = 0;
    char buf[1024] = {0};

    snprintf(buf, sizeof(buf), "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) VALUES (%d, 'Paul', 32, 'California', 20000.00 );", ID);
    int rc = sqlite3_exec(db, buf, callback, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    return 0;
}


// 查询
int CSqlite::sql_select()
{
    char *zErrMsg = 0;
    //char *sql = "SELECT * from COMPANY where ID=3"; // 制定ID
    const char *sql = "SELECT * from COMPANY";
    const char* data = "Callback function called";

    int rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    return 0;
}


// 修改
int CSqlite::sql_update()
{
    char *zErrMsg = 0;
    const char *sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
         "SELECT * from COMPANY";

    int rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    return 0;
}


// 删除
int CSqlite::sql_delete(int ID)
{
    char *zErrMsg = 0;
    char sqlCmd[1024] = {0};
    snprintf(sqlCmd, sizeof(sqlCmd),
        "DELETE from COMPANY where ID=%d;", ID);

    printf("%s\n", sqlCmd);

    int rc = sqlite3_exec(db, sqlCmd, callback, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    return 0;
}

CSqlite::~CSqlite()
{
    if (NULL != db)
        sqlite3_close(db);
}

