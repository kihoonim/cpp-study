#include <iostream>
#include <string>
#include <vector>

#include <sqlite3.h> 

class Row
{

};

class DbManager 
{
private:
	sqlite3* _db;

	void _open(const char* db_path)
	{
		if (sqlite3_open(db_path, &_db))
		{
			throw std::exception(sqlite3_errmsg(_db));
		}
	}

	void _close()
	{
		if (_db)
			sqlite3_close(_db);
	}

	static int _callback(void* data, int argc, char** argv, char** azColName)
	{
		for (int i = 0; i < argc; i++)
		{
			std::string value = argv[i] ? argv[i] : "NULL";

			std::cout << azColName[i] << value << std::endl;
		}

		return 0;
	}

public:
	DbManager()
	{
		_open(NULL);
	}

	DbManager(const std::string& db_path)
	{
		_open(db_path.c_str());
	}

	~DbManager()
	{
		_close();
	}

	void create(const std::string& sql)
	{
		const char* data = "Data";
		char* err_msg;

		int status = sqlite3_exec(_db, sql.c_str(), _callback, (void*)data, &err_msg);
		if (status != SQLITE_OK)
		{
			throw std::exception(err_msg);
		}
	}

	void read(const std::string& sql, std::vector<Row>& rows)
	{
		const char* data = "Data";
		char* err_msg;

		int status = sqlite3_exec(_db, sql.c_str(), _callback, (void*)data, &err_msg);
		if (status != SQLITE_OK)
		{
			throw std::exception(err_msg);
		}
	}
};

void run()
{
	try
	{
		std::string sql = "";

		DbManager db_manger("test.db");

		db_manger.create(sql);
		db_manger.read(sql);
	}
	catch (std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
