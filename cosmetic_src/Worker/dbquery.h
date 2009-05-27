#ifndef DBQUERY_H
#define DBQUERY_H

#define DBNAME "cosmeticdb"
#define DBFILE "./cosmeticdb"
#define SQLITEMARK "SQLite format 3"
#define SQLITEMARKLEN (15)

//**************staff management database items***************//
#define CREATE_STAFF_TABLE \
	"CREATE TABLE staff (id INTEGER PRIMARY KEY, password TEXT, name TEXT, "\
	"jobId INTEGER REFERENCES job(id), levelId INTEGER REFERENCES level(id),"\
	"sex INTEGER DEFAULT 0, bonus INTEGER DEFAULT 0, status INTEGER DEFAULT 0, "\
	"cell TEXT, phone TEXT, address TEXT, description TEXT)"
#define INSERTINTO_STAFF \
	"INSERT INTO staff (password, name, jobId, levelId, sex, bonus, "\
	"status, cell, phone, address, description)"\
	"VALUES (:password, :name, :jobId, :levelId, :sex, :bonus, "\
	":status, :cell, :phone, :address, :description)"
#define SELECT_STAFF_ALL \
	"SELECT * FROM staff WHERE id > 10000"
#define SELECT_STAFF_NOIMAGE \
	"SELECT id, password, name, jobId, levelId, sex, bonus, status, cell, "\
	"phone, address, description FROM staff  WHERE id > 10000"
#define SELECT_STAFF_BYID_NOIMAGE \
	"SELECT id, password, name, jobId, levelId, sex, bonus,status, cell, "\
	"phone, address, description FROM staff WHERE id = %1"
#define INSERTINTO_STAFF_SUPER \
	"INSERT INTO staff (id, password, name, jobId, levelId, "\
	"sex, status, cell, phone, address, description)"\
	"VALUES (:id, :password, :name, :jobId, :levelId, "\
	":sex, :status, :cell, :phone, :address, :description)"
#define UPDATA_STAFF_BASIC \
	"UPDATE staff SET name = '%1', jobId = %2, levelId = %3, "\
	"sex = %4, bonus = %5, status = %6, cell = '%7', phone = '%8', "\
	"address = '%9', description = '%10' WHERE id = %11"
#define DELETE_STAFF_BYID \
	"DELETE FROM staff WHERE id = %1"
#define GET_STAFFPASSWORD_BYID \
	"SELECT password FROM staff WHERE id = %1"
#define UPDATE_STAFFPASWORD_BYID \
	"UPDATE staff SET password = '%1' WHERE id = %2"
#define CHECK_STAFF_BYID "SELECT id FROM staff WHERE id = %1"

#define CREATE_STAFFIMAGE_TABLE \
	"CREATE TABLE staffImage (id INTEGER REFERENCES"\
	" staff(id), data BLOB DEFAULT NULL)" 
#define INSERT_STAFFIMAGE \
	"INSERT INTO staffImage (id, data)" "VALUES (:id, :data)"
#define DELETE_STAFFIMAGE \
	"DELETE FROM staffImage WHERE id = %1"
#define CHECK_STAFFIMAGE_BYID \
	"SELECT id FROM staffImage WHERE id = %1"
#define GET_STAFFIMAGE_BYID \
	"SELECT data FROM staffImage WHERE id = %1"

#define CREATE_JOB_TABLE \
	"CREATE TABLE job (id INTEGER PRIMARY KEY, name TEXT NOT NULL, "\
	"profit INTEGER DEFAULT 0, baseSalary INTEGER DEFAULT 0, description TEXT)"
#define INSERTINTO_JOB_TABLE \
	"INSERT INTO job (name, profit, baseSalary, description)"\
	"VALUES (:name, :profit, :baseSalary, :description)"
#define SELECT_JOB_ALL \
	"SELECT * FROM job"
#define SELECT_JOB_BYID \
	"SELECT * FROM job WHERE id = %1"
