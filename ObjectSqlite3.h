#include"dep/sqlite3.h"
#include"dep/Value.h"
#include<iostream>
#include<string>
#include<vector>
#include<map>

#ifndef OBJECTSQLITE3_H
#define OBJECTSQLITE3_H

struct CreateTableFieldInfo {
	std::string naem;
	std::string type;
	bool NOTNULL = false;
	bool UNIQUE = false;
};


typedef std::vector<Value> FieldData;
typedef std::vector<CreateTableFieldInfo> CreateTableFieldInfoA;
typedef std::map<std::string, Value>  WriteFieldData;

class SqlStatements {
	public:
	std::string Select(const std::string& Table, const std::string& Field) {
		std::string Sql = "SELECT ";
		Sql.append(Field).append(" FROM ").append(Table);
		return Sql;
	}
	
	std::string DROPTABLE(const std::string& TableName) {
		std::string Sql = "DROP TABLE ";
		Sql = Sql + TableName;
		return Sql;
	}

	std::string CREATETABLE(const std::string& TabelName, const CreateTableFieldInfoA& Fieldinfo){
		std::string sql = "CREATE TABLE '";
		sql = sql + TabelName +"' (";
		std::string sqls;
		for (size_t i = 0; i < Fieldinfo.size(); i++){
			sqls = sqls + "'" + Fieldinfo[i].naem + "' " + Fieldinfo[i].type;
			if (Fieldinfo[i].NOTNULL) 
				sqls = sqls + " NOT NULL";
			if (Fieldinfo[i].UNIQUE) 
				sqls = sqls + " UNIQUE";
			sqls = sqls + ",";
		}
		sqls.pop_back();
		sql.append(sqls).append(")");
		return sql;
	}

	/*INSERT INTO COMPANY(ID, NAME, AGE, ADDRESS, SALARY)
		VALUES(6, 'Kim', 22, 'South-Hall', 45000.00);*/

	std::string Insert(const std::string& TableName, WriteFieldData& Data) {
		std::string Sql = "INSERT INTO ";
		Sql.append(TableName);
		std::string TableN = "(", Values = "VALUES (";

		for (auto& index : Data){
			TableN = TableN + "'" + index.first + "'" + ",";
			Values = Values + "'" + static_cast<std::string>(Data.at(index.first)) + "'" + ",";
		}
		TableN.pop_back();
		Values.pop_back();
		TableN = TableN + ")";
		Values = Values + ")";
		Sql = Sql + TableN + "\n" + Values + ";";
		return Sql;
	}
};



class ObjectSqlite3
{
public:
	ObjectSqlite3();
	~ObjectSqlite3();
	void Open(const std::string& filename);
	bool CheckOpen();
	bool Exec(const std::string& Sql, sqlite3_callback call);
	bool ChekcTable(const std::string& TableName);
	bool DelectTable(const std::string& TableName);
	bool CreateTable(const std::string& TableName,const CreateTableFieldInfoA& Fieldinfo);
	FieldData GetAllTable();
	SqlStatements Sql;
private:
	sqlite3* db;
};


//TODO: 实现Sqlite3数据库的增，删，改，查 目前增，查已经实现
class ObjectSqlite3Table
{
public:
	ObjectSqlite3Table(ObjectSqlite3* db,std::string TableName);
	~ObjectSqlite3Table();
	bool ChekcOpen();
	FieldData Select(const std::string& FieldName);
	bool Insert(WriteFieldData& Data);
private:
	 std::string OpenTable;
	 ObjectSqlite3* DataBaseClass = nullptr;
};




#endif // !OBJECTSQLITE3_H

