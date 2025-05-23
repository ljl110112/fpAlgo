// dataclass.h
#ifndef DATACLASS_H
#define DATACLASS_H
#include <QList>
#include <QString>
#include <QPointF>
#include <cmath>

class DataClass
{
public:
    DataClass();
    ~DataClass();

    void genTestData();


    //数据定义
    /*用货车运输不同类型的鸽子到放飞地点，
     * 放飞地点能够同时放飞的鸽子数量有限制，
     * 到达放飞地点后自动放出鸽子，
     * 鸽子自动飞向指定目的地，
     * 鸽子分为不同大类和小类，
     * 每个目的地的鸽子需要的数量不一样，
     * 每种鸽子的飞行距离也不一样。*/

    // 放飞任务相关信息
    struct single_RW{
        QString rwbh;
        QString pigeonCategory0; //鸽子大类
        QString pigeonCategory1; //鸽子小类
        int pigeonQuantity; //鸽子数量
        QPointF destinationCoordinate;  //目的地坐标
        double flightDistance; // 鸽子飞行距离
    };

    // 货车相关信息
    struct single_HC{
        QString hcbh;
        QString transportedPigeonTypes0;//鸽子大类
        QString transportedPigeonTypes1;//鸽子小类
        int transportedPigeonQuantity; //鸽子数量
        QPointF truckStartingPosition; //货车当前位置
    };

    // 放飞地点相关信息
    struct single_ZD{
        QString zdid;
        QString releaseLocationRegion;  //所属地区
        QString releaseLocationType;    //放飞地点类型
        int simultaneousReleaseCount;   //容量：同时放飞数量
        QPointF releaseLocationCoordinate;//放飞地点坐标
    };
bool canPigeonsReachDestination(const single_RW& rw, const single_ZD& zd);
    QList<single_RW> rwList;
    QList<single_HC> hcList;
    QList<single_ZD> zdList;
};

#endif // DATACLASS_H
