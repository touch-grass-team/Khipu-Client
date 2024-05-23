#include "MainView.h"

CMainView::CMainView(QWidget *parent) : QFrame(parent){
    set_db();
    mainBox = new QVBoxLayout();
    filterBox = new QVBoxLayout();
    filterAndGraphBox = new QHBoxLayout();
    formFilter = new QFormLayout();
    formDateTime = new QFormLayout();
    lbLevel = new QLabel("Выберите уровень: ");
    lbLevel->setFont(QFont("Montserrat",10));
    lbLevel->setStyleSheet("font: bold");
    lbProcess = new QLabel("Выберите службу: ");
    lbProcess->setFont(QFont("Montserrat",10));
    lbProcess->setStyleSheet("font: bold");
    lbUser = new QLabel("Выберите пользователя: ");
    lbUser->setFont(QFont("Montserrat",10));
    lbUser->setStyleSheet("font: bold");
    lbDateTime = new QLabel("Выберите нужный диапазон: ");
    lbDateTime->setFont(QFont("Montserrat",10));
    lbDateTime->setStyleSheet("font: bold");
    table = new QTableView();
    tableModel = new CLogsModel(this);
    timer = new QTimer();
    graphView = new CGraphView();
    comboLevel = new QComboBox();
    comboLevel->setFont(QFont("Montserrat",10));
    comboLevel->setFixedWidth(150);
    comboLevel->addItem("Не выбрано",-1);
    comboProcesses = new QComboBox();
    comboProcesses->setFont(QFont("Montserrat",10));
    comboProcesses->setFixedWidth(150);
    comboProcesses->addItem("Не выбрано",-1);
    comboUsers = new QComboBox();
    comboUsers->setFont(QFont("Montserrat",10));
    comboUsers->setFixedWidth(150);
    comboUsers->addItem("Не выбрано",-1);
    dateTimeEditFrom = new QDateTimeEdit();
    dateTimeEditFrom->setFont(QFont("Montserrat",10));
    dateTimeEditTo = new QDateTimeEdit();
    dateTimeEditTo->setFont(QFont("Montserrat",10));
    pbFilter = new QPushButton("Отфильтровать");
    pbFilter->setFixedSize(150,50);
    pbFilter->setFont(QFont("Montserrat",12));
    pbFilter->setStyleSheet("QPushButton{"
                            "border:none;"
                            "color: white;"
                            "font: bold;"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);"
                            "border-radius: 15px;}"
                            "QPushButton:hover{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);}"
                            "QPushButton:disabled{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #E83812,stop: 0.4999 #E83812,stop: 0.5 #E83812,stop: 1 #238);}"
                            "QPushButton:pressed{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbNormal = new QPushButton("По умолчанию");
    pbNormal->setFixedSize(150,50);
    pbNormal->setFont(QFont("Montserrat",12));
    pbNormal->setStyleSheet("QPushButton{"
                            "border:none;"
                            "color: white;"
                            "font: bold;"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);"
                            "border-radius: 15px;}"
                            "QPushButton:hover{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);}"
                            "QPushButton:disabled{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #E83812,stop: 0.4999 #E83812,stop: 0.5 #E83812,stop: 1 #238);}"
                            "QPushButton:pressed{"
                            "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    table->setModel(tableModel);
    set_table_settings();
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
   // main part
    filterAndGraphBox->addLayout(filterBox);
    filterAndGraphBox->addWidget(graphView);
    timer->setInterval(5000);
    mainBox->addLayout(filterAndGraphBox);
    mainBox->addWidget(table);
    //mainBox->addWidget(table);
    this->setLayout(mainBox);
    this->setFixedSize(1200,800);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
   // connects
    connect(timer,&QTimer::timeout,this,&CMainView::timer_work);
    connect(pbFilter,&QPushButton::clicked,this,&CMainView::on_pbFilter_clicked);
    connect(pbNormal,&QPushButton::clicked,this,&CMainView::on_pbNormal_clicked);
    timer->start();
}

CMainView::~CMainView(){
    if (db.isOpen()) db.close();
}

void CMainView::set_table_settings(){
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setFont(QFont("Montserrat",12));
    table->horizontalHeader()->setFont(QFont("Montserrat",12));
    table->setColumnHidden(0,true);
    table->setStyleSheet("QHeaderView::section{"
                         "background-color: QLinearGradient(x1: 1,y1: 0,x2: 0,y2: 1, stop: 0 #FFDEAD,stop: 0.4999 #FFF8DC,stop: 0.5 #FFE4C4,stop: 1 #FFEBCD);"
                         "color: black;}");
}

void CMainView::timer_work(){
    if (!db.open()) DBErrorsHandler(db.lastError().text());
    QDateTime currentTime = QDateTime().currentDateTime();
    int64_t seconds = currentTime.toSecsSinceEpoch() - 5;
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
    }
    db.close();
    qDebug() << "work;";
}

void CMainView::on_pbFilter_clicked(){
    timer->stop();
}

void CMainView::on_pbNormal_clicked(){
    timer->start();
}