#define UPDATA_JOB \
	"UPDATE job SET name = '%1', profit = %2, "\
	"baseSalary = %3, description = '%4' WHERE id = %5"
#define DELETE_JOB_BYID \
	"DELETE FROM job WHERE id = %1"
#define CHECK_JOB_BYID \
	"SELECT id FROM staff WHERE jobId = %1"

#define CREATE_LEVET_TABLE \
	"CREATE TABLE level (id INTEGER PRIMARY KEY,name TEXT NOT NULL, "\
	"profit INTEGER DEFAULT 0, baseSalary INTEGER DEFAULT 0, description TEXT)"
#define INSERTINTO_LEVEL_TABLE \
	"INSERT INTO level (name, profit, baseSalary, description)"\
	"VALUES (:name, :profit, :baseSalary, :description)"
#define SELECT_LEVEL_ALL \
	"SELECT * FROM level"
#define SELECT_LEVEL_BYID \
	"SELECT * FROM level WHERE id = %1"
#define UPDATA_LEVEL \
	"UPDATE level SET name = '%1', profit = %2, "\
	"baseSalary = %3, description = '%4' WHERE id = %5"
#define DELETE_LEVEL_BYID \
	"DELETE FROM level WHERE id = %1"
#define CHECK_LEVEL_BYID \
	"SELECT id FROM staff WHERE LevelId = %1"

#define CREATE_STATUS_TABLE \
	"CREATE TABLE status (id INTEGER PRIMARY KEY, name TEXT NOT NULL, "\
	"description TEXT)"
#define INSERTINTO_STATUS_TABLE \
	"INSERT INTO status (name, description)"\
	"VALUES (:name, :description)"
#define SELECT_STATUS_ALL \
	"SELECT * FROM status"
#define SELECT_STATUS_BYID \
	"SELECT * FROM status WHERE id = %1"
#define UPDATA_STATUS \
	"UPDATE status SET SET name = '%1', description = '%2' WHERE id = %3"

#define CREATE_SEX_TABLE \
	"CREATE TABLE sex (id INTEGER PRIMARY KEY, name TEXT NOT NULL)"
#define INSERTINTO_SEX_TABLE \
	"INSERT INTO sex (id, name)" "VALUES (:id, :name)"
#define SELECT_SEX_ALL \
	"SELECT * FROM sex"


//**************bussiness management database items***************//
#define CREATE_BUSINESSTYPE_TABLE \
	"CREATE TABLE businessType (id INTEGER PRIMARY KEY, "\
	"name TEXT NOT NULL, cate INTEGER, description TEXT)"
#define INSERTINTO_BUSINESSTYPE_TABLE \
	"INSERT INTO businessType (name, cate, description)"\
	"VALUES (:name, :cate, :description)"
#define SELECT_BUSINESSTYPE_ALL \
	"SELECT * FROM businessType"
#define SELECT_BUSINESSTYPE_BYID \
	"SELECT * FROM businessType WHERE id = %1"
#define UPDATA_BUSINESSTYPE \
	"UPDATE businessType SET name = '%1', cate = %2, "\
	"description = '%3' WHERE id = %4"
#define DELETE_BUSINESSTYPE_BYID \
	"DELETE FROM businessType WHERE id = %1"
#define CHECK_BUSINESSTYPE_BYID \
	"SELECT * FROM business WHERE typeId = %1"

#define CREATE_BUSINESS_TABLE \
	"CREATE TABLE business (id INTEGER PRIMARY KEY, name TEXT, "\
	"typeId INTEGER REFERENCES businessType(id), brand TEXT NOT NULL, "\
	"specification TEXT NOT NULL, price INTEGER DEFAULT 0, "\
	"cost INTEGER DEFAULT 0, discount INTEGER DEFAULT 100, "\
	"adjustable INTEGER DEFAULT 0, dualDiscount INTEGER DEFAULT 0, "\
	"stocks INTEGER DEFAULT 0, sales INTEGER DEFAULT 0, buys INTEGER DEFAULT 0, "\
	"description TEXT)"
