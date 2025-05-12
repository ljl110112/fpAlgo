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

// 坐标转换函数
QList<QPointF> PlotWidget::transformCoordinates(const QList<QPointF>& originalCoordinates) {
    if (originalCoordinates.isEmpty()) {
        return QList<QPointF>();
    }

    // 找到原始坐标的最小值和最大值
    double minX = originalCoordinates[0].x();
    double maxX = originalCoordinates[0].x();
    double minY = originalCoordinates[0].y();
    double maxY = originalCoordinates[0].y();

    for (int i = 1; i < originalCoordinates.size(); ++i) {
        const QPointF& point = originalCoordinates[i];
        if (point.x() < minX) {
            minX = point.x();
        }
        if (point.x() > maxX) {
            maxX = point.x();
        }
        if (point.y() < minY) {
            minY = point.y();
        }
        if (point.y() > maxY) {
            maxY = point.y();
        }
    }

    // 目标范围
    double targetMinX = -350;
    double targetMaxX = 350;
    double targetMinY = -250;
    double targetMaxY = 250;

    // 计算缩放因子
    double scaleX = (targetMaxX - targetMinX) / (maxX - minX);
    double scaleY = (targetMaxY - targetMinY) / (maxY - minY);

    // 应用缩放和平移变换
    QList<QPointF> transformedCoordinates;
    for (int i = 0; i < originalCoordinates.size(); ++i) {
        const QPointF& originalPoint = originalCoordinates[i];
        double newX = targetMinX + (originalPoint.x() - minX) * scaleX;
        double newY = targetMinY + (originalPoint.y() - minY) * scaleY;
        transformedCoordinates.append(QPointF(newX, newY));
    }

    return transformedCoordinates;
}

// 经纬度转平面坐标（简单墨卡托投影）
QPointF PlotWidget::latLonToMercator(QPointF pos) const {
    qreal lon = pos.x();
    qreal lat = pos.y();
    const double R = 6378137; // 地球半径（米）
    double x = R * lon * M_PI / 180.0;
    double tmp = std::tan(M_PI / 4.0 + lat * M_PI / 360.0);
    double y = R * std::log(tmp);
    return QPointF(x, y);
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
    QList<QPointF> allPointsList;//用于坐标转换的所有点列表
    for (QList<DataClass::single_RW>::const_iterator rwIt = m_data.rwList.begin(); rwIt != m_data.rwList.end(); ++rwIt) {
        const DataClass::single_RW& rw = *rwIt;
        QPointF pos = latLonToMercator(rw.destinationCoordinate);
        allPointsList.append(pos);
        if (pos.x() < minX) minX = pos.x();
        if (pos.x() > maxX) maxX = pos.x();
        if (pos.y() < minY) minY = pos.y();
        if (pos.y() > maxY) maxY = pos.y();
    }
    for (QList<DataClass::single_HC>::const_iterator hcIt = m_data.hcList.begin(); hcIt != m_data.hcList.end(); ++hcIt) {
        const DataClass::single_HC& hc = *hcIt;
        QPointF pos = latLonToMercator(hc.truckStartingPosition);
        allPointsList.append(pos);
        if (pos.x() < minX) minX = pos.x();
        if (pos.x() > maxX) maxX = pos.x();
        if (pos.y() < minY) minY = pos.y();
        if (pos.y() > maxY) maxY = pos.y();
    }
    for (QList<DataClass::single_ZD>::const_iterator zdIt = m_data.zdList.begin(); zdIt != m_data.zdList.end(); ++zdIt) {
        const DataClass::single_ZD& zd = *zdIt;
        QPointF pos = latLonToMercator(zd.releaseLocationCoordinate);
        allPointsList.append(pos);
        if (pos.x() < minX) minX = pos.x();
        if (pos.x() > maxX) maxX = pos.x();
        if (pos.y() < minY) minY = pos.y();
        if (pos.y() > maxY) maxY = pos.y();
    }

    // 设置场景矩形以适应数据
    coor->setSceneRectToFitData(minX, maxX, minY, maxY);
    QList<QPointF> transformedCoordinates = transformCoordinates(allPointsList);
    for(int i=0;i<transformedCoordinates.count();i++){
        coor->plotPoint(transformedCoordinates[i].x(),transformedCoordinates[i].y(),"");
    }


//    // 计算缩放比例
//    double scaleX = width() / (maxX - minX);
//    double scaleY = height() / (maxY - minY);

//    // 绘制放飞任务的目的地
//    painter.setPen(Qt::red);
//    painter.setBrush(Qt::red);
//    for (QList<DataClass::single_RW>::const_iterator rwIt = m_data.rwList.begin(); rwIt != m_data.rwList.end(); ++rwIt) {
//        const DataClass::single_RW& rw = *rwIt;
//        QPointF pos = rw.destinationCoordinate;
//        int x = static_cast<int>((pos.x() - minX) * scaleX);
//        int y = static_cast<int>((pos.y() - minY) * scaleY);
////        painter.drawEllipse(x - 2, y - 2, 4, 4);
//        coor->plotPoint(pos.x(),pos.y(),rw.rwbh);
//    }

//    // 绘制货车的起始位置
//    painter.setPen(Qt::blue);
//    painter.setBrush(Qt::blue);
//    for (QList<DataClass::single_HC>::const_iterator hcIt = m_data.hcList.begin(); hcIt != m_data.hcList.end(); ++hcIt) {
//        const DataClass::single_HC& hc = *hcIt;
//        QPointF pos = hc.truckStartingPosition;
//        int x = static_cast<int>((pos.x() - minX) * scaleX);
//        int y = static_cast<int>((pos.y() - minY) * scaleY);
////        painter.drawRect(x - 2, y - 2, 4, 4);
//        coor->plotPoint(pos.x(),pos.y(),hc.hcbh,Qt::green);
//    }

//    // 绘制放飞地点
//    painter.setPen(Qt::green);
//    painter.setBrush(Qt::green);
//    for (QList<DataClass::single_ZD>::const_iterator zdIt = m_data.zdList.begin(); zdIt != m_data.zdList.end(); ++zdIt) {
//        const DataClass::single_ZD& zd = *zdIt;
//        QPointF pos = zd.releaseLocationCoordinate;
//        int x = static_cast<int>((pos.x() - minX) * scaleX);
//        int y = static_cast<int>((pos.y() - minY) * scaleY);
////        painter.drawEllipse(x - 2, y - 2, 4, 4);
//        coor->plotPoint(pos.x(),pos.y(),"",Qt::blue);
//    }
}
