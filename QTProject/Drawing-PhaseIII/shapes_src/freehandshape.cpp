#include "shapes_header/freehandshape.h"

FreeHandShape::FreeHandShape(QObject *parent):Drawing(parent)
{

}
FreeHandShape::~FreeHandShape()
{

}
void FreeHandShape::draw(QPainter &painter)
{
    painter.setPen(QPen(Qt::red,4));
    painter.drawPoints(drawPath);
}
void FreeHandShape::clear()
{

}
QString FreeHandShape::toString()
{
 return "FreeHand";
}
void FreeHandShape::select()
{

}
bool FreeHandShape::isPointInShapeRegion(const QPoint &point)
{
return false;
}
void FreeHandShape::addPoint(const QPoint &point)
{
    this->drawPath.append(point);
}
void FreeHandShape::pathSize() const
{

}
