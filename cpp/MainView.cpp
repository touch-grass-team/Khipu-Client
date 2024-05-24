#include "MainView.h"

CMainView::CMainView(QWidget *parent) : QFrame(parent){
    set_db();
    mainBox = new QVBoxLayout();
    filterBox = new QVBoxLayout();
    statBox = new QVBoxLayout();
    filterAndStatBox = new QHBoxLayout();
    formFilter = new QFormLayout();
    formDateTime = new QFormLayout();
    formStat = new QFormLayout();
    gbStat = new QGroupBox("Статистика по текущим логам");
    gbStat->setStyleSheet("QGroupBox { font: bold; color: red; border: 1px solid silver; border-radius: 6px; margin-top: 6px; }"
                          "QGroupBox::title { subcontrol-origin: margin; left: 7px; padding: 0px 5px 0px 5px; }");
    gbStat->setFont(QFont("Montserrat",12));
    lbLevel = new QLabel("Выберите уровень: ");
    lbLevel->setFont(QFont("Montserrat",12));
    lbLevel->setStyleSheet("font: bold");
    lbProcess = new QLabel("Выберите службу: ");
    lbProcess->setFont(QFont("Montserrat",12));
    lbProcess->setStyleSheet("font: bold");
    lbUser = new QLabel("Выберите пользователя: ");
    lbUser->setFont(QFont("Montserrat",12));
    lbUser->setStyleSheet("font: bold");
    lbDateTime = new QLabel("Выберите нужный диапазон: ");
    lbDateTime->setFont(QFont("Montserrat",12));
    lbDateTime->setStyleSheet("font: bold");
    lbWarningCnt = new QLabel("Количество warning: ");
    lbWarningCnt->setFont(QFont("Montserrat",12));
    lbWarningCnt->setStyleSheet("font: bold");
    lbWarningValue = new QLabel("0");
    lbWarningValue->setFont(QFont("Montserrat",12));
    lbWarningValue->setStyleSheet("font: bold; color: green");
    lbNoticeCnt = new QLabel("Количество notice: ");
    lbNoticeCnt->setFont(QFont("Montserrat",12));
    lbNoticeCnt->setStyleSheet("font: bold");
    lbNoticeValue = new QLabel("0");
    lbNoticeValue->setFont(QFont("Montserrat",12));
    lbNoticeValue->setStyleSheet("font: bold; color: green");
    lbInfoCnt = new QLabel("Количество info: ");
    lbInfoCnt->setFont(QFont("Montserrat",12));
    lbInfoCnt->setStyleSheet("font: bold");
    lbInfoValue = new QLabel("0");
    lbInfoValue->setFont(QFont("Montserrat",12));
    lbInfoValue->setStyleSheet("font: bold; color: green");
    lbErrCnt = new QLabel("Количество err: ");
    lbErrCnt->setFont(QFont("Montserrat",12));
    lbErrCnt->setStyleSheet("font: bold");
    lbErrValue = new QLabel("0");
    lbErrValue->setFont(QFont("Montserrat",12));
    lbErrValue->setStyleSheet("font: bold; color: green");
    lbDebugCnt = new QLabel("Количество debug: ");
    lbDebugCnt->setFont(QFont("Montserrat",12));
    lbDebugCnt->setStyleSheet("font: bold");
    lbDebugValue = new QLabel("0");
    lbDebugValue->setFont(QFont("Montserrat",12));
    lbDebugValue->setStyleSheet("font: bold; color: green");
    lbTemp1 = new QLabel();
    lbTemp2 = new QLabel();
    table = new QTableView();
    tableModel = new CLogsModel(dataSize,this);
    mainTimer = new QTimer();
    dbTimer = new QTimer();
    graphView = new CGraphView(dataSize,this);
    comboLevel = new QComboBox();
    comboLevel->setFont(QFont("Montserrat",12));
    comboLevel->setFixedWidth(150);
    comboLevel->addItem("Не выбрано","null");
    comboLevel->addItem("warning","warning");
    comboLevel->addItem("notice","notice");
    comboLevel->addItem("info","info");
    comboLevel->addItem("err","err");
    comboLevel->addItem("debug","debug");
    comboProcesses = new QComboBox();
    comboProcesses->setFont(QFont("Montserrat",12));
    comboProcesses->setFixedWidth(150);
    comboProcesses->addItem("Не выбрано","null");
    comboUsers = new QComboBox();
    comboUsers->setFont(QFont("Montserrat",12));
    comboUsers->setFixedWidth(150);
    comboUsers->addItem("Не выбрано","null");
    dateTimeEditFrom = new QDateTimeEdit();
    dateTimeEditFrom->setFont(QFont("Montserrat",12));
    dateTimeEditTo = new QDateTimeEdit();
    dateTimeEditTo->setFont(QFont("Montserrat",12));
    pbFilter = new QPushButton("Отфильтровать");
    pbFilter->setFixedSize(150,50);
    pbFilter->setFont(QFont("Montserrat",12));
    pbFilter->setStyleSheet("QPushButton{"
                            "border:none;"
                            "color: white;"
                            "font: bold;"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #F8B88B,stop: 0.4999 #F8B88B,stop: 0.5 #F8B88B,stop: 1 #F2D4D7);"
                            "border-radius: 15px;}"
                            "QPushButton:hover{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #C08081,stop: 0.4999 #C08081,stop: 0.5 #C08081,stop: 1 #F2D4D7);}"
                            "QPushButton:disabled{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #E83812,stop: 0.4999 #E83812,stop: 0.5 #E83812,stop: 1 #238);}"
                            "QPushButton:pressed{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #F8B88B,stop: 0.4999 #F8B88B,stop: 0.5 #F8B88B,stop: 1 #F2D4D7);}");
    pbNormal = new QPushButton("По умолчанию");
    pbNormal->setFixedSize(150,50);
    pbNormal->setFont(QFont("Montserrat",12));
    pbNormal->setStyleSheet("QPushButton{"
                            "border:none;"
                            "color: white;"
                            "font: bold;"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #F8B88B,stop: 0.4999 #F8B88B,stop: 0.5 #F8B88B,stop: 1 #F2D4D7);"
                            "border-radius: 15px;}"
                            "QPushButton:hover{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #C08081,stop: 0.4999 #C08081,stop: 0.5 #C08081,stop: 1 #F2D4D7);}"
                            "QPushButton:disabled{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #E83812,stop: 0.4999 #E83812,stop: 0.5 #E83812,stop: 1 #238);}"
                            "QPushButton:pressed{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #F8B88B,stop: 0.4999 #F8B88B,stop: 0.5 #F8B88B,stop: 1 #F2D4D7);}");
    table->setModel(tableModel);
    set_table_settings();
    update_combo_from_db();
   // filter part
    formFilter->setAlignment(Qt::AlignLeft);
    formFilter->setLabelAlignment(Qt::AlignLeft);
    formFilter->addRow(lbLevel,comboLevel);
    formFilter->addRow(lbUser,comboUsers);
    formFilter->addRow(lbProcess,comboProcesses);
    formDateTime->addRow(dateTimeEditFrom,dateTimeEditTo);
    formFilter->addRow(lbDateTime,formDateTime);
    formFilter->addRow(pbFilter,pbNormal);
    filterBox->addLayout(formFilter);
   // stat part
    formStat->setAlignment(Qt::AlignLeft);
    formStat->setLabelAlignment(Qt::AlignLeft);
    formStat->addRow(lbTemp1,lbTemp2);
    formStat->addRow(lbWarningCnt,lbWarningValue);
    formStat->addRow(lbNoticeCnt,lbNoticeValue);
    formStat->addRow(lbInfoCnt,lbInfoValue);
    formStat->addRow(lbErrCnt,lbErrValue);
    formStat->addRow(lbDebugCnt,lbDebugValue);
    statBox->addLayout(formStat);
    gbStat->setLayout(statBox);
    gbStat->setFixedWidth(300);
   // main part
    filterAndStatBox->addLayout(filterBox);
    filterAndStatBox->addWidget(gbStat);
    mainTimer->setInterval(timerInterval * 1000);
    dbTimer->setInterval(60000);
    mainBox->addLayout(filterAndStatBox);
    mainBox->addWidget(table);
    mainBox->addWidget(graphView);
    //mainBox->addWidget(table);
    this->setLayout(mainBox);
    this->setFixedSize(1200,800);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
   // connects
    connect(mainTimer,&QTimer::timeout,this,&CMainView::mainTimer_work);
    connect(dbTimer,&QTimer::timeout,this,&CMainView::dbTimer_work);
    connect(pbFilter,&QPushButton::clicked,this,&CMainView::on_pbFilter_clicked);
    connect(pbNormal,&QPushButton::clicked,this,&CMainView::on_pbNormal_clicked);
    connect(table,&QTableView::doubleClicked,this,&CMainView::on_table_doubleClicked);
    mainTimer->start();
    dbTimer->start();
}

