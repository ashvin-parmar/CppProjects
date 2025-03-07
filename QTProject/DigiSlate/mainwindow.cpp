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
#include<QJsonDocument>
#include<QColorDialog>

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
    this->model=new Model(this->ui->board);

    this->model->setColor(Qt::black);
    this->model->setPenWidth(1);
    this->model->setListWidget(this->ui->listWidget);

    this->model->setVisible(true);
    this->model->setGeometry(0,0,1144,700);
    this->model->setCordinates(this->ui->coordinatesModel);
//    QRadioButton *radioButton=new QRadioButton(this->ui->boardWindow);


    connect(this->ui->closeApp, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->model->setFlag(NOFLAG);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->ui->coordinatesScreen->setText(QString("x=%1,y=%2").arg(event->globalX()).arg(event->globalY()));
}

void MainWindow::on_blackColor_clicked()
{
    this->model->setColor(Qt::black);
}


void MainWindow::on_redColor_clicked()
{
    this->model->setColor(Qt::red);
}

void MainWindow::on_greenColor_clicked()
{
    this->model->setColor(Qt::green);
}

void MainWindow::on_blueColor_clicked()
{
    this->model->setColor(Qt::blue);
}

void MainWindow::on_mixColor_clicked()
{
//    this->model->setColor(Qt::black);
    QColor selectedColor=QColorDialog::getColor(Qt::black,this,"Select Color");
    if(selectedColor.isValid())
    {
        this->model->setColor(selectedColor);
    }
    else
    {
        this->model->setColor(Qt::black);
    }
}

void MainWindow::on_penWidthSlider_valueChanged(int value)
{
   this->model->setPenWidth(value);
}
void MainWindow::on_pickShape_clicked()
{
    this->model->setFlag(PICK);
}
void MainWindow::on_freeHandDraw_clicked()
{
    this->model->setFlag(FREEHAND);
}
void MainWindow::on_lineDraw_clicked()
{
    this->model->setFlag(LINE);
}
void MainWindow::on_rectangleDraw_clicked()
{
    this->model->setFlag(RECTANGLE);
}
void MainWindow::on_ellipseDraw_clicked()
{
    this->model->setFlag(ELLIPSE);
}

void MainWindow::on_circleDraw_clicked()
{
    this->model->setFlag(CIRCLE);
}

void MainWindow::on_imageDraw_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,tr("Open Image"),QDir::homePath(),"Images (*.jpg *.png)");
    if(filePath.compare("")==1)
    {
        QPixmap pixmap(filePath);
        if(pixmap.isNull()==false)
        {
        this->model->setFlag(IMAGE);
        this->model->setFilePath(filePath);
        return;
        }
    }
    QMessageBox::warning(this,"File Error","File not select");
}

void MainWindow::on_addNewPage_clicked()
{
//    QRadioButton *radioButton=new QRadioButton(this->ui->boardWindow);

}

void MainWindow::on_saveFile_clicked()
{
QString saveFile=QFileDialog::getSaveFileName(this,tr("Save File"),QDir::homePath(),tr("Files (*.slate)"));
if(saveFile.compare("")==1)
{
    if(saveFile.endsWith(".slate")==false)
    {
        saveFile+=".slate";
    }
    QFile file(saveFile);
    if(file.exists()==true)
    {
        QMessageBox::warning(this,"File Error","File already exist");
        return;
    }
    cout<<(saveFile.toStdString())<<endl;
    QJsonObject json=this->model->toJson();
    QJsonDocument *docs=new QJsonDocument();
    docs->setObject(json);
    QByteArray byteArray=docs->toJson();
    if(!file.open(QIODevice::WriteOnly | QIODevice::ReadOnly))
    {
//        qWaring("Couldn't open file");
        return ;
    }
    file.write(byteArray);
    file.close();
    delete docs;
}
}

void MainWindow::on_openFile_clicked()
{
    QString openFile=QFileDialog::getOpenFileName(this,tr("Open File"),QDir::homePath(),tr("Files (*.slate)"));
    if(openFile.compare("")==1)
    {
        QFile file(openFile);
        if(file.exists()==false)
        {
            QMessageBox::warning(this,"File Error","File not exist");
            return;
        }
        cout<<(openFile.toStdString())<<endl;
        if(!file.open(QIODevice::WriteOnly | QIODevice::ReadOnly))
        {
    //        qWaring("Couldn't open file");
            return ;
        }
        QJsonDocument docs(QJsonDocument::fromJson(file.readAll()));
        if(docs.isNull()) printf("Null");
        QJsonObject jsonObject=docs.object();
        if(jsonObject.isEmpty()) printf("Empty");
        Model *newModel=Model::fromJson(jsonObject,this->ui->board);
        if(newModel==nullptr) printf("Null model");
        delete this->model;
        this->model=newModel;
//        this->model->setParent(this->ui->board);
        this->model->setGeometry(0,0,1144,700);

        this->model->setColor(Qt::black);
        this->model->setPenWidth(1);
        this->model->setListWidget(this->ui->listWidget);

        this->model->setVisible(true);
        this->model->setCordinates(this->ui->coordinatesModel);
        this->model->update();

    }
}

void MainWindow::on_drag_clicked()
{
    this->model->setDrag(ENABLE);
    this->model->setFlag(PICK);
//    int flag=this->model->getFlag();
//    if(!(flag==PICK || flag==GROUPPICK)) this->model->setFlag(NOFLAG);

}

void MainWindow::on_group_shape_clicked()
{
    this->model->setFlag(GROUPPICK);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key::Key_Control) this->model->setFlag(GROUPPICK);
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    //if(event->key()==Qt::Key::Key_Control) this->model->setFlag(UNGROUPPICK);
}
