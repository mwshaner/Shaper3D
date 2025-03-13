#include "DB.h"

DB::DB()
    : m_db{ NULL }
{
 
}

int DB::connect()
{
    // open the database connection
    int result = sqlite3_open(":memory:", &m_db);

    if (result != SQLITE_OK)
    {
        std::cout << "Failed to connect to the database and terminating. ERROR=" << sqlite3_errmsg(m_db) << std::endl;
        return -1;
    }
    std::cout << "Connected to the database." << std::endl;
    return 0;
}

bool DB::initialize_database()
{
    char* error_message = NULL;
    std::string sql = "CREATE TABLE USERS(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "USERNAME           TEXT    NOT NULL," \
        "PASSWORD       TEXT    NOT NULL);";

    int result = sqlite3_exec(m_db, sql.c_str(), callback, NULL, &error_message);
    if (result != SQLITE_OK)
    {
        std::cout << "Failed to create USERS table. ERROR = " << error_message << std::endl;
        sqlite3_free(error_message);
        return false;
    }
    std::cout << "USERS table created." << std::endl;

    // insert some dummy data
    sql = "INSERT INTO USERS (ID, USERNAME, PASSWORD)" \
        "VALUES (1, 'Mason', '12345');" \
        "INSERT INTO USERS (ID, USERNAME, PASSWORD)" \
        "VALUES (2, 'Winston', '12345');" \
        "INSERT INTO USERS (ID, USERNAME, PASSWORD)" \
        "VALUES (3, 'Teddy', '12345');" \
        "INSERT INTO USERS (ID, USERNAME, PASSWORD)" \
        "VALUES (4, 'Jimmy', '12345');";

    result = sqlite3_exec(m_db, sql.c_str(), callback, NULL, &error_message);
    if (result != SQLITE_OK)
    {
        std::cout << "Data failed to insert to USERS table. ERROR = " << error_message << std::endl;
        sqlite3_free(error_message);
        return false;
    }

    return true;
}

int DB::closeDB()
{
    // close the connection if opened
    if (m_db != NULL)
    {
        sqlite3_close(m_db);
    }
    std::cout << "Closed database connection" << std::endl;
    return 1;
}

bool DB::run_query(std::string& sql, std::vector<user_record>& records)
{
    // Clear any prior results
    records.clear();

    char* error_message;
    if (sqlite3_exec(m_db, sql.c_str(), callback, &records, &error_message) != SQLITE_OK)
    {
        std::cout << "Data failed to be queried from USERS table. ERROR = " << error_message << std::endl;
        sqlite3_free(error_message);
        return false;
    }
    return true;
}

int DB::callback(void* possible_vector, int argc, char** argv, char** azColName)
{
    if (possible_vector == NULL)
    { // no vector passed in, so just display the results
        for (int i = 0; i < argc; i++)
        {
            std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        std::cout << std::endl;
    }
    else
    {
        std::vector< user_record >* rows =
            static_cast<std::vector< user_record > *>(possible_vector);

        rows->push_back(std::make_tuple(argv[0], argv[1], argv[2]));
    }
    return 0;
}
