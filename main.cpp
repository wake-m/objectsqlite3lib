#include"ObjectSqlite3.h"


int main() { 
	
	ObjectSqlite3 db;
	db.Open("dbname");


	ObjectSqlite3Table User(&db, "User"); // open database table user

	return 0;
}

