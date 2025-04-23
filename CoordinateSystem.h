#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <cmath>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollBar>

class CoordinateSystem : public QGraphicsView {
    Q_OBJECT
public:
    explicit CoordinateSystem(QWidget *parent = 0);
    void plotPoint(qreal lat, qreal lon, const QString& label, const QBrush &brush = Qt::red);  // 新增接口
    void plotLine(qreal lat1, qreal lon1, qreal lat2, qreal lon2, const QString& label); // 新增线段接口
    double calculateDistance(qreal lat1, qreal lon1, qreal lat2, qreal lon2) const;  // 新增计算接口

    QPointF latLonToMercator(qreal lon, qreal lat) const;
private:
    QGraphicsScene *scene;
    void drawAxes();
    void drawGrid();

    bool dragging;          // 是否正在拖动
    QPoint lastMousePos;    // 记录上一次鼠标位置

private slots:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // COORDINATESYSTEM_H
