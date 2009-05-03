#ifndef DBQUERY_H
#define DBQUERY_H

#define DBNAME "cosmeticdb"
#define DBFILE "./cosmeticdb"
#define SQLITEMARK "SQLite format 3"
#define SQLITEMARKLEN (15)
#define SUPERUSERID 10000

//**************staff management database items***************//
#define CREATE_STAFF_TABLE "CREATE TABLE staff (id INTEGER PRIMARY KEY, password TEXT, name TEXT, jobId INTEGER REFERENCES job(id), levelId INTEGER REFERENCES level(id), sex SMALLINT DEFAULT 0, baseSalary INTEGER DEFAULT 0, status SMALLINT DEFAULT 0, cell TEXT, phone TEXT, address TEXT, description TEXT)"
#define INSERTINTO_STAFF "INSERT INTO staff (password, name, jobId, levelId, sex, baseSalary, status, cell, phone, address, description) " "VALUES (:password, :name, :jobId, :levelId, :sex, :baseSalary, :status, :cell, :phone, :address, :description)"
#define SELECT_STAFF_ALL "SELECT * FROM staff WHERE id > 10000"
#define SELECT_STAFF_NOIMAGE "SELECT id, password, name, jobId, levelId, sex, baseSalary, status, cell, phone, address, description FROM staff  WHERE id > 10000"
#define SELECT_STAFF_BYID_NOIMAGE "SELECT id, password, name, jobId, levelId, sex, baseSalary, status, cell, phone, address, description FROM staff WHERE id = %1"
#define INSERTINTO_STAFF_SUPER "INSERT INTO staff (id, password, name, jobId, levelId, sex, status, cell, phone, address, description) " "VALUES (:id, :password, :name, :jobId, :levelId, :sex, :status, :cell, :phone, :address, :description)"
#define UPDATA_STAFF_BASIC "UPDATE staff SET name = '%1', jobId = %2, levelId = %3, sex = %4, baseSalary = %5, status = %6, cell = '%7', phone = '%8', address = '%9', description = '%10' WHERE id = %11"
#define DELETE_STAFF_BYID "DELETE FROM staff WHERE id = %1"
#define GET_PASSWORD_BYID "SELECT password FROM staff WHERE id = %1"
#define CHECK_STAFF_BYID "SELECT id FROM staff WHERE id = %1"

#define CREATE_STAFFIMAGE_TABLE "CREATE TABLE staffImage (id INTEGER REFERENCES staff(id), data BLOB DEFAULT NULL)" 
#define INSERT_STAFFIMAGE "INSERT INTO staffImage (id, data)" "VALUES (:id, :data)"
#define DELETE_STAFFIMAGE "DELETE FROM staffImage WHERE id = %1"
#define CHECK_STAFFIMAGE_BYID "SELECT id FROM staffImage WHERE id = %1"
#define GET_STAFFIMAGE_BYID "SELECT data FROM staffImage WHERE id = %1"

#define CREATE_JOB_TABLE "CREATE TABLE job (id INTEGER PRIMARY KEY, name TEXT NOT NULL, profit SMALLINT DEFAULT 0, baseSalary INTEGER DEFAULT 0, description TEXT)"
#define INSERTINTO_JOB_TABLE "INSERT INTO job (name, profit, baseSalary, description) " "VALUES (:name, :profit, :baseSalary, :description)"
#define SELECT_JOB_ALL "SELECT * FROM job"
#define SELECT_JOB_BYID "SELECT * FROM job WHERE id = %1"
#define UPDATA_JOB "UPDATE job SET name = '%1', profit = %2, baseSalary = %3, description = '%4' WHERE id = %5"
#define DELETE_JOB_BYID "DELETE FROM job WHERE id = %1"
#define CHECK_JOB_BYID "SELECT id FROM staff WHERE jobId = %1"

#define CREATE_LEVET_TABLE "CREATE TABLE level (id INTEGER PRIMARY KEY, name TEXT NOT NULL, profit SMALLINT DEFAULT 0, baseSalary INTEGER DEFAULT 0, description TEXT)"
#define INSERTINTO_LEVEL_TABLE "INSERT INTO level (name, profit, baseSalary, description) " "VALUES (:name, :profit, :baseSalary, :description)"
#define SELECT_LEVEL_ALL "SELECT * FROM level"
#define SELECT_LEVEL_BYID "SELECT * FROM level WHERE id = %1"
#define UPDATA_LEVEL "UPDATE level SET name = '%1', profit = %2, baseSalary = %3, description = '%4' WHERE id = %5"
#define DELETE_LEVEL_BYID "DELETE FROM level WHERE id = %1"
#define CHECK_LEVEL_BYID "SELECT id FROM staff WHERE LevelId = %1"

