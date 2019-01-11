/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.

PiResiduos is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PiResiduos is distributed in the hope that it will 
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PiResiduos.  
If not, see <https://www.gnu.org/licenses/>.
*/

/***************************************************************************
                          qtdatabase.h  -  description
                             -------------------
    begin                : Fri May 28 2010
    http://pvbrowser.org
    TODO: customize / extend this class for your own purposes

***************************************************************************/
#ifndef _QTDATABASE_
#define _QTDATABASE_

#include <stdio.h>
#include <stdlib.h>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <qstring.h>
#include <string.h>
#include <vector>
#include "processviewserver.h"

/**
The currently available driver types are:
dbtype :=  Description
"QDB2"     IBM DB2, v7.1 and higher
"QIBASE"   Borland InterBase Driver
"QMYSQL"   MySQL Driver
"QOCI"     Oracle Call Interface Driver
"QODBC"    ODBC Driver (includes Microsoft SQL Server)
"QPSQL"    PostgreSQL v6.x and v7.x Driver
"QSQLITE"  SQLite version 3 or above
"QSQLITE2" SQLite version 2
"QTDS"     Sybase Adaptive Server
*/

class qtDatabase
{
  public:
    qtDatabase();
    ~qtDatabase();
    int open(const char *dbtype, const char *hostname, const char *dbname, const char *user, const char *pass, int port);
    int isOpen();
    int reOpen();
    int close();
    int query(PARAM *p, const char *sqlcommand);
    int populateTable(PARAM *p, int id);
    int retData(PARAM *p, char ****table, int **px, int **py);
    const char *recordFieldValue(PARAM *p, int x);
    int nextRecord();

    //MODIFICACIONES BIORRECICLAJE
    std::vector <std::vector <std::string>> retData2();

    QSqlDatabase *db;
    QSqlQuery    *result;
    QSqlError    *error;
};

#endif
