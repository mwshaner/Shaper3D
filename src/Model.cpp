#include "Model.h"

/*
*		   File: DB.cpp
*		   Author: Mason Shaner
*		   Date: 3/20/2025
*		   Description:
*		    The Model class implements the connection to and communication with
*          a database. Currently, only in-memory sqlite3 databases are implemented, however
*          derived classes can be created to support different database systems as needed.
*/


sqlModel::sqlModel()
    : m_db{ nullptr }
{
 
}

int sqlModel::connect()
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

/*
    initialize_database() is a method to populate the database with dummy data.
    Should only be used for testing purposes.
*/
bool sqlModel::initialize_database()
{
    char* error_message = NULL;
    std::string sql = "CREATE TABLE USERS(" \
        "ID INTEGER PRIMARY KEY     NOT NULL," \
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
    sql = "INSERT INTO USERS (USERNAME, PASSWORD)" \
        "VALUES ('Mason', '12345');" \
        "INSERT INTO USERS (USERNAME, PASSWORD)" \
        "VALUES ('Winston', '12345');" \
        "INSERT INTO USERS (USERNAME, PASSWORD)" \
        "VALUES ('Teddy', '12345');" \
        "INSERT INTO USERS (USERNAME, PASSWORD)" \
        "VALUES ('Jimmy', '12345');";

    result = sqlite3_exec(m_db, sql.c_str(), callback, NULL, &error_message);
    if (result != SQLITE_OK)
    {
        std::cout << "Data failed to insert to USERS table. ERROR = " << error_message << std::endl;
        sqlite3_free(error_message);
        return false;
    }

    return true;
}

int sqlModel::disconnect()
{
    // close the connection if opened
    if (m_db != NULL)
    {
        sqlite3_close(m_db);
    }
    std::cout << "Closed database connection" << std::endl;
    return 1;
}
/*
    runQuery() executes a query against the users table to retrieve one or more 
    user records. The currently defined schema for the users database is:     
    [ID][USERNAME][PASSWORD].
*/
bool sqlModel::runQuery(std::string& sql, std::vector<userRecord>& records)
{
    // Clear any prior results
    records.clear();

    // Query DB, if sucessful it will copy userRecords into the argument. 
    char* error_message;
    if (sqlite3_exec(m_db, sql.c_str(), callback, &records, &error_message) != SQLITE_OK)
    {
        std::cout << "Data failed to be queried from USERS table. ERROR = " << error_message << std::endl;
        sqlite3_free(error_message);
        return false;
    }
    return true;
}

/*
    callback() processes each row returned from the DB into a userRecord
    @param possible_vector: can be null or point to std::vector<userRecord>
    @param argc: number of columns in current row
    @param argv: array of strings containing values for each column in curr row
    @param azColName: array of strings containing names of each column
*/
int sqlModel::callback(void* possible_vector, int argc, char** argv, char** azColName)
{
    // If no vector of userRecords is provided, print query results
    if (possible_vector == NULL)
    {
        for (int i = 0; i < argc; i++)
        {
            std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        std::cout << std::endl;
    }
    else
    {
        // We only support userRecord at this time
        std::vector<userRecord>* rows = static_cast<std::vector<userRecord>*>(possible_vector);

        // push each column value into vector
        rows->push_back(std::make_tuple(argv[0], argv[1], argv[2]));
    }
    return 0;
}
