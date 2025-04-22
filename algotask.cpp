#include "algotask.h"
#include <QDebug>
#include <QThread>

AlgoTask::AlgoTask()
{

}

AlgoTask::~AlgoTask()
{

}

void AlgoTask::setI_J(int i, int j)
{
    iMax = i;
    jMax = j;
}

void AlgoTask::run()
{
    for(int i=0;i<iMax;i++){
        for(int j=0;j<jMax;j++){
//            qDebug() << QThread::currentThreadId() << QString("  =>  %1-%2").arg(i).arg(j);
            k++;
        }
    }
    qDebug() << QThread::currentThreadId() <<  QString("  =>  %1").arg(k);
}