#define INSERTINTO_BUSINESS \
	"INSERT INTO business (name, typeId, brand, specification, price, cost, "\
	"discount, adjustable, dualDiscount, stocks, sales, buys, description)"\
	"VALUES (:name, :typeId, :brand, :specification, :price, :cost, :discount, "\
	":adjustable, :dualDiscount, :stocks, :sales, :buys, :description)"
#define SELECT_BUSINESS_ALL \
	"SELECT * FROM business"
#define SELECT_BUSINESS_BYID \
	"SELECT * FROM business WHERE id = %1"
#define SELECT_BUSINESS_BYTYPE \
	"SELECT * FROM business WHERE typeId = %1"
#define UPDATA_BUSINESS_BYID \
	"UPDATE business SET name = '%1', typeId = %2, brand = '%3', "\
	"specification = '%4', price = %5, cost = %6, discount = %7, stocks = %8, "\
	"sales = %9, buys = %10, description = '%11', adjustable = %12, "\
	"dualDiscount = %13 WHERE id = %14"
#define DELETE_BUSINESS_BYID \
	"DELETE FROM business WHERE id = %1"
#define CHECK_BUSINESS_BYID \
	"SELECT id FROM business WHERE id = %1"
#define SELECT_MAX_BUSINESSID \
	"SELECT MAX(id) FROM business"

#define CREATE_BUSINESSIMAGE_TABLE \
	"CREATE TABLE businessImage "\
	"(id INTEGER REFERENCES business(id), data BLOB DEFAULT NULL)" 
#define INSERT_BUSINESSIMAGE \
	"INSERT INTO businessImage (id, data)""VALUES (:id, :data)"
#define DELETE_BUSINESSIMAGE \
	"DELETE FROM businessImage WHERE id = %1"
#define CHECK_BUSINESSIMAGE_BYID \
	"SELECT id FROM businessImage WHERE id = %1"
#define GET_BUSINESSIMAGE_BYID \
	"SELECT data FROM businessImage WHERE id = %1"


//**************customer management database items***************//
#define CREATE_CUSTOMERLEVEL_TABLE \
	"CREATE TABLE customerlevel (id INTEGER PRIMARY KEY, name TEXT NOT NULL, "\
	"requireconsume INTEGER DEFAULT 0, discount INTEGER DEFAULT 100, "\
	"description TEXT)"
#define INSERTINTO_CUSTOMERLEVEL_TABLE \
	"INSERT INTO customerlevel (name, requireconsume, discount, description)"\
	"VALUES (:name, :requireconsume, :discount, :description)"
#define SELECT_CUSTOMERLEVEL_ALL \
	"SELECT * FROM customerlevel"
#define SELECT_CUSTOMERLEVEL_BYID \
	"SELECT * FROM customerlevel WHERE id = %1"
#define UPDATA_CUSTOMERLEVEL \
	"UPDATE customerlevel SET name = '%1', requireconsume = %2, discount = %3, "\
	"description = '%4' WHERE id = %5"
#define DELETE_CUSTOMERLEVEL_BYID \
	"DELETE FROM customerlevel WHERE id = %1"
#define CHECK_CUSTOMERLEVEL_BYID \
	"SELECT id FROM customer WHERE levelid = %1"


#define CREATE_CUSTOMER_TABLE \
	"CREATE TABLE customer (id INTEGER PRIMARY KEY, password TEXT, name TEXT, "\
	"sex INTEGER, levelid INTEGER REFERENCES customerlevel(id), cell TEXT, "\
	"phone TEXT, address TEXT, description TEXT, deposit INTEGER DEFAULT 0)"
#define INSERTINTO_CUSTOMER \
	"INSERT INTO customer (password, name, sex, levelid, "\
	"cell, phone, address, description, deposit)"\
	"VALUES (:password, :name, :sex, :levelid, "\
	":cell, :phone, :address, :description, :deposit)"
#define SELECT_CUSTOMER_ALL \
	"SELECT * FROM customer"
