// dataclass.cpp
#include "dataclass.h"
#include <QStringList>
#include <QDebug>

DataClass::DataClass()
{

}

DataClass::~DataClass()
{

}

bool DataClass::canPigeonsReachDestination(const single_RW& rw, const single_ZD& zd)
{
    double dx = rw.destinationCoordinate.x() - zd.releaseLocationCoordinate.x();
    double dy = rw.destinationCoordinate.y() - zd.releaseLocationCoordinate.y();
    double distance = std::sqrt(dx * dx + dy * dy);
    return distance <= rw.flightDistance;
}

void DataClass::genTestData()
{

    // 生成5个不同目的地坐标（C++98兼容方式）
    QList<QPointF> destinations;
    destinations.append(QPointF(116.4074, 39.9042));   // 北京
    destinations.append(QPointF(121.4737, 31.2304));   // 上海
    destinations.append(QPointF(113.2644, 23.1291));   // 广州
    destinations.append(QPointF(114.0579, 22.5431));   // 深圳
    destinations.append(QPointF(120.1551, 30.2741));   // 杭州

    // 1. 生成20个放飞任务（使用QStringLiteral处理中文字符）
    QStringList categories0;
    categories0.append("XinGe");
    categories0.append("SaiGe");
    categories0.append("JunYongGe");
    categories0.append("GuanShangGe");
    categories0.append("ShiYanGe");

    QStringList categories1;
    categories1.append("TypeA");
    categories1.append("TypeB");
    categories1.append("TypeC");
    categories1.append("TypeD");
    categories1.append("TypeE");

    for(int i = 0; i < 20; i++){
        DataClass::single_RW rw;
        rw.pigeonCategory0 = categories0[qrand() % 5];
        rw.pigeonCategory1 = categories1[qrand() % 5];
        rw.pigeonQuantity = qrand() % 3 + 1; // 1 - 3只
        rw.destinationCoordinate = destinations[qrand() % 5];
        rw.flightDistance = 3000 + qrand() % 200; // 生成100 - 300的飞行距离
        rw.rwbh = QString("rw%1").arg(i+1);
        rwList.append(rw);
    }

    // 2. 生成36辆货车（代码保持不变）
    for(int i = 0; i < 36; i++){
        DataClass::single_HC hc;

        // 显式指定引用类型
        DataClass::single_RW& randomRW = rwList[qrand() % 20]; // 关键修改

        hc.transportedPigeonTypes0 = randomRW.pigeonCategory0;
        hc.transportedPigeonTypes1 = randomRW.pigeonCategory1;
        hc.transportedPigeonQuantity = 3;
        hc.truckStartingPosition = QPointF(115.0 + (qrand() % 50) / 100.0, 35.0 + (qrand() % 50) / 100.0);
        hc.hcbh = QString("dy%1").arg(i+1);
        hcList.append(hc);
    }

    // 3. 生成1500个放飞地点（代码保持不变）
    QStringList regions;
    regions.append("Reg1");
    regions.append("Reg2");
    regions.append("Reg3");

    for(int i = 0; i < 1500; i++){
        DataClass::single_ZD zd;
        zd.releaseLocationRegion = regions[i % 3];
        if(i % 20 == 0){
            zd.releaseLocationType = "Z";
            zd.simultaneousReleaseCount = 1;
        } else {
            zd.releaseLocationType = "L";
            zd.simultaneousReleaseCount = 50 + qrand() % 21;
        }
        zd.releaseLocationCoordinate = QPointF(110.0 - (qrand() % 800) / 10.0, 20.0 - (qrand() % 500) / 10.0);
        zd.zdid = QString("zd%1").arg(i+1);
        zdList.append(zd);
    }

    // 检查鸽子是否能够飞到目的地
//    for (QList<single_RW>::const_iterator rwIt = data.rwList.begin(); rwIt != data.rwList.end(); ++rwIt) {
//        const single_RW& rw = *rwIt;
//        for (QList<single_ZD>::const_iterator zdIt = data.zdList.begin(); zdIt != data.zdList.end(); ++zdIt) {
//            const single_ZD& zd = *zdIt;
//            if (data.canPigeonsReachDestination(rw, zd)) {
//                qDebug() << "Pigeons of type " << rw.pigeonCategory0 << " - " << rw.pigeonCategory1 << " can reach destination from release location.";
//            } else {
//                qDebug() << "Pigeons of type " << rw.pigeonCategory0 << " - " << rw.pigeonCategory1 << " cannot reach destination from release location.";
//            }
//        }
//    }

    qDebug() << hcList.count();
}
