#ifndef FREEHANDSHAPE_H
#define FREEHANDSHAPE_H

#include <QObject>
#include<drawing.h>

class FreeHandShape : public Drawing
{
    Q_OBJECT
public:
    explicit FreeHandShape(QObject *parent=nullptr);
    ~FreeHandShape();

    void draw(QPainter &painter) override;
    void clear() override;
    QString toString() override;
    void select() override;
    bool isPointInShapeRegion(const QPoint &point) override;

    void addPoint(const QPoint &point);
    void pathSize() const;

private:
    QPolygon drawPath;
};

#endif // FREEHANDSHAPE_H
