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
#include<drawingmanager.h>
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
//    showMaximized();
    ui->setupUi(this);
//    this->setGeometry(QRect(0,0,1369,900));
    PhaseII();
    PhaseIII();
}
//This Feature is not usefull for our application

//void MainWindow::mouseMoveEvent(QMouseEvent *event) {
//    if (event->pos().y() < 40 && event->pos().x() > width()/2 - 50 && event->pos().x() < width()/2 + 100) {
//        exitFullScreenButton->show();
//    } else {
//        exitFullScreenButton->hide();
//    }
//}
void MainWindow::PhaseIII()
{
//    this->drawingManager->setVisible(false);
//    this->ui->homeFrame->setVisible(false);
//    this->ui->homeUserFrame->setVisible(false);
//    this->ui->closeButton->setVisible(false);
    this->ui->phaseII->setVisible(false);
    this->ui->menubar->setVisible(false);

    //Because mixing two different applications
    this->ui->phaseIII->setVisible(true);
    this->ui->phaseIII->setGeometry(QRect(0,0,1369,900));
    this->ui->listView->setMaximumSize(131,371);
    this->model=DrawingManager::getInstance(this->ui->board);



    connect(this->ui->closeApp, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

void MainWindow::PhaseII()
{
    this->ui->phaseIII->setVisible(false);

    this->ui->phaseII->setGeometry(QRect(0,0,1369,900));
    QStringList colorList=QColor::colorNames();
    QStringList fontFamilies=QFontDatabase().families();
    //Style Sheet Strings
    QString spinBoxUpDownButton=" QSpinBox::up-button { color: lightgray; width: 20px; } QSpinBox::down-button { color: lightgray; width: 20px; }";
    QString drawingStyleSheet="background-color: white; border: 2px solid black; border-radius: 5px";
    QString menuFrameStyleSheet="border: 2px solid black; border-radius: 5px";
    QString comboBoxStyleSheet="QComboBox { border: 1px solid gray; border-radius: 3px; padding: 2px 5px; background: white; color: black; } QComboBox QAbstractItemView {padding: 2px;  selection-background-color: lightblue; selection-color: white; } ";
    QString transparentButtonStyleSheet="background-color: rgba(0, 0, 0, 0); color: white; border: none;";
    QString shapeMenuButtonStyleSheet="background: white; border: 0px solid gray; border-radius: 5px;";
    QString pushButtonStyleSheet="background: white; border: 1px solid black; border-radius: 5px;";
    QString textLineStyleSheet="background: white; border: 1px solid black; border-radius: 5px;";
    QString spinBoxStyleSheet="QSpinBox {background: white; border: 1px solid lightgray; border-radius: 5px;}"+spinBoxUpDownButton;
    QString frameStyleSheet="QFrame {background-color: #efefef; border: 2px solid lightgray; border-radius: 5px;} QLabel {background: transparent; color: black; font: unset; border: none;} QTableWidget { background-color: white; border: 2px solid lightgray; gridline-color: lightgray; } QHeaderView::section { background-color: white; border: 0px solid lightgray; padding: 4px;} QTableWidget::item:selected { background: lightblue; color: white;}";
    QString titleLabelStyleSheet="border: 1px solid black; border-radius: 5px;";
    QString tableWidgetStyleSheet="QTableWidget { background-color: white; border: 2px solid lightgray; gridline-color: lightgray; } QHeaderView::section { background-color: white; border: 0px solid lightgray; padding: 4px;} QTableWidget::item:selected { background: lightblue; color: white;} QLabel {background: transparent; color: black; font: unset; border: none;}";

    brushStyleInitialization();
    frameSetTabOrderInitialization();
//    QSize screenSize = QGuiApplication::primaryScreen()->availableGeometry().size();
//    qDebug() << "Available Screen Size: " << screenSize;  // Debug screen resolution

//    QSize fullSize = QGuiApplication::primaryScreen()->geometry().size();
//       qDebug() << "Full Screen Size: " << fullSize;

    this->drawingManager=DrawingManager::getInstance(this->ui->drawing);
    this->drawingManager->setGeometry(10,10,1189,699);
    this->ui->drawing->setStyleSheet(drawingStyleSheet);
    this->ui->menuFrame->setStyleSheet(menuFrameStyleSheet);
    this->drawingManager->setVisible(true);
    this->ui->drawing->setVisible(false);
    this->ui->menuFrame->setVisible(false);
//    QGridLayout *layout=new QGridLayout();
//    layout->addWidget(this->home,0,0);
//    this->home->setLayout(layout);
    this->ui->homeFrame->setVisible(true);
    this->ui->homeFrame->setGeometry(0,0,width(),height());
    this->ui->homeUserFrame->setVisible(true);
    this->ui->closeButton->raise();
    this->ui->homeUserFrame->raise();
    this->ui->closeButton->setVisible(true);
//    printf("%d %d\n",width(),height());
    this->ui->homeUserFrame->setGeometry(width()/2-300,height()/2-300,600,400);
    this->ui->homeUserFrame->setStyleSheet("border: 0px;");
    //this->ui->loginButton->setGeometry(680,400,50,15);
    this->ui->loginButton->setStyleSheet("QPushButton { color: black; background-color: white; border: 1px solid black; padding: 5px; } QPushButton:hover { background-color: black; color: white;}");
    this->ui->username->setPlaceholderText("Enter username...");
    this->ui->username->setStyleSheet("background: white; border: 1px solid black; padding: 2px;");
    this->ui->username->setFocus(Qt::FocusReason::TabFocusReason);
    this->ui->username->setTabOrder(this->ui->loginButton,this->ui->loginButton);
    this->ui->loginButton->setTabOrder(this->ui->username,this->ui->username);
    this->ui->homeMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->frameOpened=false;
    this->ui->menuLabel->setStyleSheet(titleLabelStyleSheet);

    this->ui->usernameLabel->setVisible(false);
    this->ui->usernameLabel->setAlignment(Qt::AlignLeft);
    this->ui->userIcon->setVisible(false);

    //List and Tree View initializations
    this->ui->listWidget->setStyleSheet("color: black; background: white; border: 1px solid black; padding 2px; ");
    this->ui->listWidget->setVisible(false);
    this->ui->treeWidget->setVisible(false);
    this->ui->listWidgetClose->setVisible(false);
    this->ui->treeWidgetClose->setVisible(false);
    this->ui->treeWidget->raise();
    this->ui->listWidget->raise();
    this->ui->treeWidget->setHeaderLabel("Shapes");

    this->ui->listWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    this->ui->listWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    this->ui->treeWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    this->ui->treeWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

    this->ui->listWidgetClose->raise();
    this->ui->treeWidgetClose->raise();
    this->ui->listWidgetClose->setStyleSheet(transparentButtonStyleSheet);
    this->ui->treeWidgetClose->setStyleSheet(transparentButtonStyleSheet);
    this->ui->actionList_View->setEnabled(false);
    this->ui->actionTree_View->setEnabled(false);

    //line frame intial
    this->ui->lineFrame->raise();
    this->ui->lineFrame->setVisible(false);
    this->ui->lineFrame->setGeometry(670,60,520,420);
    this->ui->x1->setRange(10,1190);
    this->ui->x2->setRange(10,1190);
    this->ui->y1->setRange(10,700);
    this->ui->y2->setRange(10,700);
    this->ui->x1->setValue(100);
    this->ui->x2->setValue(200);
    this->ui->y1->setValue(100);
    this->ui->y2->setValue(200);
    this->ui->penWidth->setValue(2);    //intial value
    this->ui->colorLine->addItems(colorList);
    this->ui->colorLine->setCurrentIndex(7);
    this->ui->x1->setStyleSheet(spinBoxStyleSheet);
    this->ui->x2->setStyleSheet(spinBoxStyleSheet);
    this->ui->y1->setStyleSheet(spinBoxStyleSheet);
    this->ui->y2->setStyleSheet(spinBoxStyleSheet);
    this->ui->penWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->lineMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->lineDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->lineFrame->setStyleSheet(frameStyleSheet);
    this->ui->colorLine->setStyleSheet(comboBoxStyleSheet);
    this->ui->drawLine->setStyleSheet(pushButtonStyleSheet);
    this->ui->cancelLine->setStyleSheet(transparentButtonStyleSheet);

    //text frame intial
    this->ui->textFrame->raise();
    this->ui->textFrame->setVisible(false);
    this->ui->textFrame->setGeometry(670,60,520,420);
    this->ui->textPenWidth->setValue(2);    //intial value
    this->ui->textX->setRange(10,1190);
    this->ui->textY->setRange(10,700);
    this->ui->textX->setValue(100);
    this->ui->textY->setValue(100);
    this->ui->textFont->addItems(fontFamilies);
    this->ui->textFont->setCurrentIndex(1);
    this->ui->colorText->addItems(colorList);
    this->ui->colorText->setCurrentIndex(7);
    this->ui->textPointSize->setValue(10);
    this->ui->text->setStyleSheet(textLineStyleSheet);
    this->ui->textX->setStyleSheet(spinBoxStyleSheet);
    this->ui->textY->setStyleSheet(spinBoxStyleSheet);
    this->ui->textPenWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->textPointSize->setStyleSheet(spinBoxStyleSheet);
    this->ui->drawText->setStyleSheet(pushButtonStyleSheet);
    this->ui->textMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->textDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->textFrame->setStyleSheet(frameStyleSheet);
    this->ui->textFont->setStyleSheet(comboBoxStyleSheet);
    this->ui->colorText->setStyleSheet(comboBoxStyleSheet);
    this->ui->cancelText->setStyleSheet(transparentButtonStyleSheet);

    //point initial
    this->ui->pointFrame->raise();
    this->ui->pointFrame->setVisible(false);
    this->ui->pointFrame->setGeometry(670,60,520,420);
    this->ui->pointX->setRange(10,1190);
    this->ui->pointY->setRange(10,700);
    this->ui->pointX->setValue(100);
    this->ui->pointY->setValue(100);
    this->ui->pointPenWidth->setValue(2);    //intial value
    this->ui->colorPoint->addItems(colorList);
    this->ui->colorPoint->setCurrentIndex(7);
    this->ui->pointX->setStyleSheet(spinBoxStyleSheet);
    this->ui->pointY->setStyleSheet(spinBoxStyleSheet);
    this->ui->pointPenWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->drawPoint->setStyleSheet(pushButtonStyleSheet);
    this->ui->pointMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->pointFrame->setStyleSheet(frameStyleSheet);
    this->ui->pointDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->colorPoint->setStyleSheet(comboBoxStyleSheet);
    this->ui->cancelPoint->setStyleSheet(transparentButtonStyleSheet);

    //polyline initial
    this->ui->polylineFrame->raise();
    this->ui->polylineFrame->setVisible(false);
    this->ui->polylineFrame->setGeometry(670,60,520,480);
    this->ui->polylineX->setRange(10,1190);
    this->ui->polylineY->setRange(10,700);
    this->ui->polylineX->setValue(100);
    this->ui->polylineY->setValue(100);
    this->ui->polylinePenWidth->setValue(2);    //intial value
    this->ui->colorPolyline->addItems(colorList);
    this->ui->colorPolyline->setCurrentIndex(7);
    this->ui->brushPolyline->addItems(colorList);
    this->ui->brushPolyline->setCurrentIndex(7);
    this->ui->brushStylePolyline->setCurrentIndex(0);
    this->ui->polylinePointTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->polylinePointTable->setRowCount(2);
    this->ui->polylinePointTable->setColumnCount(0);
    this->ui->polylinePointTable->horizontalHeader()->hide();
    this->ui->polylinePointTable->setVerticalHeaderLabels({"X", "Y"});
    this->ui->polylinePointTable->setRowHeight(0,30);
    this->ui->polylinePointTable->setRowHeight(1,30);
    this->ui->polylineX->setStyleSheet(spinBoxStyleSheet);
    this->ui->polylineY->setStyleSheet(spinBoxStyleSheet);
    this->ui->polylinePointTable->setStyleSheet(tableWidgetStyleSheet);
    this->ui->polylinePenWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->drawPolyline->setStyleSheet(pushButtonStyleSheet);
    this->ui->addPointPolyline->setStyleSheet(pushButtonStyleSheet);
    this->ui->polylineMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->polylineDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->polylineFrame->setStyleSheet(frameStyleSheet);
    this->ui->colorPolyline->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushPolyline->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushStylePolyline->setStyleSheet(comboBoxStyleSheet);
    this->ui->cancelPolyline->setStyleSheet(transparentButtonStyleSheet);

    //polygone initial
    this->ui->polygonFrame->raise();
    this->ui->polygonFrame->setVisible(false);
    this->ui->polygonFrame->setGeometry(670,80,520,480);
    this->ui->polygonX->setRange(10,1190);
    this->ui->polygonY->setRange(10,700);
    this->ui->polygonX->setValue(100);
    this->ui->polygonY->setValue(100);
    this->ui->polygonPenWidth->setValue(2);    //intial value
    this->ui->colorPolygon->addItems(colorList);
    this->ui->colorPolygon->setCurrentIndex(7);
    this->ui->brushPolygon->addItems(colorList);
    this->ui->brushPolygon->setCurrentIndex(7);
    this->ui->brushStylePolygon->setCurrentIndex(4);
    this->ui->polygonPointTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->polygonPointTable->setRowCount(2);
    this->ui->polygonPointTable->setColumnCount(0);
    this->ui->polygonPointTable->horizontalHeader()->hide();
    this->ui->polygonPointTable->setVerticalHeaderLabels({"X", "Y"});
    this->ui->polygonPointTable->setRowHeight(0,30);
    this->ui->polygonPointTable->setRowHeight(1,30);
    this->ui->polygonX->setStyleSheet(spinBoxStyleSheet);
    this->ui->polygonY->setStyleSheet(spinBoxStyleSheet);
    this->ui->polygonPointTable->setStyleSheet(tableWidgetStyleSheet);
    this->ui->polygonPenWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->drawPolygon->setStyleSheet(pushButtonStyleSheet);
    this->ui->addPointPolygon->setStyleSheet(pushButtonStyleSheet);
    this->ui->polygonMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->polygonDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->polygonFrame->setStyleSheet(frameStyleSheet);
    this->ui->colorPolygon->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushPolygon->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushStylePolygon->setStyleSheet(comboBoxStyleSheet);
    this->ui->cancelPolygon->setStyleSheet(transparentButtonStyleSheet);

    //arc initial
    this->ui->arcFrame->raise();
    this->ui->arcFrame->setVisible(false);
    this->ui->arcFrame->setGeometry(670,80,520,500);
    this->ui->arcX->setRange(10,1190);
    this->ui->arcY->setRange(10,700);
    this->ui->arcWidth->setRange(0,1000);
    this->ui->arcHeight->setRange(0,500);
    this->ui->arcStartingAngle->setRange(0,360);
    this->ui->arcSpanAngle->setRange(0,360);
    this->ui->arcX->setValue(100);
    this->ui->arcY->setValue(100);
    this->ui->arcWidth->setValue(100);
    this->ui->arcHeight->setValue(100);
    this->ui->arcStartingAngle->setValue(30);
    this->ui->arcSpanAngle->setValue(30);
    this->ui->arcPenWidth->setValue(2);    //intial value
    this->ui->colorArc->addItems(colorList);
    this->ui->colorArc->setCurrentIndex(7);
    this->ui->arcFrame->setStyleSheet(frameStyleSheet);
    this->ui->arcX->setStyleSheet(spinBoxStyleSheet);
    this->ui->arcY->setStyleSheet(spinBoxStyleSheet);
    this->ui->arcWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->arcHeight->setStyleSheet(spinBoxStyleSheet);
    this->ui->arcStartingAngle->setStyleSheet(spinBoxStyleSheet);
    this->ui->arcSpanAngle->setStyleSheet(spinBoxStyleSheet);
    this->ui->arcPenWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->drawArc->setStyleSheet(pushButtonStyleSheet);
    this->ui->arcMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->arcDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->colorArc->setStyleSheet(comboBoxStyleSheet);
    this->ui->cancelArc->setStyleSheet(transparentButtonStyleSheet);

    //ellipse intial
    this->ui->ellipseFrame->raise();
    this->ui->ellipseFrame->setVisible(false);
    this->ui->ellipseCenter->setVisible(false);
    this->ui->ellipseFrame->setGeometry(670,80,520,500);
    this->ui->ellipseX->setRange(10,1190);
    this->ui->ellipseY->setRange(10,700);
    this->ui->ellipseVR->setRange(0,1000);
    this->ui->ellipseHR->setRange(0,500);
    this->ui->ellipseX->setValue(100);
    this->ui->ellipseY->setValue(100);
    this->ui->ellipseVR->setValue(100);
    this->ui->ellipseHR->setValue(100);
    this->ui->ellipsePenWidth->setValue(2);
    this->ui->colorEllipse->addItems(colorList);
    this->ui->colorEllipse->setCurrentIndex(7);
    this->ui->brushEllipse->addItems(colorList);
    this->ui->brushEllipse->setCurrentIndex(7);
    this->ui->brushStyleEllipse->setCurrentIndex(0);
    this->ui->ellipseFrame->setStyleSheet(frameStyleSheet);
    this->ui->ellipseX->setStyleSheet(spinBoxStyleSheet);
    this->ui->ellipseY->setStyleSheet(spinBoxStyleSheet);
    this->ui->ellipseVR->setStyleSheet(spinBoxStyleSheet);
    this->ui->ellipseHR->setStyleSheet(spinBoxStyleSheet);
    this->ui->ellipsePenWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->drawEllipse->setStyleSheet(pushButtonStyleSheet);
    this->ui->ellipseMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->ellipseDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->colorEllipse->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushEllipse->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushStyleEllipse->setStyleSheet(comboBoxStyleSheet);
    this->ui->cancelEllipse->setStyleSheet(transparentButtonStyleSheet);

    //circle initial

    //rectangle initial
    this->ui->rectangleFrame->raise();
    this->ui->rectangleFrame->setVisible(false);
    this->ui->rectangleFrame->setGeometry(670,80,520,500);
    this->ui->rectangleX->setRange(10,1190);
    this->ui->rectangleY->setRange(10,700);
    this->ui->rectangleWidth->setRange(0,1000);
    this->ui->rectangleHeight->setRange(0,500);
    this->ui->rectanglePenWidth->setRange(0,40);
    this->ui->colorRectangle->addItems(colorList);
    this->ui->brushRectangle->addItems(colorList);

    this->ui->rectangleX->setValue(100);
    this->ui->rectangleY->setValue(100);
    this->ui->rectangleWidth->setValue(100);
    this->ui->rectangleHeight->setValue(100);
    this->ui->rectanglePenWidth->setValue(2);
    this->ui->colorRectangle->setCurrentIndex(7);
    this->ui->brushRectangle->setCurrentIndex(7);
    this->ui->brushStyleRectangle->setCurrentIndex(0);

    this->ui->rectangleFrame->setStyleSheet(frameStyleSheet);
    this->ui->rectangleX->setStyleSheet(spinBoxStyleSheet);
    this->ui->rectangleY->setStyleSheet(spinBoxStyleSheet);
    this->ui->rectangleWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->rectangleHeight->setStyleSheet(spinBoxStyleSheet);
    this->ui->rectanglePenWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->drawRectangle->setStyleSheet(pushButtonStyleSheet);
    this->ui->rectangleMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->rectangleDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->colorRectangle->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushRectangle->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushStyleRectangle->setStyleSheet(comboBoxStyleSheet);
    this->ui->cancelRectangle->setStyleSheet(transparentButtonStyleSheet);

    //rounded rectangle initial
    this->ui->roundedRectangleFrame->raise();
    this->ui->roundedRectangleFrame->setVisible(false);
    this->ui->roundedRectangleFrame->setGeometry(670,80,520,500);
    this->ui->roundedRectangleX->setRange(10,1190);
    this->ui->roundedRectangleY->setRange(10,700);
    this->ui->roundedRectangleXRadius->setRange(0,90);
    this->ui->roundedRectangleYRadius->setRange(0,90);
    this->ui->roundedRectangleWidth->setRange(0,1000);
    this->ui->roundedRectangleHeight->setRange(0,500);
    this->ui->roundedRectanglePenWidth->setRange(0,40);
    this->ui->colorRoundedRectangle->addItems(colorList);
    this->ui->brushRoundedRectangle->addItems(colorList);
    this->ui->roundedRectangleX->setValue(100);
    this->ui->roundedRectangleY->setValue(100);
    this->ui->roundedRectangleXRadius->setValue(10);
    this->ui->roundedRectangleYRadius->setValue(10);
    this->ui->roundedRectangleWidth->setValue(100);
    this->ui->roundedRectangleHeight->setValue(100);
    this->ui->roundedRectanglePenWidth->setValue(2);
    this->ui->colorRoundedRectangle->setCurrentIndex(7);
    this->ui->brushRoundedRectangle->setCurrentIndex(7);
    this->ui->brushStyleRoundedRectangle->setCurrentIndex(0);
    this->ui->roundedRectangleFrame->setStyleSheet(frameStyleSheet);
    this->ui->roundedRectangleX->setStyleSheet(spinBoxStyleSheet);
    this->ui->roundedRectangleY->setStyleSheet(spinBoxStyleSheet);
    this->ui->roundedRectangleXRadius->setStyleSheet(spinBoxStyleSheet);
    this->ui->roundedRectangleYRadius->setStyleSheet(spinBoxStyleSheet);
    this->ui->roundedRectangleWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->roundedRectangleHeight->setStyleSheet(spinBoxStyleSheet);
    this->ui->roundedRectanglePenWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->drawRoundedRectangle->setStyleSheet(pushButtonStyleSheet);
    this->ui->roundedRectangleMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->roundedRectangleDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->colorRoundedRectangle->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushRoundedRectangle->setStyleSheet(comboBoxStyleSheet);
    this->ui->brushStyleRoundedRectangle->setStyleSheet(comboBoxStyleSheet);
    this->ui->cancelRoundedRectangle->setStyleSheet(transparentButtonStyleSheet);

    //pixmap initial

    this->ui->pixmapFrame->raise();
    this->ui->pixmapFrame->setVisible(false);
    this->ui->pixmapFrame->setGeometry(670,80,520,500);
    this->ui->pixmapX->setRange(10,1190);
    this->ui->pixmapY->setRange(10,700);
    this->ui->pixmapWidth->setRange(0,1000);
    this->ui->pixmapHeight->setRange(0,500);
    this->ui->pixmapX->setValue(100);
    this->ui->pixmapY->setValue(100);
    this->ui->pixmapWidth->setValue(100);
    this->ui->pixmapHeight->setValue(100);
    this->ui->pixmapFilePath->setText("");
    this->ui->pixmapFilePath->setStyleSheet(textLineStyleSheet);
    this->ui->pixmapFilePathButton->setStyleSheet(pushButtonStyleSheet);
    this->ui->pixmapFrame->setStyleSheet(frameStyleSheet);
    this->ui->pixmapX->setStyleSheet(spinBoxStyleSheet);
    this->ui->pixmapY->setStyleSheet(spinBoxStyleSheet);
    this->ui->pixmapWidth->setStyleSheet(spinBoxStyleSheet);
    this->ui->pixmapHeight->setStyleSheet(spinBoxStyleSheet);
    this->ui->drawPixmap->setStyleSheet(pushButtonStyleSheet);
    this->ui->pixmapMenu->setStyleSheet(shapeMenuButtonStyleSheet);
    this->ui->pixmapDrawingLabel->setStyleSheet(titleLabelStyleSheet);
    this->ui->cancelPixmap->setStyleSheet(transparentButtonStyleSheet);

    //HOme
    QLayout *layout2=new QGridLayout();
    layout2->addWidget(drawingManager);
    //this->ui->centralwidget->setLayout(layout2);

    this->ui->closeButton->setStyleSheet(transparentButtonStyleSheet);

    connect(this->ui->closeButton, &QPushButton::clicked, this, [=]() {
        this->close();
    });

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::brushStyleInitialization()
{
    // Add each brush style to the combo box with proper QVariant conversion
    this->ui->brushStylePolyline->addItem("None", QVariant::fromValue(Qt::NoBrush));
    this->ui->brushStylePolyline->addItem("SolidPattern", QVariant::fromValue(Qt::SolidPattern));
    this->ui->brushStylePolyline->addItem("Dense1Pattern", QVariant::fromValue(Qt::Dense1Pattern));
    this->ui->brushStylePolyline->addItem("Dense2Pattern", QVariant::fromValue(Qt::Dense2Pattern));
    this->ui->brushStylePolyline->addItem("Dense3Pattern", QVariant::fromValue(Qt::Dense3Pattern));
    this->ui->brushStylePolyline->addItem("Dense4Pattern", QVariant::fromValue(Qt::Dense4Pattern));
    this->ui->brushStylePolyline->addItem("Dense5Pattern", QVariant::fromValue(Qt::Dense5Pattern));
    this->ui->brushStylePolyline->addItem("Dense6Pattern", QVariant::fromValue(Qt::Dense6Pattern));
    this->ui->brushStylePolyline->addItem("Dense7Pattern", QVariant::fromValue(Qt::Dense7Pattern));
    this->ui->brushStylePolyline->addItem("HorPattern", QVariant::fromValue(Qt::HorPattern));
    this->ui->brushStylePolyline->addItem("VerPattern", QVariant::fromValue(Qt::VerPattern));
    this->ui->brushStylePolyline->addItem("CrossPattern", QVariant::fromValue(Qt::CrossPattern));
    this->ui->brushStylePolyline->addItem("BDiagPattern", QVariant::fromValue(Qt::BDiagPattern));
    this->ui->brushStylePolyline->addItem("FDiagPattern", QVariant::fromValue(Qt::FDiagPattern));
    this->ui->brushStylePolyline->addItem("DiagCrossPattern", QVariant::fromValue(Qt::DiagCrossPattern));

    this->ui->brushStylePolygon->addItem("None", QVariant::fromValue(Qt::NoBrush));
    this->ui->brushStylePolygon->addItem("SolidPattern", QVariant::fromValue(Qt::SolidPattern));
    this->ui->brushStylePolygon->addItem("Dense1Pattern", QVariant::fromValue(Qt::Dense1Pattern));
    this->ui->brushStylePolygon->addItem("Dense2Pattern", QVariant::fromValue(Qt::Dense2Pattern));
    this->ui->brushStylePolygon->addItem("Dense3Pattern", QVariant::fromValue(Qt::Dense3Pattern));
    this->ui->brushStylePolygon->addItem("Dense4Pattern", QVariant::fromValue(Qt::Dense4Pattern));
    this->ui->brushStylePolygon->addItem("Dense5Pattern", QVariant::fromValue(Qt::Dense5Pattern));
    this->ui->brushStylePolygon->addItem("Dense6Pattern", QVariant::fromValue(Qt::Dense6Pattern));
    this->ui->brushStylePolygon->addItem("Dense7Pattern", QVariant::fromValue(Qt::Dense7Pattern));
    this->ui->brushStylePolygon->addItem("HorPattern", QVariant::fromValue(Qt::HorPattern));
    this->ui->brushStylePolygon->addItem("VerPattern", QVariant::fromValue(Qt::VerPattern));
    this->ui->brushStylePolygon->addItem("CrossPattern", QVariant::fromValue(Qt::CrossPattern));
    this->ui->brushStylePolygon->addItem("BDiagPattern", QVariant::fromValue(Qt::BDiagPattern));
    this->ui->brushStylePolygon->addItem("FDiagPattern", QVariant::fromValue(Qt::FDiagPattern));
    this->ui->brushStylePolygon->addItem("DiagCrossPattern", QVariant::fromValue(Qt::DiagCrossPattern));

    this->ui->brushStyleEllipse->addItem("None", QVariant::fromValue(Qt::NoBrush));
    this->ui->brushStyleEllipse->addItem("SolidPattern", QVariant::fromValue(Qt::SolidPattern));
    this->ui->brushStyleEllipse->addItem("Dense1Pattern", QVariant::fromValue(Qt::Dense1Pattern));
    this->ui->brushStyleEllipse->addItem("Dense2Pattern", QVariant::fromValue(Qt::Dense2Pattern));
    this->ui->brushStyleEllipse->addItem("Dense3Pattern", QVariant::fromValue(Qt::Dense3Pattern));
    this->ui->brushStyleEllipse->addItem("Dense4Pattern", QVariant::fromValue(Qt::Dense4Pattern));
    this->ui->brushStyleEllipse->addItem("Dense5Pattern", QVariant::fromValue(Qt::Dense5Pattern));
    this->ui->brushStyleEllipse->addItem("Dense6Pattern", QVariant::fromValue(Qt::Dense6Pattern));
    this->ui->brushStyleEllipse->addItem("Dense7Pattern", QVariant::fromValue(Qt::Dense7Pattern));
    this->ui->brushStyleEllipse->addItem("HorPattern", QVariant::fromValue(Qt::HorPattern));
    this->ui->brushStyleEllipse->addItem("VerPattern", QVariant::fromValue(Qt::VerPattern));
    this->ui->brushStyleEllipse->addItem("CrossPattern", QVariant::fromValue(Qt::CrossPattern));
    this->ui->brushStyleEllipse->addItem("BDiagPattern", QVariant::fromValue(Qt::BDiagPattern));
    this->ui->brushStyleEllipse->addItem("FDiagPattern", QVariant::fromValue(Qt::FDiagPattern));
    this->ui->brushStyleEllipse->addItem("DiagCrossPattern", QVariant::fromValue(Qt::DiagCrossPattern));

    this->ui->brushStyleRectangle->addItem("None", QVariant::fromValue(Qt::NoBrush));
    this->ui->brushStyleRectangle->addItem("SolidPattern", QVariant::fromValue(Qt::SolidPattern));
    this->ui->brushStyleRectangle->addItem("Dense1Pattern", QVariant::fromValue(Qt::Dense1Pattern));
    this->ui->brushStyleRectangle->addItem("Dense2Pattern", QVariant::fromValue(Qt::Dense2Pattern));
    this->ui->brushStyleRectangle->addItem("Dense3Pattern", QVariant::fromValue(Qt::Dense3Pattern));
    this->ui->brushStyleRectangle->addItem("Dense4Pattern", QVariant::fromValue(Qt::Dense4Pattern));
    this->ui->brushStyleRectangle->addItem("Dense5Pattern", QVariant::fromValue(Qt::Dense5Pattern));
    this->ui->brushStyleRectangle->addItem("Dense6Pattern", QVariant::fromValue(Qt::Dense6Pattern));
    this->ui->brushStyleRectangle->addItem("Dense7Pattern", QVariant::fromValue(Qt::Dense7Pattern));
    this->ui->brushStyleRectangle->addItem("HorPattern", QVariant::fromValue(Qt::HorPattern));
    this->ui->brushStyleRectangle->addItem("VerPattern", QVariant::fromValue(Qt::VerPattern));
    this->ui->brushStyleRectangle->addItem("CrossPattern", QVariant::fromValue(Qt::CrossPattern));
    this->ui->brushStyleRectangle->addItem("BDiagPattern", QVariant::fromValue(Qt::BDiagPattern));
    this->ui->brushStyleRectangle->addItem("FDiagPattern", QVariant::fromValue(Qt::FDiagPattern));
    this->ui->brushStyleRectangle->addItem("DiagCrossPattern", QVariant::fromValue(Qt::DiagCrossPattern));

    this->ui->brushStyleRoundedRectangle->addItem("None", QVariant::fromValue(Qt::NoBrush));
    this->ui->brushStyleRoundedRectangle->addItem("SolidPattern", QVariant::fromValue(Qt::SolidPattern));
    this->ui->brushStyleRoundedRectangle->addItem("Dense1Pattern", QVariant::fromValue(Qt::Dense1Pattern));
    this->ui->brushStyleRoundedRectangle->addItem("Dense2Pattern", QVariant::fromValue(Qt::Dense2Pattern));
    this->ui->brushStyleRoundedRectangle->addItem("Dense3Pattern", QVariant::fromValue(Qt::Dense3Pattern));
    this->ui->brushStyleRoundedRectangle->addItem("Dense4Pattern", QVariant::fromValue(Qt::Dense4Pattern));
    this->ui->brushStyleRoundedRectangle->addItem("Dense5Pattern", QVariant::fromValue(Qt::Dense5Pattern));
    this->ui->brushStyleRoundedRectangle->addItem("Dense6Pattern", QVariant::fromValue(Qt::Dense6Pattern));
    this->ui->brushStyleRoundedRectangle->addItem("Dense7Pattern", QVariant::fromValue(Qt::Dense7Pattern));
    this->ui->brushStyleRoundedRectangle->addItem("HorPattern", QVariant::fromValue(Qt::HorPattern));
    this->ui->brushStyleRoundedRectangle->addItem("VerPattern", QVariant::fromValue(Qt::VerPattern));
    this->ui->brushStyleRoundedRectangle->addItem("CrossPattern", QVariant::fromValue(Qt::CrossPattern));
    this->ui->brushStyleRoundedRectangle->addItem("BDiagPattern", QVariant::fromValue(Qt::BDiagPattern));
    this->ui->brushStyleRoundedRectangle->addItem("FDiagPattern", QVariant::fromValue(Qt::FDiagPattern));
    this->ui->brushStyleRoundedRectangle->addItem("DiagCrossPattern", QVariant::fromValue(Qt::DiagCrossPattern));
}

void MainWindow::frameSetTabOrderInitialization()
{
    //tab settings
}

void MainWindow::closeAllFrame()
{
    if(this->ui->lineFrame->isVisible()) this->ui->lineFrame->setVisible(false);
    if(this->ui->textFrame->isVisible()) this->ui->textFrame->setVisible(false);
    if(this->ui->pointFrame->isVisible()) this->ui->pointFrame->setVisible(false);
    if(this->ui->polylineFrame->isVisible()) this->ui->polylineFrame->setVisible(false);
    if(this->ui->polygonFrame->isVisible()) this->ui->polygonFrame->setVisible(false);
    if(this->ui->arcFrame->isVisible()) this->ui->arcFrame->setVisible(false);
    if(this->ui->ellipseFrame->isVisible()) this->ui->ellipseFrame->setVisible(false);
    if(this->ui->rectangleFrame->isVisible()) this->ui->rectangleFrame->setVisible(false);
    if(this->ui->roundedRectangleFrame->isVisible()) this->ui->roundedRectangleFrame->setVisible(false);
    if(this->ui->pixmapFrame->isVisible()) this->ui->pixmapFrame->setVisible(false);

    //More frame to add
    this->frameOpened=false;
}


void MainWindow::on_drawLine_clicked()
{
    LineShape *line=new LineShape;
    line->setX1(this->ui->x1->value());
    line->setY1(this->ui->y1->value());
    line->setX2(this->ui->x2->value());
    line->setY2(this->ui->y2->value());
    line->setPenColor(QColor(this->ui->colorLine->currentText()));
    line->setPenWidth(this->ui->penWidth->value());
    this->drawingManager->addShape(line);
    this->ui->listWidget->insertItem(0,line->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(line->toString())));
    this->ui->lineFrame->setVisible(false);
    this->ui->x1->setValue(100);
    this->ui->y1->setValue(100);
    this->ui->x2->setValue(200);
    this->ui->y2->setValue(200);
    this->ui->colorLine->setCurrentIndex(7);
    this->ui->penWidth->setValue(2);
}

void MainWindow::on_cancelLine_clicked()
{
    this->ui->lineFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->x1->setValue(100);
    this->ui->y1->setValue(100);
    this->ui->x2->setValue(200);
    this->ui->y2->setValue(200);
    this->ui->colorLine->setCurrentIndex(7);
    this->ui->penWidth->setValue(2);
}

void MainWindow::on_lineMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->lineFrame->setVisible(true);
    this->frameOpened=true;
}
void MainWindow::on_textMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->textFrame->setVisible(true);
    this->frameOpened=true;
}
void MainWindow::on_drawText_clicked()
{
    TextShape *text=new TextShape;
    text->setX(this->ui->textX->value());
    text->setY(this->ui->textY->value());
    text->setPenColor(QColor(this->ui->colorText->currentText()));
    text->setFont(QFont(this->ui->textFont->currentText()));
    text->setPenWidth(this->ui->textPenWidth->value());
    text->setText(this->ui->text->toPlainText());
    text->setPointSize(this->ui->textPointSize->value());
    this->drawingManager->addShape(text);
    this->ui->textFrame->setVisible(false);
    this->ui->listWidget->insertItem(0,text->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(text->toString())));
    this->ui->text->setText("");
    this->ui->textX->setValue(100);
    this->ui->textY->setValue(100);
    this->ui->colorText->setCurrentIndex(7);
    this->ui->textFont->setCurrentIndex(1);
    this->ui->textPenWidth->setValue(2);
    this->ui->textPointSize->setValue(10);
}

