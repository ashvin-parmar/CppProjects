#ifndef DRAWINGMANAGER_H
#define DRAWINGMANAGER_H

#include <QWidget>
#include <QList>
#include "drawing.h"
#include<QHash>

class DrawingManager : public QWidget {
    Q_OBJECT

public:
    static DrawingManager* getInstance(QWidget *parent);  // Singleton pattern
    ~DrawingManager();

    void addShape(Drawing *shape);  // Add shape and trigger redraw
    void removeShape(const QString &shape);
    void clearCanvas();                  // Clear canvas (painted shapes)
    void drawAll();
    QList<QString> getAllShapes();
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    explicit DrawingManager(QWidget *parent = nullptr);
    static DrawingManager *instance;
    QList<Drawing*> shapes;
    QHash<QString,Drawing*> viewMap;
};

#endif // DRAWINGMANAGER_H
