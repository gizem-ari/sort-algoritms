//21100011007 Fatma Gizem ARI
//hocam programın tum kısımları çalışıyor ama bazen üst üste deneme yapınca kapanıyor.
//tekrar açınca diğerleri de yapılıyor. benim pcden de kaynaklı olabilir emin değilim
//hocam bir de eğer kodlar qt programı olduğu için çalışmazsa lütfen haber edin yanınıza gelip gösteririm.
// ödev puanına çok ihtiyacım var



#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