void MainWindow::on_cancelText_clicked()
{
    this->ui->textFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->text->setText("");
    this->ui->textX->setValue(100);
    this->ui->textY->setValue(100);
    this->ui->colorText->setCurrentIndex(7);
    this->ui->textFont->setCurrentIndex(1);
    this->ui->textPointSize->setValue(10);
    this->ui->textPenWidth->setValue(2);
}

void MainWindow::on_cancelPoint_clicked()
{
    this->ui->pointFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->pointX->setValue(100);
    this->ui->pointY->setValue(200);
    this->ui->colorPoint->setCurrentIndex(7);
    this->ui->pointPenWidth->setValue(2);
}

void MainWindow::on_drawPoint_clicked()
{
    PointShape *point=new PointShape;
    point->setX(this->ui->pointX->value());
    point->setY(this->ui->pointY->value());
    point->setPenColor(QColor(this->ui->colorPoint->currentText()));
    point->setPenWidth(this->ui->pointPenWidth->value());
    this->drawingManager->addShape(point);
    this->ui->pointFrame->setVisible(false);
    this->ui->listWidget->insertItem(0,point->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(point->toString())));
    this->drawingManager->drawAll();
    this->ui->pointX->setValue(100);
    this->ui->pointY->setValue(200);
    this->ui->colorPoint->setCurrentIndex(7);
    this->ui->pointPenWidth->setValue(2);
}
void MainWindow::on_pointMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->pointFrame->setVisible(true);
    this->frameOpened=true;
}
void MainWindow::on_polylineMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->polylineFrame->setVisible(true);
    this->frameOpened=true;
}

