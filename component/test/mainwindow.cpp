#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib_handle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lib_handle lib("chart_2d");
    abstract_component* p = lib.create();
    ui->horizontalLayout->addWidget(p->plot());
    ui->verticalLayout->addWidget(p->property());
    QString as = p->json_property();

    QVector<double> x, y;
    x << 1 << 2 << 3;
    y << 20 << 30 << 50;
    p->set_data("www", x,y);

    y.clear();
    y << 2 << 4 << 2;
    p->set_data("ccc", x,y);

    y.clear();
    y << 8 << 6 << 4;
    p->set_data("aaaa", x,y);
}

MainWindow::~MainWindow()
{
    delete ui;
}

