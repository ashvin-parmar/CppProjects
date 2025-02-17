#ifndef DRAWING_H
#define DRAWING_H

#include <QPainter>
#include <QFrame>
#include <QObject>

class Drawing : public QObject
{
    Q_OBJECT
public:
    explicit Drawing(QObject *parent = nullptr):QObject(parent) {}
    virtual ~Drawing() {}

    virtual void draw(QPainter &painter) = 0;   // Must be implemented in derived classes
    virtual void clear() = 0;                   // Clears the shape
    virtual QString toString()=0;
};

#endif // DRAWING_H
