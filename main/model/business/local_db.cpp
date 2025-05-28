// local_database.cpp
#include "local_db.h"
#include <iostream>
#include "log/log.h"

local_db::local_db(const std::string& dbFilePath)
    : m_db_file_path(dbFilePath), m_db(nullptr)
{
}

local_db::~local_db()
{
    close();
}

bool local_db::open()
{
    if (sqlite3_open(m_db_file_path.c_str(), &m_db) != SQLITE_OK)
    {
        LOGERROR("Failed to open database: %s",sqlite3_errmsg(m_db));
        return false;
    }
    return true;
}

void local_db::close()
{
    if (m_db)
    {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

bool local_db::create_config_table()
{
    const char* sql = "CREATE TABLE IF NOT EXISTS Config ("
                      "Key TEXT PRIMARY KEY NOT NULL, "
                      "Value TEXT NOT NULL);";
    char* errMsg = nullptr;
    if (sqlite3_exec(m_db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        LOGERROR("Failed to create table: ", errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool local_db::insert_config(const std::string& key, const std::string& value)
{
    const char* sql = "INSERT INTO Config (Key, Value) VALUES (?, ?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        LOGERROR("Failed to prepare statement: ",sqlite3_errmsg(m_db) );
        return false;
    }
    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        LOGERROR("Failed to insert config: " ,sqlite3_errmsg(m_db));
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

std::string local_db::get_config(const std::string& key)
{
    const char* sql = "SELECT Value FROM Config WHERE Key = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        LOGERROR("Failed to prepare statement: ",sqlite3_errmsg(m_db) );
        return "";
    }
    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_STATIC);
    std::string value;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }
    sqlite3_finalize(stmt);
    return value;
}

bool local_db::update_config(const std::string& key, const std::string& value)
{
    const char* sql = "UPDATE Config SET Value = ? WHERE Key = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        LOGERROR("Failed to prepare statement: ",sqlite3_errmsg(m_db));
        return false;
    }
    sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, key.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        LOGERROR("Failed to update config: ",sqlite3_errmsg(m_db));
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool local_db::delete_config(const std::string& key)
{
    const char* sql = "DELETE FROM Config WHERE Key = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        LOGERROR("Failed to prepare statement: ", sqlite3_errmsg(m_db));
        return false;
    }
    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        LOGERROR("Failed to delete config: " ,sqlite3_errmsg(m_db));
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}
