#include "shapes_header/pixmapshape.h"
int PixmapShape::count=1;
PixmapShape::PixmapShape(QObject *parent):Drawing(parent)
{
    this->x=100;
    this->y=100;
    this->width=100;
    this->height=100;
    number=count++;
}
PixmapShape::~PixmapShape()
{

}
void PixmapShape::draw(QPainter &painter)
{
    pixmap.scaled(width,height,Qt::AspectRatioMode::KeepAspectRatio,Qt::TransformationMode::SmoothTransformation);
    painter.drawPixmap(x,y,width,height,pixmap);
}
void PixmapShape::clear()
{

}
QString PixmapShape::toString()
{
    return QString("Image")+QString::number(number);
}
void PixmapShape::select(QPainter &painter)
{
    QVector<QPoint> points;
    points.append(QPoint(x,y));
    points.append(QPoint(x+width,y));
    points.append(QPoint(x,y+height));
    points.append(QPoint(x+width,y+height));
    painter.drawPoints(points);
}
bool PixmapShape::isPointInShapeRegion(const QPoint &point)
{
    int pointX,pointY;
    pointX=point.x();
    pointY=point.y();
    if((pointX>=x && pointY>=y) && (pointX<=(x+width) && pointY<=(y+height))) return true;
    return false;
}
void PixmapShape::moveShape(const QPointF &diffPoint)
{
    this->x+=diffPoint.x();
    this->y+=diffPoint.y();
}
int PixmapShape::getX() const
{
    return x;
}

void PixmapShape::setX(int value)
{
    x = value;
}

int PixmapShape::getY() const
{
    return y;
}

void PixmapShape::setY(int value)
{
    y = value;
}

int PixmapShape::getWidth() const
{
    return width;
}

void PixmapShape::setWidth(int value)
{
    width = value;
}

int PixmapShape::getHeight() const
{
    return height;
}

void PixmapShape::setHeight(int value)
{
    height = value;
}

double PixmapShape::getScaleFactor() const
{
    return scaleFactor;
}

void PixmapShape::setScaleFactor(double value)
{
    scaleFactor = value;
}

qreal PixmapShape::getRotationAngle() const
{
    return rotationAngle;
}

void PixmapShape::setRotationAngle(const qreal &value)
{
    rotationAngle = value;
}

Qt::TransformationMode PixmapShape::getTransformationMode() const
{
    return transformationMode;
}

void PixmapShape::setTransformationMode(const Qt::TransformationMode &value)
{
    transformationMode = value;
}

QPixmap PixmapShape::getPixmap() const
{
    return pixmap;
}

void PixmapShape::setPixmap(const QPixmap &value)
{
    pixmap = value;
}