CMainView::~CMainView(){
    if (db.isOpen()) db.close();
}

void CMainView::set_table_settings(){
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setFont(QFont("Montserrat",12));
    table->horizontalHeader()->setFont(QFont("Montserrat",12));
    table->setColumnHidden(0,true);
    table->setStyleSheet("QHeaderView::section{"
                         "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #FFDEAD,stop: 0.4999 #FFF8DC,stop: 0.5 #FFE4C4,stop: 1 #FFEBCD);"
                         "color: black;}");
    table->setFixedHeight(300);
}

void CMainView::update_combo_from_db(){
    if (!db.open()){
        DBErrorsHandler(db.lastError().text());
        return;
    }
    QString usersQueryStr = "SELECT * FROM logs.prc_get_unique_users()";
    QSqlQuery usersQuery;
    if (!usersQuery.exec(usersQueryStr)){
        DBErrorsHandler(usersQuery.lastError().text());
        db.close();
        return;
    }
    comboUsers->clear();
    comboUsers->addItem("Не выбрано","null");
    QSqlRecord recUsers = usersQuery.record();
    while(usersQuery.next()){
        QString userName = usersQuery.value(recUsers.indexOf("_user_name")).toString();
        comboUsers->addItem(userName,userName);
    }
    QString processesQueryStr = "SELECT * FROM logs.prc_get_unique_processes()";
    QSqlQuery processesQuery;
    if (!processesQuery.exec(processesQueryStr)){
        DBErrorsHandler(processesQuery.lastError().text());
        db.close();
        return;
    }
    comboProcesses->clear();
    comboProcesses->addItem("Не выбрано","null");
    QSqlRecord recProcesses = processesQuery.record();
    while(processesQuery.next()){
        QString processName = processesQuery.value(recProcesses.indexOf("_process_name")).toString();
        comboProcesses->addItem(processName,processName);
    }
}

