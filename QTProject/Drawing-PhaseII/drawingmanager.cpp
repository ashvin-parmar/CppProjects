#include "drawingmanager.h"
#include <QPainter>
#include <QDebug>
#include<iostream>
using namespace std;

DrawingManager* DrawingManager::instance = nullptr;
DrawingManager::DrawingManager(QWidget *parent) : QWidget(parent)
{

}
DrawingManager* DrawingManager::getInstance(QWidget *parent) {
    if (instance==nullptr) {
        instance = new DrawingManager(parent);
//        printf("Instance created\n");
    }
    return instance;
}


DrawingManager::~DrawingManager() {
    qDeleteAll(shapes);
}

void DrawingManager::addShape(Drawing *drawing) {
    if (drawing) {
        shapes.append(drawing);
        cout<<drawing->toString().toStdString().c_str();
        viewMap.insert(drawing->toString().toUpper(),drawing);
        update();  // Redraw the canvas
    }
}
void DrawingManager::removeShape(const QString &shape)
{
    Drawing *drawing=viewMap[shape.toUpper()];
    printf("Shape: %s\n",shape.toStdString().c_str());
    if(drawing==nullptr)
    {
        return ;
    }
    else
    {
        this->shapes.removeOne(drawing);
        this->viewMap.remove(shape.toUpper());
    }
}
QList<QString> DrawingManager::getAllShapes()
{
    return this->viewMap.keys();
}
void DrawingManager::clearCanvas() {
    QList<Drawing*> cloneShape=shapes;
    printf("Shpae size: %d\n",shapes.size());
    shapes.clear();
    printf("Shpae size: %d\n",shapes.size());
    update();
      // Triggers a repaint, effectively clearing the widget
    shapes=cloneShape;
}
void DrawingManager::drawAll()
{
    update();
}
void DrawingManager::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setClipRect(5,5,1165,680);
    painter.eraseRect(5,5,1165,680);
    cout<<"Painting got called size: "<<shapes.size()<<endl;
    for (Drawing *shape : shapes) {
        shape->draw(painter);  // Call each shape’s draw method
    }
}
