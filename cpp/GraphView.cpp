#include "GraphView.h"

CGraphView::CGraphView(int pointsSize, QWidget *parent)  : QFrame(parent){
    this->pointsSize = pointsSize;
    mainBox = new QVBoxLayout();
    customPlot = new QCustomPlot();
    set_graph_settings();
    mainBox->addWidget(customPlot);
    this->setLayout(mainBox);
   // other
    havePoints = 0;
}

void CGraphView::add_point(int64_t seconds, int curFrequency, const QString &level){
    if (level == "warning")
        customPlot->graph(warningGraph)->addData(seconds,curFrequency);
    else if (level == "notice")
        customPlot->graph(noticeGraph)->addData(seconds,curFrequency);
    else if (level == "info")
        customPlot->graph(infoGraph)->addData(seconds,curFrequency);
    else if (level == "err")
        customPlot->graph(errGraph)->addData(seconds,curFrequency);
    else
        customPlot->graph(debugGraph)->addData(seconds,curFrequency);
    havePoints++;
    pointsLevels.push_back(level);
    erase_old_point();
    customPlot->rescaleAxes(true);
    customPlot->replot();
}

void CGraphView::set_graph_settings(){
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignLeft);
    QSharedPointer <QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime());
    dateTicker->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");
    customPlot->xAxis->setTicker(dateTicker);
    customPlot->yAxis->setRange(0,pointsSize);
    customPlot->xAxis->setTickLabelFont(QFont("Montserrat",12));
    customPlot->yAxis->setTickLabelFont(QFont("Montserrat",12));
    customPlot->xAxis->setLabel("Дата и время");
    customPlot->yAxis->setLabel("Частота");
    customPlot->setFont(QFont("Montserrat",12));
    for (int i = 0;i < 5;i++) customPlot->addGraph();
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Montserrat",8));
    customPlot->graph(warningGraph)->setPen(QPen(Qt::darkYellow,2));
    customPlot->graph(warningGraph)->setName("Частота warning");
    customPlot->graph(noticeGraph)->setPen(QPen(Qt::green,2));
    customPlot->graph(noticeGraph)->setName("Частота notice");
    customPlot->graph(infoGraph)->setPen(QPen(Qt::magenta,2));
    customPlot->graph(infoGraph)->setName("Частота info");
    customPlot->graph(errGraph)->setPen(QPen(Qt::red,2));
    customPlot->graph(errGraph)->setName("Частота err");
    customPlot->graph(debugGraph)->setPen(QPen(Qt::cyan,2));
    customPlot->graph(debugGraph)->setName("Частота debug");
}

void CGraphView::erase_old_point(){
    if (havePoints > pointsSize){
        QString eraseLevel = pointsLevels.front();
        pointsLevels.pop_front();
        if (eraseLevel == "warning")
            customPlot->graph(warningGraph)->data()->removeBefore(1);
        else if (eraseLevel == "notice")
            customPlot->graph(noticeGraph)->data()->removeBefore(1);
        else if (eraseLevel == "info")
            customPlot->graph(infoGraph)->data()->removeBefore(1);
        else if (eraseLevel == "err")
            customPlot->graph(errGraph)->data()->removeBefore(1);
        else
            customPlot->graph(debugGraph)->data()->removeBefore(1);
    }
}
