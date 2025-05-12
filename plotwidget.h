// plotwidget.h
#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include "dataclass.h"
#include "coordinatesystem.h"

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = 0);
    ~PlotWidget();

    void setData(const DataClass& data);

    QPointF latLonToMercator(QPointF pos) const;
    QList<QPointF> transformCoordinates(const QList<QPointF> &originalCoordinates);
protected:
    void paintEvent(QPaintEvent *event);

private:
    DataClass m_data;
    CoordinateSystem *coor;
};

#endif // PLOTWIDGET_H
