// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataclass.h"
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_plotWidget = new PlotWidget(this);
    setCentralWidget(m_plotWidget);

    DataClass data;
    data.genTestData();
    m_plotWidget->setData(data);
}

MainWindow::~MainWindow()
{
    delete ui;
}
