// local_database.h
#ifndef LOCAL_DATABASE_H
#define LOCAL_DATABASE_H

#include <string>
#include "sqlite/sqlite3.h"

class local_db
{
public:
    local_db(const std::string& dbFilePath);
    ~local_db();

    bool open();
    void close();
    bool create_config_table();
    bool insert_config(const std::string& key, const std::string& value);
    std::string get_config(const std::string& key);
    bool update_config(const std::string& key, const std::string& value);
    bool delete_config(const std::string& key);

private:
    std::string m_db_file_path;
    sqlite3* m_db;
};

#endif // LOCAL_DATABASE_H