void MainWindow::on_addPointPolyline_clicked()
{
    int columnCount=this->ui->polylinePointTable->columnCount();
    this->ui->polylinePointTable->setColumnCount(columnCount+1);        //First increase ColumnCount then add data
    this->ui->polylinePointTable->setColumnWidth(columnCount,50);
    QTableWidgetItem *item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,this->ui->polylineX->value());
    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    this->ui->polylinePointTable->setItem(0,columnCount,item);
    item=new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    item->setData(Qt::DisplayRole,this->ui->polylineY->value());
    this->ui->polylinePointTable->setItem(1,columnCount,item);
    this->ui->polylineX->setValue(100);
    this->ui->polylineY->setValue(100);
//    int columnCount=this->ui->polylinePointTable->columnCount();
//    this->ui->polylinePointTable->setCellWidget(0,columnCount,new QLabel(QString::number(this->ui->polylineX->value()),this->ui->polylinePointTable));
//    this->ui->polylinePointTable->setCellWidget(1,columnCount,new QLabel(QString::number(this->ui->polylineY->value()),this->ui->polylinePointTable));
//    this->ui->polylinePointTable->setColumnCount(columnCount++);
//    this->ui->polylineX->setValue(100);
//    this->ui->polylineY->setValue(200);
}

void MainWindow::on_drawPolyline_clicked()
{
    if(this->ui->polylinePointTable->columnCount()<3) return ;
    PolylineShape *polyline=new PolylineShape;
    QVector<QPoint> points;
    QTableWidgetItem *item;
    for(int i=0;i<this->ui->polylinePointTable->columnCount();i++)
    {
        int x=(item=this->ui->polylinePointTable->item(0,i))->data(Qt::DisplayRole).toInt();
        delete item;
        int y=(item=this->ui->polylinePointTable->item(1,i))->data(Qt::DisplayRole).toInt();
        delete item;
        points.append(QPoint(x,y));
    }
    polyline->setPoints(points);
    polyline->setPenColor(QColor(this->ui->colorPolyline->currentText()));
    polyline->setPenWidth(this->ui->polylinePenWidth->value());
    QBrush brush(QColor(QColor(this->ui->brushPolyline->currentText())));
    brush.setStyle(this->ui->brushStylePolyline->currentData().value<Qt::BrushStyle>());
    polyline->setBrush(brush);
//    polyline->setBrush(QBrush(QColor(this->ui->brushPolyline->currentText())));
    this->drawingManager->addShape(polyline);
    this->ui->polylineFrame->setVisible(false);
    this->ui->listWidget->insertItem(0,polyline->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(polyline->toString())));
    this->ui->polylineX->setValue(100);
    this->ui->polylineY->setValue(100);
    this->ui->polylinePointTable->setColumnCount(0);
    this->ui->colorPolyline->setCurrentIndex(7);
    this->ui->brushPolyline->setCurrentIndex(7);
    this->ui->brushStylePolyline->setCurrentIndex(0);
    this->ui->polylinePenWidth->setValue(2);
}

