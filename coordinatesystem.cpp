#include "CoordinateSystem.h"
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QDebug>

CoordinateSystem::CoordinateSystem(QWidget *parent)
    : QGraphicsView(parent), dragging(false)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-400, -300, 800, 600);  // 原点在中心
    this->setScene(scene);

    this->setRenderHint(QPainter::Antialiasing);  // 抗锯齿渲染
    this->setBackgroundBrush(Qt::white);          // 白色背景

    // 启用拖动模式
    setDragMode(QGraphicsView::ScrollHandDrag);

    drawGrid();
    drawAxes();
}

void CoordinateSystem::setSceneRectToFitData(double minX, double maxX, double minY, double maxY)
{
    double padding = 10; // 边距
    //scene->setSceneRect(minX - padding, minY - padding, maxX - minX + 2 * padding, maxY - minY + 2 * padding);
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void CoordinateSystem::plotPoint(qreal x, qreal y, const QString &label, const QBrush &brush)
{
    // 绘制点符号（红色圆形）
    QGraphicsEllipseItem *point = new QGraphicsEllipseItem(x-3, y-3, 6, 6);  // 半径3像素
    point->setBrush(brush);
    scene->addItem(point);

    // 添加文本标注（黑色字体，偏移位置）
    QGraphicsTextItem *text = scene->addText(label);
    text->setPos(x + 5, y - 15);  // 文本向右上方偏移
    text->setDefaultTextColor(Qt::black);
}

void CoordinateSystem::plotLine(qreal x1, qreal y1, qreal x2, qreal y2, const QString &label)
{
    // 绘制线段（绿色实线）
    QGraphicsLineItem *line = new QGraphicsLineItem(x1, y1, x2, y2);
    line->setPen(QPen(Qt::green, 2, Qt::SolidLine)); // 线宽2像素
    scene->addItem(line);

    // 计算标签位置（线段中点偏移）
    qreal midX = (x1 + x2)/2 + 10;  // 右偏移10像素
    qreal midY = (y1 + y2)/2 - 15;  // 上偏移15像素
}

double CoordinateSystem::calculateDistance(qreal x1, qreal y1, qreal x2, qreal y2) const
{
    qreal dx = x2 - x1;  // X轴坐标差
    qreal dy = y2 - y1;  // Y轴坐标差
    return sqrt(pow(dx, 2) + pow(dy, 2));  // 欧几里得距离公式
}

void CoordinateSystem::drawAxes() {
    // X轴（红色）
    QGraphicsLineItem *xAxis = new QGraphicsLineItem(-400, 0, 400, 0);
    xAxis->setPen(QPen(Qt::red, 2));
    scene->addItem(xAxis);

    // Y轴（蓝色）
    QGraphicsLineItem *yAxis = new QGraphicsLineItem(0, -300, 0, 300);
    yAxis->setPen(QPen(Qt::blue, 2));
    scene->addItem(yAxis);

    // 坐标标签
    QGraphicsTextItem *xLabel = scene->addText("X");
    xLabel->setPos(380, -20);  // 坐标轴末端偏移量
    QGraphicsTextItem *yLabel = scene->addText("Y");
    yLabel->setPos(20, -280);

    // 绘制X轴刻度
    for (int x = -400; x <= 400; x += 50) {
        QGraphicsLineItem *tick = new QGraphicsLineItem(x, -5, x, 5);
        tick->setPen(QPen(Qt::black, 1));
        scene->addItem(tick);

        QGraphicsTextItem *label = scene->addText(QString::number(x));
        label->setPos(x - 5, 10);
        label->setDefaultTextColor(Qt::black);
    }

    // 绘制Y轴刻度
    for (int y = -300; y <= 300; y += 50) {
        QGraphicsLineItem *tick = new QGraphicsLineItem(-5, y, 5, y);
        tick->setPen(QPen(Qt::black, 1));
        scene->addItem(tick);

        QGraphicsTextItem *label = scene->addText(QString::number(y));
        label->setPos(-20, y - 5);
        label->setDefaultTextColor(Qt::black);
    }
}

void CoordinateSystem::drawGrid() {
    QPen gridPen(QColor(200, 200, 200), 1, Qt::DotLine);  // 灰色虚线

    // 水平网格（Y轴方向）
    for (int y = -300; y <= 300; y += 50) {
        scene->addLine(-400, y, 400, y, gridPen);
    }

    // 垂直网格（X轴方向）
    for (int x = -400; x <= 400; x += 50) {
        scene->addLine(x, -300, x, 300, gridPen);
    }
}

void CoordinateSystem::wheelEvent(QWheelEvent *event)
{
    qDebug() << event->delta();
    if (event->delta() > 0) {
        // 滚动鼠标滚轮向右，放大
        double scaleFactor = 1.2;
        this->scale(scaleFactor, scaleFactor);
    } else {
        // 滚动鼠标滚轮向左，缩小
        double scaleFactor = 0.8;
        this->scale(scaleFactor, scaleFactor);
    }
}

void CoordinateSystem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 记录鼠标按下的位置
        lastMousePos = event->pos();
        dragging = true;
    }
    QGraphicsView::mousePressEvent(event);
}

void CoordinateSystem::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton))
    {
        // 计算鼠标移动的偏移量
        QPoint delta = event->pos() - lastMousePos;
        lastMousePos = event->pos();

        // 平移视图
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void CoordinateSystem::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 结束拖动
        dragging = false;
    }
    QGraphicsView::mouseReleaseEvent(event);
}