void CMainView::mainTimer_work(){
    if (!db.open()) DBErrorsHandler(db.lastError().text());
    QDateTime currentTime = QDateTime().currentDateTime();
    int64_t seconds = currentTime.toSecsSinceEpoch() - timerInterval;
    QString needTime =  QDateTime().fromSecsSinceEpoch(seconds).toString("yyyy-MM-dd hh:mm:ss");
    QString queryStr = QString("SELECT * FROM logs.prc_get_logs_by_time(\'%1\');").arg(needTime);
    QSqlQuery query;
    if (!query.exec(queryStr)){
        DBErrorsHandler(query.lastError().text());
        db.close();
        return;
    }
    QSqlRecord rec = query.record();
    while(query.next()){
        int id = query.value(rec.indexOf("_id")).toInt();
        QDateTime timestamp = query.value(rec.indexOf("_timestamp")).toDateTime();
        QString level = query.value(rec.indexOf("_level")).toString();
        QString userName = query.value(rec.indexOf("_user_name")).toString();;
        QString processName = query.value(rec.indexOf("_process_name")).toString();
        int pid = query.value(rec.indexOf("_pid")).toInt();
        QString message = query.value(rec.indexOf("_message")).toString();
        CLogsData newData = {id,timestamp,level,userName,
                            processName,pid,message};
        tableModel->add_log(newData);
        graphView->add_point(timestamp.toSecsSinceEpoch(),tableModel->get_frequency_for_level(level),level);
        lbWarningValue->setText(QVariant(tableModel->get_frequency_for_level("warning")).toString());
        lbNoticeValue->setText(QVariant(tableModel->get_frequency_for_level("notice")).toString());
        lbInfoValue->setText(QVariant(tableModel->get_frequency_for_level("info")).toString());
        lbErrValue->setText(QVariant(tableModel->get_frequency_for_level("err")).toString());
        lbDebugValue->setText(QVariant(tableModel->get_frequency_for_level("debug")).toString());
    }
    db.close();
}