void MainWindow::on_cancelPolyline_clicked()
{
    this->ui->polylineFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->polylineX->setValue(100);
    this->ui->polylineY->setValue(100);
    this->ui->polylinePointTable->setColumnCount(0);
    this->ui->colorPolyline->setCurrentIndex(7);
    this->ui->brushPolyline->setCurrentIndex(7);
    this->ui->brushStylePolyline->setCurrentIndex(0);
    this->ui->polylinePenWidth->setValue(2);
}
void MainWindow::on_addPointPolygon_clicked()
{
    int columnCount=this->ui->polygonPointTable->columnCount();
    this->ui->polygonPointTable->setColumnCount(columnCount+1);        //First increase ColumnCount then add data
    this->ui->polygonPointTable->setColumnWidth(columnCount,50);
    QTableWidgetItem *item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole,this->ui->polygonX->value());
    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    this->ui->polygonPointTable->setItem(0,columnCount,item);
    item=new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    item->setData(Qt::DisplayRole,this->ui->polygonY->value());
    this->ui->polygonPointTable->setItem(1,columnCount,item);
    this->ui->polygonX->setValue(100);
    this->ui->polygonY->setValue(100);
}

void MainWindow::on_cancelPolygon_clicked()
{
    this->ui->polygonFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->polygonX->setValue(100);
    this->ui->polygonY->setValue(100);
    this->ui->polygonPointTable->setColumnCount(0);
    this->ui->colorPolygon->setCurrentIndex(7);
    this->ui->brushPolygon->setCurrentIndex(7);
    this->ui->brushStylePolygon->setCurrentIndex(0);
    this->ui->polygonPenWidth->setValue(2);
}