#define CREATE_STATUS_TABLE "CREATE TABLE status (id INTEGER PRIMARY KEY, name TEXT NOT NULL, description TEXT)"
#define INSERTINTO_STATUS_TABLE "INSERT INTO status (name, description) " "VALUES (:name, :description)"
#define SELECT_STATUS_ALL "SELECT * FROM status"
#define SELECT_STATUS_BYID "SELECT * FROM status WHERE id = %1"
#define UPDATA_STATUS "UPDATE status SET SET name = '%1', description = '%3' WHERE id = %4"

#define CREATE_SEX_TABLE "CREATE TABLE sex (id INTEGER PRIMARY KEY, name TEXT NOT NULL)"
#define INSERTINTO_SEX_TABLE "INSERT INTO sex (id, name) " "VALUES (:id, :name)"
#define SELECT_SEX_ALL "SELECT * FROM sex"

//**************shop operation database items***************//


//**************bussiness management database items***************//
#define CREATE_BUSINESSTYPE_TABLE "CREATE TABLE businessType (id INTEGER PRIMARY KEY, name TEXT NOT NULL, cate SMALLINT, description TEXT)"
#define INSERTINTO_BUSINESSTYPE_TABLE "INSERT INTO businessType (name, cate, description) " "VALUES (:name, :cate, :description)"
#define SELECT_BUSINESSTYPE_ALL "SELECT * FROM businessType"

#define CREATE_BUSINESS_TABLE "CREATE TABLE business (id INTEGER PRIMARY KEY, name TEXT, typeId INTEGER REFERENCES businessType(id), brand TEXT NOT NULL, specification TEXT NOT NULL, price INTEGER DEFAULT 0, cost INTEGER DEFAULT 0, discount SMALLINT DEFAULT 100, stocks INTEGER DEFAULT 0, sales INTEGER DEFAULT 0, buys INTEGER DEFAULT 0, description TEXT)"
#define INSERTINTO_BUSINESS "INSERT INTO business (name, typeId, brand, specification, price, cost, discount, stocks, sales, buys, description) " "VALUES (:name, :typeId, :brand, :specification, :price, :cost, :discount, :stocks, :sales, :buys, :description)"
#define SELECT_BUSINESS_ALL "SELECT * FROM business"
#define SELECT_BUSINESS_BYTYPE "SELECT * FROM business WHERE typeId = %1"
#define UPDATA_BUSINESS_BYID "UPDATE business SET name = '%1', typeId = %2, brand = '%3', specification = '%4', price = %5, costs = %6, discounts = %7, stocks = %8, sales = %9, buys = %10, description = '%11' WHERE id = %12"
#define DELETE_BUSINESS_BYID "DELETE FROM business WHERE id = %1"
#define CHECK_BUSINESS_BYID "SELECT id FROM business WHERE id = %1"

#define CREATE_BUSINESSIMAGE_TABLE "CREATE TABLE businessImage (id INTEGER REFERENCES staff(id), data BLOB DEFAULT NULL)" 
#define INSERT_BUSINESSIMAGE "INSERT INTO businessImage (id, data)" "VALUES (:id, :data)"
#define DELETE_BUSINESSIMAGE "DELETE FROM businessImage WHERE id = %1"
#define CHECK_BUSINESSIMAGE_BYID "SELECT id FROM businessImage WHERE id = %1"
#define GET_BUSINESSIMAGE_BYID "SELECT data FROM businessImage WHERE id = %1"

#define CREATE_ORDERS_TABLE "CREATE TABLE orders (id INTEGER PRIMARY KEY, casherId INTEGER REFERENCES staff(id), discount SMALLINT DEFAULT 100, status SMALLINT DEFAULT 0, dealdate DATETIME)"
#define INSERTINTO_ORDERS_TABLE "INSERT INTO orders (casherId, discount, status, dealdate) " "VALUES (:casherId, :discount, :status, :dealdate)"
#define SELECT_ORDERS_ALL "SELECT * FROM orders"

#define CREATE_TASKS_TABLE "CREATE TABLE tasks (id INTEGER PRIMARY KEY, operatorId INTEGER REFERENCES staff(id), goodsId INTEGER REFERENCES goods(id), orderId INTEGER REFERENCES orders(id), price INTEGER DEFAULT 0, costs INTEGER DEFAULT 0, amount INTEGER, discount SMALLINT DEFAULT 100, status SMALLINT DEFAULT 0, dealdate DATETIME)"
#define INSERTINTO_TASKS_TABLE "INSERT INTO tasks (operatorId, goodsId, orderId, price, costs, amount, discount, status, dealdate) " "VALUES (:operatorId, :goodsId, :orderId, :price, :costs, :amount, :discount, :status, :dealdate)"
#define SELECT_TASKS_ALL "SELECT * FROM tasks"

#endif
