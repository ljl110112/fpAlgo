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
    void plotPoint(qreal x, qreal y, const QString& label, const QBrush &brush = Qt::red);  // 新增接口
    void plotLine(qreal x1, qreal y1, qreal x2, qreal y2, const QString& label); // 新增线段接口
    double calculateDistance(qreal x1, qreal y1, qreal x2, qreal y2) const;  // 新增计算接口

    void setSceneRectToFitData(double minX, double maxX, double minY, double maxY);
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
