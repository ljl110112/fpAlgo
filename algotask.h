#ifndef ALGOTASK_H
#define ALGOTASK_H
#include <QRunnable>

class AlgoTask : public QRunnable
{
public:
    AlgoTask();
    ~AlgoTask();
    int iMax=500;
    int jMax=500;
    int k=0;
    void setI_J(int i, int j);
    void run();
};

#endif // ALGOTASK_H
