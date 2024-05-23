#include "GraphView.h"

CGraphView::CGraphView(QWidget *parent)  : QFrame(parent){
    mainBox = new QVBoxLayout();
    customPlot = new QCustomPlot();
    set_graph_settings();
    mainBox->addWidget(customPlot);
    this->setLayout(mainBox);
}

void CGraphView::set_graph_settings(){
    QSharedPointer <QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime());
    dateTicker->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setTicker(dateTicker);
    customPlot->yAxis->setRange(0,1);
}
