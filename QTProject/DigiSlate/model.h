#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include <QList>
#include "drawing.h"
#include<QHash>
#include<QMouseEvent>
class Model : public QWidget {
    Q_OBJECT

public:
    explicit Model(QWidget *parent = nullptr);
    ~Model();

    void addShape(Drawing *shape);  // Add shape and trigger redraw
    void removeShape(const QString &shape);
    void clearCanvas();                  // Clear canvas (painted shapes)
    void drawAll();
    QList<QString> getAllShapes();
    void processClicked(const QPoint &point);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QList<Drawing*> shapes;
    QHash<QString,Drawing*> viewMap;
    bool mousePressed;
};

#endif // MODEL_H