void MainWindow::on_drawPolygon_clicked()
{
    if(this->ui->polygonPointTable->columnCount()<3) return ;
    PolygonShape *polygon=new PolygonShape();
    QVector<QPoint> points;
    QTableWidgetItem *item;
    for(int i=0;i<this->ui->polygonPointTable->columnCount();i++)
    {
        int x=(item=this->ui->polygonPointTable->item(0,i))->data(Qt::DisplayRole).toInt();
        delete item;
        int y=(item=this->ui->polygonPointTable->item(1,i))->data(Qt::DisplayRole).toInt();
        delete item;
        points.append(QPoint(x,y));
    }
    polygon->setPoints(points);
    polygon->setPenColor(QColor(this->ui->colorPolygon->currentText()));
    polygon->setPenWidth(this->ui->polygonPenWidth->value());
    QBrush brush(QColor(this->ui->brushPolygon->currentText()));
    brush.setStyle(this->ui->brushStylePolygon->currentData().value<Qt::BrushStyle>());
    polygon->setBrush(brush);
//    polygon->setBrush(QBrush(QColor(this->ui->brushpolygon->currentText())));
    this->drawingManager->addShape(polygon);
    this->ui->polygonFrame->setVisible(false);
    this->ui->listWidget->insertItem(0,polygon->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(polygon->toString())));
    this->ui->polygonX->setValue(100);
    this->ui->polygonY->setValue(100);
    this->ui->polygonPointTable->setColumnCount(0);
    this->ui->colorPolygon->setCurrentIndex(7);
    this->ui->brushPolygon->setCurrentIndex(7);
    this->ui->brushStylePolygon->setCurrentIndex(0);
    this->ui->polygonPenWidth->setValue(2);
}

