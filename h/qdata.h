#ifndef QDATA_H
#define QDATA_H

#include <QtWidgets>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

void set_db();
void DBErrorsHandler(const QString &message);

extern QSqlDatabase db;

#endif // QDATA_H
