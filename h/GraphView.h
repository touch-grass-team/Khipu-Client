#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QObject>
#include <QtWidgets>
#include "qcustomplot.h"
#include <deque>

#define warningGraph 0
#define noticeGraph 1
#define infoGraph 2
#define errGraph 3
#define debugGraph 4

class CGraphView : public QFrame{
    Q_OBJECT

public:
    CGraphView(int pointsSize,QWidget *parent = 0);
    void clear();
    void add_point(int64_t seconds,int curFrequency,
                   const QString &level);
    void set_points_size(int pointsSize);

private:
   // v,h boxes
    QVBoxLayout *mainBox;
   // other
    QCustomPlot *customPlot;
    int pointsSize;
    int havePoints;
    std::deque <QString> pointsLevels;
   // methods
    void set_graph_settings();
    void erase_old_point();
};

#endif // GRAPHVIEW_H
