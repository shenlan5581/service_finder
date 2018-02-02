
#ifndef MAIN_H
#define MAIN_H

 
 
#define  PORT         8080 
#define  MAX_CONNECT  4096

/******mysql*********/
#define MYSQLADDR      "192.168.1.101"
#define MYSQLUSER      "root"
#define MYSQLPASSWORD  "xingke"
#define SQL_CREATE_DATABASE "create database  IF NOT EXISTS server_finder;" 
#define SQL_CHANG_DATABASE  "use server_finder;" 
#define SQL_CREATE_TABLE    "create table IF NOT EXISTS  server_table(\
                             ID int unsigned not null auto_increment primary key, \
                             service_name char(50) not null, \
                             IP char(20)    not null, \
                             port char(10)  not null \
                             );"                                              

#endif