#define SELECT_CUSTOMER_BYID \
	"SELECT * FROM customer WHERE id = %1"
#define UPDATA_CUSTOMER_BYID \
	"UPDATE customer SET password = '%1', name = '%2', sex = %3, "\
	"levelid = %4, cell = '%5', phone = '%6', address = '%7', "\
	"description = '%8' deposit = %9 WHERE id = %10"
#define DELETE_CUSTOMER_BYID \
	"DELETE FROM customer WHERE id = %1"
#define GET_CUSTOMERPASSWORD_BYID \
	"SELECT password FROM customer WHERE id = %1"
#define UPDATE_CUSTOMERPASWORD_BYID \
	"UPDATE customer SET password = '%1' WHERE id = %2"
#define CHECK_CUSTOMER_BYID \
	"SELECT id FROM customer WHERE id = %1"
#define SELECT_MAX_CUSTOMERID \
	"SELECT MAX(id) FROM customer"


#define CREATE_CUSTOMERIMAGE_TABLE \
	"CREATE TABLE customerImage "\
	"(id INTEGER REFERENCES customer(id), data BLOB DEFAULT NULL)" 
#define INSERT_CUSTOMERIMAGE \
	"INSERT INTO customerImage (id, data)""VALUES (:id, :data)"
#define DELETE_CUSTOMERIMAGE \
	"DELETE FROM customerImage WHERE id = %1"
#define CHECK_CUSTOMERIMAGE_BYID \
	"SELECT id FROM customerImage WHERE id = %1"
#define GET_CUSTOMERIMAGE_BYID \
	"SELECT data FROM customerImage WHERE id = %1"


//**************shop operation database items***************//

#define CREATE_ORDERS_TABLE \
	"CREATE TABLE orders (id INTEGER PRIMARY KEY, "\
	"casherId INTEGER REFERENCES staff(id), "\
	"consumerid INTEGER REFERENCES customer(id), "\
	"discount INTEGER DEFAULT 100, status INTEGER DEFAULT 0, dealdate DATETIME)"
#define INSERTINTO_ORDERS_TABLE \
	"INSERT INTO orders (casherId, consumerid, discount, status, dealdate)"\
	"VALUES (:casherId, consumerid, :discount, :status, :dealdate)"
#define SELECT_ORDERS_ALL \
	"SELECT * FROM orders"
#define SELECT_ORDERS_BYCASHER \
	"SELECT * FROM orders WHERE casherId = %1"
#define SELECT_ORDERS_BYCUSTOMER \
	"SELECT * FROM orders WHERE consumerid = %1"


#define CREATE_TASKS_TABLE \
	"CREATE TABLE tasks (id INTEGER PRIMARY KEY, "\
	"staffId INTEGER REFERENCES staff(id), "\
	"businessid INTEGER REFERENCES business(id), "\
	"orderId INTEGER REFERENCES orders(id), "\
	"businessRating INTEGER DEFAULT 0, staffRating INTEGER DEFAULT 0, "\
	"price INTEGER DEFAULT 0, costs INTEGER DEFAULT 0, amount INTEGER, "\
	"discount INTEGER DEFAULT 100, status INTEGER DEFAULT 0, dealdate DATETIME)"
#define INSERTINTO_TASKS_TABLE \
	"INSERT INTO tasks (staffId, businessId, orderId, businessRating, "\
	"staffRating, price, costs, amount, discount, status, dealdate)"\
	"VALUES (:staffId, :businessId, :orderId, :businessRating, "\
	":staffRating, :price, :costs, :amount, :discount, :status, :dealdate)"
#define SELECT_TASKS_ALL \
	"SELECT * FROM tasks"
#define SELECT_TASKS_BYSTAFF \
	"SELECT * FROM tasks WHERE staffId = %1"
#define SELECT_TASKS_BYBUSINESS \
	"SELECT * FROM tasks WHERE businessId = %1"	
#define SELECT_TASKS_BYCUSTOMER \
	"SELECT * FROM tasks"


#endif
