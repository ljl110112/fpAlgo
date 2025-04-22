// plotwidget.cpp
#include "plotwidget.h"
#include <QPainter>

PlotWidget::PlotWidget(QWidget *parent) : QWidget(parent)
{
    coor = new CoordinateSystem();
    coor->resize(900, 700);
    coor->show();
}

PlotWidget::~PlotWidget()
{

}

void PlotWidget::setData(const DataClass& data)
{
    m_data = data;
    update(); // 触发重绘
}

void PlotWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 找到数据的边界
    double minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
    for (QList<DataClass::single_RW>::const_iterator rwIt = m_data.rwList.begin(); rwIt != m_data.rwList.end(); ++rwIt) {
        const DataClass::single_RW& rw = *rwIt;
        QPointF pos = rw.destinationCoordinate;
        if (pos.x() < minX) minX = pos.x();
        if (pos.x() > maxX) maxX = pos.x();
        if (pos.y() < minY) minY = pos.y();
        if (pos.y() > maxY) maxY = pos.y();
    }
    for (QList<DataClass::single_HC>::const_iterator hcIt = m_data.hcList.begin(); hcIt != m_data.hcList.end(); ++hcIt) {
        const DataClass::single_HC& hc = *hcIt;
        QPointF pos = hc.truckStartingPosition;
        if (pos.x() < minX) minX = pos.x();
        if (pos.x() > maxX) maxX = pos.x();
        if (pos.y() < minY) minY = pos.y();
        if (pos.y() > maxY) maxY = pos.y();
    }
    for (QList<DataClass::single_ZD>::const_iterator zdIt = m_data.zdList.begin(); zdIt != m_data.zdList.end(); ++zdIt) {
        const DataClass::single_ZD& zd = *zdIt;
        QPointF pos = zd.releaseLocationCoordinate;
        if (pos.x() < minX) minX = pos.x();
        if (pos.x() > maxX) maxX = pos.x();
        if (pos.y() < minY) minY = pos.y();
        if (pos.y() > maxY) maxY = pos.y();
    }

    // 计算缩放比例
    double scaleX = width() / (maxX - minX);
    double scaleY = height() / (maxY - minY);

    // 绘制放飞任务的目的地
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    for (QList<DataClass::single_RW>::const_iterator rwIt = m_data.rwList.begin(); rwIt != m_data.rwList.end(); ++rwIt) {
        const DataClass::single_RW& rw = *rwIt;
        QPointF pos = rw.destinationCoordinate;
        int x = static_cast<int>((pos.x() - minX) * scaleX);
        int y = static_cast<int>((pos.y() - minY) * scaleY);
//        painter.drawEllipse(x - 2, y - 2, 4, 4);
        coor->plotPoint(pos.x(),pos.y(),rw.rwbh);
    }

    // 绘制货车的起始位置
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    for (QList<DataClass::single_HC>::const_iterator hcIt = m_data.hcList.begin(); hcIt != m_data.hcList.end(); ++hcIt) {
        const DataClass::single_HC& hc = *hcIt;
        QPointF pos = hc.truckStartingPosition;
        int x = static_cast<int>((pos.x() - minX) * scaleX);
        int y = static_cast<int>((pos.y() - minY) * scaleY);
//        painter.drawRect(x - 2, y - 2, 4, 4);
        coor->plotPoint(pos.x(),pos.y(),hc.hcbh,Qt::green);
    }

    // 绘制放飞地点
    painter.setPen(Qt::green);
    painter.setBrush(Qt::green);
    for (QList<DataClass::single_ZD>::const_iterator zdIt = m_data.zdList.begin(); zdIt != m_data.zdList.end(); ++zdIt) {
        const DataClass::single_ZD& zd = *zdIt;
        QPointF pos = zd.releaseLocationCoordinate;
        int x = static_cast<int>((pos.x() - minX) * scaleX);
        int y = static_cast<int>((pos.y() - minY) * scaleY);
//        painter.drawEllipse(x - 2, y - 2, 4, 4);
        coor->plotPoint(pos.x(),pos.y(),"",Qt::blue);
    }
}
