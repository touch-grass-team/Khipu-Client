#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QObject>
#include <QtWidgets>
#include "LogsModel.h"
#include "qdata.h"
#include "GraphView.h"

class CMainView : public QFrame{

public:
    CMainView(QWidget *parent = 0);
    ~CMainView();

private:
   // v,h boxes
    QVBoxLayout *mainBox;
    QVBoxLayout *filterBox;
    QHBoxLayout *filterAndGraphBox;
   // form layouts
    QFormLayout *formFilter;
    QFormLayout* formDateTime;
   // labels
    QLabel *lbLevel;
    QLabel *lbProcess;
    QLabel *lbUser;
    QLabel *lbDateTime;
   // buttons, spin boxes...
    QComboBox *comboLevel;
    QComboBox *comboProcesses;
    QComboBox *comboUsers;
    QDateTimeEdit *dateTimeEditFrom;
    QDateTimeEdit *dateTimeEditTo;
    QPushButton *pbFilter;
    QPushButton *pbNormal;
   // other
    QTableView *table;
    CLogsModel *tableModel;
    QTimer *timer;
    CGraphView *graphView;
   // methods
    void set_table_settings();

private slots:
    void timer_work();
    void on_pbFilter_clicked();
    void on_pbNormal_clicked();

};

#endif // MAINVIEW_H