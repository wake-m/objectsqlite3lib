# objectsqlite3lib

This is a wrapper of the Sqlite3 database

Among them, three classes are ObjectSqlite3, ObjectSqlite3Table and SqlStatements. 
ObjectSqlite3 is used to manage the database. ObjectSqlite3Table represents the table in ObjectSqlite3. 
SqlStatements is used to generate Sql statements. Usually, you do not need to use SqlStatements to generate Sql statements because the other two classes can complete basic additions, deletions, and changes.


Now start introducing 2 classes


objectsqlite3 class
```
 void Open(const std::string& filename);//open database
	bool CheckOpen();
	bool Exec(const std::string& Sql, sqlite3_callback call);//Execute Sql statement
	bool ChekcTable(const std::string& TableName);//Check if table exists in open database
	bool DelectTable(const std::string& TableName);// delete table
	bool CreateTable(const std::string& TableName,const CreateTableFieldInfoA& Fieldinfo); //create Table
	FieldData GetAllTable(); // Get all tables in the currently open database
```
ObjectSqlite3Table class

```
//Editing is under development
 bool ChekcOpen(); //chekco open Table
	FieldData Select(const std::string& FieldName); //read data
	bool Insert(WriteFieldData& Data);//write data

```
Then open a database and table?
```

objectsqlite3 db;

db.Open("databasefilename");

if(db.CheckOpen()){

ObjectSqlite3Table user(&db,"user) // open user table

}

```
