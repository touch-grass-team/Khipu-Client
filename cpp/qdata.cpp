#include "qdata.h"

QSqlDatabase db;

void set_db(){
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("syslog_ng");
    db.setUserName("postgres");
    db.setPassword("postgres");
}

void DBErrorsHandler(const QString &message){
    QString str = QDate::currentDate().toString("dd.MM.yyyy") + " " + QTime::currentTime().toString() + "\n" + message + "\n\n";
    QDir dir;
    if (dir.mkpath("../logs"));
    QFile f("../logs/Errors.log");
    if (f.open(QIODevice::Append)){
        f.write(str.toLocal8Bit());
    }
    f.close();
}
