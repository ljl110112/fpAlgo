// plotwidget.h
#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include "dataclass.h"

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = 0);
    ~PlotWidget();

    void setData(const DataClass& data);

protected:
    void paintEvent(QPaintEvent *event);

private:
    DataClass m_data;
};

#endif // PLOTWIDGET_H
