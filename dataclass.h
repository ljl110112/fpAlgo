#ifndef DATACLASS_H
#define DATACLASS_H
#include <QList>
#include <QString>
#include <QPointF>

class DataClass
{
public:
    DataClass();
    ~DataClass();

    void genTestData();
    void runAlgorithm(); // 新增函数，用于运行调度算法

    // 数据定义
    // 放飞任务相关信息
    struct single_RW{
        QString pigeonCategory0; // 鸽子大类
        QString pigeonCategory1; // 鸽子小类
        int distanceMax;//鸽子最远飞行距离
        int pigeonQuantity; // 鸽子数量
        QPointF destinationCoordinate;  // 目的地坐标
    };

    // 货车相关信息
    struct single_HC{
        QString hcId;
        QString transportedPigeonTypes0; // 鸽子大类
        QString transportedPigeonTypes1; // 鸽子小类
        int transportedPigeonQuantity; // 鸽子数量
        QPointF truckStartingPosition; // 货车当前位置
        bool isAssigned; // 新增标志，用于标记货车是否已分配任务
    };

    // 放飞地点相关信息
    struct single_ZD{
        QString zdBh;
        QString releaseLocationRegion;  // 所属地区
        QString releaseLocationType;    // 放飞地点类型
        int simultaneousReleaseCount;   // 容量：同时放飞数量
        QPointF releaseLocationCoordinate; // 放飞地点坐标
        int currentReleaseCount; // 新增变量，记录当前已安排放飞的鸽子数量
    };

    QList<single_RW> rwList;
    QList<single_HC> hcList;
    QList<single_ZD> zdList;
};

#endif // DATACLASS_H