void CMainView::dbTimer_work(){
    update_combo_from_db();
}

void CMainView::on_pbFilter_clicked(){
    if (!db.open()){
        DBErrorsHandler(db.lastError().text());
        return;
    }
    mainTimer->stop();
    lbWarningValue->setText("0");
    lbNoticeValue->setText("0");
    lbInfoValue->setText("0");
    lbErrValue->setText("0");
    lbDebugValue->setText("0");
    QString level = comboLevel->currentData().toString();
    QString userName = comboUsers->currentData().toString();
    QString processName = comboProcesses->currentData().toString();
    QString dateFrom = dateTimeEditFrom->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString dateTo = dateTimeEditTo->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString queryStr;
    queryStr.sprintf("SELECT * FROM logs.prc_get_n_filtered_logs_ordered_by_time('false',%d,'%s','%s','%s','%s','%s')",
                  dataSize,dateFrom.toStdString().c_str(),dateTo.toStdString().c_str(),level.toStdString().c_str(),userName.toStdString().c_str(),processName.toStdString().c_str());
    QSqlQuery query;
    if (!query.exec(queryStr)){
        DBErrorsHandler(query.lastError().text());
        db.close();
        return;
    }
    QVector <CLogsData> filteredData;
    QSqlRecord rec = query.record();
    while(query.next()){
        int id = query.value(rec.indexOf("_id")).toInt();
        QDateTime timestamp = query.value(rec.indexOf("_timestamp")).toDateTime();
        QString level = query.value(rec.indexOf("_level")).toString();
        QString userName = query.value(rec.indexOf("_user_name")).toString();
        QString processName = query.value(rec.indexOf("_process_name")).toString();
        int pid = query.value(rec.indexOf("_pid")).toInt();
        QString message = query.value(rec.indexOf("_message")).toString();
        filteredData.push_back(CLogsData{id,timestamp,level,userName,processName,pid,message});
    }
    tableModel->set_data_size((int)filteredData.size() + 1);
    graphView->set_points_size((int)filteredData.size() + 1);
    for (auto& logInfo : filteredData){
        tableModel->add_log(logInfo);
        QString level = logInfo.level;
        int64_t seconds = logInfo.timestamp.toSecsSinceEpoch();
        graphView->add_point(seconds,tableModel->get_frequency_for_level(level),level);
        lbWarningValue->setText(QVariant(tableModel->get_frequency_for_level("warning")).toString());
        lbNoticeValue->setText(QVariant(tableModel->get_frequency_for_level("notice")).toString());
        lbInfoValue->setText(QVariant(tableModel->get_frequency_for_level("info")).toString());
        lbErrValue->setText(QVariant(tableModel->get_frequency_for_level("err")).toString());
        lbDebugValue->setText(QVariant(tableModel->get_frequency_for_level("debug")).toString());
    }
    db.close();
}

void CMainView::on_pbNormal_clicked(){
    tableModel->set_data_size(dataSize);
    graphView->set_points_size(dataSize);
    lbWarningValue->setText("0");
    lbNoticeValue->setText("0");
    lbInfoValue->setText("0");
    lbErrValue->setText("0");
    lbDebugValue->setText("0");
    mainTimer->start();
}

void CMainView::on_table_doubleClicked(QModelIndex index){
    if (!index.isValid()) return;
    int row = index.row();
    QString message = tableModel->get_message(row);
    QMessageBox::information(this,"Содержание",message);
}

