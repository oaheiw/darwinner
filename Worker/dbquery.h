#ifndef DBQUERY_H
#define DBQUERY_H

#define DBNAME "cosmeticdb"
#define DBFILE "./cosmeticdb"
#define SQLITEMARK "SQLite format 3"
#define SQLITEMARKLEN (15)
#define SUPERUSERID 10000

#define CREATE_STAFF_TABLE "CREATE TABLE staff (id INTEGER PRIMARY KEY, password TEXT, name TEXT, jobId INTEGER REFERENCES job(id), levelId INTEGER REFERENCES level(id), sex SMALLINT DEFAULT 0, baseSalary INTEGER DEFAULT 0, status SMALLINT DEFAULT 0, cell TEXT, phone TEXT, address TEXT, descrption TEXT, image BLOB)"
#define INSERTINTO_STAFF "INSERT INTO staff (password, name, jobId, levelId, sex, baseSalary, status, cell, phone, address, descrption) " "VALUES (:password, :name, :jobId, :levelId, :sex, :baseSalary, :status,  :cell, :phone, :address, :descrption)"
#define INSERT_STAFF_IMAGE
#define SELECT_STAFF_ALL "SELECT * FROM staff"
#define SELECT_STAFF_NOIMAGE "SELECT id, password, name, jobId, levelId, sex, baseSalary, status, cell, phone, address, descrption FROM staff"
#define SELECT_STAFF_BYID_NOIMAGE "SELECT id, password, name, jobId, levelId, sex, baseSalary, status, cell, phone, address, descrption FROM staff WHERE id = %1"
#define INSERTINTO_STAFF_SUPER "INSERT INTO staff (id, password, name, jobId, levelId, sex, status, cell, phone, address, descrption, image) " "VALUES (:id, :password, :name, :jobId, :levelId, :sex, :status, :cell, :phone, :address, :descrption, :image)"

#define CREATE_JOB_TABLE "CREATE TABLE job (id INTEGER PRIMARY KEY, name TEXT NOT NULL, profit SMALLINT DEFAULT 0, descrption TEXT)"
#define INSERTINTO_JOB_TABLE "INSERT INTO job (name, profit, descrption) " "VALUES (:name, :profit, :descrption)"
#define SELECT_JOB_ALL "SELECT * FROM job"
#define SELECT_JOB_BYID "SELECT * FROM job WHERE id = %1)"
#define UPDATA_JOB "UPDATE job SET (name, profit, descrption) WHERE (id)" "VALUES (:name, :profit, :descrption, :id)"

#define CREATE_LEVET_TABLE "CREATE TABLE level (id INTEGER PRIMARY KEY, name TEXT NOT NULL, profit SMALLINT DEFAULT 0, descrption TEXT)" 
#define INSERTINTO_LEVEL_TABLE "INSERT INTO level (name, profit, descrption) " "VALUES (:name, :profit, :descrption)"
#define SELECT_LEVEL_ALL "SELECT * FROM level"
#define SELECT_LEVEL_BYID "SELECT * FROM level WHERE id = %1)"
#define UPDATA_LEVEL "UPDATE level SET (name, profit, descrption) WHERE (id)" "VALUES (:name, :profit, :descrption, :id)"

#define CREATE_STATUS_TABLE "CREATE TABLE status (id INTEGER PRIMARY KEY, name TEXT NOT NULL)"
#define INSERTINTO_STATUS_TABLE "INSERT INTO status (name) " "VALUES (:name)"
#define SELECT_STATUS_ALL "SELECT * FROM status"

#define CREATE_SEX_TABLE "CREATE TABLE sex (id INTEGER PRIMARY KEY, name TEXT NOT NULL)"
#define INSERTINTO_SEX_TABLE "INSERT INTO sex (name) " "VALUES (:name)"
#define SELECT_SEX_ALL "SELECT * FROM sex"

#define CREATE_STATUS_TABLE "CREATE TABLE status (id INTEGER PRIMARY KEY, name TEXT NOT NULL)"
#define INSERTINTO_STATUS_TABLE "INSERT INTO status (name) " "VALUES (:name)"
#define SELECT_STATUS_ALL "SELECT * FROM status"

#define CREATE_ORDERS_TABLE "CREATE TABLE orders (id INTEGER PRIMARY KEY, casherId INTEGER REFERENCES staff(id), discount SMALLINT DEFAULT 100, status SMALLINT DEFAULT 0, dealdate DATETIME)"
#define INSERTINTO_ORDERS_TABLE "INSERT INTO orders (casherId, discount, status, dealdate) " "VALUES (:casherId, :discount, :status, :dealdate)"
#define SELECT_ORDERS_ALL "SELECT * FROM orders"

#define CREATE_GOOSTYPE_TABLE "CREATE TABLE goodsType (id INTEGER PRIMARY KEY, name TEXT NOT NULL, cate SMALLINT, descrption TEXT)"
#define INSERTINTO_GOOSTYPE_TABLE "INSERT INTO goodsType (name, cate, descrption) " "VALUES (:name, :cate, :descrption)"
#define SELECT_GOOSTYPE_ALL "SELECT * FROM goodsType"

#define CREATE_GOODS_TABLE "CREATE TABLE goods (id INTEGER PRIMARY KEY, name TEXT, typeId INTEGER REFERENCES goodsType(id), price INTEGER DEFAULT 0, costs INTEGER DEFAULT 0, discounts SMALLINT DEFAULT 100, stocks INTEGER DEFAULT 0, sales INTEGER DEFAULT 0, buys INTEGER DEFAULT 0, descrption TEXT, image BLOB)"
#define INSERTINTO_GOODS "INSERT INTO goods (name, typeId, price, costs, discounts, stocks, sales, buys, descrption, image) " "VALUES (:name, :typeId, :price, :costs, :discounts, :stocks, :sales, :buys, :descrption, :image)"
#define SELECT_GOODS_ALL "SELECT * FROM goods"

#define CREATE_ORDERS_TABLE "CREATE TABLE orders (id INTEGER PRIMARY KEY, casherId INTEGER REFERENCES staff(id), discount SMALLINT DEFAULT 100, status SMALLINT DEFAULT 0, dealdate DATETIME)"
#define INSERTINTO_ORDERS_TABLE "INSERT INTO orders (casherId, discount, status, dealdate) " "VALUES (:casherId, :discount, :status, :dealdate)"
#define SELECT_ORDERS_ALL "SELECT * FROM orders"

#define CREATE_TASKS_TABLE "CREATE TABLE tasks (id INTEGER PRIMARY KEY, operatorId INTEGER REFERENCES staff(id), goodsId INTEGER REFERENCES goods(id), orderId INTEGER REFERENCES orders(id), price INTEGER DEFAULT 0, costs INTEGER DEFAULT 0, amount INTEGER, discount SMALLINT DEFAULT 100, status SMALLINT DEFAULT 0, dealdate DATETIME)"
#define INSERTINTO_TASKS_TABLE "INSERT INTO tasks (operatorId, goodsId, orderId, price, costs, amount, discount, status, dealdate) " "VALUES (:operatorId, :goodsId, :orderId, :price, :costs, :amount, :discount, :status, :dealdate)"
#define SELECT_TASKS_ALL "SELECT * FROM tasks"

#endif