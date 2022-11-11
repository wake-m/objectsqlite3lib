#include"ObjectSqlite3.h"

static FieldData ReadData;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (size_t i = 0; i < argc; i++){
		ReadData.push_back(argv[i]);
	}
	return 0;
}



ObjectSqlite3::ObjectSqlite3(){

}

ObjectSqlite3::~ObjectSqlite3(){

}

void ObjectSqlite3::Open(const std::string& filename){
	sqlite3_open(filename.c_str(), &db);
}

bool ObjectSqlite3::CheckOpen(){
	return db;
}

bool ObjectSqlite3::Exec(const std::string& Sql, sqlite3_callback call){
	char* msg =  0 ;
	int code = sqlite3_exec(db, Sql.c_str(), call, 0, &msg);
	sqlite3_free(msg);
	return !code;
}

bool ObjectSqlite3::ChekcTable(const std::string& TableName){
	FieldData AllTable = GetAllTable();
	for (std::string tablename : AllTable) {
		if (tablename == TableName)
			return true;
	}
	return false;
}

bool ObjectSqlite3::DelectTable(const std::string& TableName){    
	return Exec(Sql.DROPTABLE(TableName),callback);
}

bool ObjectSqlite3::CreateTable(const std::string& TableName, const CreateTableFieldInfoA& Fieldinfo){
	Exec(Sql.CREATETABLE(TableName, Fieldinfo), callback);
	return ChekcTable(TableName);
}

FieldData ObjectSqlite3::GetAllTable(){
	ObjectSqlite3Table sqlite_master(this, "sqlite_master");
	return sqlite_master.Select("name");
}



ObjectSqlite3Table::ObjectSqlite3Table(ObjectSqlite3* db, std::string TableName) {
	OpenTable = TableName;
	DataBaseClass = db;
}

ObjectSqlite3Table::~ObjectSqlite3Table() {

}

bool ObjectSqlite3Table::ChekcOpen() {
	
	if (DataBaseClass != nullptr && !OpenTable.empty())
		if (DataBaseClass->CheckOpen())
			return true;
	return false;
}

FieldData ObjectSqlite3Table::Select(const std::string& FieldName){
	ReadData.clear();
	DataBaseClass->Exec(DataBaseClass->Sql.Select(OpenTable, FieldName), callback);
	return ReadData;
}

bool ObjectSqlite3Table::Insert(WriteFieldData& Data){
	return DataBaseClass->Exec(DataBaseClass->Sql.Insert(OpenTable, Data), callback);
}