void MainWindow::on_polygonMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->polygonFrame->setVisible(true);
    this->frameOpened=true;
}

void MainWindow::on_arcMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->arcFrame->setVisible(true);
    this->frameOpened=true;
}

void MainWindow::on_cancelArc_clicked()
{
    this->ui->arcFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->arcX->setValue(100);
    this->ui->arcY->setValue(100);
    this->ui->arcWidth->setValue(100);
    this->ui->arcHeight->setValue(100);
    this->ui->arcStartingAngle->setValue(30);
    this->ui->arcSpanAngle->setValue(30);
    this->ui->arcPenWidth->setValue(2);    //intial value
    this->ui->colorArc->setCurrentIndex(7);
}

void MainWindow::on_drawArc_clicked()
{
    ArcShape *arc=new ArcShape;
    arc->setX(this->ui->arcX->value());
    arc->setY(this->ui->arcY->value());
    arc->setWidth(this->ui->arcWidth->value());
    arc->setHeight(this->ui->arcHeight->value());
    arc->setStartAngle(this->ui->arcStartingAngle->value());
    arc->setSpanAngle(this->ui->arcSpanAngle->value());
    arc->setPenColor(QColor(this->ui->colorArc->currentText()));
    arc->setPenWidth(this->ui->arcPenWidth->value());
    this->drawingManager->addShape(arc);
    this->ui->arcFrame->setVisible(false);
    this->ui->listWidget->insertItem(0,arc->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(arc->toString())));
    this->ui->arcX->setValue(100);
    this->ui->arcY->setValue(100);
    this->ui->arcWidth->setValue(100);
    this->ui->arcHeight->setValue(100);
    this->ui->arcStartingAngle->setValue(30);
    this->ui->arcSpanAngle->setValue(30);
    this->ui->colorArc->setCurrentIndex(7);
    this->ui->arcPenWidth->setValue(2);
}
void MainWindow::on_ellipseIsCenter_stateChanged(int arg1)
{
    if(!arg1)
    {
        this->ui->ellipsePoint->setVisible(true);
        this->ui->ellipseCenter->setVisible(false);
    }
    else
    {
        this->ui->ellipsePoint->setVisible(false);
        this->ui->ellipseCenter->setVisible(true);
    }
}

