#ifndef LOGSMODEL_H
#define LOGSMODEL_H

#include <QObject>
#include <QtWidgets>
#include <deque>
#include <set>

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
    CLogsModel(int dataCnt,QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const;
    void add_log(const CLogsData &newData);
    int get_frequency_for_level(const QString& level) const;
    QString get_message(int row) const;
    void set_data_size(int dataSize);

private:
    std::deque <CLogsData> storedData;
    QMap <QString,int> levelsFrequency;
    int dataSize;
   // methods
    void erase_data();

};

#endif // LOGSMODEL_H
