#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QWidget>
#include<QFontDatabase>
#include<QBrush>
#include<QGridLayout>
#include<QFileDialog>
#include<QMessageBox>
#include<QGuiApplication>
#include<QScreen>
#include<QDebug>
#include<QStringListModel>
#include<QListView>
#include<QListWidget>
#include<QTreeView>
#include<QStyledItemDelegate>
#include<QAbstractItemView>
#include<QTreeWidgetItem>

#include<drawing.h>
#include<model.h>
#include<shapes_header/arcshape.h>
#include<shapes_header/lineshape.h>
#include<shapes_header/textshape.h>
#include<shapes_header/pointshape.h>
#include<shapes_header/polylineshape.h>
#include<shapes_header/polygonshape.h>
#include<shapes_header/ellipseshape.h>
#include<shapes_header/rectangleshape.h>
#include<shapes_header/roundedrectangleshape.h>
#include<shapes_header/pixmapshape.h>
#include<shapes_header/freehandshape.h>

#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    showFullScreen();
    ui->setupUi(this);
    PhaseIII();
}

void MainWindow::PhaseIII()
{
    this->ui->phaseIII->setVisible(true);
    this->ui->phaseIII->setGeometry(QRect(0,0,1369,900));
    this->ui->listView->setMaximumSize(131,371);
    this->model=new Model(this->ui->board);
    this->model->setVisible(true);
    this->model->setGeometry(0,0,1144,700);


    connect(this->ui->closeApp, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_freeHandDraw_clicked()
{
    FreeHandShape *freeHandShape=new FreeHandShape();
    this->model->addShape(freeHandShape);
}