void MainWindow::on_ellipseMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->ellipseFrame->setVisible(true);
    this->frameOpened=true;
}

void MainWindow::on_drawEllipse_clicked()
{
    EllipseShape *ellipse=new EllipseShape();
    ellipse->setIsCenter(this->ui->ellipseIsCenter->isChecked());
    ellipse->setX(this->ui->ellipseX->value());
    ellipse->setY(this->ui->ellipseY->value());
    ellipse->setHorizontalRadius(this->ui->ellipseHR->value());
    ellipse->setVerticalRadius(this->ui->ellipseVR->value());
    ellipse->setPenColor(QColor(this->ui->colorEllipse->currentText()));
    ellipse->setPenWidth(this->ui->ellipsePenWidth->value());
    QBrush brush(QColor(this->ui->brushEllipse->currentText()));
    brush.setStyle(this->ui->brushStyleEllipse->currentData().value<Qt::BrushStyle>());
    ellipse->setBrush(brush);
//    ellipse->setBrush(QBrush(QColor(this->ui->brushEllipse->currentText())));
    this->drawingManager->addShape(ellipse);
    this->ui->ellipseFrame->setVisible(false);
    this->ui->listWidget->insertItem(0,ellipse->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(ellipse->toString())));
    this->ui->ellipseX->setValue(100);
    this->ui->ellipseY->setValue(100);
    this->ui->ellipseVR->setValue(100);
    this->ui->ellipseHR->setValue(100);
    this->ui->ellipseIsCenter->setCheckState(Qt::CheckState::Unchecked);
    this->ui->colorEllipse->setCurrentIndex(7);
    this->ui->brushEllipse->setCurrentIndex(7);
    this->ui->brushStyleEllipse->setCurrentIndex(0);
    this->ui->ellipsePenWidth->setValue(2);
}

void MainWindow::on_cancelEllipse_clicked()
{
    this->ui->ellipseFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->ellipseVR->setValue(100);
    this->ui->ellipseHR->setValue(100);
    this->ui->ellipseIsCenter->setCheckState(Qt::CheckState::Unchecked);
    this->ui->ellipseX->setValue(100);
    this->ui->ellipseY->setValue(100);
    this->ui->colorEllipse->setCurrentIndex(7);
    this->ui->brushEllipse->setCurrentIndex(7);
    this->ui->brushStyleEllipse->setCurrentIndex(0);
    this->ui->ellipsePenWidth->setValue(2);
}

void MainWindow::on_cancelRectangle_clicked()
{
    this->ui->rectangleFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->rectangleX->setValue(100);
    this->ui->rectangleY->setValue(100);
    this->ui->rectangleWidth->setValue(100);
    this->ui->rectangleHeight->setValue(100);
    this->ui->rectanglePenWidth->setValue(2);
    this->ui->colorRectangle->setCurrentIndex(7);
    this->ui->brushEllipse->setCurrentIndex(7);
    this->ui->brushStyleEllipse->setCurrentIndex(0);
}

void MainWindow::on_drawRectangle_clicked()
{
    RectangleShape *rectangle=new RectangleShape();
    rectangle->setX(this->ui->rectangleX->value());
    rectangle->setY(this->ui->rectangleY->value());
    rectangle->setWidth(this->ui->rectangleWidth->value());
    rectangle->setHeight(this->ui->rectangleHeight->value());
    rectangle->setPenColor(QColor(this->ui->colorRectangle->currentText()));
    rectangle->setPenWidth(this->ui->rectanglePenWidth->value());
    QBrush brush(QColor(this->ui->brushRectangle->currentText()));
    brush.setStyle(this->ui->brushStyleRectangle->currentData().value<Qt::BrushStyle>());
    rectangle->setBrush(brush);
//    rectangle->setBrush(QBrush(QColor(this->ui->brushRectangle->currentText())));
    this->drawingManager->addShape(rectangle);
    this->ui->rectangleFrame->setVisible(false);
    this->ui->listWidget->insertItem(0,rectangle->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(rectangle->toString())));
    this->ui->rectangleX->setValue(100);
    this->ui->rectangleY->setValue(100);
    this->ui->rectangleWidth->setValue(100);
    this->ui->rectangleHeight->setValue(100);
    this->ui->colorRectangle->setCurrentIndex(7);
    this->ui->brushRectangle->setCurrentIndex(7);
    this->ui->brushStyleRectangle->setCurrentIndex(0);
    this->ui->rectanglePenWidth->setValue(2);
}

void MainWindow::on_rectangleMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->rectangleFrame->setVisible(true);
    this->frameOpened=true;
}

void MainWindow::on_drawRoundedRectangle_clicked()
{
    RoundedRectangleShape *roundedRectangle=new RoundedRectangleShape();
    roundedRectangle->setX(this->ui->roundedRectangleX->value());
    roundedRectangle->setY(this->ui->roundedRectangleY->value());
    roundedRectangle->setXRadius(this->ui->roundedRectangleXRadius->value());
    roundedRectangle->setYRadius(this->ui->roundedRectangleYRadius->value());
    roundedRectangle->setWidth(this->ui->roundedRectangleWidth->value());
    roundedRectangle->setHeight(this->ui->roundedRectangleHeight->value());
    roundedRectangle->setPenColor(QColor(this->ui->colorRoundedRectangle->currentText()));
    roundedRectangle->setPenWidth(this->ui->roundedRectanglePenWidth->value());
    QBrush brush(QColor(this->ui->brushRoundedRectangle->currentText()));
    brush.setStyle(this->ui->brushStyleRoundedRectangle->currentData().value<Qt::BrushStyle>());
    roundedRectangle->setBrush(brush);
//    roundedRectangle->setBrush(QBrush(QColor(this->ui->brushRoundedRectangle->currentText())));
    this->drawingManager->addShape(roundedRectangle);
    this->ui->roundedRectangleFrame->setVisible(false);
    this->ui->listWidget->insertItem(0,roundedRectangle->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(roundedRectangle->toString())));
    this->ui->roundedRectangleX->setValue(100);
    this->ui->roundedRectangleY->setValue(100);
    this->ui->roundedRectangleXRadius->setValue(10);
    this->ui->roundedRectangleYRadius->setValue(10);
    this->ui->roundedRectangleWidth->setValue(100);
    this->ui->roundedRectangleHeight->setValue(100);
    this->ui->roundedRectanglePenWidth->setValue(2);
    this->ui->colorRoundedRectangle->setCurrentIndex(7);
    this->ui->brushRoundedRectangle->setCurrentIndex(7);
    this->ui->brushStyleRoundedRectangle->setCurrentIndex(0);
}
void MainWindow::on_cancelRoundedRectangle_clicked()
{
    this->ui->roundedRectangleFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->roundedRectangleX->setValue(100);
    this->ui->roundedRectangleY->setValue(100);
    this->ui->roundedRectangleXRadius->setValue(10);
    this->ui->roundedRectangleYRadius->setValue(10);
    this->ui->roundedRectangleWidth->setValue(100);
    this->ui->roundedRectangleHeight->setValue(100);
    this->ui->roundedRectanglePenWidth->setValue(2);
    this->ui->colorRoundedRectangle->setCurrentIndex(7);
    this->ui->brushRoundedRectangle->setCurrentIndex(7);
    this->ui->brushStyleRoundedRectangle->setCurrentIndex(0);
}

void MainWindow::on_roundedRectangleMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->roundedRectangleFrame->setVisible(true);
    this->frameOpened=true;
}

void MainWindow::on_pixmapFilePathButton_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,tr("Open Image"),"Downloads","Images (*.jpg *.png)");
    if(filePath.compare("")==1)
    {
//        printf("%s\n",filePath.toStdString().c_str());

    this->ui->pixmapFilePath->setText(filePath);
    }
//    else
//    {
//    this->ui->pixmapFilePath->setText("image.png");
//    }
}

