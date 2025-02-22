#include "model.h"
#include <QPainter>
#include <QDebug>
#include<iostream>
#include<shapes_header/freehandshape.h>
using namespace std;

Model::Model(QWidget *parent) : QWidget(parent)
{

}
Model::~Model()
{
        qDeleteAll(shapes);
}

void Model::addShape(Drawing *drawing)
{
    if (drawing) {
        shapes.append(drawing);
//        cout<<drawing->toString().toStdString().c_str();
        viewMap.insert(drawing->toString().toUpper(),drawing);
        update();  // Redraw the canvas
    }
}
void Model::removeShape(const QString &shape)
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
QList<QString> Model::getAllShapes()
{
    return this->viewMap.keys();
}
void Model::clearCanvas() {
    QList<Drawing*> cloneShape=shapes;
//    printf("Shpae size: %d\n",shapes.size());
    shapes.clear();
//    printf("Shpae size: %d\n",shapes.size());
    update();
      // Triggers a repaint, effectively clearing the widget
    shapes=cloneShape;
}
void Model::drawAll()
{
    update();
}
void Model::processClicked(const QPoint &point)
{
    for (Drawing *shape : shapes)
    {                               //replica of instanceof function in c++
//        FreeHandShape *freeHandShape=dynamic_cast<FreeHandShape *>(shape);
//        if(freeHandShape==nullptr)
//        {
            if(shape->isPointInShapeRegion(point))
                    {
                        shape->select();
                    }
//        }
//        else
//        {
//            if(this->mousePressed)
//            {
//                freeHandShape->addPoint(point);
//            }
//        }
    }
    update();
}
void Model::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect rect=this->rect();
    painter.setClipRect(0,0,rect.width(),rect.height());
    painter.eraseRect(0,0,rect.width(),rect.height());
    cout<<"Painting got called size: "<<shapes.size()<<endl;
    for (Drawing *shape : shapes) {
        shape->draw(painter);  // Call each shape’s draw method
    }
}
void Model::mousePressEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    this->mousePressed=true;
    this->processClicked(point);
}
void Model::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    this->processClicked(point);
    this->mousePressed=false;
}
void Model::mouseMoveEvent(QMouseEvent *event)
{
    if(!mousePressed) return;
    QPoint point=event->pos();
    this->processClicked(point);
}
