#include "mainwindow.h"
#include <QApplication>
#include "algotask.h"
#include <QThreadPool>
#include "dataclass.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QThreadPool *threadPool = QThreadPool::globalInstance();

//    // 设置线程池的最大线程数量
//    int maxThreadCount = 3; // 这里设置为3个线程
//    threadPool->setMaxThreadCount(maxThreadCount);

//    // 创建并启动任务
//    for (int i = 0; i < 10; ++i) {
//        AlgoTask *task = new AlgoTask();
//        task->setI_J((i + 1) * 100, (i + 2) * 500);
//        // 将任务加入线程池
//        threadPool->start(task);
//    }

//    // 等待所有任务完成
//    threadPool->waitForDone();

//    // 生成测试数据并运行算法
//    DataClass data;
//    data.genTestData();

    return a.exec();
}