void MainWindow::on_drawPixmap_clicked()
{
    if(this->ui->pixmapFilePath->text().compare("")==0) return ;
    QPixmap image(this->ui->pixmapFilePath->text());
    if(image.isNull())
    {
        return;
    }
    PixmapShape *pixmap=new PixmapShape();
    pixmap->setX(this->ui->pixmapX->value());
    pixmap->setY(this->ui->pixmapY->value());
    pixmap->setWidth(this->ui->pixmapWidth->value());
    pixmap->setHeight(this->ui->pixmapHeight->value());
    pixmap->setPixmap(image);
    this->drawingManager->addShape(pixmap);
    this->ui->pixmapFrame->setVisible(false);
    this->ui->listWidget->insertItem(0,pixmap->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(pixmap->toString())));
    this->ui->pixmapX->setValue(100);
    this->ui->pixmapY->setValue(100);
    this->ui->pixmapWidth->setValue(100);
    this->ui->pixmapHeight->setValue(100);
    this->ui->pixmapFilePath->setText("");
}
void MainWindow::on_cancelPixmap_clicked()
{
    this->ui->pixmapFrame->setVisible(false);
    this->drawingManager->drawAll();
    this->ui->pixmapX->setValue(100);
    this->ui->pixmapY->setValue(100);
    this->ui->pixmapWidth->setValue(100);
    this->ui->pixmapHeight->setValue(100);
    this->ui->pixmapFilePath->setText("");
}
void MainWindow::on_pixmapMenu_clicked()
{
    if(this->frameOpened==true) closeAllFrame();
    //this->drawingManager->clearCanvas();
    this->ui->pixmapFrame->setVisible(true);
    this->frameOpened=true;
}
void MainWindow::on_pixmapFilePath_textChanged(const QString &arg1)
{
    QPixmap image(arg1);
    if(image.isNull())
    {
        this->ui->pixmapFilePath->setStyleSheet("color: red;");
    }
    else
    {
        this->ui->pixmapFilePath->setStyleSheet("color: green;");
    }
}

void MainWindow::on_loginButton_clicked()
{
    QString str=this->ui->username->styleSheet();
    if(str.compare("color: green;",Qt::CaseSensitive)==0)
    {
    this->ui->homeFrame->setVisible(false);
    //this->ui->homeFrame->hide();
    this->ui->homeUserFrame->setVisible(false);
    //this->ui->homeUserFrame->hide();
    this->ui->drawing->setVisible(true);
    this->ui->menuFrame->setVisible(true);
    this->ui->usernameLabel->setText(this->ui->username->text());
    this->ui->usernameLabel->setVisible(true);
    this->ui->userIcon->setVisible(true);
    this->ui->actionTree_View->setEnabled(true);
    this->ui->actionList_View->setEnabled(true);
    this->ui->actionTree_View->setCheckable(true);
    this->ui->actionList_View->setCheckable(true);
    }
}

void MainWindow::on_homeMenu_clicked()
{
    this->ui->homeFrame->setVisible(true);
    //this->ui->homeFrame->hide();
    this->ui->homeUserFrame->setVisible(true);
    //this->ui->homeUserFrame->hide();
    if(this->frameOpened) closeAllFrame();
//    printf("Count: %d\n",this->ui->listWidget->count());
    while(this->ui->listWidget->count()>0)
    {
        QListWidgetItem *item=this->ui->listWidget->takeItem(0);
        QString data=item->text();
//        printf("Data: %s\n",data.toStdString().c_str());
        this->drawingManager->removeShape(data);
    }
    this->ui->listWidget->clear();
    this->ui->treeWidget->clear();

    this->ui->drawing->setVisible(false);
    this->ui->menuFrame->setVisible(false);
    this->ui->usernameLabel->setText("");
    this->ui->username->setText("");
    this->ui->usernameLabel->setVisible(false);
    this->ui->userIcon->setVisible(false);
    this->ui->actionTree_View->setCheckable(false);
    this->ui->actionList_View->setCheckable(false);
    this->ui->actionTree_View->setEnabled(false);
    this->ui->actionList_View->setEnabled(false);
}

void MainWindow::on_username_textChanged(const QString &arg1)
{
    QString restrictedCharacter="!@#$%^&*(){}/.'?,<>;+-_=~`\"\\";
    int size=arg1.size();
    if(size<=3 || size>=10)
    {
        if(size==0)   this->ui->username->setStyleSheet("color: black;");
        else this->ui->username->setStyleSheet("color: red;");
    }
    else
    {
        int i;
        for(i=0;i<size;i++)
        {
            if(restrictedCharacter.contains(arg1[i],Qt::CaseSensitive)) break;
        }
        if(i==size) this->ui->username->setStyleSheet("color: green;");
        else this->ui->username->setStyleSheet("color: red;");
    }
}

void MainWindow::on_exit_triggered()
{
    this->close();
}
void MainWindow::on_actionList_View_triggered()
{
    if(this->ui->actionList_View->isChecked()) this->ui->actionList_View->setChecked(true);
    else this->ui->actionList_View->setChecked(false);
    this->ui->actionTree_View->setChecked(false);
}

void MainWindow::on_listWidgetClose_clicked()
{
    this->ui->actionList_View->setChecked(false);
}
void MainWindow::on_treeWidgetClose_clicked()
{
    this->ui->actionTree_View->setChecked(false);
}
void MainWindow::on_actionList_View_changed()
{
    if(this->ui->actionList_View->isChecked())
    {
        this->ui->listWidget->setVisible(true);
        this->ui->listWidgetClose->setVisible(true);
    }
    else
    {
        this->ui->listWidget->setVisible(false);
        this->ui->listWidgetClose->setVisible(false);
    }
}

void MainWindow::on_actionTree_View_triggered()
{
    if(this->ui->actionTree_View->isChecked()) this->ui->actionTree_View->setChecked(true);
    else this->ui->actionTree_View->setChecked(false);
    this->ui->actionList_View->setChecked(false);
}

void MainWindow::on_actionTree_View_changed()
{
    if(this->ui->actionTree_View->isChecked())
    {
        this->ui->treeWidget->setVisible(true);
        this->ui->treeWidgetClose->setVisible(true);
    }
    else
    {
        this->ui->treeWidget->setVisible(false);
        this->ui->treeWidgetClose->setVisible(false);
    }
}

void MainWindow::on_changePhaseII_clicked()
{
    this->ui->phaseIII->setVisible(false);
    this->ui->phaseII->setVisible(true);
    this->ui->menubar->setVisible(true);

//    //Removing all data from listWidget + drawingmanager
//        while(this->ui->listWidget->count()>0)
//        {
//            QListWidgetItem *item=this->ui->listWidget->takeItem(0);
//            QString data=item->text();
//    //        printf("Data: %s\n",data.toStdString().c_str());
//            this->model->removeShape(data);
//        }
//        this->ui->listWidget->clear();
//        this->ui->treeWidget->clear();

}

void MainWindow::on_changePhaseIII_clicked()    //Some code to change donedone
{
    this->ui->phaseIII->setVisible(true);
    this->ui->phaseII->setVisible(false);
    this->ui->menubar->setVisible(false);
/*
    //Removing all data from listWidget + drawingmanager
    while(this->ui->listWidget->count()>0)
    {
        QListWidgetItem *item=this->ui->listWidget->takeItem(0);
        QString data=item->text();
//        printf("Data: %s\n",data.toStdString().c_str());
        this->drawingManager->removeShape(data);
    }
    this->ui->listWidget->clear();
    this->ui->treeWidget->clear();*/

}

void MainWindow::on_freeHandDraw_clicked()
{
    FreeHandShape *freeHandShape=new FreeHandShape();
    this->model->addShape(freeHandShape);
    this->ui->listWidget->insertItem(0,freeHandShape->toString());
    this->ui->treeWidget->insertTopLevelItem(0,new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(freeHandShape->toString())));
}
