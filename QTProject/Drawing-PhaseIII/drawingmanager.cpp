#include "drawingmanager.h"
#include <QPainter>
#include <QDebug>
#include<iostream>
#include<shapes_header/freehandshape.h>
using namespace std;

DrawingManager* DrawingManager::instance = nullptr;
DrawingManager::DrawingManager(QWidget *parent) : QWidget(parent)
{

}
DrawingManager* DrawingManager::getInstance(QWidget *parent) {
    if (instance==nullptr || parent==nullptr)
    {
        instance = new DrawingManager(parent);
//        printf("Instance created\n");
    }
    return instance;
}


DrawingManager::~DrawingManager()
{
    if(!instance)
    {
        qDeleteAll(shapes);
        instance=NULL;
    }
}

void DrawingManager::addShape(Drawing *drawing)
{
    if (drawing) {
        shapes.append(drawing);
//        cout<<drawing->toString().toStdString().c_str();
        viewMap.insert(drawing->toString().toUpper(),drawing);
        update();  // Redraw the canvas
    }
}
void DrawingManager::removeShape(const QString &shape)
{
    Drawing *drawing=viewMap[shape.toUpper()];
//    printf("Shape: %s\n",shape.toStdString().c_str());
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
//    printf("Shpae size: %d\n",shapes.size());
    shapes.clear();
//    printf("Shpae size: %d\n",shapes.size());
    update();
      // Triggers a repaint, effectively clearing the widget
    shapes=cloneShape;
}
void DrawingManager::drawAll()
{
    update();
}
void DrawingManager::processClicked(const QPoint &point)
{
    for (Drawing *shape : shapes)
    {                               //replica of instanceof function in c++
        FreeHandShape *freeHandShape=dynamic_cast<FreeHandShape *>(shape);
        if(freeHandShape==nullptr)
        {
            if(shape->isPointInShapeRegion(point))
                    {
                        shape->select();
                    }
        }
        else
        {
            if(this->mousePressed)
            {
                freeHandShape->addPoint(point);
            }
        }
    }
}
void DrawingManager::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect rect=this->rect();
    rect.setX(rect.x()-10);
    rect.setY(rect.x()-10);
    rect.setWidth(rect.width()-5);
    rect.setWidth(rect.height()-5);
    painter.setClipRect(this->rect());
//    painter.eraseRect(this->rect());
//    cout<<"Painting got called size: "<<shapes.size()<<endl;
    for (Drawing *shape : shapes) {
        shape->draw(painter);  // Call each shape’s draw method
    }
}
void DrawingManager::mousePressEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    this->mousePressed=true;
    this->processClicked(point);
}
void DrawingManager::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    this->processClicked(point);
    this->mousePressed=false;
}
void DrawingManager::mouseMoveEvent(QMouseEvent *event)
{
    if(!mousePressed) return;
    QPoint point=event->pos();
    this->processClicked(point);
}
