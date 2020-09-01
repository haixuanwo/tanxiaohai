/**
 * @author Clark
 * @email haixuanwo_clark@hotmail.com
 * @date 2020-09-01
 * @brief sqlite3数据库中间层接口
 */

#ifndef SQLITE_H_
#define SQLITE_H_
#include "sqlite3.h"

/**
 * @brief 数据库类，实现数据库的创建及数据的增删查改
 */
class CSqlite
{
public:
    CSqlite(const char *db_name);
    int sql_create_table();
    int sql_insert();
    int sql_insert_ID(int ID);
    int sql_select();
    int sql_update();
    int sql_delete(int ID);
    ~CSqlite();

private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    sqlite3 *db;
};

#endif

