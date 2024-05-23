#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QObject>
#include <QtWidgets>
#include "qcustomplot.h"

class CGraphView : public QFrame{
    Q_OBJECT

public:
    CGraphView(QWidget *parent = 0);

private:
   // v,h boxes
    QVBoxLayout *mainBox;
   // other
    QCustomPlot *customPlot;
   // methods
    void set_graph_settings();

};

#endif // GRAPHVIEW_H
