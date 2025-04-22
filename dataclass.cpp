#include "dataclass.h"
#include <QStringList>
#include <QDebug>

DataClass::DataClass()
{

}

DataClass::~DataClass()
{

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
        single_RW rw;
        rw.pigeonCategory0 = categories0[qrand() % 5];
        rw.pigeonCategory1 = categories1[qrand() % 5];
        rw.pigeonQuantity = qrand() % 3 + 1; // 1 - 3只
        rw.destinationCoordinate = destinations[qrand() % 5];
        rwList.append(rw);
    }

    // 2. 生成36辆货车
    for(int i = 0; i < 36; i++){
        single_HC hc;
        single_RW& randomRW = rwList[qrand() % 20]; // 关键修改
        hc.hcId = QString("dy%1").arg(i+1);
        hc.transportedPigeonTypes0 = randomRW.pigeonCategory0;
        hc.transportedPigeonTypes1 = randomRW.pigeonCategory1;
        hc.transportedPigeonQuantity = 3;
        hc.truckStartingPosition = QPointF(115.0 + (qrand() % 50) / 100.0, 35.0 + (qrand() % 50) / 100.0);
        hc.isAssigned = false; // 初始化为未分配任务
        hcList.append(hc);
    }

    // 3. 生成1500个放飞地点
    QStringList regions;
    regions.append("Reg1");
    regions.append("Reg2");
    regions.append("Reg3");

    for(int i = 0; i < 1500; i++){
        single_ZD zd;
        zd.releaseLocationRegion = regions[i % 3];
        if(i % 20 == 0){
            zd.releaseLocationType = "Z";
            zd.simultaneousReleaseCount = 1;
        } else {
            zd.releaseLocationType = "L";
            zd.simultaneousReleaseCount = 50 + qrand() % 21;
        }
        zd.zdBh = QString("zd%1").arg(i+1);
        zd.releaseLocationCoordinate = QPointF(110.0 + (qrand() % 800) / 100.0, 20.0 + (qrand() % 500) / 100.0);
        zd.currentReleaseCount = 0; // 初始化为0
        zdList.append(zd);
    }
    qDebug() << hcList.count();
}

void DataClass::runAlgorithm()
{
    // 简单的调度算法：遍历货车，为每辆货车找到合适的放飞地点
    for (QList<single_HC>::iterator hcIt = hcList.begin(); hcIt != hcList.end(); ++hcIt) {
        single_HC& hc = *hcIt;
        if (hc.isAssigned) continue; // 如果货车已分配任务，跳过
        for (QList<single_ZD>::iterator zdIt = zdList.begin(); zdIt != zdList.end(); ++zdIt) {
            single_ZD& zd = *zdIt;
            if (zd.currentReleaseCount + hc.transportedPigeonQuantity <= zd.simultaneousReleaseCount) {
                // 找到合适的放飞地点，更新相关信息
                zd.currentReleaseCount += hc.transportedPigeonQuantity;
                hc.isAssigned = true;
                qDebug() << QString("%1 assigned to release location:%2").arg(hc.hcId).arg(zd.zdBh) << zd.releaseLocationCoordinate;
                break;
            }
        }
    }
}
