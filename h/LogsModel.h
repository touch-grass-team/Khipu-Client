#ifndef LOGSMODEL_H
#define LOGSMODEL_H

#include <QObject>
#include <QtWidgets>

struct CLogsData{
    int id;
    QDateTime timestamp;
    QString level;
    QString userName;
    QString processName;
    int pid;
    QString message;
};

class CLogsModel : public QAbstractTableModel{
    Q_OBJECT

public:
    CLogsModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const;
    void add_log(const CLogsData &newData);

private:
    QVector <CLogsData> storedData;

};

#endif // LOGSMODEL_H
