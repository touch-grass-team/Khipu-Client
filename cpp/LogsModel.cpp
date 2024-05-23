#include "LogsModel.h"

CLogsModel::CLogsModel(int dataCnt,QObject *parent) : QAbstractTableModel(parent){
    this->dataCnt = dataCnt;
}

int CLogsModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return (int)storedData.size();
}

int CLogsModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 7;
}

QVariant CLogsModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid()) return QVariant();
    if (role != Qt::DisplayRole) return QVariant();
    int row = index.row(),column = index.column();
    auto curLogInfo = storedData[row];
    if (column == 0) return curLogInfo.id;
    else if (column == 1) return curLogInfo.timestamp;
    else if (column == 2) return curLogInfo.level;
    else if (column == 3) return curLogInfo.userName;
    else if (column == 4) return curLogInfo.processName;
    else if (column == 5) return curLogInfo.pid;
    else if (column == 6) return curLogInfo.message;
    return QVariant();
}

QVariant CLogsModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Vertical) return section + 1;
    else{
        if (section == 0) return QString("_id");
        else if (section == 1) return QString("Дата и время");
        else if (section == 2) return QString("Уровень");
        else if (section == 3) return QString("Пользователь");
        else if (section == 4) return QString("Служба");
        else if (section == 5) return QString("PID");
        else if (section == 6) return QString("Содержание");
    }
    return QVariant();
}

void CLogsModel::add_log(const CLogsData &newData){
    //(storedData.size() > 1000) return;
    beginInsertRows(QModelIndex(),storedData.size(),storedData.size());
    storedData.push_back(newData);
    levelsFrequency[newData.level]++;
    usersFrequency[newData.userName]++;
    processesFrequecy[newData.processName]++;
    haveLevels.insert(newData.level);
    haveUsers.insert(newData.userName);
    haveProcesses.insert(newData.processName);
    endInsertRows();
    if ((int)storedData.size() > dataCnt){
        beginRemoveRows(QModelIndex(),storedData.size() - 1,storedData.size() - 1);
        if (--levelsFrequency[storedData.front().level] == 0) haveLevels.erase(storedData.front().level);
        if (--usersFrequency[storedData.front().userName] == 0) haveUsers.erase(storedData.front().userName);
        if (--processesFrequecy[storedData.front().processName] == 0) haveProcesses.erase(storedData.front().processName);
        storedData.pop_front();
        endRemoveRows();
    }
}

int CLogsModel::get_frequency_for_level(const QString &level) const{
    return levelsFrequency[level];
}

std::set<QString> CLogsModel::get_levels() const{
    return haveLevels;
}

std::set<QString> CLogsModel::get_users() const{
    return haveUsers;
}

std::set<QString> CLogsModel::get_processes() const{
    return haveProcesses;
}
